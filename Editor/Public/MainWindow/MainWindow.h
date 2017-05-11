#ifndef SFEngine_MainWindow_H
#define SFEngine_MainWindow_H

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
#if defined (SF_EDITOR)

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <Kairos\Timestep.hpp>
#include <Kairos\FpsLite.hpp>
#include <tgui\TGUI.hpp>

#include <boost\atomic\atomic.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        MainWindow                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/08                                  */
/************************************************************************/

namespace SFEngine
{

  class MainWindow
  {
  public:
    static void Init(SPtrShared<sf::RenderWindow> Window);
    static void ShowEditorMainWindow();
    static void Cleanup();

    static void CreateUI(SPtrShared<tgui::Gui> GUI);
    static float  GetUICreationStatus();
    static bool IsUICreationComplete();
  private:
    static sf::Font GUIFont;
    static float UICreationProgress;
    static boost::atomic<std::string> UIProgressText;
    static std::shared_ptr<tgui::Theme> Theme;
    static std::string GetProgressText();
    static boost::atomic<bool> UIComplete;

    /************************************************************************/
    /* Static GUI items
     *  Alert message box */
    /************************************************************************/
    static tgui::MessageBox::Ptr AlertMessage;

    static void ShowEditorMainToolbar();
    static void ShowEditorMainTabBar();
    static void CreateToolBar(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
    static void CreateMainMenu(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
    static void CreatePanels(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
    static void CreateTools(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
  };

} // namespace SFEngine

#endif // if defined (SF_EDITOR)

#endif // SFEngine_MainWindow_H
