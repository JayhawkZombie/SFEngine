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

#include "BasicIncludes.h"
#include "Physics\Occluder.h"
#include "Utils\RayCast.h"

#include "Level\LevelObject.h"

#define COSPIBY4 0.25

void _normalize(sf::Vector2f &v);

float VDot(const sf::Vector2f &v1, const sf::Vector2f &v2);

float DistanceBetween(const sf::Vector2f &a, const sf::Vector2f &b);
  
class LightSource
{
public:
  LightSource();

  LightSource(const LightSource &light);

  ~LightSource() = default;

  SVector2F m_Position;
  SFLOAT m_Attenuation;
  SFLOAT m_Intensity;
  sf::Color m_Hue;
  std::string m_Name;
  sf::CircleShape m_OutlinedCircleArea;
  sf::Sprite m_LightSprite;
};

class LightSystem
{
public:
  LightSystem();
  ~LightSystem();

  void Update(std::map<std::string, SPtrShared<LevelObject>>& Objects);
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture, sf::View View);

  void AddLight(sf::Vector2f Pos, float Atten, sf::Color Color, std::string Name);

protected:

  void CreateLightTexture(const LightSource &lht);

  bool m_DrawTriangles = true;
  bool m_DrawLines = false;

  /* We can have one shadow map per light source */
  std::map<std::string, sf::VertexArray> m_LightRegions;
  std::map<std::string, sf::VertexArray> m_DarkRegions;
    
  //std::vector<::vec2d> m_LightRegions;
  //std::vector<::vec2d> m_DarkRegions;
  sf::RenderStates RenderState;
  sf::Texture m_RadialLightTexture;

  std::vector<SPtrShared<Collider2D>> m_MapDrawn;

  std::shared_ptr<sf::RenderTexture> m_MapTexture;

  std::map<std::string, std::shared_ptr<LightSource>> m_Lights;
  std::map<std::string, SPtrShared<sf::RenderTexture>> m_LightTextures;
  sf::Shader m_BlendingShader;
    
  sf::Shader m_LightShader;
  sf::Shader m_BlendVertexShader;
  sf::Shader m_BlendFragmentShader;
};
