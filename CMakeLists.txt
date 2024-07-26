cmake_minimum_required(VERSION 3.28)
project(adall)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(adall)
add_subdirectory(adall_sandbox)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/imgui)
add_subdirectory(external/stb)
