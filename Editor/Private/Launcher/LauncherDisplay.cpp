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
#include "Globals.h"
#include "..\..\Public\Launcher\LauncherDisplay.h"
#if defined (SF_EDITOR)

#include "Utils\Parsing.h"
#include "Exceptions\Exceptions.hpp"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <boost\xpressive\xpressive.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        LauncherDisplay                               */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/07                                  */
/************************************************************************/

namespace SFEngine
{
  LauncherDisplay::LauncherDisplay()
  {
    
  }

  LauncherDisplay::~LauncherDisplay()
  {
  }

  UINT32 LauncherDisplay::Launch(UINT32 Width, UINT32 Height)
  {
    try
    {
      m_MessageLock = std::make_shared<SMutex>();
      m_LauncherWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(Width, Height), SString("Launcher"), sf::Style::Default);
      m_SplashGui.setWindow(*m_LauncherWindow);

      SString ThemePath = "$(PATH)/Editor/Assets/Themes/TransparentGray.theme";
      SString FontPath = "$(PATH)/Editor/Assets/Fonts/Marvel-Regular.ttf";
      SString TexturePath = "$(PATH)/Source/Assets/Logos/Splash.png";
      EnvSubst(TexturePath);
      EnvSubst(ThemePath);
      EnvSubst(FontPath);

      m_Font.loadFromFile(FontPath);
      m_SplashGui.setFont(m_Font);

      m_Theme = std::make_shared<tgui::Theme>(ThemePath);

      tgui::Scrollbar::Ptr sBar = m_Theme->load("scrollbar");
      sBar->setSize({ 15.f, 480.f });
      sBar->setPosition({ float(Width) - 15.f, 0.f });

      m_MessageBox = m_Theme->load("chatbox");
      m_MessageBox->setPosition({ 20.f, 100.f });
      m_MessageBox->setSize({ 460.f, 380.f });
      m_MessageBox->setScrollbar(sBar);
      m_MessageBox->setTextSize(16);
      m_SplashGui.add(m_MessageBox);

      m_MessageBox->addLine("Loading Configuration Files...", sf::Color::White);


      m_BGTexture.loadFromFile(TexturePath);
      m_BGSprite.setTexture(m_BGTexture);
      m_BGSprite.setPosition({ 0.f, 0.f });

      return 0;
    }
    catch (EngineRuntimeError& e)
    {
      throw;
    }
  }

  void LauncherDisplay::ShutDown()
  {
    m_MessageBox.reset();
    m_SplashGui.removeAllWidgets();
  }

  void LauncherDisplay::PostLaunchUpdate(const SString & Update)
  {
    m_MessageLock->lock();
    m_MessageBox->addLine(Update, sf::Color::White);
    m_MessageLock->unlock();
  }

  SPtrShared<sf::RenderWindow> LauncherDisplay::GetWindow()
  {
    return m_LauncherWindow;
  }

  void LauncherDisplay::Update()
  {
    static sf::Event event;

    while (m_LauncherWindow->pollEvent(event)) {
      m_SplashGui.handleEvent(event);
    }
  }

  void LauncherDisplay::Draw()
  {
    m_MessageLock->lock();
    m_LauncherWindow->clear(sf::Color::Black);
    m_LauncherWindow->draw(m_BGSprite);
    m_SplashGui.draw();
    m_LauncherWindow->display();
    m_MessageLock->unlock();
  }

} // namespace SFEngine

#endif // if defined (SF_EDITOR)
