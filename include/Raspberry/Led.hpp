#include "rclcpp/rclcpp.hpp"
#include <pigpio.h>
#include <std_msgs/msg/bool.hpp>

namespace Raspberry{

class LedNode: public rclcpp::Node{
    public:
        LedNode();
    private:
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_;
        void read_pin();
        int const LED_PIN = 17;
};
}