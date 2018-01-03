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

#include "Objects/GameObject.h"

class LightningBolt : public GameObject
{
public:
  TYPEDEF_PARENT_CLASS(GameObject);

  LightningBolt();
  ~LightningBolt();

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;

  void Spark(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
  bool IsAlive() const;
  void SetDoneCallback(std::function<void(void)> Callback);
  void SetStrikeCallback(std::function<void(sf::Vector2f)> Callback);
  void Reset();
  void SetColor(sf::Color color);
  std::string GetClass() const override;

protected:
  std::function<void(sf::Vector2f)> m_StrikeCallback;
  std::function<void(void)> m_BoltDoneFunc;
  void UpdateBolt(const double &delta);
  void CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
  sf::Color m_Color        = sf::Color::White;
  bool   m_IsAlive         = false;
  float  m_SparkSpeed      = 1.f;
  double m_currentFadeTime = 0.0;
  double m_TotalFadeTime   = 400.0;
  unsigned char alpha      = 255;
  std::vector<sf::VertexArray> m_Points;
};

class CrawlingLightningBolt : public GameObject
{
public:
  TYPEDEF_PARENT_CLASS(GameObject);

  CrawlingLightningBolt();
  ~CrawlingLightningBolt();

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;

  void Spark(const std::vector<sf::Vector2f> &Positions);
  bool IsAlive() const;
  void SetDoneCallback(std::function<void(void)> Callback);
  void SetStrikeCallback(std::function<void(sf::Vector2f)> Callback);
  void Reset();

  void SetCrawlSpeed(const float &BetweenSteps);
  void SetMaxBoltLength(const float &Length);
  std::string GetClass() const override;

protected:
  float m_TimeBetweenCrawlSteps = 3.f;
  float m_MaxBoltLength         = 1000.f;

  std::function<void(sf::Vector2f)> m_StrikeCallback;
  std::function<void(void)> m_BoltDoneFunc;

  static void GenerateBoltPoints(const sf::Vector2f &Start, const sf::Vector2f &End, std::vector<sf::VertexArray> &m_Points);

  void UpdateBolt(const double &delta);
  void CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
  void StepBolt(int num_steps);

  sf::Vector2f m_CrawlDir;
  std::vector<float> m_Positions;
  float m_Sway = 40.f;
  float m_Jaggedness = 1.f / 90.f;
  float m_PrevDisplacement = 0.f;
  bool   m_IsAlive         = false;
  float  m_SparkSpeed      = 1.f;
  double m_currentFadeTime = 0.0;
  double m_TotalFadeTime   = 900.0;
  unsigned char alpha      = 255;
  std::vector<sf::VertexArray> m_Points;
  std::vector<sf::VertexArray> m_DisplayedPoints;
};
