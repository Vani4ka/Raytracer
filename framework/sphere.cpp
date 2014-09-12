#include "sphere.hpp"

//Konstruktoren

Sphere::Sphere():
center_((0.0f,0.0f,0.0f)),
radius_(0.0f)
{}

Sphere::Sphere(glm::vec3 center, float radius):
center_(center),
radius_(radius)
{}

Sphere::Sphere(std::string name, std::string materialname, glm::vec3 center, float radius):
center_(center),
radius_(radius),
Shape(name, materialname)
{}

//Getter

float Sphere::radius()
{
	return radius_;
}

glm::vec3 Sphere::center()
{
	return center_;
}

//Intersection

Hit Sphere::intersect(Ray const& ra) const
{
	Hit h;
	auto originDifference = ra.origin_ - center_;

	float a2Inv = 0;
	float discSqrt = 0;

	float a = glm::dot(ra.direction_, ra.direction_);
	float b = 2.0f * glm::dot(ra.direction_, originDifference);
	float c = glm::dot(originDifference, originDifference) - radius_*radius_;

	float discriminant = b*b - 4.0f*c*a;

	if (discriminant < 0) {
		h.hit=false;
		h.t= -1;
		return h;
	}
	else 
	{
		discSqrt = std::sqrt(discriminant);
	}
	
	if (a!=0)
	{
		a2Inv = 1 / (2.0f * a);
	}
	else 
	{
		std::cout<<"Error"<<std::endl;
	}

	float t1 = (-b + discSqrt) * a2Inv; //quadratische Gleichung lösen
	float t2 = (-b - discSqrt) * a2Inv;

	if (t1 > t2) {
		std::swap(t1, t2);
	}

	if (t2 < 0) {
		h.hit=false;
		h.t= -1;
		return h;
	}

	if (t1 < 0) {
		h.hit=true;
		h.t= t2;
		return h;
	} else {
		h.hit=true;
		h.t= t1;
		return h;
	}
}

glm::vec3 Sphere::intersectPoint(Ray const& ra) const
{
	auto h= intersect(ra);
	return ra.origin_+h.t*ra.direction_;
}

glm::vec3 Sphere::normal(glm::vec3 cutpoint, std::shared_ptr<Shape> const shape ) const
{
	auto normal= cutpoint-center_;
	if (shape->isTransformed())
	{
		normal=glm::transpose(glm::mat3(shape -> transformMatrixInv())) * normal;
	}-

	return normal;
}
