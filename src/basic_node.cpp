#include "rclcpp/rclcpp.hpp"


class BasicNode : public rclcpp::Node
{
   public:
       BasicNode() : rclcpp::Node("basic"), m_Counter(0)
       {
            RCLCPP_INFO(this->get_logger(), "Hello world");
            m_Timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&BasicNode::PrintCallback, this));
       }

    private:
       void PrintCallback()
       {
            RCLCPP_INFO(this->get_logger(), "Hello %d", m_Counter);
            ++m_Counter;
       }

       rclcpp::TimerBase::SharedPtr m_Timer;
       int m_Counter;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto Node = std::make_shared<BasicNode>();
    rclcpp::spin(Node);
    rclcpp::shutdown();
    return 0;
}