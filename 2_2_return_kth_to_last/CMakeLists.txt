cmake_minimum_required(VERSION 3.4)
project(2_2_return_kth_to_last)

add_executable(2_2_return_kth_to_last 2_2_return_kth_to_last.cpp)
target_include_directories(2_2_return_kth_to_last PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_2_return_kth_to_last ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_2_return_kth_to_last COMMAND 2_2_return_kth_to_last)
