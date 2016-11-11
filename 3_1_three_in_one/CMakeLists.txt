cmake_minimum_required(VERSION 3.4)
project(3_1_three_in_one)

add_executable(3_1_three_in_one 3_1_three_in_one.cpp)
target_include_directories(3_1_three_in_one PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(3_1_three_in_one ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 3_1_three_in_one COMMAND 3_1_three_in_one)
