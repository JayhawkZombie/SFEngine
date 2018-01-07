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
#include "Messaging\CoreMessager.h"
#include "Time/TimerManager.h"
#include "Parsing/IniParser.h"

UINT32 SFEngine::Init(int argc, char **argv)
{
  //Initialize the messager
  Messager::Init();
  ASyncLevelStreamThread::Launch();
  LevelsLock = std::make_shared<std::mutex>();

  //Init timer manager
  m_GlobalTimerManager = std::make_unique<TimerManager>();

  Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "EngineStartup"), MessageLogLevel::Normal);

  std::vector<std::string> Commands;

  for (int i = 0; i < argc; i++) {
    Commands.emplace_back(std::string(argv[i]));
  }

  currentRenderWindow = new sf::RenderWindow(sf::VideoMode(400, 400), "splash screen", sf::Style::None);
  sf::Font loadfont;
  loadfont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Marvel-Regular.ttf");
  sf::Text loadingtext;
  loadingtext.setString("Please Wait... \nLoading...");

  auto rect = loadingtext.getGlobalBounds();

  loadingtext.setPosition({ rect.width / 2.f, rect.height / 2.f });
  currentRenderWindow->draw(loadingtext);
  currentRenderWindow->display();

  return Startup();
}
