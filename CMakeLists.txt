cmake_minimum_required(VERSION 3.5)
project(bfuk)

link_libraries(pthread)

add_executable(bfuk src/main.cpp src/interpreter.cpp src/term.cpp)
