#include "rclcpp/rclcpp.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include <wiringPi.h>

namespace Raspberry{
using std::placeholders::_1;
using namespace std::chrono_literals;

class USNode: public rclcpp::Node{
    public:
        USNode();
    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr light_status_pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        const int GPIO_TRIGGER = 1;
        const int GPIO_ECHO = 5;
        const float SPEED_OF_SOUND = 0.0343; //cm/microsecond
        const int DELAY_TIME = 10; //microseconds
        //A good rule of thumb is to set the timeout to a value that is at least two times the maximum expected round-trip time for the ultrasonic pulse. 
        //For example, if the maximum distance that the sensor can measure is 4 meters and the speed of sound in air is approximately 340 meters per second, the maximum round-trip time 
        //for the ultrasonic pulse is 2*(4/340) = 0.024 seconds or 24 milliseconds. So, a good value for the timeout in 
        //this case would be around 50-100 milliseconds
        const int TIMEOUT = 5000; //microseconds
        void Distance_Calculator();
        std::chrono::time_point<std::chrono::steady_clock> start_time_;
        std::chrono::time_point<std::chrono::steady_clock> end_time_;
};
}