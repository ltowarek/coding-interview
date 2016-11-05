cmake_minimum_required(VERSION 3.4)
project(2_6_palindrome)

add_executable(2_6_palindrome 2_6_palindrome.cpp)
target_include_directories(2_6_palindrome PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_6_palindrome ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_6_palindrome COMMAND 2_6_palindrome)
