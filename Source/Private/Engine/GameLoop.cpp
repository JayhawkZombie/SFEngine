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
#include <Plinth\Common.hpp>
#include <Kairos\all.hpp>

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
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{

  UINT32 Engine::GameLoop()
  {
    Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Engine GameLoop"), MessageLogLevel::Normal);

    SharedRTexture EditorTexture = std::make_shared<RTexture>();
    EditorTexture->create(static_cast<unsigned int>(std::ceil(WindowSize.x)), static_cast<unsigned int>(std::ceil(WindowSize.y)));
    EditorTexture->clear(sf::Color::Transparent);
    sf::Event evnt;

    m_CurrentRenderWindow->setVerticalSyncEnabled(true);
    m_CurrentRenderWindow->setKeyRepeatEnabled(false);
    bool Closed = false;

    ::vec2d Gravity;
    AssignBoundaries((float)WindowSize.x, (float)WindowSize.y);

    //There MUST be a valid InitialLevel instance to start from
    if (!StartingLevel)
      return m_StaticCurrentEngine->ShutDown();

    sf::Time fTime{ sf::seconds(0) };
    sf::Clock _clock;

    //Draw rect to screen (filled with the render texture)
    SRectShape LevelRect;
    LevelRect.setPosition({ 0.f, 0.f });
    LevelRect.setSize({1700.f, 900.f});
    LevelRect.setTexture(&EditorTexture->getTexture());
    LevelRect.setTextureRect(SINTRECT(0, 0, 1700, 900));

    auto EngineInst = GetCurrentEngine();
    SFENGINE_ASSERT(EngineInst);

    //And just before we begin the game loop, we will tell the current level to begin
    Engine::m_CurrentLevel->OnBegin();

    fpsFont.loadFromFile("./Demos/MainMenu/Assets/Fonts/Raleway-Light.ttf");
    fpsText.setCharacterSize(25);
    fpsText.setFont(fpsFont);
    fpsText.setFillColor(sf::Color(99, 99, 99));
    fpsText.setPosition({WindowSize.x - 800.f, 10.f});

    SFLOAT StepAlpha = 0.f;
    DoInterpolateRender = true;

    for ( ; ; ) {  
      Closed = EngineInst->m_Handler.PollEvents(EngineInst->m_CurrentRenderWindow, evnt, true);
      if (Closed || ((m_Flags & Exit) != 0) || !EngineInst->m_CurrentRenderWindow || !EngineInst->m_CurrentRenderWindow->isOpen())
        break;
      
      try
      {

        StepAlpha = UpdatePass();

        RenderPass(StepAlpha, EditorTexture, LevelRect);
      }
      catch (EngineRuntimeError& e)
      {
        std::cerr << "EngineRumTimeError: " << e.what() << std::endl;
      }

    } // for ( ; ; )

    EditorTexture.reset();
    if (m_CurrentLevel)
      m_CurrentLevel->Unload();

    return ShutDown();
  } // Engine::GameLoop

}
