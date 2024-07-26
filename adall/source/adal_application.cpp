#include "adall/adal_application.h"

#include "adall/adal_component.h"
#include "adall/adal_system.h"

adlApplication::adlApplication()
	: m_window(nullptr) {
	if (!init()) {
		std::cout << "failed to initialize adlApplication" << std::endl;
		glfwTerminate();
		m_running = false;
		return;
	}
}

bool adlApplication::setupGLFW() {
	if (!glfwInit()) {
		std::cout << "failed to initialize glfw" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	m_window = glfwCreateWindow(640, 480, "adallgl <3", nullptr, nullptr);
	if (m_window == nullptr) {
		std::cout << "failed to create glfw window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		return false;
	}

	return true;
}

bool adlApplication::setupAdallCore() {
	m_registry = std::make_unique<adlCore::adlRegistry>();
	m_editor   = std::make_unique<adlEditor>(m_window);
	m_editor->init();

	if (const auto camera2D = std::make_shared<adlSystem::Camera2D>(m_window); !m_registry->adlAddContext<
		std::shared_ptr<adlSystem::Camera2D> >(camera2D)) {
		return false;
	}

	const auto assetManager = std::make_shared<adlCore::adlAssetManager>();
	if (!m_registry->adlAddContext<std::shared_ptr<adlCore::adlAssetManager> >(assetManager)) {
		return false;
	}

	if (!assetManager->makeShader(
	                         "shader",
	                         "asset/shader/basic.vert.glsl",
	                         "asset/shader/basic.frag.glsl"
	                        )) {
		return false;
	};

	if (const auto entityManager = std::make_shared<adlCore::adlEntityManager>(*m_registry); !m_registry->adlAddContext<
		std::shared_ptr<adlCore::adlEntityManager> >(entityManager)) {
		return false;
	}

	auto em     = m_registry->adlGetContext<std::shared_ptr<adlCore::adlEntityManager> >();
	auto camera = em->makeEntity();
	camera.addComponent<adlComponent::Camera>();


	return true;
}

void adlApplication::makeGraphicsPipeline() {
}

bool adlApplication::init() {
	if (!setupGLFW()) {
		std::cout << "failed to create glfw window" << std::endl;
		return false;
	}

	if (!setupAdallCore()) {
		std::cout << "failed to setup adall core" << std::endl;
		return false;
	}

	return true;
}

void adlApplication::run() {
	while (!glfwWindowShouldClose(m_window) && m_running) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		m_editor->render();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

adlApplication &adlApplication::getInstance() {
	static adlApplication instance;
	return instance;
}



