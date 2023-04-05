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
        // Pin numbers for the red and green LEDs on the Raspberry Pi 4 Model B
        const int LED_PIN_RED = 4;
        const int LED_PIN_GREEN = 6;
};
}