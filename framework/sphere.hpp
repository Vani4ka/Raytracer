#ifndef SPHERE_HPP
#define SPHERE_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "glm/gtx/transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "ray.hpp"
#include <string>

class Sphere
{
	private:
		std::string name_; 
		glm::vec3 center_;
		float radius_;
		std::string materialname_;
		//glm::mat4 transformMatrix_;
		//glm::mat4 transformMatrixInv_;

	public:
		Sphere();
		Sphere(std::string name, glm::vec3 center, float radius, std::string materialname);
		std::string name() const;
		float radius();
		glm::vec3 center();
		std::string materialname() const;

		float intersec(Ray const& ra) const;
		glm::vec3 intersectPoint(Ray const& ra) const;
		glm::vec3 normal(glm::vec3 cutpoint) const;

		//void translate(glm::vec3 const& tvector);

};

#endif