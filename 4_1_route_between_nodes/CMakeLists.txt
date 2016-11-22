cmake_minimum_required(VERSION 3.4)
project(4_1_route_between_nodes)

add_executable(4_1_route_between_nodes 4_1_route_between_nodes.cpp)
target_include_directories(4_1_route_between_nodes PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(4_1_route_between_nodes ${GTEST_LIBRARIES})

enable_testing()
add_test(NAME 4_1_route_between_nodes COMMAND 4_1_route_between_nodes)
