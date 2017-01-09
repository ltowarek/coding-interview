cmake_minimum_required(VERSION 3.4)
project(4_9_bst_sequences)

add_executable(4_9_bst_sequences 4_9_bst_sequences.cpp)
target_include_directories(4_9_bst_sequences PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_9_bst_sequences ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_9_bst_sequences COMMAND 4_9_bst_sequences)
