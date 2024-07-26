#ifndef ADALLGL_SYSTEM_H
#define ADALLGL_SYSTEM_H

#include "adal_core.h"
#include "adal_pch.h"

namespace adlSystem {
	class Renderer {
	private:
		GLuint m_VAO, m_VBO, m_IBO;

		GLFWwindow *m_window;

	private:
		void init();

		void makeGfxPipeline();

	public:
		Renderer(GLFWwindow *window);

		void update();

		void render();
	};

	class Camera2D {
	private:
		GLFWwindow *m_window;
		GLuint      m_viewLocation;
		glm::vec3   m_globalUp = {0.0f, 0.0f, 1.0f};

	public:
		explicit Camera2D(GLFWwindow* window)
			: m_window(window),
			  m_viewLocation(0) {
		};
		void     update();
	};
}

#endif //ADALLGL_SYSTEM_H
