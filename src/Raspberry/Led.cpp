#include "Raspberry/Led.hpp"
#include <wiringPi.h>

namespace Raspberry{
using std::placeholders::_1;
using namespace std::chrono_literals;

LedNode::LedNode():Node("LedNode"){
      if (wiringPiSetup() < 0) {
      RCLCPP_ERROR(this->get_logger(), "wiringPI initialisation failed");
      return;
    }
    pinMode(LED_PIN_RED, OUTPUT);
    pinMode(LED_PIN_GREEN, OUTPUT);

    scan_sub = create_subscription<std_msgs::msg::Int32>("US_Measured_Distance",rclcpp::SensorDataQoS(), std::bind(&LedNode::scan_callback,this,_1));  
}

void  LedNode::scan_callback(std_msgs::msg::Int32::UniquePtr msg){
        if (msg->data > 10) {
            digitalWrite(LED_PIN_RED, LOW);
            digitalWrite(LED_PIN_GREEN, HIGH);
        } else if (msg->data < 3) {
            digitalWrite(LED_PIN_RED, HIGH);
            digitalWrite(LED_PIN_GREEN, LOW);
        } else {
            digitalWrite(LED_PIN_RED, LOW);
            digitalWrite(LED_PIN_GREEN, LOW);
        }
    }

}