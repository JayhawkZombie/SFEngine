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
/*                         Internal  Headers                            
/************************************************************************/
#include "Globals.h"
#if defined (SF_EDITOR)

#include "MainWindow\MainWindow.h"
#include "Utils\Parsing.h"
/************************************************************************/
/*                       Dependency  Headers                            
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       
/************************************************************************/

/************************************************************************/
/*                         MainWindow                                   
/************************************************************************/
/*                                                                      
/*                                                                      
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/10                                  
/************************************************************************/

namespace SFEngine
{

  float MainWindow::UICreationProgress;
  boost::atomic<std::string> MainWindow::UIProgressText;
  std::shared_ptr<tgui::Theme> MainWindow::Theme;
  boost::atomic<bool> MainWindow::UIComplete;
  sf::Font MainWindow::GUIFont;

  float MainWindow::GetUICreationStatus()
  {
    return 0;
  }

  bool MainWindow::IsUICreationComplete()
  {
    bool b = UIComplete.load();
    return b;
  }

  std::string MainWindow::GetProgressText()
  {
    std::string text = UIProgressText.load();
    return text;
  }

  void MainWindow::CreateUI(SPtrShared<tgui::Gui> GUI)
  {
    SString EnvPath("$(PATH)");
    EnvSubst(EnvPath);

    SString ThemePath("$(PATH)/Editor/Assets/Themes/TransparentGray.theme");
    EnvSubst(ThemePath);

    Theme = std::make_shared<tgui::Theme>(ThemePath);
    /* Create MenuBar */
    tgui::MenuBar::Ptr MBar = Theme->load("menubar");

    GUIFont.loadFromFile(EnvPath + "/Editor/Assets/Fonts/Marvel-Regular.ttf");
    GUI->setFont(GUIFont);

    MBar->addMenu("File");
    MBar->addMenuItem("File", "Open");
    MBar->addMenuItem("File", "Exit");

    MBar->addMenu("Edit");
    MBar->addMenu("View");
    MBar->addMenu("Help");
    MBar->setTextSize(10);
    MBar->setPosition({ 0.f, 0.f });
    GUI->add(MBar);

    CreateToolBar(GUI, Theme);
    CreateMainMenu(GUI, Theme);
    CreatePanels(GUI, Theme);
    CreateTools(GUI, Theme);

    UIComplete.store(true);
  }

  void MainWindow::CreateToolBar(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme)
  {

  }

  void MainWindow::CreateMainMenu(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme)
  {

  }

  void MainWindow::CreatePanels(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme)
  {

  }

  void MainWindow::CreateTools(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme)
  {

  }

} // namespace SFEngine

#endif // if defined (SF_EDITOR)
