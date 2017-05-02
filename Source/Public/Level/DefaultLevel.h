#ifndef SFEngine_DefaultLevel_H
#define SFEngine_DefaultLevel_H

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
#include "Level\BasicLevel.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <TGUI\TGUI.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        DefaultLevel                                  */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{

  class DefaultLevel : public BasicLevel
  {
  public:
    DefaultLevel();
    ~DefaultLevel() override final;
    /************************************************************************/
    /* Required method overrides                                            */
    /************************************************************************/
    virtual void TickUpdate(const SFLOAT &delta) override final;
    virtual void Render(SFLOAT Alpha, SharedRTexture Target) override final;
    virtual void OnShutDown() override final;
    virtual void SerializeOut(SOFStream &out) override final;
    virtual void SerializeIn(SIFStream &in) override final;
    virtual void HandleInputEvent(const UserEvent &evnt) override final;
    virtual void StepSimulation(SFLOAT Dt) override final;
    virtual SString GetClass() const override final;
    virtual void EventUpdate(sf::Event Event) override final;

    /************************************************************************/
    /* Basic functionality methods                                          */
    /************************************************************************/
    virtual void LoadLevel(const std::string &lvlfile) override final;
    virtual void OnBegin() override final;
    virtual void OnEnd() override final;
    virtual void HideUI() override final;
    virtual void ShowUI() override final;
    virtual void Reset() override final;
    virtual void CleanUp() override final;
    virtual void SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position) override final;
    virtual void SpawnObject(std::shared_ptr<GameObject> Object, const sf::Vector2f &Position) override final;
    virtual void RenderOnTexture(SFLOAT Alpha, SharedRTexture Texture) override final;
    virtual void Load() override final;
    virtual void Unload() override final;

  protected:
    tgui::Button::Ptr m_QuitButtonPtr;
    tgui::Theme::Ptr m_MenuThemePtr;
    sf::CircleShape m_Circ;

    sf::Font m_Font;
    sf::Text m_Text;

    float circ_vel = 100.f;
    sf::Vector2f circ_pos;
    sf::Vector2f old_circ_pos;
    sf::Vector2f circ_dir = { 0, 1 };
  };

}

#endif // SFEngine_DefaultLevel_H 
