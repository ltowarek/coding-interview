cmake_minimum_required(VERSION 3.4)
project(2_7_intersection)

add_executable(2_7_intersection 2_7_intersection.cpp)
target_include_directories(2_7_intersection PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_7_intersection ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_7_intersection COMMAND 2_7_intersection)
