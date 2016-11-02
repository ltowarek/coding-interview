cmake_minimum_required(VERSION 3.4)
project(2_1_remove_dups)

add_executable(2_1_remove_dups 2_1_remove_dups.cpp)
target_include_directories(2_1_remove_dups PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(2_1_remove_dups ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 2_1_remove_dups COMMAND 2_1_remove_dups)
