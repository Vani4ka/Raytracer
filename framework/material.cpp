#include "material.hpp"
#include <string>
#include <iostream>

//Konstruktoren

Material::Material():
name_("empty"),
ka_(Color::Color(0.0f,0.0f,0.0f)),
kd_(Color::Color(0.0f,0.0f,0.0f)),
ks_(Color::Color(0.0f,0.0f,0.0f)),
m_(0.0f)
{}

Material::Material(std::string name, Color const& ka, Color const& kd, Color const& ks, float m):
name_(name),
ka_(ka),
kd_(kd),
ks_(ks),
m_(m)
{}

//Getter

std::string Material::name() const
{
	return name_;
}

Color Material::ka() const
{
	return ka_;
}

Color Material::kd() const
{
	return kd_;
}

Color Material::ks() const
{
	return ks_;
}

float Material::m() const
{
	return m_;
}

std::ostream& Material::print(std::ostream& os) const
{
	os<<"Das Material "<<name()<<" hat die Koeffizienten fuer ambiente "<<ka()<<", diffuse "<<kd()<<" und spiegelnde "<<ks()<<" Reflektion."<<std::endl
	  <<"Der Exponent m der Reflektion betraegt "<<m()<<std::endl;
	return os;

}

std::ostream& operator<<(std::ostream& os, Material const& mat)
{
	return mat.print(os);
}

