cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Definitions
add_compile_definitions(PROJECT_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")

# Source Files
set(SOURCES
    src/vk.cpp
    src/window.cpp
    src/debug.cpp
)

# Libraries
set(LIBRARIES
    glfw
    vulkan
)

# Project
project(vk VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)