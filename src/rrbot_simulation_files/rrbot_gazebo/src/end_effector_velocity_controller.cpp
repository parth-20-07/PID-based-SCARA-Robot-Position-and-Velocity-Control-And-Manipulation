#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <math.h> /* round, floor, ceil, trunc */

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "custom_interfaces/srv/set_joint_velocity.hpp"
#include "custom_interfaces/srv/set_end_effector_velocity.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/* ----------------------- Robot Parameter Definition ----------------------- */
class velocity_controller : public rclcpp::Node
{
public:
  velocity_controller() : Node("velocity_controller_server"), count_(0)
  {
    joint_velocity_service_ = this->create_service<custom_interfaces::srv::SetJointVelocity>("joint_velocity_service", std::bind(&velocity_controller::set_joint_velocity_from_service, this, _1));
    end_effector_velocity_service_ = this->create_service<custom_interfaces::srv::SetEndEffectorVelocity>("end_effector_velocity_service", std::bind(&velocity_controller::set_end_effector_velocity_from_service, this, _1));
  }

private:
  void set_joint_velocity_from_service(const std::shared_ptr<custom_interfaces::srv::SetJointVelocity::Request> request)
  {
    request_joint_velocity = {request->vq1, request->vq2, request->vq3};
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Request (vq1,vq2,vq3): ('%f','%f','%f')", request_joint_velocity[0], request_joint_velocity[1], request_joint_velocity[2]);
    if (pub_sub_uninitialized_)
    {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Launching Publisher Subscribers");
      joint_state_subscriber_ = create_subscription<sensor_msgs::msg::JointState>("/joint_states", 10, std::bind(&velocity_controller::calculate_joint_efforts, this, _1));
      velocity_publisher_ = create_publisher<std_msgs::msg::Float64MultiArray>("/forward_effort_controller/commands", 10);
      reference_value_publisher_ = create_publisher<std_msgs::msg::Float64MultiArray>("/reference_joint_states/commands", 10);
      pub_sub_uninitialized_ = false;
    }
    service_call_for_joint_velocity_control = true;
  }

