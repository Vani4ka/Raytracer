#ifndef BOX_HPP
#define BOX_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "glm/gtx/transform.hpp"
#include <string>
#include <math.h>
#include <iostream>
#include "ray.hpp"
#include "shape.hpp"
#include "hit.hpp"


class Box : public Shape
{
	private: 
		glm::vec3 p1_;
		glm::vec3 p2_;
	public:
		Box();
		Box(glm::vec3 p1, glm::vec3 p2);
		Box(std::string name, std::string materialname, glm::vec3 p1, glm::vec3 p2);
		glm::vec3 p1();
		glm::vec3 p2();
		Hit intersect(Ray const& ra) const;
		glm::vec3 intersectPoint(Ray const& ra) const;
		glm::vec3 normal(glm::vec3 cutpoint, std::shared_ptr<Shape> const shape ) const;

};

#endif