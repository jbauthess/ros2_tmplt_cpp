cmake_minimum_required(VERSION 3.10)
project(ros2_tmplt_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# ===================================================
# find dependencies
# ===================================================
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# ===================================================
# Add ROS2 packages to build...
# ===================================================
add_executable(basic src/basic_node.cpp)
add_executable(publisher src/publisher_node.cpp)
add_executable(subscriber src/subscriber_node.cpp)
add_executable(server src/server_node.cpp)
add_executable(client src/client_node.cpp)
add_executable(parameter src/parameter_node.cpp)
# ... with dependencies
ament_target_dependencies(basic rclcpp)
ament_target_dependencies(publisher rclcpp example_interfaces)
ament_target_dependencies(subscriber rclcpp example_interfaces)
ament_target_dependencies(server rclcpp example_interfaces)
ament_target_dependencies(client rclcpp example_interfaces)
ament_target_dependencies(parameter rclcpp example_interfaces)
# Packages to install 
install(TARGETS 
        basic
        publisher
        subscriber
        server
        client
        parameter
        DESTINATION lib/${PROJECT_NAME})

ament_package()
