project(stb)

add_library(${PROJECT_NAME} STATIC src/stb.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)