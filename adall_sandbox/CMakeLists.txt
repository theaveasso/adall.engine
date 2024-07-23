project(adallgl_sandbox)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE adall)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)
