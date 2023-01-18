#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <pigpio.h>
#include "Raspberry/Led.hpp"


namespace Raspberry{


LedNode::LedNode():Node("LedNode"){
      
      pub_ = create_publisher<std_msgs::msg::Bool>("pin_state", rclcpp::QoS(1));
      gpioSetMode(LED_PIN, PI_OUTPUT);
      gpioWrite(LED_PIN,1);
}
void 
LedNode::read_pin(){
     std_msgs::msg::Bool pin_state_msg;
     int pin_state = gpioRead(LED_PIN);
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