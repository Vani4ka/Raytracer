#include "light.hpp"

Light::Light():
name_("empty"),
position_((0.0f, 0.0f, 0.0f)),
ambient_(Color::Color(0.0f, 0.0f, 0.0f)),
diffuse_(Color::Color(0.0f, 0.0f, 0.0f))
{}

Light::Light(std::string name, glm::vec3 position, Color const& ambient, Color const& diffuse):
name_(name),
position_(position),
ambient_(ambient),
diffuse_(diffuse)
{}

Color Light::ambient() const&
{
	return ambient_;
}

Color Light::diffuse() const&
{
	return diffuse_;
}

glm::vec3 Light::position() const&
{
	return position_;
}