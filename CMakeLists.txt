cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Lab1)
project(${PROJECT_NAME})

file (GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
