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

#include "Manager\EditorManager.h"
#include "Launcher\Launcher.h"
#include "Level\BasicLevel.h"
#include "MainWindow\MainWindow.h"
#include "Messaging\Messager.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <boost\make_shared.hpp>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL3_IMPLEMENTATION
#include <nuklear/nuklear.h>

#include <nuklear/demo/sfml_opengl3/nuklear_sfml_gl3.h>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        EditorManager                                 */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/07                                  */
/************************************************************************/

namespace SFEngine
{
  boost::shared_ptr<EditorManager> EditorManager::m_StaticManager;
  EditorManager::~EditorManager()
  {
  }

  EditorManager::EditorManager()
  {
  }

  UINT32 EditorManager::Launch(boost::program_options::options_description &Options, boost::program_options::variables_map &VarMap)
  {
    SFENGINE_ASSERT(!m_StaticManager);
    Messager::Init();
    m_StaticManager = boost::shared_ptr<EditorManager>(new EditorManager);
    m_StaticManager->m_StaticEngine = boost::make_shared<Engine>();

    /************************************************************************/
    /* Launcher loop                                                        */
    /************************************************************************/

    UINT32 LStatus = Launcher::Go(Options, VarMap, m_StaticManager->m_Properties);

    return LStatus;
  }

  UINT32 EditorManager::MainLoop(SPtrShared<sf::RenderWindow> Window)
  {
    Get()->m_EditorGui = std::make_shared<tgui::Gui>();
    Get()->m_EditorGui->setWindow(*Window);

    Get()->UILoadingLoop();
    Window->create(sf::VideoMode(1700, 900), "SFEngine Editor", sf::Style::Default);
    Get()->m_EditorGui->setWindow(*Window);

    //Get()->m_EditorGui->setWindow(*Window);
    Get()->m_GameTexture = std::make_shared<RTexture>();
    Engine::m_StaticCurrentEngine = new Engine();
    Engine::GetCurrentEngine()->InitFromEditor(Get()->m_GameTexture);
    Engine::GetCurrentEngine()->m_CurrentRenderWindow = Window.get();
    Engine::m_EngineGUI = Get()->m_EditorGui;

    bool Done = false;
    sf::Event event;
    for ( ; ; ) {

      Done = Engine::GetCurrentEngine()->m_Handler.PollEvents(Window.get(), event, true);

      if (Done)
        break;

      Get()->m_InterpDelta = Get()->UpdatePass();
      Get()->RenderPass(Window);
      Get()->m_EditorGui->draw();
      Window->display();
    }

    if (Engine::m_CurrentLevel)
      Engine::m_CurrentLevel->Unload();

    Get()->m_EditorGui->removeAllWidgets();
    Get()->m_EditorGui.reset();
    Get()->m_GameTexture.reset();
   
    UINT32 EngineShutdownRet = Engine::GetCurrentEngine()->ShutDown();
    UINT32 StaticShutdownRet = Engine::StaticShutDown();
    //Window.reset();
    Window.reset();
    return EngineShutdownRet;
  }

  std::shared_ptr<tgui::Gui> EditorManager::GetUIHandle()
  {
    return (Get()->m_EditorGui);
  }

  boost::shared_ptr<EditorManager> EditorManager::Get()
  {
    return m_StaticManager;
  }

} // namespace SFEngine

#endif // if defined (SF_EDITOR)
