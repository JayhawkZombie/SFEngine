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

#include <vector>
#include <SFML\Graphics.hpp>
#include <cassert>

struct RenderSettings {
  float Brightness;
  float Contrast;
  float Gamma;
  sf::Color BGClearColor = sf::Color::Black;
  int PostProcess;
  sf::Color HueShift;
  sf::RenderTexture *texture;
};

sf::FloatRect DefaultBounds();

void RenderText(const sf::Text *text);
void RenderText(const sf::Text *text, const sf::FloatRect &bounds);

void RenderVertices(const sf::VertexArray *arr);
void RenderVertices(const sf::VertexArray *arr, const sf::FloatRect &bounds);

void RenderShape(const sf::Shape *shape);
void RenderShape(const sf::Shape *shape, const sf::FloatRect &bounds);

void RenderSprite(const sf::Sprite *spr);
void RenderSprite(const sf::Sprite *spr, const sf::FloatRect &bounds);

void RenderSFDrawable(const sf::Drawable *drawable);
void RenderSFDrawable(const sf::Drawable *drawable, const sf::FloatRect &bounds);

void RenderVertexArrayVector(const std::vector<sf::VertexArray> &arr);

void RenderVertexArray(const sf::VertexArray &arr);

void SecondPassRender();
void ClearRender();

void __Set__Window(sf::RenderWindow *window);
void __Create__ViewPanel(const sf::FloatRect &bounds);
void __Set__Core__Shaders(sf::Shader *frag, sf::Shader *vert);
void __Set__Render__States(const sf::RenderStates &states);
void __Set__Render__Settings(const RenderSettings &settings);
