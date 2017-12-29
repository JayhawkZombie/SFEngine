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

#include "Utils\Decoders.h"

namespace Decode
{

  std::shared_ptr<sf::Image> Image(std::ifstream &in)
  {
    //get the size of the image
    sf::Vector2u size;
    in.read((char *)(&size.x), sizeof(size.x));
    in.read((char *)(&size.y), sizeof(size.y));

    std::shared_ptr<sf::Image> image(new sf::Image);
    image->create(size.x, size.y);

    //now read in the actual image
    sf::Color PixelColor;
    for (std::size_t y = 0; y < size.y; ++y) {
      for (std::size_t x = 0; x < size.x; ++x) {
        PixelColor = Decode::Color(in);
        image->setPixel(x, y, PixelColor);
      }
    }

    return image;
  }

  sf::Vector2f Vector2f(std::ifstream &in)
  {
    sf::Vector2f f{ 0, 0 };
    in.read((char *)(&f.x), sizeof(f.x));
    in.read((char *)(&f.y), sizeof(f.y));

    return f;
  }

  std::string String(std::ifstream &in)
  {
    std::size_t strl{ 0 };
    std::string str{ "" };

    in.read((char *)(&strl), sizeof(strl));
    str.resize(strl);
    in.read(&str[0], strl);
    return str;
  }

  sf::Color Color(std::ifstream & in)
  {
    sf::Color c{ 0,0,0 };
    in.read((char *)(&c.r), sizeof(c.r));
    in.read((char *)(&c.g), sizeof(c.g));
    in.read((char *)(&c.b), sizeof(c.b));
    in.read((char *)(&c.a), sizeof(c.a));

    return c;
  }

}
