cmake_minimum_required(VERSION 3.28)
project(adall)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(adallengine)
add_subdirectory(adallgl)
add_subdirectory(adallengine_sandbox)
add_subdirectory(adallgl_sandbox)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)