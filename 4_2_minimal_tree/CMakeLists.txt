cmake_minimum_required(VERSION 3.4)
project(4_2_minimal_tree)

add_executable(4_2_minimal_tree 4_2_minimal_tree.cpp)
target_include_directories(4_2_minimal_tree PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_2_minimal_tree ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_2_minimal_tree COMMAND 4_2_minimal_tree)
