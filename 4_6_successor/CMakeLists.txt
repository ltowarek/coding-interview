cmake_minimum_required(VERSION 3.4)
project(4_6_successor)

add_executable(4_6_successor 4_6_successor.cpp)
target_include_directories(4_6_successor PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_6_successor ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_6_successor COMMAND 4_6_successor)
