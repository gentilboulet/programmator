cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lib default.cpp logger.cpp)
target_include_directories(lib PUBLIC ../inc)
