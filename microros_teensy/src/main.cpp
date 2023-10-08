#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/twist.h>

// Define motor control pins
const int RF = 0; // Right Forward
const int RB = 1; // Right Backward
const int LF = 2; // Left Forward
const int LB = 3; // Left Backward

// Create ROS node, publisher, and message
rcl_node_t node;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_subscription_t twist_subscriber;
geometry_msgs__msg__Twist twist_msg;
rclc_executor_t executor_twist;

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}

void error_loop(){
  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

void twist_callback(const void * msgin){
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
  float linear_x = msg->linear.x;
  float angular_z = msg->angular.z;

  int pwmRF = 0;
  int pwmRB = 0;
  int pwmLF = 0;
  int pwmLB = 0;

  if (linear_x > 0)
  {
    pwmRF = 255;
    pwmRB = 0;
    pwmLF = 255;
    pwmLB = 0;
  }
  else if (linear_x < 0)
  {
    pwmRF = 0;
    pwmRB = 255;
    pwmLF = 0;
    pwmLB = 255;
  }
  else if (angular_z < 0)
  {
    pwmRF = 0;
    pwmRB = 255;
    pwmLF = 255;
    pwmLB = 0;
  }
  else if (angular_z > 0)
  {
    pwmRF = 255;
    pwmRB = 0;
    pwmLF = 0;
    pwmLB = 255;
  }
  else{
    pwmRF = 0;
    pwmRB = 0;
    pwmLF = 0;
    pwmLB = 0;
  }


  // Set motor PWM values
  analogWrite(RF, pwmRF/2);
  analogWrite(RB, pwmRB/2);
  analogWrite(LF, pwmLF/2);
  analogWrite(LB, pwmLB/2);
}

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  set_microros_serial_transports(Serial);

  delay(1000);

  allocator = rcl_get_default_allocator();

  // create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "micro_ros_teensy_node", "", &support));

  // create twist_subscriber
  RCCHECK(rclc_subscription_init_default(
    &twist_subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "/turtle1/cmd_vel"));

  // create executor
  RCCHECK(rclc_executor_init(&executor_twist, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor_twist, &twist_subscriber, &twist_msg, &twist_callback, ON_NEW_DATA));

  // init twist message
  twist_msg.linear.x = 0.0;
  twist_msg.angular.z = 0.0;
}

void loop(){
  RCSOFTCHECK(rclc_executor_spin_some(&executor_twist, RCL_MS_TO_NS(100)));
  delay(100);
}