#ifndef SDFLOADER_HPP_BUW
#define SDFLOADER_HPP_BUW

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stddef.h>
#include <glm/glm.hpp>
#include <memory>
#include "material.hpp"
#include "color.hpp"
#include "light.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "cylinder.hpp"

class sdfloader
{
	private:
		std::vector<Material> materials_;
		std::vector<std::shared_ptr<Shape>> shapes_;
		std::vector<Light> lights_;
	public:
		std::vector<Material> const& materials() const; 
		std::vector<std::shared_ptr<Shape>> const& shapes() const;
		std::vector<Light> const& lights() const;
		void load();
};

#endif