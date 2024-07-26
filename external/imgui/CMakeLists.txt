project(imgui)

file(GLOB_RECURSE SOURCES
        docking/imgui.cpp
        docking/imgui_demo.cpp
        docking/imgui_draw.cpp
        docking/imgui_tables.cpp
        docking/imgui_widgets.cpp
        docking/backends/imgui_impl_glfw.cpp
        docking/backends/imgui_impl_opengl3.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC docking)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)