#include "box.hpp"
#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

Box::Box():
name_("empty"),
p1_((0.0f,0.0f,0.0f)),
p2_((0.0f,0.0f,0.0f)),
materialname_("empty")
{}

Box::Box(std::string name, glm::vec3 p1, glm::vec3 p2, std::string materialname):
name_(name),
p1_(p1),
p2_(p2),
materialname_(materialname)
{}

glm::vec3 Box::p1()
{
	return p1_;
}

glm::vec3 Box::p2()
{
	return p2_;
}

std::string Box::materialname()
{
	return materialname_;
}

glm::vec3 Box::intersectPoint(Ray const& ra)
{
	return ra.origin_+intersec(ra)*ra.direction_;
}

float Box::intersec(Ray const& ra)
{
	float divx= 1/ra.direction_.x;
	float divy= 1/ra.direction_.y;
	float divz= 1/ra.direction_.z;

	float tmin=(p1_.x - ra.origin_.x)*divx;
	float tmax=(p2_.x - ra.origin_.x)*divx;
	if (tmin > tmax)
	{
		std::swap(tmin, tmax);
	}

	float tymin=(p1_.y - ra.origin_.y)*divy;
	float tymax=(p2_.y - ra.origin_.y)*divy;
	if (tymin > tymax)
	{
		std::swap(tymin, tymax);
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		return -1;
	}

	if (tymin > tmin)
	{
		tmin=tymin;
	}

	if (tymax < tmax)
	{
		tmax=tymax;
	}

	float tzmin=(p1_.z - ra.origin_.z)*divz;
	float tzmax=(p2_.z - ra.origin_.z)*divz;
	if (tzmin > tzmax)
	{
		std::swap(tzmin, tzmax);
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return -1;
	}

	if (tzmin > tmin)
	{
		tmin=tzmin;
	}

	if (tzmax < tmax)
	{
		tmax=tzmax;
	}

	return tmin;
}

glm::vec3 Box::normal(glm::vec3 cutpoint)
{
	return {0,0,1};
}