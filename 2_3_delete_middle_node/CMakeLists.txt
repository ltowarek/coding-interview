cmake_minimum_required(VERSION 3.4)
project(2_3_delete_middle_node)

add_executable(2_3_delete_middle_node 2_3_delete_middle_node.cpp)
target_include_directories(2_3_delete_middle_node PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_3_delete_middle_node ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_3_delete_middle_node COMMAND 2_3_delete_middle_node)
