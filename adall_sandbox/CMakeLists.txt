project(adallengine_sandbox)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE adallengine)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
