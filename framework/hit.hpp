#ifndef HIT_HPP
#define HIT_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "glm/gtx/transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "ray.hpp"
#include "shape.hpp"
#include <string>



struct Hit
{
  bool hit = false; 
  //Shape const* shape = nullptr;
  float t = -1.0;
};

#endif
