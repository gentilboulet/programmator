cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRCS
    "*.cpp"
)

add_library(lib ${SRCS})

target_include_directories(lib 
    PUBLIC 
        ../inc
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(lib
    PUBLIC
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
)
