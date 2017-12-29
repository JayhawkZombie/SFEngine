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

#include "Utils\Encoders.h"

namespace Encode
{

  void Image(const sf::Image &image, std::ofstream &out)
  {
    //write the size of the image
    auto size = image.getSize();
    Encode::Vector2<>(size, out);
    //out.write((char *)(&size.x), sizeof(size.x));
    //out.write((char *)(&size.y), sizeof(size.y));

    //write out the image itself
    sf::Color PixelColor;
    for (std::size_t y = 0; y < size.y; ++y) {
      for (std::size_t x = 0; x < size.x; ++x) {
        PixelColor = image.getPixel(x, y);
        Encode::Color(PixelColor, out);
      }
    }
  }

  void String(const std::string &str, std::ofstream &out)
  {
    std::size_t strl = str.length();
    out.write((char *)(&strl), sizeof(strl));
    out.write(str.c_str(), strl);
  }

  void Color(const sf::Color & c, std::ofstream & out)
  {
    out.write((char *)(&c.r), sizeof(c.r));
    out.write((char *)(&c.g), sizeof(c.g));
    out.write((char *)(&c.b), sizeof(c.b));
    out.write((char *)(&c.a), sizeof(c.a));
  }

}
