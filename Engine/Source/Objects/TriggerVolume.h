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

namespace Engine
{
  class Collider2D;
  class LevelObject;

  enum class TriggerMethod
  {
    Touch_PhysicalResponse = 0,
    Touch_NoPhysicalResponse,
    MinimumOverlap_NoPhysicalResponse
  };


  class TriggerVolume
  {
  public:
    TriggerVolume(TriggerMethod Method);
    TriggerVolume(std::function<void(void)> TriggerCB,
                  std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB,
                  bool DoTriggerCheck = false);
    ~TriggerVolume();

    //Do we even want to be able to clone trigger objects?
    TriggerVolume(const TriggerVolume &);
    TriggerVolume(const TriggerVolume &&) = delete;
    TriggerVolume() = delete;

    virtual std::shared_ptr<TriggerVolume> Clone() const;

    void TickUpdate(const double & TickDelta);
    void Render(std::shared_ptr<sf::RenderTarget> Target);
    void DoTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> &Objects);
    void Cleanup();

    void Sleep(bool MakeDefault = false);
    void Wake();
    void SleepFor(double Ms);

    void Enable(bool MakeDefault = true);
    void Disable(bool MakeDefault = true);
    void Reset();
    void SetCollider(std::shared_ptr<Collider2D> Collider);

    void SetTriggerMethod(TriggerMethod Method, bool MakeDefault = true);

  private:
    std::shared_ptr<Collider2D> m_Collider;
    TriggerMethod               m_TriggerMethod;
    bool                        m_Enabled = true;
    bool                        m_DoPhysicalResponse = false;
    bool                        m_Sleeping = false;
    bool                        m_DoTriggerCheck = false;
    double                      m_SleepingDuration = 0.0;
    double                      m_CurrentSleepingDuration = 0.0;

    //Stuff for default state
    TriggerMethod            m_DefaultTriggerMethod;
    bool                     m_DefaultEnabled;
    bool                     m_DefaultDoPhysicalResponse;
    bool                     m_DefaultSleeping;
    std::function<bool(std::shared_ptr<LevelObject>)>  m_DefaultTriggerCheckCallback;
    std::function<void(void)> m_DefaultTriggerCallback;
  };

}
