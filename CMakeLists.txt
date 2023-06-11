cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories("include")

# Source Files
set(SOURCES
    src/main.cpp
)

# Libraries
set(LIBRARIES
    glfw
    vulkan
)

# Project
project(vk VERSION 0.1.0 LANGUAGES C CXX)
add_executable(vk ${SOURCES})
target_link_libraries(vk ${LIBRARIES})
