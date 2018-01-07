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

#include "Minimal.h"

template<class T>
class Interpolator
{
public:
  Interpolator(const sf::Vector2f &MinPt, const sf::Vector2f &InterpPoint1, const sf::Vector2f &InterpPoint2, const sf::Vector2f &MaxPt);
  Interpolator() = default;
  ~Interpolator() = default;

  void SetInterpolationPoints(const sf::Vector2f &P1, const sf::Vector2f &P2);
  void SetInterpolationEndpoints(const sf::Vector2f &First, const sf::Vector2f &Second);

  T GetValue(float TimePercElapsed) const;
  T GetPoint1() const;
  T GetPoint2() const;

private:

  sf::Vector2f m_Point1;
  sf::Vector2f m_Point2;
  sf::Vector2f m_First;
  sf::Vector2f m_Last;

};

const Interpolator<float> LinearFloatInterpolator = Interpolator<float>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(1.f, 1.f));
const Interpolator<sf::Vector2f> LinearVector2fInterpolator = Interpolator<sf::Vector2f>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(1.f, 1.f));
const Interpolator<int32_t> LinearIntInterpolator = Interpolator<int>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Vector2f(1.f, 1.f));

const Interpolator<float> EaseFloatInterpolator = Interpolator<float>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.25f, 0.1f), sf::Vector2f(0.25f, 0.1f), sf::Vector2f(1.f, 1.f));
const Interpolator<sf::Vector2f> EaseVector2fInterpolator = Interpolator<sf::Vector2f>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.25f, 0.1f), sf::Vector2f(0.25f, 0.1f), sf::Vector2f(1.f, 1.f));
const Interpolator<int32_t> EaseIntInterpolator = Interpolator<int>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.25f, 0.1f), sf::Vector2f(0.25f, 0.1f), sf::Vector2f(1.f, 1.f));

#include "Interpolators.inl"
