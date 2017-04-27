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
#include "Engine\Engine.h"
#include "Level\BasicLevel.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        HandleMouseEvent                              */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

namespace SFEngine
{

  void Engine::HandleMouseMovement(const sf::Vector2i &v)
  {
    m_UEvent.Key = sf::Keyboard::Unknown;
    m_UEvent.PreviousMousePosition = m_UEvent.CurrentMousePosition;
    m_UEvent.CurrentMousePosition = sf::Mouse::getPosition(*m_CurrentRenderWindow);
    m_UEvent.MouseButtonWasPressed = false;
    m_UEvent.MouseButtonWasReleased = false;
    m_UEvent.KeyRepeat = false;
    m_UEvent.KeyWasPressed = false;
    m_UEvent.KeyWasReleased = false;
    m_UEvent.EventType = UserEventType::MouseMovement;
    m_UEvent.MouseScrolled = false;
    m_UEvent.MouseScrollDelta = 0.f;

    if (m_CurrentLevel)
      m_CurrentLevel->HandleInputEvent(m_UEvent);
  }

  void Engine::HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    m_UEvent.Key = sf::Keyboard::Unknown;
    m_UEvent.Button = b;
    m_UEvent.PreviousMousePosition = m_UEvent.CurrentMousePosition;
    m_UEvent.CurrentMousePosition = sf::Mouse::getPosition(*m_CurrentRenderWindow);
    m_UEvent.MouseButtonWasPressed = true;
    m_UEvent.MouseButtonWasReleased = false;
    m_UEvent.KeyRepeat = false;
    m_UEvent.KeyWasPressed = false;
    m_UEvent.KeyWasReleased = false;
    m_UEvent.EventType = UserEventType::MousePress;
    m_UEvent.MouseScrolled = false;
    m_UEvent.MouseScrollDelta = 0.f;

    if (m_CurrentLevel)
      m_CurrentLevel->HandleInputEvent(m_UEvent);
  }

  void Engine::HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    m_UEvent.Key = sf::Keyboard::Unknown;
    m_UEvent.Button = b;
    m_UEvent.PreviousMousePosition = m_UEvent.CurrentMousePosition;
    m_UEvent.CurrentMousePosition = sf::Mouse::getPosition(*m_CurrentRenderWindow);
    m_UEvent.MouseButtonWasPressed = false;
    m_UEvent.MouseButtonWasReleased = true;
    m_UEvent.KeyRepeat = false;
    m_UEvent.KeyWasPressed = false;
    m_UEvent.KeyWasReleased = false;
    m_UEvent.EventType = UserEventType::MouseRelease;
    m_UEvent.MouseScrolled = false;
    m_UEvent.MouseScrollDelta = 0.f;

    if (m_CurrentLevel)
      m_CurrentLevel->HandleInputEvent(m_UEvent);
  }

  void Engine::HandleMouseScroll(const sf::Vector2i &v, sf::Mouse::Wheel wheel, float delta)
  {
    m_UEvent.Key = sf::Keyboard::Unknown;
    m_UEvent.PreviousMousePosition = m_UEvent.CurrentMousePosition;
    m_UEvent.CurrentMousePosition = v;
    m_UEvent.MouseButtonWasPressed = false;
    m_UEvent.MouseButtonWasReleased = false;
    m_UEvent.KeyRepeat = false;
    m_UEvent.KeyWasPressed = false;
    m_UEvent.KeyWasReleased = false;
    m_UEvent.MouseScrolled = true;
    m_UEvent.EventType = (wheel == sf::Mouse::Wheel::HorizontalWheel ?
                        UserEventType::MouseScrollHorizontal : UserEventType::MouseScrollVertical);
    m_UEvent.MouseWheenScrolled = wheel;
    m_UEvent.MouseScrollDelta = delta;

    if (m_CurrentLevel)
      m_CurrentLevel->HandleInputEvent(m_UEvent);
  }

} // namespace SFEngine
