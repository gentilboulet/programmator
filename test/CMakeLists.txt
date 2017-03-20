cmake_minimum_required(VERSION 3.0)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

add_definitions (-DBOOST_TEST_DYN_LINK)
add_definitions (-DSTAND_ALONE)

add_executable(test_empty empty.cpp)
target_link_libraries(test_empty ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(test_empty lib)
add_test(empty test_empty)
