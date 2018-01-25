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

#include "SpacialDistributions.h"


RadialDistribution::RadialDistribution()
  : m_AngleDistribution(0.f, 2 * 3.14159f)
{

}

RadialDistribution::RadialDistribution(const sf::Vector2f &Center, float Radius)
  : m_Center(Center), m_Radius(Radius)
{

}

sf::Vector2f RadialDistribution::operator()()
{
  auto angle = m_AngleDistribution();

  sf::Vector2f dir(std::cosf(angle), std::sinf(angle));

  return ( m_Center + m_Radius * dir );
}

void RadialDistribution::SetCenter(const sf::Vector2f &Center)
{
  m_Center = Center;
}

void RadialDistribution::SetRadius(float Radius)
{
  m_Radius = Radius;
}

CircularDistribution::CircularDistribution()
  : m_DistanceDistribution(0.f, 1.f)
{

}

CircularDistribution::CircularDistribution(const sf::Vector2f &Center, float Radius)
  : RadialDistribution(Center, Radius)
  , m_DistanceDistribution(0.f, 1.f)
{

}

sf::Vector2f CircularDistribution::operator()()
{
  auto dist = m_DistanceDistribution();
  auto angle = m_AngleDistribution();

  sf::Vector2f dir(std::cosf(angle), std::sinf(angle));
  
  return ( m_Center + dist * m_Radius * dir );
}

RectangularDistribution::RectangularDistribution(float left, float top, float width, float height)
  : m_Bounds(left, top, width, height)
  , m_XDirDist(left, left + width)
  , m_YDirDist(top, top + height)
{

}

sf::Vector2f RectangularDistribution::operator()()
{
  auto x = m_XDirDist();
  auto y = m_YDirDist();
}

void RectangularDistribution::SetBounds(float left, float top, float width, float height)
{
  m_Bounds = sf::FloatRect(left, top, width, height);

  m_XDirDist = UniformRealDistribution<float>(left, left + width);
  m_YDirDist = UniformRealDistribution<float>(top, top + height);
}

DirectionalDistribution::DirectionalDistribution()
{

}

DirectionalDistribution::DirectionalDistribution(float Angle, float Deviation)
  : m_Angle(Angle), m_Deviation(Deviation), m_DeviationDistribution(-Deviation, Deviation)
{

}

sf::Vector2f DirectionalDistribution::operator()()
{
  auto angle = m_Angle + m_DeviationDistribution();

  sf::Vector2f dir(std::cosf(angle), std::sinf(angle));
  return dir;
}

LineDistribution::LineDistribution()
  : m_DistanceDistribution(0.f, 1.f)
{

}

LineDistribution::LineDistribution(const sf::Vector2f &Start, const sf::Vector2f &End)
  : m_Start(Start), m_End(End), m_DistanceDistribution(0.f, 1.f)
{

}

sf::Vector2f LineDistribution::operator()()
{
  auto diff = m_End - m_Start;

  return ( m_Start + m_DistanceDistribution() * diff );
}

void LineDistribution::SetPoints(const sf::Vector2f &Start, const sf::Vector2f &End)
{
  m_Start = Start;
  m_End = End;
}
