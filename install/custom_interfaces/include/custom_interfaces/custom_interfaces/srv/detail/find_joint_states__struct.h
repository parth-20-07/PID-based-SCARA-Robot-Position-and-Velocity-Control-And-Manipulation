// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:srv/FindJointStates.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__FIND_JOINT_STATES__STRUCT_H_
#define CUSTOM_INTERFACES__SRV__DETAIL__FIND_JOINT_STATES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/FindJointStates in the package custom_interfaces.
typedef struct custom_interfaces__srv__FindJointStates_Request
{
  double x;
  double y;
  double z;
} custom_interfaces__srv__FindJointStates_Request;

// Struct for a sequence of custom_interfaces__srv__FindJointStates_Request.
typedef struct custom_interfaces__srv__FindJointStates_Request__Sequence
{
  custom_interfaces__srv__FindJointStates_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__FindJointStates_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/FindJointStates in the package custom_interfaces.
typedef struct custom_interfaces__srv__FindJointStates_Response
{
  double q1;
  double q2;
  double q3;
} custom_interfaces__srv__FindJointStates_Response;

// Struct for a sequence of custom_interfaces__srv__FindJointStates_Response.
typedef struct custom_interfaces__srv__FindJointStates_Response__Sequence
{
  custom_interfaces__srv__FindJointStates_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__FindJointStates_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__FIND_JOINT_STATES__STRUCT_H_
