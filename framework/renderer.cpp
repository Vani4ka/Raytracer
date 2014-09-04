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
  //std::cerr<<"Section 1"<<std::endl;
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

      if (sdf.spheres().begin() != sdf.spheres().end())
      {
        std::vector<Sphere>::iterator iSphere=sdf.spheres().begin();
      
        while(iSphere != sdf.spheres().end())
        {
          
          //std::cerr<<"Section 2"<<std::endl;

          temp=(*iSphere).intersect(ray);

          //std::cerr<<"Section 3"<<std::endl;

          if (temp!= -1)
          {
            if (!sdf.lights().empty())
            {
             // std::cerr<<"Renderer 4"<<std::endl;
              p.color=raytrace((*iSphere), sdf.lights().front(), sdf, ray);
              //std::cerr<<"Renderer 5"<<std::endl;
            }
            else 
            {
              if ((x==0)&&(y==0))
              {  
                std::cout<<"No light found"<<std::endl;
              }
            }
          }
          //std::cerr<<"Section 5"<<std::endl;
          iSphere++;
          //std::cerr<<"Section 6"<<std::endl;
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
      
     /* if (sdf.bx().begin() != sdf.boxes().end())
      {
        std::vector<Box>::iterator iBox=sdf.boxes().begin();
      
        while(iBox != sdf.boxes().end())
        {
          auto box=*iBox;
          

          temp=box.intersect(ray);

          if (temp!= -1)
          {

            p.color=raytrace(box, sdf.lights().front(), sdf, ray);
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
      }*/  
      
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
    Color final{0, 0, 0};
    //std::cerr<<"Raytrace 1"<<std::endl;
    for (auto i=sdf.materials().begin(); i!=sdf.materials().end(); ++i)
    { 
      /*std::cerr<<"Shape: "<<shape.name()<<std::endl;
      std::cerr<<"Mat-Name: "<<shape.materialname()<<std::endl;
      std::cerr<<"iter-name: "<<(*i).name()<<std::endl;
      std::cerr<<"Raytrace 2"<<std::endl;*/
      if (shape.materialname()==(*i).name())
      {
        //std::cerr<<"Raytrace 3"<<std::endl;
        Color ambient{0, 0, 0};
        Color diffuse{0, 0, 0};
        Color reflection{0, 0, 0};
        Color shadowfactor{1, 1, 1};
        Color ownshadow{1,1,1};
        
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

        auto vec = sdf.spheres();
        
        for (int j=0; j != vec.size(); ++j)
        {
          if(vec[j].name() == shape.name())
          {
            auto temp=vec[j+1].intersect(shadow);
            
            //std::cout<<temp<<std::endl;
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
      }
      else 
      {
        //std::cout<<"cant find Material "<<std::endl;
      }
    }
  return final;
}