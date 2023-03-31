#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/int32.hpp>
#include <wiringPi.h>

namespace Raspberry{

class LedNode: public rclcpp::Node{
    public:
        LedNode();
    private:
<<<<<<< HEAD
        void scan_callback(std_msgs::msg::Int32::UniquePtr msg);
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr scan_sub;
        const int LED_PIN_RED = 4;
        const int LED_PIN_GREEN = 6;
=======
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_;
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr scan_sub;
        rclcpp::TimerBase::SharedPtr timer_;
        void scan_callback(std_msgs::msg::String::UniquePtr msg);
        void read_pin();
        int const LED_PIN = 0;
>>>>>>> 42c490a1a0d89a43c89ee8b1dc4a654977c76fb3
};
}