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

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include <SFML\Graphics.hpp>

namespace Decode
{

  std::shared_ptr<sf::Image> Image(std::ifstream &in);
  template<typename T>
  sf::Rect<T> Rect(std::ifstream &in)
  {
    sf::Rect<T> rect{ 0,0,0,0 };
    in.read((char *)(&rect.left), sizeof(rect.left));
    in.read((char *)(&rect.top), sizeof(rect.top));
    in.read((char *)(&rect.width), sizeof(rect.width));
    in.read((char *)(&rect.height), sizeof(rect.height));

    return rect;
  }

  template<typename T>
  sf::Vector2<T> Vector2(std::ifstream &in)
  {
    sf::Vector2<T> rect{ 0, 0 };
    in.read((char *)(&rect.x), sizeof(rect.x));
    in.read((char *)(&rect.y), sizeof(rect.y));

    return rect;
  }
  sf::Vector2f Vector2f(std::ifstream &in);
  std::string String(std::ifstream &in);
  sf::Color Color(std::ifstream &in);

}
