////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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
#include "Engine\Engine.h"
#include "Level\BasicLevel.h"
#include "Resources\Resources.h"
#include "Messaging\Messager.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                           ShutDown                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/29                                  */
/************************************************************************/

namespace SFEngine
{

  UINT32 Engine::ShutDown()
  {
    Messager::PostToActivityLog(SystemMessage(SystemMessageType::ActivityLog, 0, 0, SString("m_StaticCurrentEngine::ShutDown()")));

    m_CurrentLevel.reset();
    m_StaticCurrentEngine->m_Levels.clear();

    ClearTextures();
    ClearShaders();
    ClearFonts();
    ClearSoundBuffers();

    return Success::GAMELOOP_SUCCESS;
  }

  UINT32 Engine::StaticShutDown()
  {
    Messager::PostToActivityLog(SystemMessage(SystemMessageType::ActivityLog, 0, 0, SString("Engine::StaticShutDown()")));
    SFENGINE_ASSERT(m_StaticCurrentEngine != nullptr);

    for (auto & level : m_StaticCurrentEngine->m_Levels) {
      level.second->Unload();
      level.second->CleanUp();
    }

    if (StartingLevel)
      StartingLevel.reset();

    m_EngineGUI.reset();
    delete m_StaticCurrentEngine->m_CurrentRenderWindow;

    delete m_StaticCurrentEngine;
    m_StaticCurrentEngine = nullptr;

    Messager::PurgeLogsToFile("MessageCachePurge.log", "ActivityLogPurge.log", "RankedMessageLogPurge.log");
    Messager::Shutdown();

    return 0;
  }

} // namespace SFEngine
