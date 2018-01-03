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
#include "Level/Level.h"

void SFEngine::InitRenderWindow()
{
  sf::ContextSettings csettings;

  Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Engine InitRenderWindow"), MessageLogLevel::Normal);
   
  csettings.antialiasingLevel = 8;
  if (currentRenderWindow)
    delete currentRenderWindow;

#ifdef WITH_EDITOR
  WindowStyle = sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar;
  WindowTitle = "SFEngine";
  Window = new sf::RenderWindow(sf::VideoMode(1700, 900), "SFEngine", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar, csettings);
  WindowSize = static_cast<sf::Vector2f>(Window->getSize());
#else
  Window = new sf::RenderWindow(sf::VideoMode(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y), "SFEngine V0.1.1", sf::Style::Default, ContextSettings);
  WindowSize = { EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y };
#endif
  MaximumWindowView = Window->getDefaultView();
  Window->setKeyRepeatEnabled(false);
  Window->setVerticalSyncEnabled(false);
  currentRenderWindow = Window;
  CurrentEngine = this;

  FragmentShader = new sf::Shader;
  VertexShader = new sf::Shader;
  if (!FragmentShader->loadFromFile("./SFEngine/Source/CoreFragmentShader.fsh", sf::Shader::Fragment)) {
    std::cerr << "Failed to load fragment shader from file" << std::endl;
  }
  if (!VertexShader->loadFromFile("./SFEngine/Source/CoreVertexShader.vsh", sf::Shader::Vertex)) {
    std::cerr << "Failed to load vertex shader from file" << std::endl;
  }

  RenderStates.blendMode = sf::BlendAdd;
  __Set__Core__Shaders(FragmentShader, VertexShader);
  __Set__Render__States(RenderStates);
  __Set__Render__Settings(RSettings);

  __Set__Window(Window);
  Window->clear(sf::Color::Black);
  Window->display();
}

UINT32 SFEngine::Startup()
{
  if (!sf::Shader::isAvailable()) {
    return(GL_NO_SHADERS);
  }

  Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Engine Startup"), MessageLogLevel::Normal);

  Handler.BindCallback(Events::GainedFocus,
                        [this]() {this->HandleWindowGainedFocus(); });

  Handler.BindCallback(Events::LostFocus,
                        [this]() {this->HandleWindowLostFocus(); });

  Handler.BindCallback(Events::WindowClosed,
                        [this]() {this->HandleWindowClosed(); });

  Handler.BindCallback(Events::WindowResized,
                        [this]() {this->HandleWindowResized(); });

  Handler.BindCallback(Events::MouseDown,
                        [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMousePress(i, b); });

  Handler.BindCallback(Events::MouseReleased,
                        [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMouseRelease(i, b); });

  Handler.BindCallback(Events::MouseMoved,
                        [this](const sf::Vector2i &i) {this->HandleMouseMovement(i); });

  Handler.BindCallback(Events::KeyPressed,
                        [this](const sf::Keyboard::Key &k) {this->HandleKeyPress(k); });

  Handler.BindCallback(Events::KeyReleased,
                        [this](const sf::Keyboard::Key &k) {this->HandleKeyRelease(k); });

  Handler.BindTextEnterHandler([this](const sf::Uint32 &unicode) {this->HandleTextEntered(unicode); });

  Handler.BindCallback(Events::MouseScrolled,
                        [this](const sf::Vector2i &v, sf::Mouse::Wheel w, float d) { this->HandleMouseScroll(v, w, d); });

  std::ifstream _IN("SFEngine/Config/Engine.ini");
  sf::Vector2u lSize;
  sf::Vector2f gridSpac;
  sf::FloatRect initView;
  bool showgrid;
  if (_IN.fail()) {
    std::cerr << "Failed to open configuration file: \"Engine.ini\"" << std::endl;

  }
  else {
    EngineConfig.Window_v2fWindowSize   = Util::GetVec2fConfig("Window", "WindowSize", sf::Vector2f(800, 800), "Engine.ini", _IN);
    //WindowSize = EngineConfig.Window_v2fWindowSize;
    InitialLevel                        = Util::GetStringConfig("Game", "InitialLevel", "test.map", "Engine.ini", _IN);
    EngineRenderSettings.Brightness     = Util::GetFloatConfig("Render", "Brightness", 1, "Engine.ini", _IN);
    EngineRenderSettings.Contrast       = Util::GetFloatConfig("Render", "Contrast", 0.5, "Engine.ini", _IN);
    EngineRenderSettings.Gamma          = Util::GetFloatConfig("Render", "Gamma", 0.5, "Engine.ini", _IN);
    EngineRenderSettings.PostProcess    = Util::GetUnsignedIntConfig("Render", "PostProcess", 0, "Engine.ini", _IN);
    EngineRenderSettings.BGClearColor.r = static_cast<sf::Uint8>(Util::GetUnsignedIntConfig("Render", "ClearColor.r", 0, "Engine.ini", _IN));
    EngineRenderSettings.BGClearColor.g = static_cast<sf::Uint8>(Util::GetUnsignedIntConfig("Render", "ClearColor.g", 0, "Engine.ini", _IN));
    EngineRenderSettings.BGClearColor.b = static_cast<sf::Uint8>(Util::GetUnsignedIntConfig("Render", "ClearColor.b", 0, "Engine.ini", _IN));

    ContextSettings.antialiasingLevel   = Util::GetUnsignedIntConfig("Render", "uiAALevel", 1, "Engine.ini", _IN);
    ContextSettings.depthBits           = Util::GetUnsignedIntConfig("Render", "uiDepthBits", 0, "Engine.ini", _IN);
    ContextSettings.sRgbCapable         = Util::GetBooleanConfig("Render", "bSRGBCapable", true, "Engine.ini", _IN);
    ContextSettings.stencilBits         = Util::GetUnsignedIntConfig("Render", "uiStencilBits", 0, "Engine.ini", _IN);
    _IN.clear();
    _IN.close();
  }

  InitRenderWindow();
  //Create the GUI window immediately
  GUI = std::make_shared<tgui::Gui>(*currentRenderWindow);

  tgui::ToolTip::setTimeToDisplay(sf::milliseconds(300));


  if (!EngineLogoTexture.loadFromFile("./SFEngine/Samples/Logos/SFEngineLogoLarge.png")) {
    std::cerr << "Unable to load EngineLogo texture" << std::endl;
  }
  else {
    EngineLogoSprite.setTexture(EngineLogoTexture);
    Window->draw(EngineLogoSprite);
  }

  if (!EngineLoadingFont.loadFromFile("./SFEngine/Samples/Fonts/PressStart2P.ttf")) {
    std::cerr << "Unable to load EngineLoadingFont" << std::endl;
  }
  else {
    EngineLoadingText.setFont(EngineLoadingFont);
    EngineLoadingText.setPosition(sf::Vector2f(100, 650));
    EngineLoadingText.setFillColor(sf::Color::White);
    EngineLoadingText.setCharacterSize(20);
    Window->draw(EngineLoadingText);
  }
  Window->display();

  Window->clear();
  EngineLoadingText.setString("Loading...");
  Window->draw(EngineLogoSprite);
  Window->draw(EngineLoadingText);
  Window->display();
  Window->clear();

  Levels["Main"] = Level::DefaultEmptyLevel();
  auto ret = GameLoop();

  if (ret)
  {
    ret = Shutdown();
  }

  return ret;
}
