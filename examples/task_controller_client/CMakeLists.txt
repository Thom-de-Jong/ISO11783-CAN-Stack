cmake_minimum_required(VERSION 3.16)
project(task_controller_client_example)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT BUILD_EXAMPLES)
  find_package(isobus REQUIRED)
endif()
find_package(Threads REQUIRED)

add_executable(
  TaskControllerClientExample
  main.cpp console_logger.cpp section_control_implement_sim.cpp
  section_control_implement_sim.hpp)
target_link_libraries(
  TaskControllerClientExample
  PRIVATE isobus::Isobus isobus::HardwareIntegration Threads::Threads
          isobus::Utility)
