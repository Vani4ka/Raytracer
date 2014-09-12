#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <glm/glm.hpp>
#include <string>
#include <math.h>
#include <iostream>
#include "ray.hpp"
#include "shape.hpp"
#include "hit.hpp"

class Cylinder : public Shape
{
	private:
		glm::vec3 center_;
		float height_;
		float radius_;
	public:
		Cylinder();
		Cylinder(std::string name, std::string materialname, glm::vec3 center, float height, float radius);

		Hit intersect(Ray const& ra) const;
		glm::vec3 intersectPoint(Ray const& ra) const;
		glm::vec3 normal(glm::vec3 cutpoint, std::shared_ptr<Shape> const shape ) const;
};

#endif