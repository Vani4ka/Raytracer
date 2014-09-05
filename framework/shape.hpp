#ifndef SHAPE_HPP
#define SHAPE_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "glm/gtx/transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "ray.hpp"
#include "hit.hpp"
#include <string>

class Shape 
{
	public:
		std::string name_;
		std::string materialname_;
		glm::mat4 transformMatrix_;
	    glm::mat4 transformMatrixInv_;
	//public:
		Shape();
		Shape(std::string name, std::string materialname);
		Shape(std::string name, std::string materialname, glm::vec3 center, float radius);
		Shape(std::string name, std::string materialname, glm::vec3 p1, glm::vec3 p2);

		std::string name() const;
		std::string materialname() const;
		virtual Hit intersect(Ray const& ra) const;
		virtual glm::vec3 intersectPoint(Ray const& ra) const;
		virtual glm::vec3 normal(glm::vec3 cutpoint) const;

		//void translate(glm::vec3 const& tvector);

};

#endif

