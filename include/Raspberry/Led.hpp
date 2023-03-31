#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/int32.hpp>
#include <wiringPi.h>

namespace Raspberry{

class LedNode: public rclcpp::Node{
    public:
        LedNode();
    private:
        void scan_callback(std_msgs::msg::Int32::UniquePtr msg);
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr scan_sub;
        const int LED_PIN_RED = 4;
        const int LED_PIN_GREEN = 6;
};
}