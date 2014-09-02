#include "box.hpp"
#include <glm/glm.hpp>
#include <math.h>
#include <iostream>

Box::Box():
name_("empty"),
p1_((0.0f,0.0f,0.0f)),
p2_((0.0f,0.0f,0.0f)),
normal_(0,0,0),
materialname_("empty")
{}

Box::Box(std::string name, glm::vec3 p1, glm::vec3 p2, std::string materialname):
name_(name),
normal_((0,0,0)),
materialname_(materialname)
{
	if(p1.x<p2.x){
		std::swap(p1.x, p2.x);
	}
	if(p1.y<p2.y){
		std::swap(p1.y, p2.y);
	}
	if(p1.z<p2.z){
		std::swap(p1.z, p2.z);
	}
	p1_=glm::vec3{p1.x, p1.y, p1.z};
	p2_=glm::vec3{p2.x, p2.y, p2.z};
	// p2=p2-p1;
}

std::string Box::name() const
{
	return name_;
}

glm::vec3 Box::p1()
{
	return p1_;
}

glm::vec3 Box::p2()
{
	return p2_;
}

std::string Box::materialname() const
{
	return materialname_;
}

glm::vec3 Box::intersectPoint(Ray const& ra) const
{
	return ra.origin_+intersec(ra)*ra.direction_;
}

float Box::intersec(Ray const& r) const
{
	bool hit= false; 

	glm::vec3 pz1;

	Ray ra=r;//Ray{r.origin_ +(p1_-p2_)/2.0f, r.direction_ };

	float divx= 1.0f/ra.direction_.x;
	float divy= 1.0f/ra.direction_.y;
	float divz= 1.0f/ra.direction_.z;

	
	float t1=(p1_.x - ra.origin_.x)*divx; //linke Seite
	float asdf=p1_.x /*- ra.origin_.x*/;
	if (t1 >=0)
	{

		auto px1=ra.origin_+t1*ra.direction_;
		

		if ((p1_.z <= px1.z <= p2_.z) && (p1_.y <= px1.y <= p2_.y))
		{
			
			hit=true;
			normal_=glm::vec3(-1.0f, 0.0f , 0.0f);
		}
	}

	float t2=(p2_.x - ra.origin_.x)*divx; //rechte Seite 
	auto px2=ra.origin_+t2*ra.direction_;
	if(t2>=0){
	if  ((p1_.z <= px2.z <= p2_.z) && (p1_.y <= px2.y <= p2_.y))
	{
		
		if ((t2<t1) || (hit==false))
		{
			
			t1=t2;
			hit= true;
			normal_={1, 0, 0};
		}
			
	}
}
	t2=(p1_.y - ra.origin_.y)*divy;	//untere Seite
	if(t2>=0){
	auto py1=ra.origin_+t2*ra.direction_;

	if  ((p1_.z <= py1.z <= p2_.z) && (p1_.x <= py1.x <= p2_.x))
	{
		
		if ((t2<t1) || (hit==false))
		{
			
			t1=t2;
			hit= true;
			normal_={0, -1, 0};
		}
			
	}
}
	t2=(p2_.y - ra.origin_.y)*divy; //obere Seite

	if(t2>=0){
	auto py2=ra.origin_+t2*ra.direction_;

	if  ((p1_.z <= py2.z <= p2_.z) && (p1_.x <= py2.x <= p2_.x))
	{
		
		if ((t2<t1) || (hit==false))
		{
			
			t1=t2;
			hit= true;
			normal_={0, 1, 0};
		}
			
	}
}


	t2=(p1_.z - ra.origin_.z)*divz;

if(t2>=0){
	pz1=ra.origin_+t2*ra.direction_;

	if  ((p1_.y <= pz1.y <= p2_.y) && (p1_.x <= pz1.x<= p2_.x))
	{
		
		if ((t2<t1) || (hit==false))
		{
			// std::cout<<"vordere seite \n";
			
			t1=t2;
			hit= true;
			normal_={0, 0, -1};
		}
			
	}
}
	t2=(p2_.z - ra.origin_.z)*divz;


if(t2>=0){
	pz1=ra.origin_+t2*ra.direction_;

	if  ((p1_.y <= pz1.y <= p2_.y) && (p1_.x <= pz1.x<= p2_.x))
	{
		
		if ((t2<t1) || (hit==false))
		{

			t1=t2;
			hit= true;
			normal_={0, 0, 1};
		}
			
	}
}
	if (hit==true)
	{
		return t1;
	}

	else 
	{
		return -1;
	}
}	

glm::vec3 Box::normal(glm::vec3 cutpoint) const
{
	return normal_;
}