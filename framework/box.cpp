#include "box.hpp"

//Konstruktoren

Box::Box():
p1_((0.0f,0.0f,0.0f)),
p2_((0.0f,0.0f,0.0f))
{}

Box::Box(glm::vec3 p1, glm::vec3 p2)
{
	if(p1.x<p2.x){					// p1= pmin 
		std::swap(p1.x, p2.x);		// p2= pmax
	}
	if(p1.y<p2.y){
		std::swap(p1.y, p2.y);
	}
	if(p1.z<p2.z){
		std::swap(p1.z, p2.z);
	}
	p1_=glm::vec3{p1.x, p1.y, p1.z};
	p2_=glm::vec3{p2.x, p2.y, p2.z};
}

Box::Box(std::string name, std::string materialname, glm::vec3 p1, glm::vec3 p2):
p1_(p1),
p2_(p2),
Shape(name, materialname)
{}

//Gtter

glm::vec3 Box::p1()
{
	return p1_;
}

glm::vec3 Box::p2()
{
	return p2_;
}

//Intersection

glm::vec3 Box::intersectPoint(Ray const& ra) const
{
	auto temp=intersect(ra);
	return ra.origin_+temp.t*ra.direction_;
}

Hit Box::intersect(Ray const& r) const
{
	Hit h; 

	float divx= 1.0f/r.direction_.x;
	float divy= 1.0f/r.direction_.y;
	float divz= 1.0f/r.direction_.z;

	auto minx = (p1_.x - r.origin_.x) * divx;
	auto maxx = (p2_.x - r.origin_.x) * divx;

	if (minx > maxx)
	{
		std::swap(minx, maxx);
	}

	auto miny = (p1_.y - r.origin_.y) * divy;
	auto maxy = (p2_.y - r.origin_.y) * divy;

	if (miny > maxy)
	{
		std::swap(miny, maxy);
	}

	if (minx > maxy || miny >maxx)
	{
		h.hit=false;
		h.t=-1;
		return h;
	}

	if (miny > minx)
	{
		minx = miny;
	}

	if (maxy < maxx)
	{
		maxx=maxy;
	}

	auto minz = (p1_.z - r.origin_.z) * divz;
	auto maxz = (p2_.z - r.origin_.z) * divz;

	if (minz > maxz)
	{
		std::swap(minz, maxz);
	}

	if (minx > maxz || minz > maxx)
	{
		h.hit=false;
		h.t=-1;
		return h;
	}

	if (minz > minx)
	{
		minx = minz;
	}

	if (maxz < maxx)
	{
		maxx = maxz;
	}

	h.t=minx;
	h.hit=true;

	return h;
}

glm::vec3 Box::normal(glm::vec3 cutpoint, std::shared_ptr<Shape> const shape) const
{
	glm::vec3 normal;
	if (fabs(cutpoint.x - p1_.x) <= 0.001) //linke Seite
		normal=glm::vec3(-1, 0, 0);
	if (fabs(cutpoint.x - p2_.x) <= 0.001) //rechte Seite
		normal=glm::vec3(1, 0, 0);
	if (fabs(cutpoint.y - p1_.y) <= 0.001) //untere Seite
		normal=glm::vec3(0, -1, 0);
	if (fabs(cutpoint.y - p2_.y) <= 0.001) //obere Seite
		normal=glm::vec3(0, 1, 0);
	if (fabs(cutpoint.z - p1_.z) <= 0.001) //vordere Seite
		normal=glm::vec3(0, 0, 1);
	if (fabs(cutpoint.z - p2_.z) <= 0.001) //hintere Seite
		normal=glm::vec3(0, 0, -1);

	if (shape->isTransformed())
	{
		normal=glm::transpose(glm::mat3(shape -> transformMatrixInv())) * normal;
	}

	return normal;
}