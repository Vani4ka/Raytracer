#ifndef SPHERE_HPP
#define SPHERE_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "glm/gtx/transform.hpp"
#include <math.h>
#include <iostream>
#include <string>
#include "ray.hpp"
#include "shape.hpp"
#include "hit.hpp"


class Sphere : public Shape
{
	private:
		glm::vec3 center_;
		float radius_;

	public:
		Sphere();
		Sphere(glm::vec3 center, float radius);
		Sphere(std::string name, std::string materialname, glm::vec3 center, float radius);
		

		float radius();
		glm::vec3 center();

		Hit intersect(Ray const& ra) const;
		glm::vec3 intersectPoint(Ray const& ra) const;
		glm::vec3 normal(glm::vec3 cutpoint, std::shared_ptr<Shape> const shape) const;
};

#endif