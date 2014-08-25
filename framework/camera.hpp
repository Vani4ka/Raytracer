#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Camera
{
	private: 
		glm::vec3 direction_;
		glm::vec3 position_;
		float angle_;
		float cameradepth_;
	public:
		Camera(); 
		Camera(glm::vec3 direction, glm::vec3 position, float angle);

		glm:: vec3 position();
		float angle();

		Ray getRay(float screenX, float screenY) const&;
};

#endif