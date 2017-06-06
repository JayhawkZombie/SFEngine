#ifndef SFCSS_CUBIC_BEZIER_H
#define SFCSS_CUBIC_BEZIER_H

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
#include <sfcss/utils/vec.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  class CubicBezier
  {
  public:
    CubicBezier()
      : m_P0({ 0.f, 0.f }), m_P1({ 0.f, 0.f }), m_P2({ 0.f, 0.f }), m_P3({ 0.f, 0.f }) {}
    CubicBezier(float x1, float y1, float x2, float y2)
      : m_P0({ 0.f, 0.f }), m_P1({ x1, y1 }), m_P2({ x2, y2 }), m_P3({ 1.f, 1.f }) {}
    CubicBezier(const Vec2 &p0, const Vec2 &p1, const Vec2 &p2, const Vec2 &p3);
    CubicBezier(const CubicBezier &) = default;

    Vec2 Evaluate(const float &t);

    static CubicBezier EaseIn()         { return CubicBezier(0.4f,   0.f,   1.f,    1.f);   }
    static CubicBezier EaseInOut()      { return CubicBezier(0.4f,   0.f,   0.2f,   1.f);   }
    static CubicBezier Deceleration()   { return CubicBezier(0.f,    0.f,   0.2f,   1.f);   }
    static CubicBezier EaseInOutBack()  { return CubicBezier(0.68f, -0.55f, 0.265f, 1.55f); }
    static CubicBezier EaseInOutQuint() { return CubicBezier(0.86f,  0.f,   0.07f,  1.f);   }
    static CubicBezier Acceleration()   { return EaseIn(); }

  private:
    Vec2 m_P0 = Vec2(0.f, 0.f);
    Vec2 m_P1 = Vec2(0.f, 0.f);
    Vec2 m_P2 = Vec2(0.f, 0.f);
    Vec2 m_P3 = Vec2(0.f, 0.f);
  };

}

#endif // SFCSS_CUBIC_BEZIER_H
