#ifndef SDFLOADER_HPP_BUW
#define SDFLOADER_HPP_BUW

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stddef.h>
#include "material.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include "box.hpp"
#include "light.hpp"

class sdfloader
{
	private:
		std::vector<Material> mats_;
		std::vector<Sphere> sphs_;
		std::vector<Box> bx_;
		std::vector<Light> li_;
		//map<Shape*> shapes;//abstrakte Klasse Shape
	public:
		std::vector<Material> mats() const; 
		std::vector<Sphere> sphs(); 
		std::vector<Box> bx();
		std::vector<Light> li();
		void load();

		template<typename T>
		std::vector<T> vectorsort(std::vector<T> vec);
};

#endif