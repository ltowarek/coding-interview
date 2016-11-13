cmake_minimum_required(VERSION 3.4)
project(3_5_sort_stack)

add_executable(3_5_sort_stack 3_5_sort_stack.cpp)
target_include_directories(3_5_sort_stack PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(3_5_sort_stack ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 3_5_sort_stack COMMAND 3_5_sort_stack)
