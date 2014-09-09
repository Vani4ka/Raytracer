#ifndef SHAPE_HPP
#define SHAPE_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "glm/gtx/transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "ray.hpp"
#include "hit.hpp"
#include <string>

class Shape 
{
	private:
		std::string name_;
		std::string materialname_;
		glm::mat4 transformMatrix_;
	    glm::mat4 transformMatrixInv_;
	    bool isTransformed_;
	public:
		Shape();
		Shape(std::string name, std::string materialname);

		std::string name() const;
		std::string materialname() const;
		glm::mat4 transformMatrix() const;
		glm::mat4 transformMatrixInv() const;
		bool isTransformed() const;
		void setTransformed();
		virtual Hit intersect(Ray const& ra) const = 0;
		virtual glm::vec3 intersectPoint(Ray const& ra) const = 0;
		virtual glm::vec3 normal(glm::vec3 cutpoint, std::shared_ptr<Shape> const shape ) const = 0;

		void translate(glm::vec3 const& tvector);
		void scale(glm::vec3 const& svector);
		void rotate(float deg, glm::vec3 const& axis);

};

#endif

