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
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  UINT32 Engine::GameLoop()
  {
    sf::Event SEvent;

    SFENGINE_ASSERT(m_CurrentRenderWindow != nullptr);

    SharedRTexture LevelTexture = std::make_shared<RTexture>();
    auto Size = m_CurrentRenderWindow->getSize();
    LevelTexture->create(Size.x, Size.y);

    SRectShape LevelRect;
    LevelRect.setPosition(SVector2F(0.f, 0.f));
    LevelRect.setSize(SVector2F(SF_TOFLOAT(Size.x), SF_TOFLOAT(Size.y)));
    LevelRect.setTexture(&(LevelTexture->getTexture()));
    LevelRect.setTextureRect(SINTRECT(0, 0, SF_TOINT(Size.x), SF_TOINT(Size.y)));

    SFENGINE_ASSERT(StartingLevel);
    m_CurrentLevel = StartingLevel;

    STime fTime;
    
    auto CEngine = GetCurrentEngine();
    SFENGINE_ASSERT(CEngine);

    bool Closed = false;

    SClockHigh::time_point LastTickStart = SClockHigh::now();
    SClockHigh::time_point CurrentTickStart = SClockHigh::now();

    SClockHigh::time_point UpdateStart;
    SClockHigh::time_point UpdateEnd;
    SClockHigh::time_point RenderStart;
    SClockHigh::time_point RenderEnd;

    SFLOAT STickDelta = 0.f;
    SFLOAT SUpdateDelta = 0.f;
    SFLOAT SRenderDelta = 0.f;
    SFLOAT STickDeltaAccumulator = 0.f;
    SFLOAT STickAccumulatorRemainder = 0.f;

    for (;;) {
      Closed = CEngine->m_Handler.PollEvents(m_CurrentRenderWindow, SEvent, true);

      if (Closed || CEngine->m_SignalForClose || !m_CurrentRenderWindow || !m_CurrentRenderWindow->isOpen())
        break;

      try
      {
        CurrentTickStart = SClockHigh::now();
        STickDelta = STimeDuration<SFLOAT, std::milli>(CurrentTickStart - LastTickStart).count();
        if (STickDelta > 0.25f)
          STickDelta = 0.25f;

        STickDeltaAccumulator += STickDelta;

        while (STickDeltaAccumulator >= STickAccumulatorRemainder) {
          CEngine->StepSimulation(STickDelta, STickAccumulatorRemainder);
          STickDeltaAccumulator -= STickAccumulatorRemainder;
        }

        CEngine->RenderPass(LevelTexture, LevelRect);

        GUI()->draw();
        m_CurrentRenderWindow->display();
      }
      catch (EngineRuntimeError& e)
      {
        ERR << "Runtime Exception (Uncaught) : " << e.what() << std::endl;
      }

    } // for (;;)

    return 0;
  } // Engine::GameLoop

}
