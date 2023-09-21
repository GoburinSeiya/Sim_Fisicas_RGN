cmake_minimum_required(VERSION 3.26)
project(Carburo_Tungsteno_Jupiter_RGN)

set(CMAKE_CXX_STANDARD 17)

add_executable(Carburo_Tungsteno_Jupiter_RGN main.cpp)

find_package(box2d CONFIG REQUIRED)
target_link_libraries(Carburo_Tungsteno_Jupiter_RGN PRIVATE box2d::box2d)
