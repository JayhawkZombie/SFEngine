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

#include <SFML/Graphics.hpp>

namespace Math
{

  template<typename T>
  T Dot(const sf::Vector2<T> & V1, const sf::Vector2<T> &V2)
  {
    return ( V1.x * V2.x + V1.y * V2.y );
  }

  template<typename T>
  float Mag(const sf::Vector2<T> &Vector)
  {
    return std::hypot(Vector.x, Vector.y);
  }

  template<typename T>
  void Normalize(sf::Vector2<T> &Vector)
  {
    auto m = Mag(Vector);

    if (m > std::numeric_limits<float>::epsilon())
      Vector /= m;
  }

  template<typename T>
  float ScalarProject(const sf::Vector2<T> &a, const sf::Vector2<T> &b)
  {
    const auto d = Dot(a, b);

    return ( d / Mag(b) );
  }

  template<typename T>
  sf::Vector2f VectorProject(const sf::Vector2<T> &a, const sf::Vector2<T> & b)
  {
    const auto scalarP = ScalarProject(a, b);

    const auto vec = b;
    Normalize(vec);

    return ( scalarP * vec );
  }

}
