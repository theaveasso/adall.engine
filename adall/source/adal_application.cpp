#include "adall/adal_application.h"

adlglApplication::adlglApplication(): m_window(nullptr) {
	if (!init()) {
		std::cout << "failed to initialize adlglApplication" << std::endl;
		glfwTerminate();
		m_running = false;
		return;
	}
}

bool adlglApplication::setupGLFW() {
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

bool adlglApplication::setupAdallCore() {

	m_registry = std::make_unique<adlCore::adlRegistry>();

	if (const auto assetManager = std::make_shared<adlCore::adlAssetManager>(); !m_registry->adlAddContext<std::shared_ptr<adlCore::adlAssetManager>>(assetManager)) {
		return false;
	}

	return true;
}

void adlglApplication::makeGraphicsPipeline() {
}

bool adlglApplication::init() {
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

void adlglApplication::run() {
	while (!glfwWindowShouldClose(m_window) && m_running) {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

adlglApplication &adlglApplication::getInstance() {
	static adlglApplication instance;
	return instance;
}



