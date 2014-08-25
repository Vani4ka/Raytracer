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

	float t1x=(p1_.x - ra.origin_.x)*divx;
	auto px=ra.origin_+t1x*ra.direction_.x;
	if ( (p1_.x <= px.x) && (p2_.x >= px.x) )
	{
		return t1x;
	}

	float t2x=(p2_.x - ra.origin_.x)*divx;
	auto px2=ra.origin_+t2x*ra.direction_.x;
	if ( (p1_.x >= px2.x) && (p2_.x <= px2.x) )
	{
		return t2x;
	}
	//float tmax=(p2_.x - ra.origin_.x)*divx;

	

	float t1y=(p1_.y - ra.origin_.y)*divy;
	auto py2=ra.origin_+t1y*ra.direction_.y;
	if ( (p1_.y <= py2.y) && (p2_.y>=py2.y) )
	{
		return t1y;
	}

	float t2y=(p2_.y - ra.origin_.y)*divy;
	auto py=ra.origin_+t2y*ra.direction_.y;
	if ( (p1_.y >= py.y) && (p2_.y <= py.y) )
	{
		return t2y;
	}
	//float tymax=(p2_.y - ra.origin_.y)*divy;
	

	float t1z=(p1_.z - ra.origin_.z)*divz;
	auto pz=ra.origin_+t1z*ra.direction_.z;
	if ( (p1_.z <= pz.z) && (p2_.z>=pz.z) )
	{
		return t1z;
	}

	float t2z=(p2_.z - ra.origin_.z)*divz;
	auto pz2=ra.origin_+t2z*ra.direction_.z;
	if ( (p1_.z >= pz2.z) && (p2_.z <= pz2.z) )
	{
		return t2z;
	}
	//float tzmax=(p2_.z - ra.origin_.z)*divz;
}	

glm::vec3 Box::normal(glm::vec3 cutpoint)
{
	return {0,0,1};
}