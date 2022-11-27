#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <math.h> /* round, floor, ceil, trunc */

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "custom_interfaces/srv/set_joint_states.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/* ----------------------- Robot Parameter Definition ----------------------- */
class joint_state_controller : public rclcpp::Node
{
public:
  joint_state_controller() : Node("joint_controller_server"), count_(0)
  {
    service_ = this->create_service<custom_interfaces::srv::SetJointStates>("joint_state_controller", std::bind(&joint_state_controller::recieve_reference_joint_position_from_service, this, _1));
  }

  void recieve_reference_joint_position_from_service(const std::shared_ptr<custom_interfaces::srv::SetJointStates::Request> request)
  {
    if (request->rq3 > 2.1 || request->rq3 < 0)
    {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Joint State 3 not reachable");
      return;
    }
    std::vector<std::double_t> reference_position = {
        request->rq1,
        request->rq2,
        request->rq3};
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Request (q1,q2,q3): ('%f','%f','%f')", reference_position[0], reference_position[1], reference_position[2]);
  }

private:
  size_t count_;
  rclcpp::Service<custom_interfaces::srv::SetJointStates>::SharedPtr service_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<joint_state_controller>();
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Starting Position Control.");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
