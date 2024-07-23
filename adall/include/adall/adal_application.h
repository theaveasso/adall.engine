#ifndef ADALLGL_APPLICATION_H
#define ADALLGL_APPLICATION_H

#include "adal_pch.h"
#include "adal_core.h"

class adlglApplication {
private:
	GLFWwindow *m_window;

	std::unique_ptr<adlCore::adlRegistry> m_registry;

	bool m_running = true;

	adlglApplication();

	bool init();

	bool setupGLFW();

	bool setupAdallCore();

	void makeGraphicsPipeline();

public:
	adlglApplication(const adlglApplication &) = delete;

	adlglApplication &operator=(const adlglApplication &) = delete;

	static adlglApplication &getInstance();

	virtual ~adlglApplication() = default;

	void run();
};

#endif //ADALLGL_APPLICATION_H
