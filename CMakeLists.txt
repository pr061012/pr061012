cmake_minimum_required(VERSION 2.8)

project(pr061012)

# Debug version.
if(BUILD STREQUAL "Release")
    message("-- Release mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")
else()
    message("-- Debug mode")
    add_definitions(-DVIEW_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
endif()

# Adding include directory.
include_directories(inc/)

# Getting file list.
file(GLOB_RECURSE SOURCES common/*.cpp model/*.cpp view/*.cpp control/*.cpp cli/*.cpp)

# Executable target.
add_executable(pr061012-${CMAKE_BUILD_TYPE} main.cpp ${SOURCES})

# Linking libraries.
target_link_libraries(pr061012-${CMAKE_BUILD_TYPE} armadillo
                               GL
                               SOIL
                               glfw
                               GLC
                               jsoncpp)
