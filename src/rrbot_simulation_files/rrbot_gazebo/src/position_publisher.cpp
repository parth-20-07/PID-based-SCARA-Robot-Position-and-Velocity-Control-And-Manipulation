#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <math.h> /* round, floor, ceil, trunc */

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/* ----------------------- Robot Parameter Definition ----------------------- */
std::double_t l1 = 1, l2 = 1, ao = 0.05, lb = 1;

class FKin_Publisher : public rclcpp::Node
{
public:
  FKin_Publisher() : Node("minimal_publisher"), count_(0)
  {
    fkin_publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/forward_position_controller/commands", 10);
    joint_state_subscriber_ = this->create_subscription<sensor_msgs::msg::JointState>("/joint_states", 10, std::bind(&FKin_Publisher::topic_callback, this, _1));
  }

private:
  void topic_callback(const sensor_msgs::msg::JointState::SharedPtr msg) const
  {
    std::vector<std::double_t> joint_states = {
        msg->position[0],
        msg->position[1],
        msg->position[2]};
    std::cout << joint_states[0] << "," << joint_states[1] << "," << joint_states[2] << std::endl;
    std::double_t pose[4][4] =
        {
            {
                {cos(joint_states[1] + joint_states[0])},
                {-sin(joint_states[1] + joint_states[0])},
                {(0)},
                {cos(joint_states[1] + joint_states[0]) + (9 * cos(joint_states[0])) / 10},
            },
            {
                {sin(joint_states[1] + joint_states[0])},
                {cos(joint_states[1] + joint_states[0])},
                {(0)},
                {sin(joint_states[1] + joint_states[0]) + (9 * sin(joint_states[0])) / 10},
            },
            {
                {(0)},
                {(0)},
                {(1)},
                {2.1 - joint_states[2]},
            },
            {
                {(0)},
                {(0)},
                {(0)},
                {(1)},
            }};

    std_msgs::msg::Float64MultiArray message;
    message.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
    message.layout.dim.push_back(std_msgs::msg::MultiArrayDimension());
    message.layout.dim[0].label = "width";
    message.layout.dim[0].size = 4;
    message.layout.dim[0].stride = 4 * 4;
    message.layout.dim[1].label = "height";
    message.layout.dim[1].size = 4;
    message.layout.dim[0].stride = 4;
    message.layout.data_offset = 0;
    message.data.clear();
    std::vector<double_t> vec(16, 0);
    for (size_t i = 0; i < 4; i++)
      for (size_t j = 0; j < 4; j++)
        vec[(i * 4) + j] = pose[i][j];
    message.data = vec;
    RCLCPP_INFO(this->get_logger(), "Publishing...");
    fkin_publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr fkin_publisher_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber_;
  size_t count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FKin_Publisher>());
  rclcpp::shutdown();
  return 0;
}