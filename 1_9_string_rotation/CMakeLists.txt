cmake_minimum_required(VERSION 3.4)
project(1_9_string_rotation)

add_executable(1_9_string_rotation 1_9_string_rotation.cpp)
target_include_directories(1_9_string_rotation PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_9_string_rotation ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_9_string_rotation COMMAND 1_9_string_rotation)
