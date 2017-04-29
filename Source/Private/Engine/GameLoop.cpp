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
#include "Globals.h"
#include "Engine\Engine.h"
#include "Messaging\Messager.h"
#include "Exceptions\Exceptions.hpp"
#include "Level\BasicLevel.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <Physics\common.h>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                           GameLoop                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/29                                  */
/************************************************************************/

namespace SFEngine
{

  UINT32 Engine::GameLoop()
  {
    Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Engine GameLoop"), MessageLogLevel::Normal);

    SClockHigh::time_point LastFrameStart = std::chrono::high_resolution_clock::now();
    SClockHigh::time_point CurrentFrameStart = std::chrono::high_resolution_clock::now();
    SClockHigh::time_point TickEnd;
    SClockHigh::time_point UpdateStart;
    SClockHigh::time_point UpdateEnd;
    SClockHigh::time_point RenderStart;
    SClockHigh::time_point RenderEnd;

    SharedRTexture EditorTexture = std::make_shared<RTexture>();
    EditorTexture->create(static_cast<unsigned int>(std::ceil(WindowSize.x)), static_cast<unsigned int>(std::ceil(WindowSize.y)));
    EditorTexture->clear(sf::Color::Transparent);

    SFLOAT TickDelta = 0.0;
    SFLOAT RenderDelta = 0.0;
    SFLOAT UpdateDelta = 0.0;
    sf::Event evnt;

    m_CurrentRenderWindow->setVerticalSyncEnabled(false);
    m_CurrentRenderWindow->setKeyRepeatEnabled(false);
    bool Closed = false;

    ::vec2d Gravity;
    AssignBoundaries((float)WindowSize.x, (float)WindowSize.y);

    //There MUST be a valid InitialLevel instance to start from
    SFENGINE_ASSERT(StartingLevel);
    sf::Time fTime{ sf::seconds(0) };
    sf::Clock _clock;

    //Draw rect to screen (filled with the render texture)
    SRectShape LevelRect;
    LevelRect.setSize(static_cast<sf::Vector2f>(WindowSize));

    for ( ; ; ) {
      auto EngineInst = GetCurrentEngine();
      SFENGINE_ASSERT(EngineInst);

      Closed = EngineInst->m_Handler.PollEvents(EngineInst->m_CurrentRenderWindow, evnt, true);
      if (Closed || ((m_Flags & Exit) != 0) | !EngineInst->m_CurrentRenderWindow || !EngineInst->m_CurrentRenderWindow->isOpen())
        break;
      
      try
      {

        CurrentFrameStart = SClockHigh::now();
        TickDelta = STimeDuration<SFLOAT, std::milli>(CurrentFrameStart - LastFrameStart).count();
        UpdateDelta = STimeDuration<SFLOAT, std::milli>(UpdateEnd - UpdateStart).count();
        RenderDelta = STimeDuration<SFLOAT, std::milli>(RenderEnd - RenderStart).count();

        UpdateStart = SClockHigh::now();
        fTime = _clock.restart();

#ifdef WITH_EDITOR
        ImGui::SFML::Update(*EngineInst->m_CurrentRenderWindow, fTime);
#endif

        SFENGINE_ASSERT(m_CurrentLevel);
        m_CurrentLevel->TickUpdate(TickDelta);

        UpdateEnd = SClockHigh::now();
        RenderStart = SClockHigh::now();

        /************************************************************************/
        /* Rendering the current level (+ GUI)                                  */
        /************************************************************************/
        auto win = m_StaticCurrentEngine->m_CurrentRenderWindow;
        win->clear(sf::Color::Black);
        EditorTexture->clear(sf::Color::Transparent);
        m_CurrentLevel->RenderOnTexture(EditorTexture);
        EditorTexture->display();

        win->draw(LevelRect);
        Engine::GUI()->draw();
#ifdef WITH_EDITOR
        ImGui::Render();
#endif
        win->display();
        RenderEnd = SClockHigh::now();
        LastFrameStart = CurrentFrameStart;
      }
      catch (EngineRuntimeError& e)
      {
        std::cerr << "EngineRumTimeError: " << e.what() << std::endl;
      }

    } // for ( ; ; )

    EditorTexture.reset();

    return m_StaticCurrentEngine->ShutDown();
  } // Engine::GameLoop

}
