#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/glm.hpp>
#include "ray.hpp"
#include <string>

class Sphere
{
	private:
		std::string name_;
		glm::vec3 center_;
		float radius_;
		std::string materialname_;
	public:
		Sphere();
		Sphere(std::string name, glm::vec3 center, float radius, std::string materialname);
		float radius();
		glm::vec3 center();
		std::string materialname();

		float intersec(Ray const& ra);
		glm::vec3 intersectPoint(Ray const& ra);
		glm::vec3 normal(glm::vec3 cutpoint);

};

#endif