#pragma once

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

template<typename InterpType>
class CubicBezierInterpolant
{
public:
  CubicBezierInterpolant() = default;
  ~CubicBezierInterpolant() = default;

  CubicBezierInterpolant(const sf::Vector2f &Pt1, const sf::Vector2f &Pt2,
    const InterpType &InterpStart, const InterpType &InterpEnd)
    : m_Pt1(Pt1), m_Pt2(Pt2), m_StartVal(InterpStart), m_EndVal(InterpEnd)
  { }

  void SetPoints(const sf::Vector2f &Pt1, const sf::Vector2f &Pt2)
  {
    m_Pt1 = Pt1;
    m_Pt2 = Pt2;
  }
  
  void SetInterpolationValues(const InterpType &StartVal, const InterpType &EndVal)
  {
    m_StartVal = StartVal;
    m_EndVal = EndVal;
  }

  InterpType Interpolate(float perc)
  {
    sf::Vector2f pt(0.f, 0.f);
    float a = 1 - perc;
    float b = a * a;
    float y = perc * perc;

    pt += 3 * b * perc * m_Pt1;
    pt += 3 * a * y * m_Pt2;
    pt += y * perc;

    pt.x = std::clamp(pt.x, 0.f, 1.f);
    pt.y = std::clamp(pt.y, 0.f, 1.f);

    return (m_StartVal + pt.y * (m_EndVal - m_StartVal));
  }

private:

  sf::Vector2f m_Pt1 = sf::Vector2f(0.5f, 0.5f);
  sf::Vector2f m_Pt2 = sf::Vector2f(0.5f, 0.5f);

  InterpType m_StartVal;
  InterpType m_EndVal;

};
