cmake_minimum_required(VERSION 3.4)
project(1_2_check_permutation)

add_executable(1_2_check_permutation 1_2_check_permutation.cpp)
target_include_directories(1_2_check_permutation PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_2_check_permutation ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_2_check_permutation COMMAND 1_2_check_permutation)
