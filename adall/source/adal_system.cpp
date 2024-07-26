#include "adall/adal_system.h"

namespace adlSystem {
	Renderer::Renderer(GLFWwindow *window, adlCore::adlRegistry &registry) : m_window(window) {

	}

	void Renderer::init() {
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(adlVertex), nullptr, GL_DYNAMIC_DRAW);

		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0,
		};

		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), indices, GL_DYNAMIC_DRAW);

		glBindVertexArray(0);
	}

	void Renderer::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, ())
	}

	void Renderer::update() {
		glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);
		glViewport(0, 0, w, h);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}





}
