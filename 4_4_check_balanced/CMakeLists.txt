cmake_minimum_required(VERSION 3.4)
project(4_4_check_balanced)

add_executable(4_4_check_balanced 4_4_check_balanced.cpp)
target_include_directories(4_4_check_balanced PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_4_check_balanced ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_4_check_balanced COMMAND 4_4_check_balanced)
