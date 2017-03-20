cmake_minimum_required(VERSION 3.0)

if (${CMAKE_VERSION} VERSION_LESS "3.1")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
        if(COMPILER_SUPPORTS_CXX14)
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
        else()
                message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
        endif()
else()
        set (CMAKE_CXX_STANDARD 14)
        set (CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(programmator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

add_subdirectory (src) 

add_executable(programmator src/programmator_main.cpp)
target_link_libraries(programmator lib)

enable_testing ()
add_subdirectory (test)
