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

add_executable(switch src/controller_switch.cpp)
ament_target_dependencies(switch rclcpp controller_manager_msgs)

add_executable(ikin_publisher src/joint_state_publisher.cpp)
ament_target_dependencies(ikin_publisher rclcpp custom_interfaces)

install(TARGETS
  fkin_publisher
  ikin_publisher
  switch
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