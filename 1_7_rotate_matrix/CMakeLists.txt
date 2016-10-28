cmake_minimum_required(VERSION 3.4)
project(1_7_rotate_matrix)

add_executable(1_7_rotate_matrix 1_7_rotate_matrix.cpp)
target_include_directories(1_7_rotate_matrix PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_7_rotate_matrix ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_7_rotate_matrix COMMAND 1_7_rotate_matrix)
