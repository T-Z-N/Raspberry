#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include "Raspberry/Led.hpp"
#include <wiringPi.h>

namespace Raspberry{

using namespace std::chrono_literals;

LedNode::LedNode():Node("LedNode"){

      if (wiringPiSetup() < 0) {
      RCLCPP_ERROR(this->get_logger(), "wiringPI initialisation failed");
      return;
    }
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);

    pub_ = create_publisher<std_msgs::msg::Bool>("pin_state", rclcpp::QoS(1));
    timer_ = create_wall_timer(500ms, std::bind(&LedNode::read_pin, this));
}
void 
LedNode::read_pin(){
     std_msgs::msg::Bool pin_state_msg;
     int pin_state = digitalRead(LED_PIN);
      if (pin_state == 1){
            std::cout << "The LED is lit.\n";
            pin_state_msg.data = true;
      }
      else {
            std::cout <<"The LED is not lit.\n";
            pin_state_msg.data = false;
      }
      pub_->publish(pin_state_msg);
  }
}