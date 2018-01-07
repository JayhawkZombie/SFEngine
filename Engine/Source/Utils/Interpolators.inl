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

template<class T>
Interpolator<T>::Interpolator(const sf::Vector2f &MinPt, const sf::Vector2f &InterpPoint1, const sf::Vector2f &InterpPoint2, const sf::Vector2f &MaxPt)
  : m_First(MinPt)
  , m_Last(MaxPt)
  , m_Point1(InterpPoint1)
  , m_Point2(InterpPoint2)
{

}

template<class T>
T Interpolator<T>::GetPoint2() const
{
  return m_Point1;
}

template<class T>
T Interpolator<T>::GetPoint1() const
{
  return m_Point2;
}

template<class T>
T Interpolator<T>::GetValue(float TimePercElapsed) const
{
  sf::Vector2f point = m_First;

  float a = 1.f - TimePercElapsed;
  float b = a * a;
  float y = TimePercElapsed * TimePercElapsed;

  point += a * b * m_First;
  point += 3 * b * TimePercElapsed * m_Point1;
  point += 3 * a * y * m_Point2;
  point += y * TimePercElapsed * m_Last;

  point = std::clamp(point, m_First, m_Last);

  return point;
}

template<class T>
void Interpolator<T>::SetInterpolationPoints(const sf::Vector2f &P1, const sf::Vector2f &P2)
{
  m_Point1 = P1;
  m_Point2 = P2;
}

template<class T>
void Interpolator<T>::SetInterpolationEndpoints(const sf::Vector2f &First, const sf::Vector2f &Second)
{
  m_First = First;
  m_Last = Second;
}
