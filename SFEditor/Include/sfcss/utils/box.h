#ifndef SFCSS_BOX_H
#define SFCSS_BOX_H

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
#include "vec.h"

#include <sfcss/sfml_types.h>
#include <sfcss/property/position.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  class Box
  {
  public:
    Box() = default;
    Box(const Box &) = default;
    Box(const Vec2 &position, const Vec2 &size)
      : left(position.X()), top(position.Y()), width(size.X()), height(size.Y()) {}
    Box(const float &v1, const float &p2, const float &p3, const float &p4)
      : left(v1), top(p2), width(p3), height(p4) {}

    operator sf::FloatRect() { return sf::FloatRect(left, top, width, height); }
    FloatRect sf_rect() const { return FloatRect(left, top, width, height); }

    Box& operator=(const Box &other);
    bool operator==(const Box &other)
    {
      return
        (
          std::abs(left - other.left) < 0.001 && std::abs(top - other.top) < 0.001
          && std::abs(width - other.width) < 0.001 && std::abs(height - other.height) < 0.001
          );
    }

    void operator *= (const float &factor) { left *= factor; top *= factor; width *= factor; height *= factor; }
    void operator /= (const float &factor) { left /= factor; top /= factor; width /= factor; height /= factor; }

    friend Box operator *(const Box &box, const float &factor) { return Box(box.left * factor, box.top * factor, box.width * factor, box.height * factor); }
    friend Box operator *(const float &factor, const Box &box) { return Box(box.left * factor, box.top * factor, box.width * factor, box.height * factor); }
    friend Box operator /(const Box &box, const float &factor) { return Box(box.left / factor, box.top / factor, box.width / factor, box.height / factor); }
    friend Box operator /(const float &factor, const Box &box) { return Box(box.left / factor, box.top / factor, box.width / factor, box.height / factor); }

    float Area() const { return width * height; }

    bool contains(const Vec2 &pos) const 
    { 
      return
        ( pos.X() >= left && pos.X() <= left + width &&
          pos.Y() >= top  && pos.Y() <= top  + height );
    }

    bool intersects(const Box &other) const
    {
      Vec2 l1 = TLCorner();
      Vec2 l2 = other.TLCorner();
      Vec2 r1 = BRCorner();
      Vec2 r2 = other.BRCorner();
      return
        (
          !((l1.X() > r2.X()) || (l2.X() > r1.X())) && 
          !((l1.Y() < r2.Y()) || (l2.Y() < r1.Y()))
        );
    }

    Vec2 Position() const { return Vec2(left, top); }
    Vec2 Size() const { return Vec2(width, height); }

    Vec2 TLCorner() const { return Vec2(left, top); }
    Vec2 TRCorner() const { return Vec2(left + width, top); }
    Vec2 BRCorner() const { return Vec2(left + width, top + height); }
    Vec2 BLCorner() const { return Vec2(left, top + height); }

    float left = 0.f;
    float top = 0.f;
    float width = 0.f;
    float height = 0.f;
  };

}

#endif // SFCSS_BOX_H
