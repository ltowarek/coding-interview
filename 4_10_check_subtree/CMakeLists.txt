cmake_minimum_required(VERSION 3.4)
project(4_10_check_subtree)

add_executable(4_10_check_subtree 4_10_check_subtree.cpp)
target_include_directories(4_10_check_subtree PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_10_check_subtree ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_10_check_subtree COMMAND 4_10_check_subtree)
