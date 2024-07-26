#ifndef ADAL_EDITOR_H
#define ADAL_EDITOR_H

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "adal_pch.h"

class adlEditor {
private:
	GLFWwindow* m_window;

public:
	explicit adlEditor(GLFWwindow* window);
	~adlEditor();

	bool init();
	void render();
	void update();
};

#endif //ADAL_EDITOR_H
