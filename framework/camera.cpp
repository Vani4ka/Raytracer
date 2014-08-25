#include "camera.hpp"

Camera::Camera():
direction_({0,0,-1}),
position_({0,0,0}),
angle_(45),
cameradepth_(1.0f / (2.0f * std::tan(angle_ / 360.0f * M_PI)))
{}

Camera::Camera(glm::vec3 direction, glm::vec3 position, float angle):
direction_(direction),
position_(position),
angle_(angle),
cameradepth_(1.0f / (2.0f * std::tan(angle_ / 360.0f * M_PI)))
{}

glm::vec3 Camera::position()
{
	return position_;
}

float Camera::angle()
{
	return angle_;
}

Ray Camera::getRay(float screenX, float screenY) const& 
{
	Ray r(position_,glm::normalize(glm::vec3{screenX, screenY, -cameradepth_}));
	return r;
}