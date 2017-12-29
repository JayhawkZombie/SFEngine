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

#include "Level\Level.h"
#include "Engine\Console.h"
#include "Physics\Collider.h"

void Level::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  //SceneBlendTexture->clear(sf::Color::Transparent);

  Texture->draw(*TileMap);

  if (ShowGridLines) {
    for (auto & arr : GridLines)
      Texture->draw(arr);
  }

  for (auto & obj : LevelObjects)
    Texture->draw(obj.second->Sprite);

  //If we are using the editor, draw the meshes too
  //Make this configurable later
#ifdef WITH_EDITOR
  BasicLevel::RenderEditorUI(Texture);
#endif
}

void Level::Render(std::shared_ptr<sf::RenderTarget> Target)
{

}

std::string Level::GetClass() const
{
  return std::string("Level");
}

void Level::RenderRegular()
{

}

void Level::RenderLoadingScreen()
{

}
