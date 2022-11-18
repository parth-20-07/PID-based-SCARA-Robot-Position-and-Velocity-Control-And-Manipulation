#include "custom_interfaces/srv/find_joint_states.hpp"
#include "rclcpp/rclcpp.hpp"
#include <bits/stdc++.h>
#include <math.h>
#include <memory>

void add(const std::shared_ptr<custom_interfaces::srv::FindJointStates::Request> request, std::shared_ptr<custom_interfaces::srv::FindJointStates::Response> response)
{
    std::double_t x = round(request->x * 100) / 100; // x component of the end effector pose
    std::double_t y = round(request->y * 100) / 100; // y component of the end effector pose
    std::double_t z = round(request->z * 100) / 100; // z component of the end effector pose
    bool solution_possible = true;
    if (std::sqrt((x * x) + (y * y)) > 2)
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "XY Values out of Bound");
        solution_possible = false;
    }
    if (x == 0 && y == 0)
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "XY Values not reachable. Detected Singularity");
        solution_possible = false;
    }
    if (z > 2.1 || z < 0)
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Z Value out of Bound");
        solution_possible = false;
    }
    if (!solution_possible)
        return;

    std::double_t lb = 2;   // length of the base of the robot
    std::double_t l1 = 0.9; // length of first link
    std::double_t l2 = 1;   // length of second link
    std::double_t l3 = 2.2; // length of third link

    std::double_t q1_1, q1_2, q2_1, q2_2;
    std::double_t q3 = lb + 0.1 - z; // prismatic joint displacement

    double cos_of_q2 = (pow(x, 2) + pow(y, 2) - pow(l1, 2) - pow(l2, 2)) / (2 * l1 * l2);
    auto get_q2 = [=](bool is_positive, double cos_of_q2)
    { return atan2((is_positive ? 1 : -1) * sqrt(1 - pow(cos_of_q2, 2)), cos_of_q2); };
    q2_1 = get_q2(true, cos_of_q2);
    q2_2 = get_q2(false, cos_of_q2);
    auto get_q1 = [=](double q2)
    { return atan2(y, x) - atan2(l2 * sin(q2), l1 + (l2 * cos(q2))); };
    q1_1 = get_q1(q2_1);
    q1_2 = get_q1(q2_2);

    // allocating the joint values to the server response
    response->q1 = round(q1_1 * 100) / 100;
    response->q2 = round(q2_1 * 100) / 100;
    response->q3 = round(q3 * 100) / 100;

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\n(x,y,z): ('%f','%f','%f')", request->x, request->y, request->z);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Outgoing Response\n(x,y,z): ('%f','%f','%f')", response->q1, response->q2, response->q3);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("inverse_kinematics_server");
    rclcpp::Service<custom_interfaces::srv::FindJointStates>::SharedPtr service = node->create_service<custom_interfaces::srv::FindJointStates>("inverse_kinematics", &add);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Calculating Inverse Kinematics.");
    rclcpp::spin(node);
    rclcpp::shutdown();
}