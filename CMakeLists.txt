cmake_minimum_required(VERSION 3.22)
project(console-formatting-benchmarks CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(
  STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(TARGET_NAME console-formatting-benchmarks)
add_executable(
  ${TARGET_NAME}
  src/main.cpp src/tester/tester.cpp src/tester/console-write-tester.cpp
  src/tester/string-tester.cpp)
