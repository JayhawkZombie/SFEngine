#ifndef VEC2D_H_INCLUDED
#define VEC2D_H_INCLUDED

#include<cmath>

#include <cereal/access.hpp>

class vec2d
{
public:

  explicit operator sf::Vector2f() const 
  {
    return sf::Vector2f(x, y);
  }

  float x, y;
  vec2d(float X = 0.0, float Y = 0.0) : x(X), y(Y) {}
  vec2d& operator +=(const vec2d& v);
  vec2d operator+(const vec2d& v)const;
  vec2d& operator -=(const vec2d& v);
  vec2d operator-(const vec2d& v)const;
  vec2d& operator*=(float c) { x *= c; y *= c; return *this; }
  vec2d& operator/=(float c) { x /= c; y /= c; return *this; }
  vec2d operator*(float c)const;
  vec2d operator/(float c)const;

  vec2d operator-() const { return (*this)*-1.0f; }

  float mag()const { return sqrtf(x*x + y * y); }
  float dot(const vec2d& v)const { return x * v.x + y * v.y; }
  float cross(const vec2d& v)const { return x * v.y - y * v.x; }
  vec2d get_LH_norm()const;

  // coordinate transforms
  vec2d from_base(vec2d baseT)const;// get components in x,y
  vec2d to_base(vec2d baseT)const;// get components in base.x, base.y
  vec2d Rotate(float ang)const;

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(x, y);
  }
};

vec2d operator*(float c, vec2d v);

#endif // VEC2D_H_INCLUDED
