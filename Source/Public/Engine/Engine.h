#ifndef SFEngine_Engine_H
#define SFEngine_Engine_H

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
#include "Events\EventHandler.h"
#include "Events\UserEvent.h"
#include "Engine\BaseEngineInterface.h"
#include "Engine\EngineConfiguration.h"
#include "Engine\ReturnValues.h"
#include "Engine\EngineConfiguration.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <cereal\access.hpp>
#include <SFML\Graphics.hpp>
#include <TGUI\TGUI.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        Engine                                        */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{

  class Engine
  {
  public:
    friend class cereal::access;
    Engine();
    Engine(const Engine &) = delete; //No copy constructor allowed
    Engine(const Engine &&) = delete;
    ~Engine();

    static UINT32 Go(int argc, char **argv, EngineConfig &Config);
    static Engine* GetCurrentEngine();
    static sf::RenderWindow* GetCurrentRenderWindow();
    static SharedLevel GetCurrentLevel();
    static bool AddLevel(const SString &Name, SharedLevel LevelPtr);

    static SharedLevel StartingLevel;
    
    /************************************************************************/
    /* Signal for the engine to perform actions                             */
    /************************************************************************/
    static void SignalForClose();
    static void SignalForThrottle();

    static SPtrShared<tgui::Gui> GUI();

    /************************************************************************/
    /* Flags to signal behavior to the engine                               */
    /************************************************************************/
    enum Flags
    {
      VSyncOn = 1,
      VSyncOff = 2,
      Exit = 4,
      Throttle = 8
    };

  private:
    template<class Archive>
    void save(Archive &ar) const;

    template<class Archive>
    void load(Archive &ar);

    static Engine* m_StaticCurrentEngine;
    static STDMap<SString, SharedLevel> m_Levels;
    static SharedLevel m_CurrentLevel;
    static SPtrShared<tgui::Gui> m_EngineGUI;
    static UINT32 m_Flags;
    sf::RenderWindow *m_CurrentRenderWindow;

    UINT32 Startup();
    UINT32 GameLoop();
    UINT32 ShutDown();
    static UINT32 StaticShutDown();
    UINT32 Init(int argc, char **argv);
    UINT32 InitRenderWindow();
    void   StepSimulation(SFLOAT STick, SFLOAT STickDt);
    void   UpdatePass(SFLOAT STick, SFLOAT STickDt);   
    void   RenderPass(SharedRTexture Texture, SRectShape &LevelRect);

    UserEvent    m_UEvent;
    EngineConfig m_Configuration;
    EventHandler m_Handler;
    bool         m_SignalForClose;

    /************************************************************************/
    /* Event handlers                                                       */
    /************************************************************************/
    void HandleWindowClosed();
    std::function<void(void)> Callback_HandleWindowClosed;

    void HandleTextEntered(const sf::Uint32 &unicode);
    std::function<void(const sf::Uint32 &unicode)> Callback_HandleTextEntered;

    void HandleWindowResized();
    std::function<void(void)> Callback_HandleWindowResized;

    void HandleWindowLostFocus();
    std::function<void(void)> Callback_HandleWindowLostFocus;

    void HandleWindowGainedFocus();
    std::function<void(void)> Callback_HandleWindowGainedFocus;

    void HandleMouseMovement(const sf::Vector2i &v);
    std::function<void(const sf::Vector2i &v)> Callback_HandleMouseMovement;

    void HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b);
    std::function<void(const sf::Vector2i &v, const sf::Mouse::Button &b)> Callback_HandleMousePress;

    void HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b);
    std::function<void(const sf::Vector2i &v, const sf::Mouse::Button &b)> Callback_HandleMouseRelease;

    void HandleKeyPress(const sf::Keyboard::Key &k);
    std::function<void(const sf::Keyboard::Key &k)> Callback_HandleKeyPress;

    void HandleKeyRelease(const sf::Keyboard::Key &k);
    std::function<void(const sf::Keyboard::Key &k)> Callback_HandleKeyRelease;

    void HandleMouseScroll(const sf::Vector2i &v, sf::Mouse::Wheel wheel, float delta);
    std::function<void(const sf::Vector2i &v, sf::Mouse::Wheel, float delta)> Callback_MouseScrolled;
  };

}

namespace cereal {

}

#endif // SFEngine_Engine_H
