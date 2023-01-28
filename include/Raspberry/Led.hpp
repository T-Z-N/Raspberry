#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/string.hpp>
#include <wiringPi.h>

namespace Raspberry{

class LedNode: public rclcpp::Node{
    public:
        LedNode();
    private:
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr scan_sub;
        rclcpp::TimerBase::SharedPtr timer_;
        void scan_callback(std_msgs::msg::String::UniquePtr msg);
        void read_pin();
        int const LED_PIN = 0;
};
}