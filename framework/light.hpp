#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <glm/glm.hpp>
#include "color.hpp"

class Light
{
	private:
		std::string name_;
		glm::vec3 position_;
		Color ambient_;
		Color diffuse_;
	public:
		Light();
		Light(std::string name, glm::vec3 position, Color const& ambient, Color const& diffuse);
		Color ambient() const&;
		Color diffuse() const&;
		glm::vec3 position() const&;


};

#endif