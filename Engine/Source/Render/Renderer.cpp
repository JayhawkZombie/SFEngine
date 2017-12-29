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

#include "Render\Render.h"
#include "Lights\GlobalLightSource.h"

#include <iostream>

namespace
{
  sf::RenderWindow *DrawWindow = nullptr;
  sf::Sprite renderSprite;
  std::vector<sf::Shader *> PostProcessShaders;
  sf::Vector2u WinSize;
  sf::FloatRect ViewPanel;
  sf::RenderStates RenderStates;
  sf::View view;
  sf::Shader *FragmentShader;
  sf::Shader *VertexShader;
  RenderSettings CoreRenderSettings;
  GlobalLightSource GlobalLight;
  std::shared_ptr<sf::Mutex> Mutex;
}

sf::FloatRect DefaultBounds()
{
  return sf::FloatRect(0.f, 0.f, static_cast<float>(WinSize.x), static_cast<float>(WinSize.y));
}

void RenderText(const sf::Text *text)
{
  RenderText(text, DefaultBounds());
}

void RenderText(const sf::Text *text, const sf::FloatRect &bounds)
{
  RenderSFDrawable(text, bounds);
}

void RenderVertices(const sf::VertexArray *arr)
{
  RenderVertices(arr, DefaultBounds());
}

void RenderVertices(const sf::VertexArray *arr, const sf::FloatRect &bounds)
{
  RenderSFDrawable(arr, bounds);
}

void RenderShape(const sf::Shape *shape)
{
  RenderShape(shape, DefaultBounds());
}

void RenderShape(const sf::Shape *shape, const sf::FloatRect &bounds)
{
  RenderSFDrawable(shape, bounds);
}

void RenderSprite(const sf::Sprite *spr)
{
  RenderSprite(spr, DefaultBounds());
}

void RenderSprite(const sf::Sprite *spr, const sf::FloatRect &bounds)
{
  RenderSFDrawable(spr, bounds);
}

void RenderSFDrawable(const sf::Drawable *drawable)
{
  RenderSFDrawable(drawable, DefaultBounds());
}

//void RenderLightingArray(const std::vector<sf::VertexArray> &arr, sf::RenderStates &state)
//{
//  Mutex->lock();

//  sf::FloatRect bounds = DefaultBounds();

//  if (DrawWindow) {
//    __Create__ViewPanel(bounds);

//    ViewPanel = sf::FloatRect(
//      bounds.left / WinSize.x,
//      bounds.top / WinSize.y,
//      bounds.width / WinSize.x,
//      bounds.height / WinSize.y
//    );

//    view.reset(bounds);
//    view.setViewport(ViewPanel);

//    CoreRenderSettings.texture->setActive(true);
//    CoreRenderSettings.texture->setView(view);
//    for (auto & v : arr)
//      CoreRenderSettings.texture->draw(v, state);

//    CoreRenderSettings.texture->setView(CoreRenderSettings.texture->getDefaultView());
//  }

//  Mutex->unlock();
//}

void RenderSFDrawable(const sf::Drawable *drawable, const sf::FloatRect &bounds)
{
  Mutex->lock();


  if (DrawWindow) {
    __Create__ViewPanel(bounds);

    ViewPanel = sf::FloatRect(
      bounds.left / WinSize.x,
      bounds.top / WinSize.y,
      bounds.width / WinSize.x,
      bounds.height / WinSize.y
    );

    view.reset(bounds);
    view.setViewport(ViewPanel);

    CoreRenderSettings.texture->setActive(true);
    CoreRenderSettings.texture->setView(view);
    CoreRenderSettings.texture->draw(*drawable);
    CoreRenderSettings.texture->setView(CoreRenderSettings.texture->getDefaultView());
  }

  Mutex->unlock();
}

void RenderVertexArray(const sf::VertexArray &arr)
{
  Mutex->lock();

  CoreRenderSettings.texture->setActive(true);
  CoreRenderSettings.texture->draw(arr);

  Mutex->unlock();
}

void RenderVertexArrayVector(const std::vector<sf::VertexArray>& arr)
{
  Mutex->lock();

  CoreRenderSettings.texture->setActive(true);
  for (auto & vert : arr)
    CoreRenderSettings.texture->draw(vert);

  Mutex->unlock();
}

void ClearRender()
{
  CoreRenderSettings.texture->setActive(true);
  CoreRenderSettings.texture->clear();
}

void SecondPassRender()
{
  //Now that every has been drawn to a render texture, draw that one huge texture
  CoreRenderSettings.texture->setActive(true);
  CoreRenderSettings.texture->display();

  FragmentShader->setUniform("BRIGHTNESS", CoreRenderSettings.Brightness);
  FragmentShader->setUniform("CONTRAST", CoreRenderSettings.Contrast);
  FragmentShader->setUniform("SCENE", sf::Shader::CurrentTexture);
  FragmentShader->setUniform("GAMMA", CoreRenderSettings.Gamma);
  FragmentShader->setUniform("POST_PROCESS_EFFECT", CoreRenderSettings.PostProcess);

  FragmentShader->setUniform("GLOBAL_LIGHT", sf::Glsl::Vec4(GlobalLight.GetColor()));
  FragmentShader->setUniform("GLOBAL_LIGHT_INTENSITY", 100.f);

  sf::Sprite spr(CoreRenderSettings.texture->getTexture());

  DrawWindow->draw(spr, FragmentShader);
}

void __Set__Window(sf::RenderWindow *window)
{
  DrawWindow = window;
  if (DrawWindow) {
    WinSize = DrawWindow->getSize();
  }

  assert(DrawWindow);
}


void __Create__ViewPanel(const sf::FloatRect &bounds)
{
  ViewPanel = sf::FloatRect(
    bounds.left / WinSize.x,
    bounds.top / WinSize.y,
    bounds.width / WinSize.x,
    bounds.height / WinSize.y
  );

  view.reset(bounds);
  view.setViewport(ViewPanel);
}

void __Set__Core__Shaders(sf::Shader *frag, sf::Shader *vert)
{
  VertexShader = vert;
  FragmentShader = frag;

}

void __Set__Render__States(const sf::RenderStates &states)
{
  RenderStates = states;
  if (!Mutex)
    Mutex = std::shared_ptr<sf::Mutex>(new sf::Mutex);
}

void __Set__Render__Settings(const RenderSettings &settings)
{
  CoreRenderSettings.Brightness = settings.Brightness;
  CoreRenderSettings.Contrast = settings.Contrast;
  CoreRenderSettings.HueShift = settings.HueShift;
  CoreRenderSettings.texture = settings.texture;
  CoreRenderSettings.Gamma = settings.Gamma;
  CoreRenderSettings.PostProcess = settings.PostProcess;
}
  