#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include <wiringPi.h>
#include <nav_msgs/msg/odometry.hpp>

namespace Raspberry{

class LedNode: public rclcpp::Node{
    public:
        LedNode();
    private:
        void scan_callback(geometry_msgs::msg::Twist::UniquePtr msg);
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr scan_sub;
        void odom_callback(nav_msgs::msg::Odometry::UniquePtr msg);
        rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub;
        // Wiring Pi pin numbers for the red,blue and green LEDs on the Raspberry Pi 4 Model B
        const int LED_PIN_RED = 4;
        const int LED_PIN_GREEN = 6;
        const int LED_PIN_BLUE = 29;
};
}