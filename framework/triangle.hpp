#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/glm.hpp>
#include "ray.hpp"

class Triangle
{
	private:
		glm::vec3 p1_;
		glm::vec3 p2_;
		glm::vec3 p3_;
	public:
		Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
		float intersec(Ray const& ra);
};


#endif