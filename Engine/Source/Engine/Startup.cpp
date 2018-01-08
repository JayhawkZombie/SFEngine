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
   
  csettings.antialiasingLevel = 8;
  if (currentRenderWindow)
    delete currentRenderWindow;

  csettings.majorVersion = EngineConfig.Context_VersionMajor;
  csettings.minorVersion = EngineConfig.Context_VersionMinor;

#ifdef WITH_EDITOR
  WindowStyle = sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar;
  WindowTitle = "SFEngine";
  Window = new sf::RenderWindow(sf::VideoMode(EngineConfig.Window_v2uWindowSize.x, EngineConfig.Window_v2uWindowSize.y), "SFEngine", 
    sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar, csettings);

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

  //Parse engine ini file
  IniParser parser;
  parser.Parse("Engine.ini");

  auto winSize = parser.TryGetValue("Window", "WindowSize");
  auto initLevel = parser.TryGetValue("Game", "LevelFile");
  auto brightness = parser.TryGetValue("Render", "Brightness");
  auto contrast = parser.TryGetValue("Render", "Contrast");
  auto gamma = parser.TryGetValue("Render", "Gamma");
  auto clearcolor_r = parser.TryGetValue("Render", "ClearColor.r");
  auto clearcolor_g = parser.TryGetValue("Render", "Clearcolor.g");
  auto clearcolor_b = parser.TryGetValue("Render", "ClearColor.b");
  auto aalevel = parser.TryGetValue("Render", "uiAALevel");
  auto majorversion = parser.TryGetValue("Render", "MajorVersion");
  auto minorversion = parser.TryGetValue("Render", "MinorVersion");
  
  EngineConfig.Window_v2uWindowSize = Util::StringToVec2<unsigned int>(winSize.value_or("(1700, 900)"));
  InitialLevel = initLevel.value_or("none");
  EngineRenderSettings.Brightness = Util::StringToType<float>(brightness.value_or("1"));
  EngineRenderSettings.Contrast = Util::StringToType<float>(contrast.value_or("0.5"));
  EngineRenderSettings.Gamma = Util::StringToType<float>(gamma.value_or("0.5"));
  EngineRenderSettings.BGClearColor.r = Util::StringToType<sf::Uint8>(clearcolor_r.value_or("0"));
  EngineRenderSettings.BGClearColor.g = Util::StringToType<sf::Uint8>(clearcolor_g.value_or("0"));
  EngineRenderSettings.BGClearColor.b = Util::StringToType<sf::Uint8>(clearcolor_b.value_or("0"));
  EngineConfig.Context_VersionMajor = Util::StringToType<unsigned int>(majorversion.value_or("3"));
  EngineConfig.Context_VersionMinor = Util::StringToType<unsigned int>(minorversion.value_or("0"));

  InitRenderWindow();

  //Create the GUI window immediately
  GUI = std::make_shared<tgui::Gui>(*currentRenderWindow);

  tgui::ToolTip::setTimeToDisplay(sf::milliseconds(300));


  if (!EngineLogoTexture.loadFromFile("SFEngineLogoLarge.png")) {
    std::cerr << "Unable to load EngineLogo texture" << std::endl;
  }
  else {
    EngineLogoSprite.setTexture(EngineLogoTexture);
    Window->draw(EngineLogoSprite);
  }

  if (!EngineLoadingFont.loadFromFile("NotoSans-Regular.ttf")) {
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

  //Init timer manager
  m_GlobalTimerManager = std::make_unique<TimerManager>();

  Levels["Main"] = BasicLevel::DefaultEmptyLevel();

  CurrentLevel = Levels["Main"].get();
  auto ret = GameLoop();

  if (ret)
  {
    ret = Shutdown();
  }

  return ret;
}
