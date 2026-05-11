#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"


class ClientNode : public rclcpp::Node
{
   public:
       ClientNode() : rclcpp::Node("subscriber")
       {
            RCLCPP_INFO(this->get_logger(), "subscriber has started...");

            // listen on the "/counter" topic and call CounterCallback() method with a
            // placeholder to store the topic message
            m_Subscriber = this->create_subscription<example_interfaces::msg::String>("counter", 
                10, 
                std::bind(&ClientNode::CounterCallback, this, std::placeholders::_1));
       }

    private:
       void CounterCallback(const example_interfaces::msg::String::SharedPtr Msg)
       {
            RCLCPP_INFO(this->get_logger(), "%s", Msg->data.c_str());

       } 

       rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr m_Subscriber;

};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<ClientNode>();
    rclcpp::spin(Node);
    rclcpp::shutdown();
    return 0;
}