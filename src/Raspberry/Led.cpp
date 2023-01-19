#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include "Raspberry/Led.hpp"
#include <pigpio.h>


namespace Raspberry{

using namespace std::chrono_literals;

LedNode::LedNode():Node("LedNode"){

      if (gpioInitialise() < 0) {
      RCLCPP_ERROR(this->get_logger(), "pigpio initialisation failed");
      return;
    }
    gpioSetMode(17, PI_OUTPUT);
    gpioWrite(17, 1);

    pub_ = create_publisher<std_msgs::msg::Bool>("pin_state", rclcpp::QoS(1));
    timer_ = create_wall_timer(500ms, std::bind(&LedNode::read_pin, this));
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