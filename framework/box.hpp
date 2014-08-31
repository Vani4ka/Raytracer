#ifndef BOX_HPP
#define BOX_HPP
#include <glm/glm.hpp>
#include <string>
#include "ray.hpp"

class Box
{
	private: 
		std::string name_;
		glm::vec3 p1_;
		glm::vec3 p2_;
		glm::vec3 normal_;
		std::string materialname_;
	public:
		Box();
		Box(std::string name, glm::vec3 p1, glm::vec3 p2, std::string materialname);
		glm::vec3 p1();
		glm::vec3 p2();
		std::string materialname() const;
		float intersec(Ray const& ra) const;
		glm::vec3 intersectPoint(Ray const& ra) const;
		glm::vec3 normal(glm::vec3 cutpoint) const;

};

#endif