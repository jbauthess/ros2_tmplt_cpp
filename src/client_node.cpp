#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

#define SERVICE_NAME "add_two_ints"

class ClientNode : public rclcpp::Node
{
   public:
       ClientNode() : rclcpp::Node("client")
       {
            RCLCPP_INFO(this->get_logger(), "client has started...");

            // listen on the "/counter" topic and call CounterCallback() method with a
            // placeholder to store the topic message
            m_Client= this->create_client<example_interfaces::srv::AddTwoInts>(SERVICE_NAME);
       }

    
       void CallAddTwoInts(int64_t i_A, int64_t i_B)
       {
            // wait for the server to be up 
            while (!m_Client->wait_for_service(std::chrono::seconds(1)))
                RCLCPP_WARN(this->get_logger(), "Waiting for server to be up...");

            // create the request
            auto Request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
            Request->a = i_A;
            Request->b = i_B;

            // send the request
            // and log a callback to process the server response
            m_Client->async_send_request(
                    Request,
                    std::bind(
                    &ClientNode::AddTwoIntsCallback,
                    this,
                    std::placeholders::_1
                )
            );

       }

       private:
            
            void AddTwoIntsCallback(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture i_Future)
            {
                    RCLCPP_INFO(this->get_logger(), "sum = %d", (int) i_Future.get()->sum);
            } 

            rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr m_Client;

};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<ClientNode>();
    Node->CallAddTwoInts(32, 38);
    rclcpp::spin(Node);
    rclcpp::shutdown();

    /*
    // No OOP version
    // ==========================================
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<rclcpp::Node>("client");
    auto Client = Node->create_client<example_interfaces::srv::AddTwoInts>(SERVICE_NAME);

    while (!Client->wait_for_service(std::chrono::seconds(1)))
        RCLCPP_WARN(Node->get_logger(), "Waiting for server to be up...");

    // Create request
    auto Request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    Request->a = 3;
    Request->b = 2;

    // send request
    auto Future = Client->async_send_request(Request);
    // ... and wait until answer
    rclcpp::spin_until_future_complete(Node, Future);
    // log result
    RCLCPP_INFO(this->get_logger(), "%ld", Future->get().sum); 

    rclcpp::shutdown();
    // ==========================================
    */
    return 0;
}