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

#include "Engine\Engine.h"
#include "Lights\LightingSystem.h"

#ifdef WITH_EDITOR

#endif

void func()
{
  std::cerr << "Func called" << std::endl;
}

void SomeCallback(std::shared_ptr<sf::Texture> tex, const std::string &ID)
{
  std::cerr << "<<<<< OOOOOOOH!!!!!" << std::endl;
}

UINT32 SFEngine::GameLoop()
{
  Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Engine GameLoop"), MessageLogLevel::Normal);

  std::chrono::high_resolution_clock::time_point LastFrameStart = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point CurrentFrameStart = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point TickEnd;
  std::chrono::high_resolution_clock::time_point UpdateStart;
  std::chrono::high_resolution_clock::time_point UpdateEnd;
  std::chrono::high_resolution_clock::time_point RenderStart;
  std::chrono::high_resolution_clock::time_point RenderEnd;

  double TickDelta = 0.0;
  double RenderDelta = 0.0;
  double UpdateDelta = 0.0;
  sf::Event evnt;

  std::shared_ptr<sf::RenderTexture> GameMainTexture = std::make_shared<sf::RenderTexture>();
  GameMainTexture->create(static_cast<unsigned int>(std::ceil(WindowSize.x)), static_cast<unsigned int>(std::ceil(WindowSize.y)));

  sf::Sprite GameSprite;
  GameSprite.setTexture(GameMainTexture->getTexture());

  Window->clear(sf::Color::Black);
  std::shared_ptr<sf::RenderTexture> EditorTexture(new sf::RenderTexture);
  EditorTexture->create(static_cast<unsigned int>(std::ceil(WindowSize.x)), static_cast<unsigned int>(std::ceil(WindowSize.y)));
  EditorTexture->clear(sf::Color::Transparent);

  sf::Sprite EditorSprite;
  EditorSprite.setTexture(EditorTexture->getTexture());

  //Window->setFramerateLimit(120);
  Window->setVerticalSyncEnabled(false);
  Window->setKeyRepeatEnabled(false);
  bool Closed = false;

#ifdef WITH_EDITOR
  sf::Clock dClock;
  ImGui::SFML::Init(*currentRenderWindow);
#endif

#ifdef WITH_EDITOR
  
#endif
  vec2d Gravity;

  AssignBoundaries(900, 1700);

  std::shared_ptr<sf::RenderTexture> LevelTexture = std::make_shared<sf::RenderTexture>();
  LevelTexture->create(1700, 900);
  sf::RectangleShape LevelRect;
  LevelRect.setPosition({ 0, 0 });
  LevelRect.setSize({ 1700, 900 });
  LevelRect.setTexture(&(EditorTexture->getTexture()));
  LevelRect.setTextureRect({ 0, 0, 1700, 900 });

  //There should already have been a Main level loaded in Startup
  auto it = Levels.find("Main");

  if (it != Levels.end()) {
    it->second->OnBegin();
    CurrentLevel = it->second.get();
  }
  else {
    FlagForClose = true;
  }
    
  sf::Time fTime = { sf::seconds(0) };
  EngineRenderSettings.BGClearColor = sf::Color::Black;

  while (true) {
    //When the window gets closed, we will be alerted, break out, and alert everything that we're closing down
    Closed = Handler.PollEvents(currentRenderWindow, evnt, true);
    if (Closed || FlagForClose || !currentRenderWindow || !currentRenderWindow->isOpen())
      break;

    try
    {
      CurrentFrameStart = std::chrono::high_resolution_clock::now();
      TickDelta = std::chrono::duration<double, std::milli>(CurrentFrameStart - LastFrameStart).count();
      UpdateDelta = std::chrono::duration<double, std::milli>(UpdateEnd - UpdateStart).count();
      RenderDelta = std::chrono::duration<double, std::milli>(RenderEnd - RenderStart).count();

      TickDelta *= TimeScaleFactor;
      UpdateStart = std::chrono::high_resolution_clock::now();

      fTime = dClock.restart();
        
      if (CurrentLevel) {
        CurrentLevel->TickUpdate(TickDelta);
      }

      UpdateEnd = std::chrono::high_resolution_clock::now();
      RenderStart = std::chrono::high_resolution_clock::now();

      Window->clear(sf::Color::Black);
      EditorTexture->clear(sf::Color::Black); 
        
      if (CurrentLevel) {
        CurrentLevel->RenderOnTexture(EditorTexture);
      }

      EditorTexture->display();
      Window->draw(LevelRect); 

      GUI->draw();
      Window->display();

      RenderEnd = std::chrono::high_resolution_clock::now();
      LastFrameStart = CurrentFrameStart;
    }
    catch (std::runtime_error &err )
    {
      std::cerr << "Error during runtime: " << err.what() << std::endl;
    }

  }
  EditorTexture.reset();
  LevelTexture.reset();

  CurrentLevel = nullptr;

  Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Engine Beginning Shutdown"), MessageLogLevel::Normal);
  return Shutdown();
}
