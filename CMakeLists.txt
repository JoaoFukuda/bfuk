cmake_minimum_required(VERSION 3.15..3.21)
project(bfuk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libbfuk)
add_subdirectory(bfuk)
add_subdirectory(tests)
