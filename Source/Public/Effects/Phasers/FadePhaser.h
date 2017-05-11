#ifndef SFEngine_FadePhaser_H
#define SFEngine_FadePhaser_H

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
#include "BasicIncludes.h"
#include "Effects\Phasers\Phaser.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                         FadePhaser                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/03                                  */
/************************************************************************/

namespace SFEngine
{

  template<typename T>
  class FadePhaser : public Phaser
  {
  public:
    FadePhaser();
    ~FadePhaser();

    virtual void Update(SFLOAT Dt) override;
    virtual void Start(SFLOAT Duration) override;
    virtual void Start(SFLOAT Duration, UINT32 StartingAlpha, UINT32 EndingAlpha);
    virtual void Restart(SFLOAT Duration) override;
    virtual void SetFadeTime(SFLOAT Seconds);
    virtual void SetFadeMin(UINT32 MinAlpha);
    virtual void SetFadeMax(UINT32 MaxAlpha);

  protected:
    T*     m_TransformTarget = nullptr;
    UINT32 m_MinAlpha = 0;
    UINT32 m_MaxAlpha = 255;
    UINT32 m_StartingAlpha = 0;
    UINT32 m_EndingAlpha = 0;
    UINT32 m_FadeRate = 0;
    UINT32 m_CurrentAlphaLevel = 0;
  };

  using SpriteFader = FadePhaser<sf::Sprite>;
  using ShapeFader = FadePhaser<sf::Shape>;
  using TextFader = FadePhaser<sf::Text>;

}

#include "Effects\Phasers\FadePhaser.inl"

#endif // SFEngine_FadePhaser_H 
