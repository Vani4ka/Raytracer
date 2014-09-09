// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

float Renderer::modulus(glm::vec3 v) const
{
    float asquare=v.x * v.x;
    float bsquare=v.y * v.y;
    float csquare=v.z * v.z;
    return sqrt(asquare + bsquare + csquare);
}

Hit Renderer::trace(sdfloader const& sdf, Ray const& ray)
{
  Hit final;
  auto ray_untransformed = ray;
  for (auto const& shape: sdf.shapes())
  {
    //std::cout<<shape -> name() << " | "<<shape -> isTransformed() << std::endl;
    
    if (shape->isTransformed())
    {
      auto origin = glm::vec3(shape -> transformMatrixInv() * glm::vec4(ray.origin_, 1));
      auto direction = glm::vec3(shape -> transformMatrixInv() * glm::vec4(ray.direction_, 0));
      ray = Ray(origin, direction); 
      //std::cout<< shape -> name() <<std::endl;
    }
    else 
    {
      ray = ray_untransformed;
    }


    auto temp=shape->intersect(ray);
    if (temp.hit == true && temp.t < final.t)
    {
      final.t=temp.t;
      final.hit=true;
      final.shape=shape;
      final.hitray=ray;
    }
  }
  return final;
}

void Renderer::render()
{
  const std::size_t checkersize = 20;
  sdfloader sdf;
  Camera camera;
  sdf.load();
  
  float widthInv = 1.0f / float(width_);
  float heightInv = 1.0f / float(height_);


  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      
      Pixel p(x,y);

      float screenX = float(x) * widthInv - 0.5;
      float screenY = float(y) * heightInv - 0.5;

      Ray ray=camera.getRay(screenX,screenY);
      for (auto const& light : sdf.lights())
      {
      
      auto h=trace(sdf, ray);
      if(h.hit)
      {
        p.color=raytrace(h.shape, light, sdf, h.hitray);
      }
      
      write(p);
      }
    }
  }
  ppm_.save(filename_);
}


void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }
  ppm_.write(p);
}

Color Renderer::raytrace(std::shared_ptr<Shape> const shape, Light const& light, sdfloader const& sdf, Ray const& ray) const
{
    Color final{0, 0, 0};
    for (auto const& mat : sdf.materials())
    { 
      if (shape->materialname()==mat.name())
      {
        //std::cerr<<"Raytrace 3"<<std::endl;
        Color ambient{0, 0, 0};
        Color diffuse{0, 0, 0};
        Color reflection{0, 0, 0};
        Color shadowfactor{1, 1, 1};
        Color ownshadow{1,1,1};
        
        ambient = mat.ka() + light.ambient(); //Ambientes Licht

        final = ambient;
      
        float invmodulus= 1 / (modulus(shape->normal(shape->intersectPoint(ray), shape)) * modulus(-(shape->intersectPoint(ray)-light.position())));   //Diffuses Licht
        float diffusefactor= glm::dot(shape->normal(shape->intersectPoint(ray), shape), -(shape->intersectPoint(ray) -light.position())) * invmodulus;

        if (diffusefactor > 0) 
        {
          diffuse=light.diffuse()*diffusefactor*mat.kd();
        }
        else 
        {
          shadowfactor={0, 0, 0};
          ownshadow={0.3, 0.3, 0.3};
        }
        
        
        auto n=shape->normal(shape->intersectPoint(ray), shape); //Spekulares Licht
        auto I= - (shape->intersectPoint(ray) - light.position());
        auto nscalarI= glm::dot(n, I);
        auto r= (2 * nscalarI * n) - I;
        auto v= shape->intersectPoint(ray) - light.position();
        auto rnormal= r / modulus(r);
        auto vnormal= v / modulus(v);
        auto cosbexpo= std::pow(glm::dot(rnormal, vnormal), mat.m());
        reflection = light.diffuse() * mat.ks() * cosbexpo;

        Ray shadow(shape->intersectPoint(ray), glm::normalize(light.position() - shape->intersectPoint(ray))); //Schatten
        //std::cout<<shape->name()<<std::endl;
        for (auto const& s1 : sdf.shapes())
        {
            if(s1->name() != shape->name())
            {
              auto temp= s1->intersect(shadow);
              if (temp.t > 0 && temp.hit==true)
              {
                final = final * Color(0.3, 0.3, 0.3);
              }
              else 
              {
                final= (ambient * ownshadow) + shadowfactor * (diffuse + reflection);
              }
            }
        }
        //final= (ambient * ownshadow) + shadowfactor * (diffuse + reflection);
              
      }
    }
  return final;
}