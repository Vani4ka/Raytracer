#include "shape.hpp"

Shape::Shape():
name_("empty"),
materialname_("empty"),
transformMatrix_ 	((1, 0, 0, 0,
				  	  0, 1, 0, 0,
				  	  0, 0, 1, 0,
				      0, 0, 0, 1)),
transformMatrixInv_ ((0, 0, 0, 1,
					  0, 0, 1, 0,
					  0, 1, 0, 0,
					  1, 0, 0, 0 ))
{
	//Sphere::Sphere();
	//Box::Box();
}

Shape::Shape(std::string name,std::string materialname):
name_(name),
materialname_(materialname),
transformMatrix_ 	((1, 0, 0, 0,
				  	  0, 1, 0, 0,
				  	  0, 0, 1, 0,
				      0, 0, 0, 1)),
transformMatrixInv_ ((0, 0, 0, 1,
					  0, 0, 1, 0,
					  0, 1, 0, 0,
					  1, 0, 0, 0 ))
{}

Shape::Shape(std::string name, std::string materialname, glm::vec3 center, float radius):
name_(name),
materialname_(materialname),
transformMatrix_ 	((1, 0, 0, 0,
				  	  0, 1, 0, 0,
				  	  0, 0, 1, 0,
				      0, 0, 0, 1)),
transformMatrixInv_ ((0, 0, 0, 1,
					  0, 0, 1, 0,
					  0, 1, 0, 0,
					  1, 0, 0, 0 ))
{
	//Sphere::Sphere(center, radius);
}

Shape::Shape(std::string name, std::string materialname, glm::vec3 p1, glm::vec3 p2):
name_(name),
materialname_(materialname),
transformMatrix_ 	((1, 0, 0, 0,
				  	  0, 1, 0, 0,
				  	  0, 0, 1, 0,
				      0, 0, 0, 1)),
transformMatrixInv_ ((0, 0, 0, 1,
					  0, 0, 1, 0,
					  0, 1, 0, 0,
					  1, 0, 0, 0 ))
{
	//Box::Box(p1, p2);
}

std::string Shape::name() const
{
	return name_;
}

std::string Shape::materialname() const
{
	return materialname_;
}