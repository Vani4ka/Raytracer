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

void Renderer::render()
{
  std::cerr<<"Section 1"<<std::endl;
  const std::size_t checkersize = 20;
  sdfloader sdf;
  Camera camera;
  sdf.load();
  float temp;
  
  float widthInv = 1.0f / float(width_);
  float heightInv = 1.0f / float(height_);


  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      
      Pixel p(x,y);

      float screenX = float(x) * widthInv - 0.5;
      float screenY = float(y) * heightInv - 0.5;

      Ray ray=camera.getRay(screenX,screenY);

      //Sphere

      if (sdf.sphs().begin() != sdf.sphs().end())
      {
        std::vector<Sphere>::iterator iSphere=sdf.sphs().begin();
      
        while(iSphere != sdf.sphs().end())
        {
          
          //std::cerr<<"Section 2"<<std::endl;

          temp=(*iSphere).intersec(ray);

          //std::cerr<<temp<<std::endl;

          if (temp!= -1)
          {
            //std::cerr<<"Section 4"<<std::endl;
            if (sdf.li().empty())
            {
              p.color=raytrace((*iSphere), sdf.li().front(), sdf, ray);
            }
            else 
            {
              if ((x==0)&&(y==0))
              {  
                std::cout<<"No light found"<<std::endl;
              }
            }
          }

          ++iSphere;
        }
      }
      else
      {
        if ((x==0) && (y==0))
        {
          std::cout << "<Sphere> is empty" << std::endl;
        }
      }

      //Box
      
      if (sdf.bx().begin() != sdf.bx().end())
      {
        std::vector<Box>::iterator iBox=sdf.bx().begin();
      
        while(iBox != sdf.bx().end())
        {
          auto box=*iBox;
          

          temp=box.intersec(ray);

          if (temp!= -1)
          {

            p.color=raytrace(box, sdf.li().front(), sdf, ray);
          }
          ++iBox;
        }
      }
      else
      {
        if ((x==0) && (y==0))
        {
          std::cout << "<Box> is empty" << std::endl;
        }
      }  
      
      write(p);
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

template <typename T>
Color Renderer::raytrace(T const& shape, Light const& light, sdfloader const& sdf, Ray const& ray) const&
{
    for (std::vector<Material>::iterator i=sdf.mats().begin(); i!=sdf.mats().end(); ++i)
    {
      if (shape.materialname()==(*i).name())
      {
        Color ambient{0, 0, 0};
        Color diffuse{0, 0, 0};
        Color reflection{0, 0, 0};
        Color shadowfactor{1, 1, 1};
        Color ownshadow{1,1,1};

        Color final{0, 0, 0};
        
        ambient = (*i).ka() + light.ambient(); //Ambientes Licht

        
        float invmodulus= 1 / (modulus(shape.normal(shape.intersectPoint(ray))) * modulus(-(shape.intersectPoint(ray)-light.position())));   //Diffuses Licht
        float diffusefactor= glm::dot(shape.normal(shape.intersectPoint(ray)), -(shape.intersectPoint(ray) -light.position())) * invmodulus;

        if (diffusefactor > 0) 
        {
          diffuse=light.diffuse()*diffusefactor*(*i).kd();
        }
        else 
        {
          shadowfactor={0, 0, 0};
          ownshadow={0.3, 0.3, 0.3};
        }
        
        
        auto n=shape.normal(shape.intersectPoint(ray)); //Spekulares Licht
        auto I= - (shape.intersectPoint(ray) - light.position());
        auto nscalarI= glm::dot(n, I);
        auto r= (2 * nscalarI * n) - I;
        auto v= shape.intersectPoint(ray) - light.position();
        auto rnormal= r / modulus(r);
        auto vnormal= v / modulus(v);
        auto cosbexpo= std::pow(glm::dot(rnormal, vnormal), (*i).m());
        reflection = light.diffuse() * (*i).ks() * cosbexpo;


        Ray shadow(shape.intersectPoint(ray), glm::normalize(light.position() - shape.intersectPoint(ray))); //Schatten

        auto vec = sdf.sphs();
        
        for (int j=0; j != vec.size(); ++j)
        {
          if(vec[j].name() == shape.name())
          {
            auto temp=vec[j+1].intersec(shadow);
            
            if (temp != -1) 
            {
              final= ambient;
              final = final * Color(0.3, 0.3, 0.3);
            }
            else 
            {
              final= (ambient * ownshadow) + shadowfactor * (diffuse + reflection);
            }
          }
        }

        return final;
      }
    }
}