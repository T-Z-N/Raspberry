#include "Raspberry/US_Sensor.hpp"
#include <wiringPi.h>


namespace Raspberry{
using std::placeholders::_1;
using namespace std::chrono_literals;


// Constructor for the USNode class
USNode::USNode():Node("Ultra_Sonic_Sensor"){
    // Initialize wiringPi library
    if (wiringPiSetup() < 0){
    // Log an error message if initialization fails
      RCLCPP_ERROR(this->get_logger(), "wiringPI initialisation failed");
      return;
    }
    // Set the pin modes for the trigger and echo pins
    pinMode(GPIO_TRIGGER, OUTPUT);
    pinMode(GPIO_ECHO, INPUT);
    // Create publishers for the measured distance and light status
    measured_distance_pub_ = create_publisher<std_msgs::msg::Int32>("US_Measured_Distance",rclcpp::QoS(1));
    light_status_pub_ = create_publisher<geometry_msgs::msg::Twist>("light",rclcpp::QoS(1));
    // Create a timer to trigger the distance calculation
    timer_ = create_wall_timer(100ms, std::bind(&USNode::Distance_Calculator, this));
}
// Function to calculate the distance to an object using the ultrasonic sensor and publish the result
void USNode::Distance_Calculator(){
        // set Trigger to HIGH
        digitalWrite(GPIO_TRIGGER, HIGH);
        // set Trigger after DELAY_TIME to LOW
        delayMicroseconds(DELAY_TIME);
        digitalWrite(GPIO_TRIGGER, LOW);

    // Wait for echo signal to start
    auto start_time = std::chrono::steady_clock::now();
    while (digitalRead(GPIO_ECHO) == LOW) {
        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time).count();
        if (elapsed_time > TIMEOUT) {
            RCLCPP_ERROR(this->get_logger(), "Timeout waiting for echo signal to start");
            return;
        }
    }
    // Record the start time of the echo signal
    auto echo_start_time = std::chrono::steady_clock::now();

    // Wait for echo signal to end
    while (digitalRead(GPIO_ECHO) == HIGH) {
        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - echo_start_time).count();
        if (elapsed_time > TIMEOUT) {
            RCLCPP_ERROR(this->get_logger(), "Timeout waiting for echo signal to end");
            return;
        }
    }
    // Record the end time of the echo signal
    auto echo_end_time = std::chrono::steady_clock::now();    
    
    // time difference between start and arrival
    auto pulse_duration = std::chrono::duration_cast<std::chrono::microseconds>(echo_end_time - echo_start_time).count();
    // multiply with the sonic speed (SPEED_OF_SOUND)
    // and divide by 2, because there and back
    float distance = (pulse_duration * SPEED_OF_SOUND) / 2;

    std::cout << "Measured Distance = " << distance << " cm" << std::endl;
    // Publish the measured distance for Omniverse
    auto light_msg = geometry_msgs::msg::Twist();
    light_msg.linear.x = distance;
    light_status_pub_->publish(light_msg);

    // Publish the measured distance for Real System
    auto distance_msg = std_msgs::msg::Int32();
    distance_msg.data = distance;
    measured_distance_pub_->publish(distance_msg);
    start_time_ = end_time_;
}
}













