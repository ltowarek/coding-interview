cmake_minimum_required(VERSION 3.4)
project(2_4_partition)

add_executable(2_4_partition 2_4_partition.cpp)
target_include_directories(2_4_partition PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_4_partition ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_4_partition COMMAND 2_4_partition)
