cmake_minimum_required(VERSION 2.8)

project(pr061012)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCES common/*.cpp model/*.cpp view/*.cpp control/*.cpp cli/*.cpp)

add_executable(pr061012 main.cpp ${SOURCES})

target_link_libraries(pr061012 armadillo
                               GL
                               SOIL
                               glfw
                               GLC
                               jsoncpp)
