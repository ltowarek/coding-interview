cmake_minimum_required(VERSION 3.4)
project(4_5_validate_bst)

add_executable(4_5_validate_bst 4_5_validate_bst.cpp)
target_include_directories(4_5_validate_bst PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_5_validate_bst ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_5_validate_bst COMMAND 4_5_validate_bst)
