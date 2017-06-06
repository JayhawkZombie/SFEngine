#ifndef SFCSS_VEC_H
#define SFCSS_VEC_H

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Internal Headers
////////////////////////////////////////////////////////////
#include <sfcss/types.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <algorithm>

namespace css
{

  class Vec2
  {
  public:
    Vec2() = default;
    Vec2(const Vec2 &) = default;
    Vec2(const float &a, const float &b) : m_X(a), m_Y(b) {}
    ~Vec2() = default;

    operator sf::Vector2f() const { return sf::Vector2f({ m_X, m_Y }); }

    void operator=(const sf::Vector2f &vec) { m_X = vec.x; m_Y = vec.y; }
    void operator=(const sf::Vector2i &vec) { m_X = to_float(vec.x); m_Y = to_float(vec.y); }
    void operator=(const sf::Vector2u &vec) { m_X = to_float(vec.x); m_Y = to_float(vec.y); }
    Vec2& operator =(const Vec2 &other) {
      if (&other == this) return *this;
      m_X = other.m_X;
      m_Y = other.m_Y;
      return *this;
    }

    float mag() const
    {
      static float s_mag = std::sqrt(( m_X * m_X ) + ( m_Y * m_Y ));
      static float s_x = m_X;
      static float s_y = m_Y;

      if (std::abs(s_x - m_X) < 0.01 && std::abs(s_y - m_Y) < 0.01)
        return s_mag;

      s_mag = std::sqrt(( m_X * m_X ) + ( m_Y * m_Y ));
      return s_mag;
    }

    void operator += (const Vec2 &other) { m_X += other.m_X; m_Y += other.m_Y; }
    void operator -= (const Vec2 &other) { m_X -= other.m_X; m_Y -= other.m_Y; }
    void operator *= (const float &factor) { m_X *= factor; m_Y *= factor; }
    void operator /= (const float &factor) { m_X /= factor; m_Y /= factor; }

    bool operator==(const Vec2 &other) const {
      return
        ( std::abs(m_X - other.m_X) < 0.0001 && std::abs(m_Y - other.m_Y) < 0.0001 );
    }

    friend Vec2 operator *(const float &factor, const Vec2 &vec) { return Vec2(vec.m_X * factor, vec.m_Y * factor); }
    friend Vec2 operator *(const Vec2 &vec, const float &factor) { return Vec2(vec.m_X * factor, vec.m_Y * factor); }
    friend Vec2 operator /(const float &factor, const Vec2 &vec) { return Vec2(vec.m_X / factor, vec.m_Y / factor); }
    friend Vec2 operator /(const Vec2 &vec, const float &factor) { return Vec2(vec.m_X / factor, vec.m_Y / factor); }

    float X() const { return m_X; }
    float Y() const { return m_Y; }

    void SetX(const float &x) { m_X = x; }
    void SetY(const float &y) { m_Y = y; }

  private:
    float m_X = 0.f;
    float m_Y = 0.f;
  };

}

#endif // SFCSS_VEC_H
