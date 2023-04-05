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
    // Create a subscription to the "US_Measured_Distance" topic
    scan_sub = create_subscription<std_msgs::msg::Int32>("US_Measured_Distance",rclcpp::SensorDataQoS(), std::bind(&LedNode::scan_callback,this,_1));  
}
// Callback function for the scan_sub subscription
void  LedNode::scan_callback(std_msgs::msg::Int32::UniquePtr msg){
        if (msg->data > 10) {
            // If the data in the message is greater than 10, turn the red LED on and the green LED off
            digitalWrite(LED_PIN_RED, LOW);
            digitalWrite(LED_PIN_GREEN, HIGH);
        } else {
            // Turn on the red LED and turn off the green LED
            digitalWrite(LED_PIN_RED, HIGH);
            digitalWrite(LED_PIN_GREEN, LOW);
        } 
    }
}