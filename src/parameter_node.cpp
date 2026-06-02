#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

#define PARAM_NAME "name"

class ParameterNode : public rclcpp::Node
{
   public:
       ParameterNode() : rclcpp::Node("parameter"), m_param_name("")
       {
          RCLCPP_INFO(this->get_logger(), "parameter has started...");
          m_Timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&ParameterNode::PrintNodeCallback, this));
          m_Publisher = this->create_publisher<example_interfaces::msg::String>("print_name", 10);

          // declare parameter
          this->declare_parameter(PARAM_NAME, "R2D2");


          // get parameter value
          m_param_name = this->get_parameter(PARAM_NAME).as_string();

          // Set a callback to modify parameter at run-time
          m_ParamCallbackOwner= this->add_post_set_parameters_callback(
            std::bind(
            &ParameterNode::postSetParameterCallback, 
            this,
            std::placeholders::_1
            )
          );

       }

    private:
       void PrintNodeCallback()
       {
            auto Msg = example_interfaces::msg::String();
            Msg.data = std::string("Hello  this is ") + m_param_name;
            m_Publisher->publish(Msg);
       }

       void
         postSetParameterCallback(const std::vector<rclcpp::Parameter> & parameters)
         {
         for(const auto & param:parameters) {
            // the internal class member can be changed after
            // successful change to param1 or param2
            if(param.get_name() == PARAM_NAME) {
               m_param_name = param.get_value<std::string>();
            }
         }
 }

       rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr m_Publisher;
       rclcpp::TimerBase::SharedPtr m_Timer;
       std::string m_param_name;
       rclcpp::node_interfaces::PostSetParametersCallbackHandle::SharedPtr m_ParamCallbackOwner;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<ParameterNode>();
    rclcpp::spin(Node);
    rclcpp::shutdown();
    return 0;
}

// Test this code:
// > ros2 param set /parameter name "C3POOOO"
// > ros2 param get /parameter name
// > ros2 topic echo /print_name