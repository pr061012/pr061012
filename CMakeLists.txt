cmake_minimum_required(VERSION 2.8)

project(pr061012)

# View debug option.
option(VIEW_DEBUG "VIEW_DEBUG" OFF)
if(VIEW_DEBUG)
    message("-- View debug is enabled.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVIEW_DEBUG")
endif()

# Adding include directory.
include_directories(inc/)

# Setting several compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -std=c++11")

# Getting file list.
file(GLOB_RECURSE SOURCES common/*.cpp model/*.cpp view/*.cpp control/*.cpp cli/*.cpp)

# Executable target.
add_executable(pr061012 main.cpp ${SOURCES})

# Linking libraries.
target_link_libraries(pr061012 armadillo
                               GL
                               SOIL
                               glfw
                               GLC
                               jsoncpp)
