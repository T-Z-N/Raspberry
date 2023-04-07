#include "Raspberry/Led.hpp"
#include <wiringPi.h>

namespace Raspberry{
using std::placeholders::_1;
using namespace std::chrono_literals;

// Constructor for the LedNode class
LedNode::LedNode():Node("LedNode"){
      // Initialize wiringPi library
      if (wiringPiSetup() < 0) {
      // Log an error message if initialization fails
      RCLCPP_ERROR(this->get_logger(), "wiringPI initialisation failed");
      return;
    }
    // Set the pin modes for the red and green LEDs
    pinMode(LED_PIN_RED, OUTPUT);
    pinMode(LED_PIN_GREEN, OUTPUT);
    pinMode(LED_PIN_BLUE, OUTPUT);
    // Create a subscription to the "US_Measured_Distance" topic
    scan_sub = create_subscription<geometry_msgs::msg::Twist>("light",rclcpp::SensorDataQoS(), std::bind(&LedNode::scan_callback,this,_1));
    odom_sub = create_subscription<nav_msgs::msg::Odometry>("odom",rclcpp::SensorDataQoS(), std::bind(&LedNode::odom_callback,this,_1));  
}
// Callback function for the scan_sub subscription
void  LedNode::scan_callback(geometry_msgs::msg::Twist::UniquePtr msg){
        if (msg->linear.x > 10) {
            // If the data in the message is greater than 10, turn the red LED on and the green LED off
            digitalWrite(LED_PIN_RED, LOW);
            digitalWrite(LED_PIN_GREEN, HIGH);
        } else {
            // Turn on the red LED and turn off the green LED
            digitalWrite(LED_PIN_RED, HIGH);
            digitalWrite(LED_PIN_GREEN, LOW);
        } 
    }
void LedNode::odom_callback(nav_msgs::msg::Odometry::UniquePtr msg){
        if(msg->pose.pose.position.x > 10){
            digitalWrite(LED_PIN_BLUE, HIGH);
        }
        else{
            digitalWrite(LED_PIN_BLUE, LOW);
        }
}     
}
