project(adall)

file(GLOB_RECURSE HEADERS "include/adall/*.h")
file(GLOB_RECURSE SOURCES "source/*.cpp")

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/entt/include)

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw)

target_precompile_headers(${PROJECT_NAME} PRIVATE include/adall/adal_pch.h)