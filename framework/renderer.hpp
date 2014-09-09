// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "sdfloader.hpp"
#include "ray.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "hit.hpp"
#include "shape.hpp"
#include <math.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <memory>


class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  void render();
  void write(Pixel const& p);
  
  Color raytrace(std::shared_ptr<Shape> const shape, Light const& light, sdfloader const& sdf, Ray const& r) const;
  Hit trace(sdfloader const& sdf, Ray const& ray);
  Color shade(sdfloader const& sdf, Ray const& r, unsigned int depth) {
    if (depth == 0) {
      return Color(0,0,0);
    } else {

    }
  }
  float modulus(glm::vec3 v) const;

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
