cmake_minimum_required(VERSION 3.4)
project(1_1_is_unique)

add_executable(1_1_is_unique 1_1_is_unique.cpp)
target_include_directories(1_1_is_unique PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_1_is_unique ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_1_is_unique COMMAND 1_1_is_unique)
