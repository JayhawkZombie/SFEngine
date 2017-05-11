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

#include "MainWindow/MainWindow.h"
#include "Manager/EditorManager.h"
#include "Utils\Parsing.h"

#include "LoadingRing.cpp"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <SelbaWard/Ring.hpp>
#include <SelbaWard/ProgressBar.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                           CreateUI                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/10                                  */
/************************************************************************/

namespace SFEngine
{

  void EditorManager::UILoadingLoop()
  {
    //Window will be 600 x 500
    std::thread SetupThread(
      []() { Get()->SetupUI(); }
    );
    auto Win = Get()->m_MainWindow;

    while (!MainWindow::IsUICreationComplete())
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    SetupThread.join();
  }

  void EditorManager::SetupUI()
  {
    /* Create the main UI */
    MainWindow::CreateUI(Get()->m_EditorGui);
  }

  void EditorManager::CreateBMPFont(sw::BitmapFont &BFont, sw::BitmapText &BText)
  {

  }

} // namespace SFEngine

#endif // if defined (SF_EDITOR)
