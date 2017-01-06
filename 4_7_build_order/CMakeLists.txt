cmake_minimum_required(VERSION 3.4)
project(4_7_build_order)

add_executable(4_7_build_order 4_7_build_order.cpp)
target_include_directories(4_7_build_order PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_7_build_order ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_7_build_order COMMAND 4_7_build_order)
