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
#include "Globals.h"
#include "Messaging\Messager.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                               Init                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/29                                  */
/************************************************************************/

namespace SFEngine
{

  UINT32 Engine::Init(int argc, char **argv)
  {
    SFENGINE_ASSERT(m_StaticCurrentEngine != nullptr);

    SFENGINE_ASSERT(m_StaticCurrentEngine->m_Configuration.WindowSize.x != 0 &&
                    m_StaticCurrentEngine->m_Configuration.WindowSize.y != 0);

    auto size = m_StaticCurrentEngine->m_Configuration.WindowSize;
    auto title = m_StaticCurrentEngine->m_Configuration.WindowTitle;

    WindowSize = size;

    m_StaticCurrentEngine->m_CurrentRenderWindow = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title, m_StaticCurrentEngine->m_Configuration.Style, m_StaticCurrentEngine->m_Configuration.__context_settings);

    sf::Texture texture;
    sf::RectangleShape SplashRect;
    SplashRect.setSize(static_cast<sf::Vector2f>(size));

    m_StaticCurrentEngine->m_TimeStep.setStep(1.0 / 40.0);
    m_StaticCurrentEngine->m_TimeStep.setMaxAccumulation(0.50);

    //Should we show a splash screen while this thing boots up?
    if (m_StaticCurrentEngine->m_Configuration.ShowSplashScreen) {
      texture.loadFromFile(m_StaticCurrentEngine->m_Configuration.SplashScreenTexturePath);
      SplashRect.setTexture(&texture);
    }
    else {
      texture.loadFromFile("./Source/Assets/Logos/SFEngineLogoNewAnalogized.png");
      SplashRect.setTexture(&texture);
    }

    m_StaticCurrentEngine->m_CurrentRenderWindow->clear(sf::Color::Black);
    m_StaticCurrentEngine->m_CurrentRenderWindow->draw(SplashRect);
    m_StaticCurrentEngine->m_CurrentRenderWindow->display();

    return m_StaticCurrentEngine->Startup();
  }

}
