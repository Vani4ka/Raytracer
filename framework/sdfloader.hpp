#ifndef SDFLOADER_HPP_BUW
#define SDFLOADER_HPP_BUW

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stddef.h>
#include <glm/glm.hpp>
#include "material.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include "box.hpp"
#include "light.hpp"

class sdfloader
{
	private:
		std::vector<Material> materials_;
		std::vector<Sphere> spheres_;
		std::vector<Box> boxes_;
		std::vector<Light> lights_;
		//map<Shape*> shapes;//abstrakte Klasse Shape
	public:
		std::vector<Material> materials() const; 
		std::vector<Sphere> spheres() const; 
		std::vector<Box> boxes() const;
		std::vector<Light> lights() const;
		void load();

		template<typename T>
		std::vector<T> vectorsort(std::vector<T> vec);
};

#endif