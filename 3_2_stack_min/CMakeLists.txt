cmake_minimum_required(VERSION 3.4)
project(3_2_stack_min)

add_executable(3_2_stack_min 3_2_stack_min.cpp)
target_include_directories(3_2_stack_min PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(3_2_stack_min ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 3_2_stack_min COMMAND 3_2_stack_min)
