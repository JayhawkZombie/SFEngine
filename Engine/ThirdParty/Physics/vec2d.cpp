#include "vec2d.h"

vec2d& vec2d::operator +=(const vec2d& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

vec2d vec2d::operator+(const vec2d& v)const
{
  //    return vec2d( *this += v );
  vec2d temp(*this);
  temp += v;
  return temp;
}

vec2d& vec2d::operator -=(const vec2d& v)
{
  x -= v.x;
  y -= v.y;
  return *this;
}

vec2d vec2d::operator-(const vec2d& v)const
{
  //    return vec2d( *this += v );
  vec2d temp(*this);
  temp -= v;
  return temp;
}

vec2d vec2d::operator*(float c)const
{
  vec2d temp(*this);
  temp *= c;
  return temp;
}

vec2d vec2d::operator/(float c)const
{
  vec2d temp(*this);
  temp /= c;
  return temp;
}

vec2d vec2d::get_LH_norm()const
{
  vec2d temp(y, -x);
  temp *= 1.0f / sqrtf(x*x + y*y);
  return temp;
}

vec2d vec2d::from_base(vec2d baseT)const// get components in base
{
  vec2d baseN(baseT.get_LH_norm());
  vec2d res;
  res.x = x*baseT.x + y*baseN.x;
  res.y = x*baseT.y + y*baseN.y;
  return res;
}

vec2d vec2d::to_base(vec2d baseT)const// get components in base
{
  return vec2d(dot(baseT), dot(baseT.get_LH_norm()));
}

vec2d vec2d::Rotate(float ang)const
{
  return vec2d(x*cosf(ang) - y*sinf(ang), x*sinf(ang) + y*cosf(ang));
}

// non member funcs
vec2d operator*(float c, vec2d v)
{
  v *= c;
  return v;
}


