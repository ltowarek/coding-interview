cmake_minimum_required(VERSION 3.4)
project(3_3_stack_of_plates)

add_executable(3_3_stack_of_plates 3_3_stack_of_plates.cpp)
target_include_directories(3_3_stack_of_plates PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(3_3_stack_of_plates ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 3_3_stack_of_plates COMMAND 3_3_stack_of_plates)
