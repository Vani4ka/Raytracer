#ifndef SPHERE_HPP
#define SPHERE_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include "ray.hpp"
#include "shape.hpp"
#include "hit.hpp"


class Sphere : Shape
{
	private:
		glm::vec3 center_;
		float radius_;

	public:
		Sphere();
		//Sphere(Sphere const& ) = default;
		//Sphere(Sphere&&) = default;
		//~Sphere() = default;
		//Sphere& operator=(Sphere const& other) = default;
		Sphere(glm::vec3 center, float radius);
		Sphere(std::string name, std::string materialname, glm::vec3 center, float radius);
		

		float radius();
		glm::vec3 center();

		Hit intersect(Ray const& ra) const;
		glm::vec3 Sphere::intersectPoint(Ray const& ra) const;
		glm::vec3 normal(glm::vec3 cutpoint) const;

		

};

#endif