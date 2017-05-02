#ifndef SFEngine_Lightning_H
#define SFEngine_Lightning_H

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
#include "BasicIncludes.h"
#include "Objects\GameObject.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                          Lightning                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  class LightningBolt : public GameObject
  {
  public:
    LightningBolt();
    ~LightningBolt();

    void TickUpdate(const SFLOAT &delta) override;
    void Render(SFLOAT Alpha, SharedRTexture Target) override;

    void Spark(const SVector2F &StartPosition, const SVector2F &EndPosition);
    bool IsAlive() const;
    void SetDoneCallback(std::function<void(void)> Callback);
    void SetStrikeCallback(std::function<void(SVector2F)> Callback);
    void Reset();
    void SetColor(sf::Color color);
    SString GetClass() const override;

  protected:
    std::function<void(SVector2F)> m_StrikeCallback;
    std::function<void(void)> m_BoltDoneFunc;
    void UpdateBolt(const SFLOAT &delta);
    void CreateBolt(const SVector2F &StartPosition, const SVector2F &EndPosition);
    sf::Color m_Color = sf::Color::White;
    bool   m_IsAlive = false;
    float  m_SparkSpeed = 1.f;
    SFLOAT m_currentFadeTime = 0.0;
    SFLOAT m_TotalFadeTime = 400.0;
    unsigned char alpha = 255;
    std::vector<sf::VertexArray> m_Points;
  };

  class CrawlingLightningBolt : public GameObject
  {
  public:
    CrawlingLightningBolt();
    ~CrawlingLightningBolt();

    void TickUpdate(const SFLOAT &delta) override;
    void Render(SFLOAT Alpha, SharedRTexture Target) override;

    void Spark(const STDVector<SVector2F> &Positions);
    bool IsAlive() const;
    void SetDoneCallback(std::function<void(void)> Callback);
    void SetStrikeCallback(std::function<void(SVector2F)> Callback);
    void Reset();

    void SetCrawlSpeed(const float &BetweenSteps);
    void SetMaxBoltLength(const float &Length);
    SString GetClass() const override;

  protected:
    float m_TimeBetweenCrawlSteps = 3.f;
    float m_MaxBoltLength = 1000.f;

    std::function<void(SVector2F)> m_StrikeCallback;
    std::function<void(void)> m_BoltDoneFunc;

    static void GenerateBoltPoints(const SVector2F &Start, const SVector2F &End, STDVector<sf::VertexArray> &m_Points);

    void UpdateBolt(const SFLOAT &delta);
    void CreateBolt(const SVector2F &StartPosition, const SVector2F &EndPosition);
    void StepBolt(int num_steps);

    SVector2F m_CrawlDir;
    STDVector<SFLOAT> m_Positions;
    SFLOAT m_Sway = 40.f;
    SFLOAT m_Jaggedness = 1.f / 90.f;
    SFLOAT m_PrevDisplacement = 0.f;
    bool   m_IsAlive = false;
    SFLOAT  m_SparkSpeed = 1.f;
    SFLOAT m_currentFadeTime = 0.0;
    SFLOAT m_TotalFadeTime = 900.0;
    unsigned char alpha = 255;
    std::vector<sf::VertexArray> m_Points;
    std::vector<sf::VertexArray> m_DisplayedPoints;
  };

}

#endif // SFEngine_Lightning_H 
