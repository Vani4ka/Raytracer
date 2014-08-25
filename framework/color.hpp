// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator*= (float a)
  {
    r *= a;
    g *= a;
    b *= a;
    return *this;
  }

  Color& operator/= (float a)
  {
    r /= a;
    g /= a;
    b /= a;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp.r *= b.r;
    tmp.g *= b.g;
    tmp.b *= b.b;
    return tmp;    
  }

  friend Color operator*(Color const& a, float b)
  {
    auto tmp(a);
    tmp.r *= b;
    tmp.g *= b;
    tmp.b *= b;
    return tmp;
  }

  friend Color operator/(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp.r /= b.r;
    tmp.g /= b.g;
    tmp.b /= b.b;
    return tmp;
  }
};

#endif //#define BUW_COLOR_HPP
