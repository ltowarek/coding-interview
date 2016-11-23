cmake_minimum_required(VERSION 3.4)
project(4_3_list_of_depths)

add_executable(4_3_list_of_depths 4_3_list_of_depths.cpp)
target_include_directories(4_3_list_of_depths PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_3_list_of_depths ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_3_list_of_depths COMMAND 4_3_list_of_depths)
