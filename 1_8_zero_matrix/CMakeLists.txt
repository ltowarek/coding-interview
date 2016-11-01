cmake_minimum_required(VERSION 3.4)
project(1_8_zero_matrix)

add_executable(1_8_zero_matrix 1_8_zero_matrix.cpp)
target_include_directories(1_8_zero_matrix PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_8_zero_matrix ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_8_zero_matrix COMMAND 1_8_zero_matrix)
