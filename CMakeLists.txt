cmake_minimum_required(VERSION 2.8)

project(pr061012)

# View debug option.
option(VIEW_DEBUG "VIEW_DEBUG" OFF)
if(VIEW_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIEW_DEBUG")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -std=c++11")

file(GLOB_RECURSE SOURCES common/*.cpp model/*.cpp view/*.cpp control/*.cpp cli/*.cpp)

add_executable(pr061012 main.cpp ${SOURCES})

target_link_libraries(pr061012 armadillo
                               GL
                               SOIL
                               GLC
                               jsoncpp)

# Check for glfw version
find_file(GLFW glfw.h /usr/include/GL/)
if(GLFW)
    target_link_libraries(pr061012 glfw)
else()
    target_link_libraries(pr061012 glfw3)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_GLFW3")
endif()
