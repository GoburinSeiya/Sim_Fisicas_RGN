cmake_minimum_required(VERSION 3.26)
project(PolygonShapes)

set(CMAKE_CXX_STANDARD 17)

add_executable(PolygonShapes main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(PolygonShapes PRIVATE box2d::box2d)