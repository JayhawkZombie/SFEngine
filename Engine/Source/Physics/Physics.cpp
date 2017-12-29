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

#include <SFML\Graphics.hpp>

namespace
{

  sf::Vector2f __i = sf::Vector2f(1, 0);
  sf::Vector2f __j = sf::Vector2f(0, 1);
  float __eps = 1E-4f;
}

bool BoxesOverlap(const sf::FloatRect &FR1, const sf::FloatRect &FR2)
{
  return(FR1.intersects(FR2));
}

sf::Vector2f PointOfIntersection(const sf::Vector2f start, const sf::Vector2f end, const sf::Vector2f &P1, const sf::Vector2f &P2)
{
  sf::Vector2f u = end - start;
  sf::Vector2f v = P2 - P1;
  sf::Vector2f w = P1 - start;

  float s = (v.y * w.x - v.x * w.y) / (v.x * u.y - v.y * u.x);
  return sf::Vector2f(start + s * u);
}

float Dot(const sf::Vector2f &a, const sf::Vector2f &b)
{
  return (a.x * b.x + a.y * a.y);
}

unsigned int Dot(const sf::Vector2u &a, const sf::Vector2u &b)
{
  return (a.x * b.x + a.y * a.y);
}

int Dot(const sf::Vector2i &a, const sf::Vector2i &b)
{
  return (a.x * b.x + a.y * a.y);
}

float Mag(const sf::Vector2f &a)
{
  return std::sqrt(a.x * a.x + a.y * a.y);
}

float Mag(const sf::Vector2u &a)
{
  return static_cast< float >(std::sqrt(a.x * a.x + a.y * a.y));
}

float Mag(const sf::Vector2i &a)
{
  return static_cast< float >(std::sqrt(a.x * a.x + a.y * a.y));
}
