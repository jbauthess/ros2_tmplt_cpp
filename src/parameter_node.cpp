#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"


class ParameterNode : public rclcpp::Node
{
   public:
       ParameterNode() : rclcpp::Node("parameter"), m_param_name("")
       {
          RCLCPP_INFO(this->get_logger(), "parameter has started...");
          m_Timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&ParameterNode::PrintNodeCallback, this));
          m_Publisher = this->create_publisher<example_interfaces::msg::String>("print_name", 10);

          // declare parameter
          this->declare_parameter("name", "R2D2");


          // get parmaeter value
          m_param_name = this->get_parameter("name").as_string();

       }

    private:
       void PrintNodeCallback()
       {
            auto Msg = example_interfaces::msg::String();
            Msg.data = std::string("Hello  this is ") + m_param_name;
            m_Publisher->publish(Msg);
       }

       rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr m_Publisher;
       rclcpp::TimerBase::SharedPtr m_Timer;
       std::string m_param_name;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<ParameterNode>();
    rclcpp::spin(Node);
    rclcpp::shutdown();
    return 0;
}