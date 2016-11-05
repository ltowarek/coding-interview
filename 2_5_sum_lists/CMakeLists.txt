cmake_minimum_required(VERSION 3.4)
project(2_5_sum_lists)

add_executable(2_5_sum_lists 2_5_sum_lists.cpp)
target_include_directories(2_5_sum_lists PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_5_sum_lists ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_5_sum_lists COMMAND 2_5_sum_lists)
