cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Source Files
set(SOURCES
    src/main.cpp
)

# Libraries
set(LIBRARIES
    glfw
    vulkan
    mathutil
)

# Project
project(vk VERSION 0.1.0 LANGUAGES C CXX)
add_executable(vk ${SOURCES})
target_link_libraries(vk ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

add_subdirectory(mathutil)
