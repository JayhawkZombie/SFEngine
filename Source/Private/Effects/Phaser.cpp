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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "Effects\Phasers\Phaser.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                             Phaser                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/03                                  */
/************************************************************************/

namespace SFEngine
{

  void Phaser::Update(SFLOAT Dt)
  {
    if (!m_IsAffecting || m_IsDone)
      return;

    m_UpdateStep.addFrame();
    m_EffectDuration += Dt;

    if (m_EffectDuration.asMilliseconds() >= m_TotalEffectDuration.asMilliseconds()) {
      m_IsDone = true;
      if (m_EndCallBack) m_EndCallBack();
    }
  }

  void Phaser::Start(SFLOAT Duration)
  {
    m_EffectDuration.zero();
    m_UpdateStep.resetTime();
    m_TotalEffectDuration.setFromSeconds((double)Duration);
    m_IsDone = false;
    if (m_StartCallBack) m_StartCallBack();
  }

  void Phaser::Restart(SFLOAT Duration)
  {
    m_EffectDuration.zero();
    m_UpdateStep.resetTime();
    m_IsDone = false;
    m_TotalEffectDuration.setFromSeconds((double)Duration);
  }

  void Phaser::SetStartCallback(std::function<void(void)> Ftn)
  {
    m_StartCallBack = Ftn;
  }

  void Phaser::SetFinishedCallback(std::function<void(void)> Ftn)
  {
    m_EndCallBack = Ftn;
  }

  void Phaser::SetObjectPtr(GameObject * Ptr)
  {
    m_ObjectPtr = Ptr;
  }

  void Phaser::SetUpdateStep(SFLOAT Delta)
  {
    m_UpdateStep.setStep((double)Delta);
  }

} // namespace SFEngine
