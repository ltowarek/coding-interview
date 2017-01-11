cmake_minimum_required(VERSION 3.4)
project(4_12_paths_with_sum)

add_executable(4_12_paths_with_sum 4_12_paths_with_sum.cpp)
target_include_directories(4_12_paths_with_sum PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_12_paths_with_sum ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_12_paths_with_sum COMMAND 4_12_paths_with_sum)
