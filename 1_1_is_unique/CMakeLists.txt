cmake_minimum_required(VERSION 3.4)
project(1_1_is_unique)

add_executable(1_1_is_unique_test 1_1_is_unique_test.cpp)
target_include_directories(1_1_is_unique_test PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_1_is_unique_test ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_1_is_unique_test COMMAND 1_1_is_unique_test)
