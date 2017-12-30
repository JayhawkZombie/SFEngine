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

#include "Weather\Lightning.h"

LightningBolt::LightningBolt()
  : m_BoltDoneFunc([]() {}), m_StrikeCallback([](auto v) {})
{
}

LightningBolt::~LightningBolt()
{
}

void LightningBolt::TickUpdate(const double & delta)
{
  UpdateBolt(delta);
}

void LightningBolt::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  if (m_IsAlive) {
    for (auto & seg : m_Points)
      Target->draw(seg);
  }
}


void LightningBolt::Spark(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition)
{
  m_IsAlive = true;
  m_Points.clear();
  m_currentFadeTime = 0.0;
  CreateBolt(StartPosition, EndPosition);
  alpha = 255;
}

bool LightningBolt::IsAlive() const
{
  return m_IsAlive;
}

void LightningBolt::SetDoneCallback(std::function<void(void)> Callback)
{
  m_BoltDoneFunc = Callback;
}

void LightningBolt::SetStrikeCallback(std::function<void(sf::Vector2f)> Callback)
{
  m_StrikeCallback = Callback;
}

void LightningBolt::Reset()
{
  m_currentFadeTime = 0.f;
  m_IsAlive = false;
  m_Points.clear();
}

void LightningBolt::SetColor(sf::Color color)
{
  m_Color = color;

  for (auto & seg : m_Points) {
    seg[0].color = color;
    seg[1].color = color;
  }
}

std::string LightningBolt::GetClass() const
{
  return std::string("LightningBolt");
}

void LightningBolt::UpdateBolt(const double &delta)
{
  if (!m_IsAlive) {
    return;
  }

  m_currentFadeTime += delta;

  if (m_currentFadeTime >= m_TotalFadeTime) {
    m_IsAlive = false;
    m_currentFadeTime = 0.0;
    alpha = 0;
  }
  else {
    alpha = (unsigned char)(floor(255 * (1 - (m_currentFadeTime / m_TotalFadeTime))));
    for (auto & seg : m_Points) {
      seg[0].color.a = alpha;
      seg[1].color.a = alpha;
    }
  }
}

void LightningBolt::CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition)
{
  sf::Vector2f Tangent = EndPosition - StartPosition;
  sf::Vector2f Normal = sf::Vector2f(Tangent.y, -Tangent.x);

  float mag = std::sqrt((Tangent.x * Tangent.x) + (Tangent.y * Tangent.y));
  Normal /= mag;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  sf::Vector2f DistanceVec = StartPosition - EndPosition;
  float Distance = std::sqrt((DistanceVec.x * DistanceVec.x) + (DistanceVec.y * DistanceVec.y));

  std::vector<float> Positions;
  Positions.push_back(0);
  for (std::size_t i = 0; i < (std::size_t)(std::round((Distance / 8))); ++i) {
    Positions.push_back(__TO_FLOAT__(dis(gen)));
  }

  std::sort(Positions.begin(), Positions.end());

  const float sway = 60;
  const float jaggedness = 1.f / sway;

  std::uniform_real_distribution<> _dis(-sway, sway);
  sf::Vector2f prevPoint = StartPosition;
  float prevDisplacement = 0.f;

  for (std::size_t i = 1; i < Positions.size(); ++i) {
    float pos = Positions[i];
    float scale = (Distance * jaggedness) * (pos - Positions[i - 1]);

    float envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

    float displ = __TO_FLOAT__(_dis(gen));
    displ -= (displ - prevDisplacement) * (1 - scale);
    displ *= envelope;

    sf::Vector2f postan = pos * Tangent;
    sf::Vector2f dispn = displ * Normal;

    sf::Vector2f point = StartPosition + postan + dispn;
    m_Points.push_back(sf::VertexArray(sf::Lines, 2));
    m_Points.back()[0].position = prevPoint; m_Points.back()[0].color = m_Color;
    m_Points.back()[1].position = point;     m_Points.back()[1].color = m_Color;

    prevPoint = point;
    prevDisplacement = displ;
  }

  m_Points.push_back(sf::VertexArray(sf::Lines, 2));
  m_Points.back()[0].position = prevPoint;   m_Points.back()[0].color = m_Color;
  m_Points.back()[1].position = EndPosition; m_Points.back()[1].color = m_Color;
}


/*
  Cawling lightning bolt
*/
CrawlingLightningBolt::CrawlingLightningBolt()
  : m_BoltDoneFunc([]() {}), m_StrikeCallback([](auto v) {})
{
    
}

CrawlingLightningBolt::~CrawlingLightningBolt()
{
}

