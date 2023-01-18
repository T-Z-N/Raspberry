#include "rclcpp/rclcpp.hpp"
#include "Raspberry/Led.hpp"

int main(int argc, char * argv[])
{
   rclcpp::init(argc,argv);

   auto led_node = std::make_shared<Raspberry::LedNode>();

   rclcpp::executors::SingleThreadedExecutor executor;
   executor.add_node(led_node->get_node_base_interface());

   executor.spin();
   rclcpp::shutdown();
   return 0;
}