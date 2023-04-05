#include "rclcpp/rclcpp.hpp"
#include "Raspberry/Led.hpp"
#include "Raspberry/US_Sensor.hpp"

int main(int argc, char * argv[])
{
   // Initialize ROS
   rclcpp::init(argc,argv);
   // Create the nodes
   auto led_node = std::make_shared<Raspberry::LedNode>();
   auto us_node = std::make_shared<Raspberry::USNode>();
   // Create an executor to run the nodes
   rclcpp::executors::SingleThreadedExecutor executor;
   executor.add_node(led_node->get_node_base_interface());
   executor.add_node(us_node->get_node_base_interface());
   // Spin the executor
   executor.spin();
   // Shutdown ROS
   rclcpp::shutdown();
   return 0;
}