  void set_end_effector_velocity_from_service(const std::shared_ptr<custom_interfaces::srv::SetEndEffectorVelocity::Request> request)
  {
    request_end_effector_velocity = {request->vx, request->vy, request->vz};
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Request (vx,vy,vz): ('%f','%f','%f')", request_end_effector_velocity[0], request_end_effector_velocity[1], request_end_effector_velocity[2]);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Launching Publisher Subscribers");
    if (pub_sub_uninitialized_)
    {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Launching Publisher Subscribers");
      joint_state_subscriber_ = create_subscription<sensor_msgs::msg::JointState>("/joint_states", 10, std::bind(&velocity_controller::calculate_joint_efforts, this, _1));
      velocity_publisher_ = create_publisher<std_msgs::msg::Float64MultiArray>("/forward_velocity_controller/commands", 10);
      reference_value_publisher_ = create_publisher<std_msgs::msg::Float64MultiArray>("/reference_joint_states/commands", 10);
      pub_sub_uninitialized_ = false;
    }
    service_call_for_joint_velocity_control = false;
  }

  void calculate_joint_efforts(const sensor_msgs::msg::JointState::SharedPtr msg)
  {
    end = msg->header.stamp.nanosec;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "\n\n\n\n");

    std::vector<std::double_t> joint_position = {
        msg->position[0],
        msg->position[1],
        msg->position[2]};

    std::vector<std::double_t> joint_velocity = {
        msg->velocity[0],
        msg->velocity[1],
        msg->velocity[2]};

    if (service_call_for_joint_velocity_control)
    {
      std::vector<std::double_t> end_effector_velocity; // x,y,z
      end_effector_velocity[0] = (-0.9 * std::sin(joint_position[0]) * request_joint_velocity[0]) + (-0.95 * std::sin(joint_position[0] + joint_position[1]) * (request_joint_velocity[0] + request_joint_velocity[1]));
      end_effector_velocity[1] = (0.9 * std::cos(joint_position[0]) * request_joint_velocity[0]) + (0.95 * std::cos(joint_position[0] + joint_position[1]) * (request_joint_velocity[0] + request_joint_velocity[1]));
      end_effector_velocity[2] = request_joint_velocity[2];
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "End Effector Velocity (vx,vy,vz): ('%f','%f','%f')", end_effector_velocity[0], end_effector_velocity[1], end_effector_velocity[2]);
    }
    else
    {
      request_joint_velocity[0] = -(10 * (request_end_effector_velocity[0] * std::cos(joint_position[0] + joint_position[1]) + request_end_effector_velocity[1] * std::sin(joint_position[0] + joint_position[1]))) / (9 * (std::cos(joint_position[0] + joint_position[1]) * std::sin(joint_position[0]) - std::sin(joint_position[0] + joint_position[1]) * std::cos(joint_position[0])));
      request_joint_velocity[1] = (10 * (19 * request_end_effector_velocity[0] * std::cos(joint_position[0] + joint_position[1]) + 19 * request_end_effector_velocity[1] * std::sin(joint_position[0] + joint_position[1]) + 18 * request_end_effector_velocity[0] * std::cos(joint_position[0]) + 18 * request_end_effector_velocity[1] * std::sin(joint_position[0]))) / (171 * (std::cos(joint_position[0] + joint_position[1]) * std::sin(joint_position[0]) - std::sin(joint_position[0] + joint_position[1]) * std::cos(joint_position[0])));
      request_joint_velocity[2] = request_end_effector_velocity[2];
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Joint Velocity (vq1,vq2,vq3): ('%f','%f','%f')", request_joint_velocity[0], request_joint_velocity[1], request_joint_velocity[2]);
    }

    std::vector<std::double_t> error = {
        joint_velocity[0] - request_joint_velocity[0],
        joint_velocity[1] - request_joint_velocity[1],
        joint_velocity[2] - request_joint_velocity[2]};

    std::double_t duration = (end - begin) / 1000000000.0f;
    // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Duration: '%f'", duration);

    std::vector<std::double_t> error_dot = {
        (last_iteration_joint_error[0] - error[0]) / duration,
        (last_iteration_joint_error[1] - error[1]) / duration,
        (last_iteration_joint_error[2] - error[2]) / duration};

    // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Calculating Efforts");
    if (abs(error[0]) > acceptable_error) // Joint 1
      apply_joint_efforts[0] = -(proportional_gain[0] * error[0]) - (derivative_gain[0] * error_dot[0]);

    if (abs(error[1]) > acceptable_error) // Joint 2
      apply_joint_efforts[1] = -(proportional_gain[1] * error[1]) - (derivative_gain[1] * error_dot[1]);

    if (msg->position[2] >= 2.1)
      apply_joint_efforts[2] = 9.8;
    else if (abs(error[2]) > acceptable_error) // Joint 3
      apply_joint_efforts[2] = -(proportional_gain[2] * error[2]) - (derivative_gain[2] * error_dot[2]);

    std_msgs::msg::Float64MultiArray message;
    message.data.clear();
    message.data = apply_joint_efforts;

    std_msgs::msg::Float64MultiArray reference_joint_states;
    reference_joint_states.data = request_joint_velocity;
    reference_value_publisher_->publish(reference_joint_states);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Errors (q1,q2,q3): ('%f','%f','%f')", error[0], error[1], error[2]);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Publishing Joint Efforts (u1,u2,u3): ('%f','%f','%f')", apply_joint_efforts[0], apply_joint_efforts[1], apply_joint_efforts[2]);
    velocity_publisher_->publish(message);
    begin = msg->header.stamp.nanosec;
    last_iteration_joint_error = error;
  }

  // Variable Definition for class
  rclcpp::Service<custom_interfaces::srv::SetJointVelocity>::SharedPtr joint_velocity_service_;
  rclcpp::Service<custom_interfaces::srv::SetEndEffectorVelocity>::SharedPtr end_effector_velocity_service_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr velocity_publisher_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr reference_value_publisher_;

  bool pub_sub_uninitialized_ = true;
  bool service_call_for_joint_velocity_control = true;
  size_t count_;
  std::vector<std::double_t> request_joint_velocity;
  std::vector<std::double_t> request_end_effector_velocity;
  std::vector<std::double_t> last_iteration_joint_error = {0, 0, 0};
  std::vector<std::double_t> apply_joint_efforts = {0, 0, 9.8};
  std::uint64_t begin, end;

  std::double_t acceptable_error = 0.005f;
  std::vector<std::double_t> proportional_gain = {50, 20, 0}; // 50
  std::vector<std::double_t> derivative_gain = {0.15, 0, 0};  // 0.15
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<velocity_controller>();
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Starting End Effector Velocity Control.");
  system("ros2 run rrbot_gazebo switch_eff");
  system("ros2 topic pub --once /forward_effort_controller/commands std_msgs/msg/Float64MultiArray 'data: [0,0,0]'");
  rclcpp::spin(node);
  rclcpp::shutdown();
  system("ros2 topic pub --once /forward_effort_controller/commands std_msgs/msg/Float64MultiArray 'data: [0,0,0]'");
  return 0;
}
