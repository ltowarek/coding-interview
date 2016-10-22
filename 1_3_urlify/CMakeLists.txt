cmake_minimum_required(VERSION 3.4)
project(1_3_urlify)

add_executable(1_3_urlify 1_3_urlify.cpp)
target_include_directories(1_3_urlify PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(1_3_urlify ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 1_3_urlify COMMAND 1_3_urlify)
