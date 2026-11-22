cmake_minimum_required(VERSION 3.20)

project(TinyEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glad)

add_subdirectory(Engine)
add_subdirectory(Sandbox)