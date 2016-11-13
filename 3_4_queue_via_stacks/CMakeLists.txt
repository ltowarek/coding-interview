cmake_minimum_required(VERSION 3.4)
project(3_4_queue_via_stacks)

add_executable(3_4_queue_via_stacks 3_4_queue_via_stacks.cpp)
target_include_directories(3_4_queue_via_stacks PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(3_4_queue_via_stacks ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 3_4_queue_via_stacks COMMAND 3_4_queue_via_stacks)
