cmake_minimum_required(VERSION 3.5)
project(rrbot_gazebo)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(controller_manager_msgs REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(fkin_publisher src/position_publisher.cpp)
ament_target_dependencies(fkin_publisher rclcpp std_msgs sensor_msgs)

add_executable(joint_effort_control src/joint_effort_controller.cpp)
ament_target_dependencies(joint_effort_control rclcpp std_msgs sensor_msgs custom_interfaces)

add_executable(switch_eff src/controller_effort_switch.cpp)
ament_target_dependencies(switch_eff rclcpp controller_manager_msgs)

add_executable(switch_vel src/controller_velocity_switch.cpp)
ament_target_dependencies(switch_vel rclcpp controller_manager_msgs)

add_executable(ikin_publisher src/joint_state_publisher.cpp)
ament_target_dependencies(ikin_publisher rclcpp custom_interfaces)

install(TARGETS
  fkin_publisher
  ikin_publisher
  switch_eff
  switch_vel
  joint_effort_control
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
install(DIRECTORY worlds
  DESTINATION share/${PROJECT_NAME}
)
install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)
ament_package()