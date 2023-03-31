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
<<<<<<< HEAD
    pinMode(LED_PIN_RED, OUTPUT);
    pinMode(LED_PIN_GREEN, OUTPUT);

    scan_sub = create_subscription<std_msgs::msg::Int32>("US_Measured_Distance",rclcpp::SensorDataQoS(), std::bind(&LedNode::scan_callback,this,_1));  
=======
    pinMode(LED_PIN, OUTPUT);
    scan_sub = create_subscription<std_msgs::msg::String>("chatter",rclcpp::SensorDataQoS(), std::bind(&LedNode::scan_callback,this,_1));  
    pub_ = create_publisher<std_msgs::msg::Bool>("pin_state", rclcpp::QoS(1));
    timer_ = create_wall_timer(500ms, std::bind(&LedNode::read_pin, this));
>>>>>>> 42c490a1a0d89a43c89ee8b1dc4a654977c76fb3
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