#include "sdfloader.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "ray.hpp"
#include <iostream>
#include <unittest++/UnitTest++.h>

SUITE (test1)
{
	TEST(is_drinne_was_drauf_steht)
	{
		sdfloader sdf;
		sdf.load();
		Material y={"red",{1.0,0.0,0.0},{1.0,0.0,0.0},{1.0,0.0,0.0},1.0};
		CHECK_EQUAL(sdf.materials().front().m() ,y.m());
	}

	/*TEST(is_drinne_was_drauf_steht2)
	{
		sdfloader sdf;
		sdf.load();
		Sphere x={{2.0, 2.0, 2.0}, 4.0};
		CHECK_EQUAL(sdf.sphs().front().radius() ,x.radius());
	}*/

	/*TEST(intersec)
	{
		sdfloader sdf;
  		Camera c({0,0,-1}, {0,0,0}, 45);
  		sdf.load();
  		for (unsigned y = 0; y < 600; ++y) {
    		for (unsigned x = 0; x < 600; ++x) {
      			Ray r(c.position(), {2*x/600-1, 2*y/600-1, -((600/2)/tan(c.angle()/2))});

      			std::cout<<sdf.sphs().front().intersec(r)<<std::endl;
      		}
      	}
	}*/

    /* TEST(intersec)
     {
     	Sphere s({0.0,0.0,-100},100);
     	Ray r({0,0,0,},{0,0, -((600/2)/tan(45/2))});
     	CHECK_EQUAL(0, s.intersec(r));
     }*/
}

int main() { return UnitTest::RunAllTests(); }