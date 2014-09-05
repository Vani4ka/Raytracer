#ifndef BOX_HPP
#define BOX_HPP
#include <glm/glm.hpp>
#include <string>
#include <math.h>
#include <iostream>
#include "ray.hpp"
#include "shape.hpp"
#include "hit.hpp"


class Box : Shape
{
	private: 
		glm::vec3 p1_;
		glm::vec3 p2_;
		glm::vec3 normal_;
	public:
		Box();
		Box(glm::vec3 p1, glm::vec3 p2);
		glm::vec3 p1();
		glm::vec3 p2();
		Hit intersect(Ray const& ra) const;
		glm::vec3 intersectPoint(Ray const& ra) const;
		glm::vec3 normal(glm::vec3 cutpoint) const;

};

#endif