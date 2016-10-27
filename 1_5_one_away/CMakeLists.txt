cmake_minimum_required(VERSION 3.4)
project(1_5_one_away)

add_executable(1_5_one_away 1_5_one_away.cpp)
target_include_directories(1_5_one_away PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_5_one_away ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_5_one_away COMMAND 1_5_one_away)
