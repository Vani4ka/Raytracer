#include "sphere.hpp"
#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

Sphere::Sphere():
name_("empty"),
center_((0.0f,0.0f,0.0f)),
radius_(0.0f),
materialname_("empty")/*,
transformMatrix_((0 , 0 , 0 , 0, 
				 0 , 0 , 0 , 0, 
				 0 , 0 , 0 , 0,
				 0 , 0 , 0 , 0))

transformMatrixInv_((0 , 0 , 0 , 0, 
				 	 0 , 0 , 0 , 0, 
					 0 , 0 , 0 , 0,
				 	 0 , 0 , 0 , 0))*/
{}

Sphere::Sphere(std::string name, glm::vec3 center, float radius, std::string materialname):
name_(name),
center_(center),
radius_(radius),
materialname_(materialname)/*,
transformMatrix_((0 , 0 , 0 , 0, 
				 0 , 0 , 0 , 0, 
				 0 , 0 , 0 , 0,
				 0 , 0 , 0 , 0))

transformMatrixInv_((0 , 0 , 0 , 0, 
				 	 0 , 0 , 0 , 0, 
					 0 , 0 , 0 , 0,
				 	 0 , 0 , 0 , 0))*/
{}

std::string Sphere::name() const
{
	return name_;
}

float Sphere::radius()
{
	return radius_;
}

glm::vec3 Sphere::center()
{
	return center_;
}

std::string Sphere::materialname() const
{
	return materialname_;
}

//pair <bool, Ray>
float Sphere::intersec(Ray const& ra) const
{
	auto originDifference = ra.origin_ - center_;

	float a = glm::dot(ra.direction_, ra.direction_);
	float b = 2.0f * glm::dot(ra.direction_, originDifference);
	float c = glm::dot(originDifference, originDifference) - radius_*radius_;

	float discriminant = b*b - 4.0f*c*a;

	if (discriminant < 0) {
		return -1;
	}

	float discSqrt = std::sqrt(discriminant);
	float a2Inv = 1 / (2.0f * a);

	float t1 = (-b + discSqrt) * a2Inv;
	float t2 = (-b - discSqrt) * a2Inv;

	if (t1 > t2) {
		std::swap(t1, t2);
	}

	if (t2 < 0) {
		return -1;
	}

	if (t1 < 0) {
		return t2;
	} else {
		return t1;
	}
}

glm::vec3 Sphere::intersectPoint(Ray const& ra) const
{
	return ra.origin_+intersec(ra)*ra.direction_;
}

glm::vec3 Sphere::normal(glm::vec3 cutpoint) const
{
	return cutpoint-center_;
}

/*void Sphere::translate(glm::vec3 const& tvector)
{
	auto m = glm::translate(glm::mat4(), tvector);
	auto m_inv= glm::translate(glm::mat4(), -tvector);
	transformMatrix_=transformMatrix_ * m;
	transformMatrix_inv_= transformMatrix_inv_ *m_inv;

}*/