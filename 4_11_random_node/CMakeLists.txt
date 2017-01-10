cmake_minimum_required(VERSION 3.4)
project(4_11_random_node)

add_executable(4_11_random_node 4_11_random_node.cpp)
target_include_directories(4_11_random_node PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_11_random_node ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_11_random_node COMMAND 4_11_random_node)
