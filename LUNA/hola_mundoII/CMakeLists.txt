cmake_minimum_required(VERSION 3.26)
project(hola_mundoII)

set(CMAKE_CXX_STANDARD 17)

add_executable(hola_mundoII main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(hola_mundoII PRIVATE box2d::box2d)
