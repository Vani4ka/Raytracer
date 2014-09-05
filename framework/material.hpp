#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <string>
#include "color.hpp"
#include <iostream>

class Material
{
	private:
		std::string name_; 
		Color ka_, kd_, ks_;
		float m_;
	public:
		Material();
		Material(std::string name, Color const& ka, Color const& kd, Color const& ks, float m);
		std::string name() const;
		Color ka() const;
		Color kd() const;
		Color ks() const;
		float m() const;
		std::ostream& print(std::ostream& os) const;

};

std::ostream& operator<<(std::ostream& os, Material const& mat);

#endif 