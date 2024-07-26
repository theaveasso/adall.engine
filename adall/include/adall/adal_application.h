#ifndef ADALLGL_APPLICATION_H
#define ADALLGL_APPLICATION_H

#include "adal_core.h"
#include "adal_editor.h"
#include "adal_pch.h"

class adlApplication {
private:
	GLFWwindow *m_window;

	std::unique_ptr<adlCore::adlRegistry> m_registry;

	std::unique_ptr<adlEditor> m_editor;

	bool m_running = true;

	adlApplication();

	bool init();

	bool setupGLFW();

	bool setupAdallCore();

	void makeGraphicsPipeline();

public:
	adlApplication(const adlApplication &) = delete;

	adlApplication &operator=(const adlApplication &) = delete;

	static adlApplication &getInstance();

	virtual ~adlApplication() = default;

	void run();
};

#endif //ADALLGL_APPLICATION_H
