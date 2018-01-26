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

#include "Engine/stdafx.h"
#include "Engine/Engine.h"
#include "Engine/ReturnValues.h"
#include "Level/BasicLevel.h"
#include "Parsing/IniParser.h"
#include "Utils/Convert.h"

void SFEngine::InitRenderWindow()
{
  sf::ContextSettings csettings;

  Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Engine InitRenderWindow"), MessageLogLevel::Normal);
   
  csettings.antialiasingLevel = EngineConfig.Render_uiAALevel;
  csettings.majorVersion      = EngineConfig.Context_VersionMajor;
  csettings.minorVersion      = EngineConfig.Context_VersionMinor;
  csettings.depthBits         = EngineConfig.Window_uiDepthBits;
  csettings.stencilBits       = EngineConfig.Window_uiStencilBits;
  csettings.attributeFlags    = EngineConfig.Window_u32AttributeFlags;

  currentRenderWindow->create(sf::VideoMode(1700, 900), EngineConfig.Window_strTitle, EngineConfig.Window_ui8Style, csettings);
  currentRenderWindow->setVerticalSyncEnabled(EngineConfig.Render_bVsyncEnabled);
  WindowSize = static_cast<sf::Vector2f>(EngineConfig.Window_v2uWindowSize);
  MaximumWindowView = currentRenderWindow->getDefaultView();

  currentRenderWindow->clear(sf::Color::Black);
  currentRenderWindow->display();
}

UINT32 SFEngine::Startup()
{
  Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Beginning engine startup"), MessageLogLevel::Normal);

  Handler.BindCallback(Events::GainedFocus,   [this]() {this->HandleWindowGainedFocus(); });
  Handler.BindCallback(Events::LostFocus,     [this]() {this->HandleWindowLostFocus(); });
  Handler.BindCallback(Events::WindowClosed,  [this]() {this->HandleWindowClosed(); });
  Handler.BindCallback(Events::WindowResized, [this]() {this->HandleWindowResized(); });
  Handler.BindCallback(Events::MouseDown,     [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMousePress(i, b); });
  Handler.BindCallback(Events::MouseReleased, [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMouseRelease(i, b); });
  Handler.BindCallback(Events::MouseMoved,    [this](const sf::Vector2i &i) {this->HandleMouseMovement(i); });
  Handler.BindCallback(Events::KeyPressed,    [this](const sf::Keyboard::Key &k) {this->HandleKeyPress(k); });
  Handler.BindCallback(Events::MouseScrolled, [this](const sf::Vector2i &v, sf::Mouse::Wheel w, float d) { this->HandleMouseScroll(v, w, d); });
  Handler.BindCallback(Events::KeyReleased,   [this](const sf::Keyboard::Key &k) {this->HandleKeyRelease(k); });
  Handler.BindTextEnterHandler([this](const sf::Uint32 &unicode) {this->HandleTextEntered(unicode); });

  uint32_t LoopReturn = 0;
  uint32_t ShutdownReturn = 0;

  /* Ensure we create the window before engine initializes any gpu resources */

  sf::RenderWindow RWindow;

  {
    currentRenderWindow = &RWindow;

    CheckPlatformDisplaySettings();
    InitRenderWindow();

    //Create the GUI window immediately
    GUI = std::make_shared<tgui::Gui>(*currentRenderWindow);
    tgui::ToolTip::setTimeToDisplay(sf::milliseconds(300));

    Levels["Main"] = BasicLevel::DefaultEmptyLevel();

    CurrentLevel = Levels["Main"].get();

    LoopReturn = GameLoop();
    ShutdownReturn = Shutdown();
  }

  if (RWindow.isOpen())
  {
    RWindow.close();
  }

  return ( LoopReturn || ShutdownReturn );
}
