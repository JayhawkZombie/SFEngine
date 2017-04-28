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

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        HandleKeyEvent                                */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  void Engine::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    m_UEvent.Key = k;
    m_UEvent.TextUnicode = k;
    m_UEvent.TextWasEntered = false;
    m_UEvent.PreviousMousePosition = m_UEvent.CurrentMousePosition;
    m_UEvent.CurrentMousePosition = sf::Mouse::getPosition(*m_CurrentRenderWindow);
    m_UEvent.MouseButtonWasPressed = false;
    m_UEvent.MouseButtonWasReleased = false;
    m_UEvent.EventType = UserEventType::KeyboardPress;
    m_UEvent.KeyRepeat = false;
    m_UEvent.KeyWasPressed = true;
    m_UEvent.KeyWasReleased = false;
    m_UEvent.MouseScrollDelta = 0.f;
    m_UEvent.MouseScrolled = false;

    if (m_CurrentLevel)
      m_CurrentLevel->HandleInputEvent(m_UEvent);
  }

  void Engine::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    m_UEvent.Key = k;
    m_UEvent.TextUnicode = 0;
    m_UEvent.TextWasEntered = false;
    m_UEvent.PreviousMousePosition = m_UEvent.CurrentMousePosition;
    m_UEvent.CurrentMousePosition = sf::Mouse::getPosition(*m_CurrentRenderWindow);
    m_UEvent.MouseButtonWasPressed = false;
    m_UEvent.MouseButtonWasReleased = false;
    m_UEvent.EventType = UserEventType::KeyboardRelease;
    m_UEvent.KeyRepeat = false;
    m_UEvent.KeyWasPressed = false;
    m_UEvent.KeyWasReleased = true;
    m_UEvent.MouseScrollDelta = 0.f;
    m_UEvent.MouseScrolled = false;

    if (m_CurrentLevel)
      m_CurrentLevel->HandleInputEvent(m_UEvent);
  }

  void Engine::HandleTextEntered(const sf::Uint32 &unicode)
  {
    m_UEvent.Key = sf::Keyboard::Unknown;
    m_UEvent.TextUnicode = unicode;
    m_UEvent.TextWasEntered = true;
    m_UEvent.PreviousMousePosition = m_UEvent.CurrentMousePosition;
    m_UEvent.CurrentMousePosition = sf::Mouse::getPosition(*m_CurrentRenderWindow);
    m_UEvent.MouseButtonWasPressed = false;
    m_UEvent.MouseButtonWasReleased = false;
    m_UEvent.EventType = UserEventType::TextEntered;
    m_UEvent.KeyRepeat = false;
    m_UEvent.KeyWasPressed = false;
    m_UEvent.KeyWasReleased = false;
    m_UEvent.MouseScrollDelta = 0.f;
    m_UEvent.MouseScrolled = false;

    if (m_CurrentLevel)
      m_CurrentLevel->HandleInputEvent(m_UEvent);
  }

}
