cmake_minimum_required(VERSION 3.4)
project(1_6_string_compression)

add_executable(1_6_string_compression 1_6_string_compression.cpp)
target_include_directories(1_6_string_compression PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_6_string_compression ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_6_string_compression COMMAND 1_6_string_compression)
