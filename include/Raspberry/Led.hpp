#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/bool.hpp>
#include <wiringPi.h>

namespace Raspberry{

class LedNode: public rclcpp::Node{
    public:
        LedNode();
    private:
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        void read_pin();
        int const LED_PIN = 0;
};
}