#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"


class NumberPublisherNode : public rclcpp::Node
{
   public:
       NumberPublisherNode() : rclcpp::Node("publisher"), m_Counter(0)
       {
            RCLCPP_INFO(this->get_logger(), "publisher has started...");
            m_Timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&NumberPublisherNode::CounterCallback, this));
            m_Publisher = this->create_publisher<example_interfaces::msg::String>("counter", 10);
       }

    private:
       void CounterCallback()
       {
            auto Msg = example_interfaces::msg::String();
            Msg.data = std::string("Counter=") + std::to_string(m_Counter);
            m_Publisher->publish(Msg);
            ++m_Counter;
       }

       rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr m_Publisher;
       rclcpp::TimerBase::SharedPtr m_Timer;
       int m_Counter;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<NumberPublisherNode>();
    rclcpp::spin(Node);
    rclcpp::shutdown();
    return 0;
}