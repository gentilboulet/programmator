cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(programmator)

find_package(Boost
    COMPONENTS program_options)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

add_subdirectory (src) 

# programmator executable
add_executable(programmator src/programmator_main.cpp)
target_include_directories(programmator PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(programmator 
    lib
    ${Boost_LIBRARIES}
)


enable_testing ()
add_subdirectory (test)
