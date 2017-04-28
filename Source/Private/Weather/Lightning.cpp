////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "Weather\Lightning.h"
#include "Globals.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <random>

/************************************************************************/
/*                          Lightning                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  LightningBolt::LightningBolt()
    : m_BoltDoneFunc([]() {}), m_StrikeCallback([](auto v) {})
  {
  }

  LightningBolt::~LightningBolt()
  {
  }

  void LightningBolt::TickUpdate(const SFLOAT & delta)
  {
    UpdateBolt(delta);
  }

  void LightningBolt::Render(SharedRTexture Target)
  {
    if (m_IsAlive) {
      for (auto & seg : m_Points)
        Target->draw(seg);
    }
  }


  void LightningBolt::Spark(const SVector2F &StartPosition, const SVector2F &EndPosition)
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

  void LightningBolt::SetStrikeCallback(std::function<void(SVector2F)> Callback)
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

  void LightningBolt::UpdateBolt(const SFLOAT &delta)
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

  void LightningBolt::CreateBolt(const SVector2F &StartPosition, const SVector2F &EndPosition)
  {
    SVector2F Tangent = EndPosition - StartPosition;
    SVector2F Normal = SVector2F(Tangent.y, -Tangent.x);

    SFLOAT mag = std::sqrt((Tangent.x * Tangent.x) + (Tangent.y * Tangent.y));
    Normal /= mag;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    SVector2F DistanceVec = StartPosition - EndPosition;
    SFLOAT Distance = std::sqrt((DistanceVec.x * DistanceVec.x) + (DistanceVec.y * DistanceVec.y));

    STDVector<SFLOAT> Positions;
    Positions.push_back(0);
    for (std::size_t i = 0; i < (int)(Distance / 8); ++i) {
      Positions.push_back(SF_TOFLOAT(dis(gen)));
    }

    std::sort(Positions.begin(), Positions.end());

    const SFLOAT sway = 60;
    const SFLOAT jaggedness = 1.f / sway;

    std::uniform_real_distribution<> _dis(-sway, sway);
    SVector2F prevPoint = StartPosition;
    SFLOAT prevDisplacement = 0.f;

    for (std::size_t i = 1; i < Positions.size(); ++i) {
      SFLOAT pos = Positions[i];
      SFLOAT scale = (Distance * jaggedness) * (pos - Positions[i - 1]);

      SFLOAT envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

      SFLOAT displ = SF_TOFLOAT(_dis(gen));
      displ -= (displ - prevDisplacement) * (1 - scale);
      displ *= envelope;

      SVector2F postan = pos * Tangent;
      SVector2F dispn = displ * Normal;

      SVector2F point = StartPosition + postan + dispn;
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

  void CrawlingLightningBolt::GenerateBoltPoints(const SVector2F & Start, const SVector2F & End, STDVector<sf::VertexArray> &m_Points)
  {
    SVector2F Tangent = End - Start;
    SVector2F Normal = SVector2F(Tangent.y, -Tangent.x);

    SFLOAT mag = std::sqrt((Tangent.x * Tangent.x) + (Tangent.y * Tangent.y));
    Normal /= mag;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    SVector2F DistanceVec = Start - End;
    SFLOAT Distance = std::sqrt((DistanceVec.x * DistanceVec.x) + (DistanceVec.y * DistanceVec.y));

    STDVector<SFLOAT> Positions;
    Positions.push_back(0);
    for (std::size_t i = 0; i < (int)(Distance / 8); ++i) {
      Positions.push_back(SF_TOFLOAT(dis(gen)));
    }

    std::sort(Positions.begin(), Positions.end());

    const SFLOAT sway = 15;
    const SFLOAT jaggedness = 1.f / 50.f;

    std::uniform_real_distribution<> _dis(-sway, sway);
    SVector2F prevPoint = Start;
    SFLOAT prevDisplacement = 0.f;

    for (std::size_t i = 1; i < Positions.size(); ++i) {
      SFLOAT pos = Positions[i];
      SFLOAT scale = (Distance * jaggedness) * (pos - Positions[i - 1]);

      SFLOAT envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

      SFLOAT displ = SF_TOFLOAT(_dis(gen));
      displ -= (displ - prevDisplacement) * (1 - scale);
      displ *= envelope;

      SVector2F postan = pos * Tangent;
      SVector2F dispn = displ * Normal;

      SVector2F point = Start + postan + dispn;
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

  void CrawlingLightningBolt::UpdateBolt(const SFLOAT & delta)
  {
    static SFLOAT _delta_count = 0;
    _delta_count += (SFLOAT)delta;

    if (_delta_count >= m_TimeBetweenCrawlSteps) {
      StepBolt(1);
      _delta_count = 0;
      if (m_DisplayedPoints.size() > m_MaxBoltLength)
        m_DisplayedPoints.erase(m_DisplayedPoints.begin() + 0);
    }
  }

  void CrawlingLightningBolt::CreateBolt(const SVector2F & StartPosition, const SVector2F & EndPosition)
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

  void CrawlingLightningBolt::TickUpdate(const SFLOAT & delta)
  {
    UpdateBolt(delta);
  }

  void CrawlingLightningBolt::Render(SharedRTexture Target)
  {
    if (m_IsAlive) {
      for (auto & seg : m_DisplayedPoints)
        Target->draw(seg);
    }
  }

  void CrawlingLightningBolt::Spark(const STDVector<SVector2F> &Positions)
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

  void CrawlingLightningBolt::SetStrikeCallback(std::function<void(SVector2F)> Callback)
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

  void CrawlingLightningBolt::SetCrawlSpeed(const SFLOAT & BetweenSteps)
  {
    m_TimeBetweenCrawlSteps = BetweenSteps;
  }

  void CrawlingLightningBolt::SetMaxBoltLength(const SFLOAT & Length)
  {
    m_MaxBoltLength = Length;
  }

  std::string CrawlingLightningBolt::GetClass() const
  {
    return std::string("CrawlingLightningBolt");
  }

} // namespace SFEngine
