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

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <cmath>

/************************************************************************/
/*                        FadePhaser                                    */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: (Name) - 2017/05/03                                       */
/************************************************************************/

namespace SFEngine
{

  template<typename T>
  FadePhaser<T>::FadePhaser()
  {

  }

  template<typename T>
  FadePhaser<T>::~FadePhaser()
  {

  }

  template<typename T>
  void FadePhaser<T>::Update(SFLOAT Dt)
  {
    Phaser::Update(Dt);
    if (m_IsDone)
      return;

    SFLOAT tot_dur = (SFLOAT)m_EffectDuration.asSeconds();

    m_CurrentAlphaLevel = UINT32(tot_dur * m_FadeRate);
    if (m_FadeRate > 0)
      m_CurrentAlphaLevel = std::min(m_CurrentAlphaLevel, m_MaxAlpha);
    else
      m_CurrentAlphaLevel = std::max(m_CurrentAlphaLevel, m_MinAlpha);

    auto color = m_TransformTarget->getFillColor();
    color.a = (sf::Uint8)(m_CurrentAlphaLevel);
    m_TransformTarget->setColor(color);
  }

  template<typename T>
  void FadePhaser<T>::Start(SFLOAT Duration)
  {
    Phaser::Start(Duration);
  }

  template<typename T>
  void FadePhaser<T>::Start(SFLOAT Duration, UINT32 StartingAlpha, UINT32 EndingAlpha)
  {
    Phaser::Start(Duration);
    m_FadeRate = UINT32((EndingAlpha - StartingAlpha) / Duration);
  }

  template<typename T>
  void FadePhaser<T>::Restart(SFLOAT Duration)
  {
    Phaser::Restart(Duration);
  }

  template<typename T>
  void FadePhaser<T>::SetFadeTime(SFLOAT Seconds)
  {
    m_UpdateStep.setStep((double)Seconds);
  }

  template<typename T>
  void FadePhaser<T>::SetFadeMin(UINT32 MinAlpha)
  {
    m_MinAlpha = MinAlpha;
  }

  template<typename T>
  void FadePhaser<T>::SetFadeMax(UINT32 MaxAlpha)
  {
    m_MaxAlpha = MaxAlpha;
  }

} // namespace SFEngine
