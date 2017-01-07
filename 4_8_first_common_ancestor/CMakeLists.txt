cmake_minimum_required(VERSION 3.4)
project(4_8_first_common_ancestor)

add_executable(4_8_first_common_ancestor 4_8_first_common_ancestor.cpp)
target_include_directories(4_8_first_common_ancestor PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_8_first_common_ancestor ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_8_first_common_ancestor COMMAND 4_8_first_common_ancestor)
