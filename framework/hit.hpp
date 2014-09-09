#ifndef HIT_HPP
#define HIT_HPP
#include <memory>
#include <limits>
#include "ray.hpp"

class Shape;

struct Hit
{
  bool hit = false; 
  std::shared_ptr<Shape> shape = nullptr;
  float t=std::numeric_limits<float>::infinity();
  Ray hitray = Ray({0, 0, 0}, {0, 0, 0});
};

#endif
