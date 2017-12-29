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

#include <SFML\Graphics.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace Encode
{

  const std::size_t EncodeBit[8] = { 
    0b010000000, 
    0b001000000, 
    0b000100000, 
    0b000010000, 
    0b000001000, 
    0b000000100, 
    0b000000010, 
    0b000000001 
  };

  void Image(const sf::Image &image, std::ofstream &out);

  template<typename T>
  void Rect(const sf::Rect<T> &rect, std::ofstream &out)
  {
    out.write((char *)(&rect.left), sizeof(rect.left));
    out.write((char *)(&rect.top), sizeof(rect.top));
    out.write((char *)(&rect.width), sizeof(rect.width));
    out.write((char *)(&rect.height), sizeof(rect.height));
  }
   
  template<typename T>
  void Vector2(const sf::Vector2<T> &vec, std::ofstream &out)
  {
    out.write((char *)(&vec.x), sizeof(vec.x));
    out.write((char *)(&vec.y), sizeof(vec.y));
  }

  void String(const std::string &str, std::ofstream &out);
  void Color(const sf::Color &c, std::ofstream &out);

}
