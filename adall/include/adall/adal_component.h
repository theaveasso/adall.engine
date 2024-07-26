#ifndef ADALLGL_COMPONENT_H
#define ADALLGL_COMPONENT_H

#include "adal_pch.h"

namespace adlComponent {
	struct Camera {
		int width;
		int height;
		float scale;

		glm::vec2 position;
		glm::mat4 cameraMatrix;
		glm::mat4 orthorProjection;
	};

}

#endif //ADALLGL_COMPONENT_H
