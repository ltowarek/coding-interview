cmake_minimum_required(VERSION 3.4)
project(2_8_loop_detection)

add_executable(2_8_loop_detection 2_8_loop_detection.cpp)
target_include_directories(2_8_loop_detection PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_8_loop_detection ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_8_loop_detection COMMAND 2_8_loop_detection)
