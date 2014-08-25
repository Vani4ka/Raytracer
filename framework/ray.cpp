#include "ray.hpp"

Ray::Ray(glm::vec3 origin, glm::vec3 direction):
origin_(origin),
direction_(direction)
{}

glm::vec3 Ray::origin()
{
	return origin_;
}

glm::vec3 Ray::direction()
{
	return direction_;
}
