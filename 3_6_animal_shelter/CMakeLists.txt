cmake_minimum_required(VERSION 3.4)
project(3_6_animal_shelter)

add_executable(3_6_animal_shelter 3_6_animal_shelter.cpp)
target_include_directories(3_6_animal_shelter PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(3_6_animal_shelter ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 3_6_animal_shelter COMMAND 3_6_animal_shelter)
