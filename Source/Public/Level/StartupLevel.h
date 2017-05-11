#ifndef SFEngine_StartupLevel_H
#define SFEngine_StartupLevel_H

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
#include "Level\BasicLevel.h"
#include "Effects\Phasers\FadePhaser.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        StartupLevel                                  */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/02                                  */
/************************************************************************/

namespace SFEngine
{

  class StartupLevel : public BasicLevel 
  {
  public:
    StartupLevel(const StartupLevel &) = delete;
    StartupLevel& operator=(const StartupLevel &) = delete;
    StartupLevel(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
    virtual ~StartupLevel();

    /************************************************************************/
    /* Required method overrides                                            */
    /************************************************************************/
    virtual void TickUpdate(const SFLOAT &delta) override;
    virtual void Render(SFLOAT Alpha, SharedRTexture Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(SOFStream &out) override;
    virtual void SerializeIn(SIFStream &in) override;
    virtual void HandleInputEvent(const UserEvent &evnt) override;
    virtual void StepSimulation(SFLOAT Dt) override;
    virtual void InterpolateState(SFLOAT Alpha) override;
    virtual void EventUpdate(sf::Event Event) override;

    /************************************************************************/
    /* Basic functionality methods                                          */
    /************************************************************************/
    virtual void OnBegin() override;
    virtual void OnEnd() override;
    virtual void HideUI() override;
    virtual void ShowUI() override;
    virtual void Reset() override;
    virtual void CleanUp() override;
    virtual void RenderOnTexture(SFLOAT Alpha, SharedRTexture Texture) override;
    virtual void Load() override;
    virtual void Unload() override;

  protected:
    TextFader m_LogoTextFader;
  };

}

#endif // SFEngine_StartupLevel_H 
