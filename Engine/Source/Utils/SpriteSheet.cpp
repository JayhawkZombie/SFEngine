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

#include "Utils\SpriteSheet.h"

SpriteSheet::SpriteSheet()
  : TextureHeight(0), TextureWidth(0)
{

}

SpriteSheet::SpriteSheet(const SpriteSheet &copy)
{

}

SpriteSheet::~SpriteSheet()
{
  for (auto & spr : Sprites)
    spr.reset();
}

void SpriteSheet::SerializeIn(std::ifstream &in)
{

}

void SpriteSheet::SerializeOut(std::ofstream &out)
{
  //write out the texture itself
  sf::Image image = Texture->copyToImage();
  Encode::Image(image, out);

  //write out the number of frames in the image
  std::size_t framecnt{ 0 };
  framecnt = Frames.size();
  out.write((char *)(&framecnt), sizeof(framecnt));

  //write out each of the frames
  for (auto & frame : Frames)
    Encode::Rect<>(frame, out);
}

void SpriteSheet::SetTexture(SharedTexture tex)
{
  Texture = tex;

  TextureHeight = tex->getSize().y;
  TextureWidth = tex->getSize().x;
}

std::shared_ptr<sf::Sprite> SpriteSheet::GetSprite(std::size_t index)
{
  if (index < Sprites.size())
    return Sprites[index];

  throw EngineRuntimeError({ ExceptionCause::InvalidObjectUsed }, EXCEPTION_MESSAGE("Sprite index out of boudns"));
}

SharedTexture SpriteSheet::GetTexture() const
{
  return Texture;
}

void SpriteSheet::AddFrame(const sf::IntRect &frame)
{
  Frames.push_back(frame);
}

void SpriteSheet::EvenlyDivideFrames(std::uint32_t frameWidth, std::uint32_t frameHeight)
{
  //Get the # of frames wide
  std::uint32_t NumFramesWide = TextureWidth / frameWidth;
  std::uint32_t NumFramesHigh = TextureHeight / frameHeight;

  for (std::uint32_t i = 0; i < NumFramesWide; ++i) {
    for (std::uint32_t j = 0; j < NumFramesHigh; ++j) {
      sf::IntRect rect;

      rect.left = i * frameWidth;
      rect.top = j * frameHeight;
      rect.height = frameHeight;
      rect.width = frameWidth;

      Frames.push_back(rect);
    } //for j = 0 -> NumFramesHigh
  } //for i = 0 -> NumFramesWide

  //For each of those frames, create a sprite
  for (auto & frame : Frames) {

    Sprites.push_back(std::shared_ptr<sf::Sprite>(new sf::Sprite));
    Sprites.back()->setTexture(*Texture);
    Sprites.back()->setTextureRect(frame);
  }
}
