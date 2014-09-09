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
					  1, 0, 0, 0 )),
isTransformed_(false)
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
transformMatrixInv_ ((1, 0, 0, 0,
				  	  0, 1, 0, 0,
				  	  0, 0, 1, 0,
				      0, 0, 0, 1)),
isTransformed_(false)
{}

std::string Shape::name() const
{
	return name_;
}

std::string Shape::materialname() const
{
	return materialname_;
}

glm::mat4 Shape::transformMatrix() const
{
	return transformMatrix_;
}

glm::mat4 Shape::transformMatrixInv() const
{
	return transformMatrixInv_;
}

bool Shape::isTransformed() const
{
	return isTransformed_;
}

void Shape::setTransformed()
{
	isTransformed_=true;
}

void Shape::translate(glm::vec3 const& tvector)
{
	auto m = glm::translate(glm::mat4(), tvector);
	auto m_inv= glm::translate(glm::mat4(), -tvector);
	transformMatrix_=transformMatrix_ * m;
	transformMatrixInv_= transformMatrixInv_ *m_inv;
}

void Shape::scale(glm::vec3 const& svector)
{
	auto m = glm::scale(glm::mat4(), svector);
	auto m_inv= glm::scale(glm::mat4(), 1.0f / svector);
	transformMatrix_=transformMatrix_ * m;
	transformMatrixInv_=transformMatrixInv_ * m_inv;
}

void Shape::rotate(float deg, glm::vec3 const& axis)
{
	float rad=deg * M_PI / 180;
	auto m = glm::rotate(glm::mat4(), rad, axis);
	auto m_inv = glm::rotate(glm::mat4(), -rad, axis);
	transformMatrix_=transformMatrix_ * m;
	transformMatrixInv_=transformMatrixInv_ * m_inv;
}