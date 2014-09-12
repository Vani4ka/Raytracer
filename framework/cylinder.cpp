#include "cylinder.hpp"

//Konstruktoren

Cylinder::Cylinder():
Shape("emtpy", "empty"),
center_({0, 0, 0}),
height_(0),
radius_(0)
{}

Cylinder::Cylinder(std::string name, std::string materialname, glm::vec3 center, float height, float radius):
Shape(name, materialname),
center_(center),
height_(height),
radius_(radius)
{}

Hit Cylinder::intersect(Ray const& ra) const
{
	Hit h;
	float ainv ;

	float a = (ra.direction_.z * ra.direction_.z) +  (ra.direction_.x * ra.direction_.x);
	float b = 2* ((ra.direction_.z * ra.origin_.z) + (ra.direction_.x * ra.origin_.x));
	float c = (ra.origin_.z * ra.origin_.z) +  (ra.origin_.x * ra.origin_.x) - (radius_ * radius_);

	auto center2 = glm::vec3 ( center_.x, center_.y + height_ , center_.z);
	auto axis = center2 - center_;
	auto deltap = ra.origin_ - center_;

	auto vva = glm::dot(ra.direction_, axis);
	auto pva = glm::dot(deltap, axis);

	
	auto discriminant = (b * b) - (4 * a * c);

	if(discriminant < 0)
	{
		h.hit = false;
		h.t = -1;
		return h;
	}

	if(a > 0)
	{
		ainv = 1 / (2 * a);
	}
	else
	{
		h.hit = false;
		h.t = -1;
		return h;
	}

	float t1 = (-b - sqrt(discriminant)) * ainv;
	float t2 = (-b + sqrt(discriminant)) * ainv; 

	if (t1 > t2) {
		std::swap(t1, t2);
	}

	if (t2 < 0) {
		h.hit=false;
		h.t= -1;
		return h;
	}
	auto y1 = ra.origin_.y + t1 * ra.direction_.y;
	auto y2 = ra.origin_.y + t2 * ra.direction_.y;

	if (y1 < -1)
	{
		if(y2 < -1)
		{
			h.hit = false;
			h.t = -1;
			return h;
		}
		else 
		{
			float th = t1 + (t2-t1) * (y1+1) / (y1-y2);
			if (th <= 0)
			{
				h.hit = false;
				h.t = -1;
				return h;
			}


			h.hit = true;
			h.t=th;
			return h;
		}
	}

	else if (y1 >= -1 && y1 <= 1)
	{
		if (t1<=0)
		{
			h.hit = false;
			h.t = -1;
			return h;
		}

		h.hit = true;
		h.t=t1;
		return h;
	}

	else if (y1 >1)
	{
		if (y2 > 1)
		{
			h.hit = false;
			h.t = -1;
			return h;
		}
		else 
		{
			float th = t1 + (t2-t1) * (y1+1) / (y1-y2);
			if (th <= 0)
			{
				h.hit = false;
				h.t = -1;
				return h;
			}

			h.hit = true;
			h.t=th;
			return h;

		}


	}
h.hit = false;
h.t = -1;
return h;
}

glm::vec3 Cylinder::intersectPoint(Ray const& ra) const
{
	auto h= intersect(ra);
	return ra.origin_+h.t*ra.direction_;
}

glm::vec3 Cylinder::normal(glm::vec3 cutpoint, std::shared_ptr<Shape> const shape ) const
{
 	auto qminpa = cutpoint - center_;
	auto center2 = glm::vec3(center_.x, center_.y + height_, center_.z);
	auto va =center_ - (center2 - center_);
	auto dot = glm::dot(va, qminpa);

 	auto normal = glm::normalize(qminpa - (dot * va));
	if (shape->isTransformed())
	{
		normal=glm::transpose(glm::mat3(shape -> transformMatrixInv())) * normal;
	}
	return normal;
}