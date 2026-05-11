#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#define SERVICE_NAME "add_two_ints"

class ClientNode : public rclcpp::Node
{
   public:
       ClientNode() : rclcpp::Node("server")
       {
            RCLCPP_INFO(this->get_logger(), "server has started...");

            // listen on the "/counter" topic and call CounterCallback() method with a
            // placeholder to store the topic message
            m_Server = this->create_service<example_interfaces::srv::AddTwoInts>(
                SERVICE_NAME, 
                std::bind(&ClientNode::AddTwoIntsCallback, 
                this, 
                std::placeholders::_1,
                std::placeholders::_2));
       }

    private:
       void AddTwoIntsCallback(
        const example_interfaces::srv::AddTwoInts::Request::SharedPtr Request,
        const example_interfaces::srv::AddTwoInts::Response::SharedPtr Response
        )
       {
            Response->sum = Request->a + Request->b;
            RCLCPP_INFO(this->get_logger(), "%ld+%ld = %ld", 
            Request->a,
            Request->b,
            Response->sum
            );

       } 

       rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr m_Server;

};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<ClientNode>();
    rclcpp::spin(Node);
    rclcpp::shutdown();
    return 0;
}