#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <QTRSensors.h>
#include <stdio.h>
#include <unistd.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/string.h>
#include <std_msgs/msg/int32.h>

#define ARRAY_LEN 100

rcl_node_t node;
rclc_support_t support;
rcl_allocator_t allocator;

//publisher
rcl_publisher_t publisher;
std_msgs__msg__Int32 msg_int32_pub;
rclc_executor_t executor_pub;
rcl_timer_t timer;

//string publisher
rcl_publisher_t publisher_str;
std_msgs__msg__String msg_str_pub;
rclc_executor_t executor_str;

//subscriber
rcl_subscription_t subscriber;
std_msgs__msg__Int32 msg_int32_sub;
rclc_executor_t executor_sub;

QTRSensors qtr;

const uint8_t SensorCount = 3;
uint16_t sensorValues[SensorCount];

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}

void error_loop(){
  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("error");
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}
int x = 0;

void timer_calback(rcl_timer_t * timer, int64_t last_call_time){
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    RCSOFTCHECK(rcl_publish(&publisher, &msg_int32_pub, NULL));
    qtr.read(sensorValues);
    msg_int32_pub.data = sensorValues[0] ;
    x = msg_int32_sub.data;
    sprintf(msg_str_pub.data.data, "sensorValues: %d, %d, %d  substan gelen sayi: %d",
            sensorValues[0], sensorValues[1], sensorValues[2],x);

    msg_str_pub.data.size = strlen(msg_str_pub.data.data);
    RCSOFTCHECK(rcl_publish(&publisher_str, &msg_str_pub, NULL));

  }
}


void subscription_callback(const void * msgin){
  const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
}

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  set_microros_serial_transports(Serial);

  delay(1000);

  // init qtr
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){14, 15, 16}, SensorCount);
  qtr.setEmitterPin(2);



  allocator = rcl_get_default_allocator();

  // create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "micro_ros_teensy_node", "", &support));

  //create subscriber
  RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_int32_pc"));

  //create publisher
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
    "micro_ros_int32_teensy"));

  //create publisher_str
  RCCHECK(rclc_publisher_init_default(
    &publisher_str,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
    "micro_ros_string_teensy"));

  // create timer
  const unsigned int timer_timeout = 1000;
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_calback));

  // create executor
  RCCHECK(rclc_executor_init(&executor_pub, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor_pub, &timer));

  RCCHECK(rclc_executor_init(&executor_sub, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor_sub, &subscriber, &msg_int32_sub, &subscription_callback, ON_NEW_DATA));

  RCCHECK(rclc_executor_init(&executor_str, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor_str, &timer));

  // init msg
  msg_int32_pub.data = 0;

  //fill the array with a known sqe--equence
  msg_str_pub.data.data = (char *)malloc(ARRAY_LEN*sizeof(char));
  msg_str_pub.data.size = 0;
  msg_str_pub.data.capacity = ARRAY_LEN;

}

void loop(){
  RCSOFTCHECK(rclc_executor_spin_some(&executor_pub, RCL_MS_TO_NS(100)));
  RCSOFTCHECK(rclc_executor_spin_some(&executor_sub, RCL_MS_TO_NS(100)));
  RCSOFTCHECK(rclc_executor_spin_some(&executor_str, RCL_MS_TO_NS(100)));
  delay(100);
}