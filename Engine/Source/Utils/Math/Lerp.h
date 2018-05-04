#pragma once

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2018 Kurt Slagle - kurt_slagle@yahoo.com
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

#include <type_traits>
#include <SFML/Graphics.hpp>

namespace Math
{

  template<typename T>
  inline float Lerp(const T &first, const T &second, float alpha)
  {
    if constexpr (std::is_floating_point_v<T>)
    {
      return (first + alpha * (second - first));
    }
    else
    {
      const float f_first = static_cast< float >(first);
      const float f_second = static_cast< float >(second);

      return (f_first + alpha * (f_second - f_first));
    }
  }

  template<typename T>
  inline float Lerp(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2, float alpha)
  {
    if constexpr (std::is_floating_point_v<T>)
    {
      return (v1 + alpha * (v2 - v1));
    }
    else
    {
      const sf::Vector2f f_v1 = static_cast< sf::Vector2f >(v1);
      const sf::Vector2f f_v2 = static_cast< sf::Vector2f >(v2);

      return (f_v1 + alpha * (f_v2 - f_v1));
    }
  }

  template<typename T>
  inline float Lerp(const sf::Vector3<T> &v1, const sf::Vector3<T> &v2, float alpha)
  {
    if constexpr (std::is_floating_point_v<T>)
    {
      return (v1 + alpha * (v2 - v1));
    }
    else
    {
      const sf::Vector2f f_v1 = static_cast< sf::Vector2f >(v1);
      const sf::Vector2f f_v2 = static_cast< sf::Vector2f >(v2);

      return (f_v1 + alpha * (f_v2 - f_v1));
    }
  }

  sf::Color Lerp(const sf::Color &c1, const sf::Color &c2, float alpha)
  {
    const float r1 = static_cast< float >(c1.r);
    const float g1 = static_cast< float >(c1.g);
    const float b1 = static_cast< float >(c1.b);
    const float a1 = static_cast< float >(c1.a);

    const float r2 = static_cast< float >(c2.r);
    const float g2 = static_cast< float >(c2.g);
    const float b2 = static_cast< float >(c2.b);
    const float a2 = static_cast< float >(c2.a);

    const float lr = Lerp(r1, r2, alpha);
    const float lg = Lerp(g1, g2, alpha);
    const float lb = Lerp(b1, b2, alpha);
    const float la = Lerp(a1, a2, alpha);

    sf::Color clerp;
    clerp.r = static_cast< sf::Uint8 >(lr);
    clerp.g = static_cast< sf::Uint8 >(lg);
    clerp.b = static_cast< sf::Uint8 >(lb);
    clerp.a = static_cast< sf::Uint8 >(la);

    return clerp;
  }

}
