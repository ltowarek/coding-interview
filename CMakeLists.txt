cmake_minimum_required(VERSION 3.4)
project(coding_interview)

set(CMAKE_CXX_STANDARD 14)

set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll")
set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest)
set(GTEST_INCLUDE_DIRS ${GTEST_ROOT}/include ${GTEST_ROOT})
set(GTEST_LIBRARIES gtest gtest_main)
add_subdirectory(${GTEST_ROOT} EXCLUDE_FROM_ALL)

enable_testing()

add_subdirectory(1_1_is_unique)
add_subdirectory(1_2_check_permutation)
add_subdirectory(1_3_urlify)
add_subdirectory(1_4_palindrome_permutation)
add_subdirectory(1_5_one_away)
add_subdirectory(1_6_string_compression)
add_subdirectory(1_7_rotate_matrix)
add_subdirectory(1_8_zero_matrix)
add_subdirectory(1_9_string_rotation)
add_subdirectory(2_1_remove_dups)
