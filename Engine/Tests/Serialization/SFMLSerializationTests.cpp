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

#include "SFMLSerializationTests.h"


extern void RunSFMLSerializationTests()
{
  /*
   *  Test1 - serialize a rectangle and load it back
   **/

  /* Let's use random data for tests */

  std::default_random_engine engine;
  std::uniform_real_distribution<float> dist(0.f, 200.f);

  std::uniform_int_distribution<int> int_dist(10, 157);

  sf::RectangleShape rect;

  rect.setPosition(sf::Vector2f(dist(engine), dist(engine)));
  rect.setRotation(dist(engine));
  rect.setScale(sf::Vector2f(dist(engine), dist(engine)));
  rect.setSize(sf::Vector2f(dist(engine), dist(engine)));
  rect.setOrigin(sf::Vector2f(dist(engine), dist(engine)));
  rect.setTextureRect(sf::IntRect(int_dist(engine), int_dist(engine), int_dist(engine), int_dist(engine)));
  rect.setFillColor(sf::Color(int_dist(engine), int_dist(engine), int_dist(engine), int_dist(engine)));
  rect.setOutlineColor(sf::Color(int_dist(engine), int_dist(engine), int_dist(engine), int_dist(engine)));
  rect.setOutlineThickness(dist(engine));

  /* Create output file & serialize rect */
  std::ofstream ofile("rect.bin", std::ios_base::binary);

  {
    cereal::PortableBinaryOutputArchive archive(ofile);
    archive(rect);
  }
  ofile.close();

  /* Create a new rect and load it from the serialized file we just made */

  sf::RectangleShape newrect;

  std::ifstream ifile("rect.bin", std::ios_base::binary);

  {
    cereal::PortableBinaryInputArchive archive(ifile);
    archive(newrect);
  }
  ifile.close();

  /*
   *  Verify loaded data matches the data for the original rect
   **/

  auto pos = newrect.getPosition();
  auto size = newrect.getSize();
  auto scale = newrect.getScale();
  auto origin = newrect.getOrigin();
  auto fillcolor = newrect.getFillColor();
  auto outlinecolor = newrect.getOutlineColor();
  auto outlinethk = newrect.getOutlineThickness();
  auto rot = newrect.getRotation();
  auto texrect = newrect.getTextureRect();

  std::cout << "pos   : (" << rect.getPosition().x << ", " << rect.getPosition().y << ") ==? (" << pos.x    << ", " << pos.y    << ")\n";
  std::cout << "size  : (" << rect.getSize().x     << ", " << rect.getSize().y     << ") ==? (" << size.x   << ", " << size.y   << ")\n";
  std::cout << "scale : (" << rect.getScale().x    << ", " << rect.getScale().y    << ") ==? (" << scale.x  << ", " << scale.y  << ")\n";
  std::cout << "origin: (" << rect.getOrigin().x   << ", " << rect.getOrigin().y   << ") ==? (" << origin.x << ", " << origin.y << ")\n";
  std::cout << "fill  : (" << rect.getFillColor().r << ", " << rect.getFillColor().g << ", " << rect.getFillColor().b << ", " << rect.getFillColor().a << ") == ? ("
    << fillcolor.r << ", " << fillcolor.g << ", " << fillcolor.b << ", " << fillcolor.a << ")\n";
  std::cout << "out   : (" << rect.getOutlineColor().r << ", " << rect.getOutlineColor().g << ", " << rect.getOutlineColor().b << ", " << rect.getOutlineColor().a << ") ==? ("
    << outlinecolor.r << ", " << outlinecolor.g << ", " << outlinecolor.b << ", " << outlinecolor.a << ")\n";
  std::cout << "outthk: " << rect.getOutlineThickness() << " ==? " << outlinethk << "\n";
  std::cout << "rot   : " << rect.getRotation() << " ==? " << rot << "\n";
  std::cout << "texrct: (" << rect.getTextureRect().left << ", " << rect.getTextureRect().top << ", " << rect.getTextureRect().width << ", " << rect.getTextureRect().height << ") ==? ("
    << texrect.left << ", " << texrect.top << ", " << texrect.width << ", " << texrect.height << ")\n";
}