void CrawlingLightningBolt::GenerateBoltPoints(const sf::Vector2f & Start, const sf::Vector2f & End, std::vector<sf::VertexArray> &m_Points)
{
  sf::Vector2f Tangent = End - Start;
  sf::Vector2f Normal = sf::Vector2f(Tangent.y, -Tangent.x);

  float mag = std::sqrt((Tangent.x * Tangent.x) + (Tangent.y * Tangent.y));
  Normal /= mag;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  sf::Vector2f DistanceVec = Start - End;
  float Distance = std::sqrt((DistanceVec.x * DistanceVec.x) + (DistanceVec.y * DistanceVec.y));

  std::vector<float> Positions;
  Positions.push_back(0);
  for (std::size_t i = 0; i < (std::size_t)(std::round((Distance / 8))); ++i) {
    Positions.push_back(__TO_FLOAT__(dis(gen)));
  }

  std::sort(Positions.begin(), Positions.end());

  const float sway = 15;
  const float jaggedness = 1.f / 50.f;

  std::uniform_real_distribution<> _dis(-sway, sway);
  sf::Vector2f prevPoint = Start;
  float prevDisplacement = 0.f;

  for (std::size_t i = 1; i < Positions.size(); ++i) {
    float pos = Positions[i];
    float scale = (Distance * jaggedness) * (pos - Positions[i - 1]);

    float envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

    float displ = __TO_FLOAT__(_dis(gen));
    displ -= (displ - prevDisplacement) * (1 - scale);
    displ *= envelope;

    sf::Vector2f postan = pos * Tangent;
    sf::Vector2f dispn = displ * Normal;

    sf::Vector2f point = Start + postan + dispn;
    m_Points.push_back(sf::VertexArray(sf::Lines, 2));
    m_Points.back()[0].position = prevPoint; m_Points.back()[0].color = sf::Color(255, 229, 255);
    m_Points.back()[1].position = point;     m_Points.back()[1].color = sf::Color(255, 229, 255);

    prevPoint = point;
    prevDisplacement = displ;
  }

  m_Points.push_back(sf::VertexArray(sf::Lines, 2));
  m_Points.back()[0].position = prevPoint;   m_Points.back()[0].color = sf::Color(255, 229, 255);
  m_Points.back()[1].position = End;         m_Points.back()[1].color = sf::Color(255, 229, 255);
}

void CrawlingLightningBolt::UpdateBolt(const double & delta)
{
  static float _delta_count = 0;
  _delta_count += (float)delta;

  if (_delta_count >= m_TimeBetweenCrawlSteps) {
    StepBolt(1);
    _delta_count = 0;
    if (m_DisplayedPoints.size() > m_MaxBoltLength)
      m_DisplayedPoints.erase(m_DisplayedPoints.begin() + 0);
  }
}

void CrawlingLightningBolt::CreateBolt(const sf::Vector2f & StartPosition, const sf::Vector2f & EndPosition)
{
  m_CrawlDir = EndPosition - StartPosition;
}

void CrawlingLightningBolt::StepBolt(int num_steps)
{
  if (m_Points.size() > 0) {
    int count = std::min(m_Points.size(), (std::size_t)num_steps);

    for (int i = 0; i < count; ++i) {
      m_DisplayedPoints.push_back(m_Points[0]);
      m_Points.erase(m_Points.begin() + 0);
    }
  }
  else if (m_DisplayedPoints.size() > 0) {
    //Now, then, I suppose we start erasing from the end of us here
    m_DisplayedPoints.erase(m_DisplayedPoints.begin() + 0);
  }
  else {
    m_IsAlive = false;
    m_DisplayedPoints.clear();
    m_Points.clear();
  }
}

void CrawlingLightningBolt::TickUpdate(const double & delta)
{
  UpdateBolt(delta);
}

void CrawlingLightningBolt::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  if (m_IsAlive) {
    for (auto & seg : m_DisplayedPoints)
      Target->draw(seg);
  }
}

void CrawlingLightningBolt::Spark(const std::vector<sf::Vector2f> &Positions)
{
  for (std::size_t i = 1; i < Positions.size(); ++i) {
    GenerateBoltPoints(Positions[i - 1], Positions[i], m_Points);
  }
  m_IsAlive = true;
}

bool CrawlingLightningBolt::IsAlive() const
{
  return m_IsAlive;
}

void CrawlingLightningBolt::SetDoneCallback(std::function<void(void)> Callback)
{
  m_BoltDoneFunc = Callback;
}

void CrawlingLightningBolt::SetStrikeCallback(std::function<void(sf::Vector2f)> Callback)
{
  m_StrikeCallback = Callback;
}

void CrawlingLightningBolt::Reset()
{
  m_IsAlive = false;
  m_currentFadeTime = 0.f;
  m_Points.clear();
  m_DisplayedPoints.clear();
}

void CrawlingLightningBolt::SetCrawlSpeed(const float & BetweenSteps)
{
  m_TimeBetweenCrawlSteps = BetweenSteps;
}

void CrawlingLightningBolt::SetMaxBoltLength(const float & Length)
{
  m_MaxBoltLength = Length;
}

std::string CrawlingLightningBolt::GetClass() const
{
  return std::string("CrawlingLightningBolt");
}
