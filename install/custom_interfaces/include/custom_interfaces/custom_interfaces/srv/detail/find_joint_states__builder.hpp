// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:srv/FindJointStates.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__FIND_JOINT_STATES__BUILDER_HPP_
#define CUSTOM_INTERFACES__SRV__DETAIL__FIND_JOINT_STATES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interfaces/srv/detail/find_joint_states__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interfaces
{

namespace srv
{

namespace builder
{

class Init_FindJointStates_Request_z
{
public:
  explicit Init_FindJointStates_Request_z(::custom_interfaces::srv::FindJointStates_Request & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::srv::FindJointStates_Request z(::custom_interfaces::srv::FindJointStates_Request::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::srv::FindJointStates_Request msg_;
};

class Init_FindJointStates_Request_y
{
public:
  explicit Init_FindJointStates_Request_y(::custom_interfaces::srv::FindJointStates_Request & msg)
  : msg_(msg)
  {}
  Init_FindJointStates_Request_z y(::custom_interfaces::srv::FindJointStates_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_FindJointStates_Request_z(msg_);
  }

private:
  ::custom_interfaces::srv::FindJointStates_Request msg_;
};

class Init_FindJointStates_Request_x
{
public:
  Init_FindJointStates_Request_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FindJointStates_Request_y x(::custom_interfaces::srv::FindJointStates_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_FindJointStates_Request_y(msg_);
  }

private:
  ::custom_interfaces::srv::FindJointStates_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::srv::FindJointStates_Request>()
{
  return custom_interfaces::srv::builder::Init_FindJointStates_Request_x();
}

}  // namespace custom_interfaces


namespace custom_interfaces
{

namespace srv
{

namespace builder
{

class Init_FindJointStates_Response_q3
{
public:
  explicit Init_FindJointStates_Response_q3(::custom_interfaces::srv::FindJointStates_Response & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::srv::FindJointStates_Response q3(::custom_interfaces::srv::FindJointStates_Response::_q3_type arg)
  {
    msg_.q3 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::srv::FindJointStates_Response msg_;
};

class Init_FindJointStates_Response_q2
{
public:
  explicit Init_FindJointStates_Response_q2(::custom_interfaces::srv::FindJointStates_Response & msg)
  : msg_(msg)
  {}
  Init_FindJointStates_Response_q3 q2(::custom_interfaces::srv::FindJointStates_Response::_q2_type arg)
  {
    msg_.q2 = std::move(arg);
    return Init_FindJointStates_Response_q3(msg_);
  }

private:
  ::custom_interfaces::srv::FindJointStates_Response msg_;
};

class Init_FindJointStates_Response_q1
{
public:
  Init_FindJointStates_Response_q1()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FindJointStates_Response_q2 q1(::custom_interfaces::srv::FindJointStates_Response::_q1_type arg)
  {
    msg_.q1 = std::move(arg);
    return Init_FindJointStates_Response_q2(msg_);
  }

private:
  ::custom_interfaces::srv::FindJointStates_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::srv::FindJointStates_Response>()
{
  return custom_interfaces::srv::builder::Init_FindJointStates_Response_q1();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__FIND_JOINT_STATES__BUILDER_HPP_
