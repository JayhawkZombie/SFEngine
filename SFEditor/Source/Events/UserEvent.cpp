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

////////////////////////////////////////////////////////////
// Internal Headers
////////////////////////////////////////////////////////////
#include <Include/Events/UserEvent.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  UserEvent::UserEvent()
  {

  }

  UserEvent::UserEvent(const sf::Event &event, sf::RenderWindow *Win)
    : UserEvent()
  {
    m_PreviousMousePos = m_CurrentMousePos;
    m_CurrentMousePos = sf::Mouse::getPosition(*Win);
    m_LeftMouseButtonDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    m_RightMouseButtonDown = sf::Mouse::isButtonPressed(sf::Mouse::Right);

    switch (event.type)
    {
      case sf::Event::Closed:
      {
        m_EventType = EventType::Closed;
        m_WasClosed = true;
        break;
      }
      case sf::Event::MouseMoved:
      {
        m_EventType = EventType::MouseMoved;
        m_MouseWasMoved = true;
        break;
      }
      case sf::Event::MouseButtonPressed:
      {
        m_EventType = EventType::MousePressed;
        m_MouseButton = event.mouseButton.button;
        m_MousePressed = true;
        break;
      }
      case sf::Event::MouseButtonReleased:
      {
        m_EventType = EventType::MouseReleased;
        m_MouseButton = event.mouseButton.button;
        m_MouseReleased = true;
        break;
      }
      case sf::Event::KeyPressed:
      {
        m_EventType = EventType::KeyPressed;
        m_WasKeyPressed = true;
        m_Key = event.key.code;
        break;
      }
      case sf::Event::KeyReleased:
      {
        m_EventType = EventType::KeyReleased;
        m_WasKeyReleased = true;
        m_Key = event.key.code;
        break;
      }
      case sf::Event::TextEntered:
      {
        m_EventType = EventType::TextEntered;
        m_TextWasEntered = true;
        m_TextUnicode = event.text.unicode;
        break;
      }
      case sf::Event::LostFocus:
      {
        m_EventType = EventType::LostFocus;
        break;
      }
      case sf::Event::GainedFocus:
      {
        m_EventType = EventType::GainedFocus;
        break;
      }
      case sf::Event::MouseEntered:
      {
        m_EventType = EventType::MouseEntered;
        break;
      }
      case sf::Event::MouseLeft:
      {
        m_EventType = EventType::MouseLeft;
        break;
      }
    }
  }

  void UserEvent::OffsetFrom(Vec2i Pos)
  {
    m_CurrentMousePos -= Pos;
    m_PreviousMousePos -= Pos;
  }

  Vec2i UserEvent::GetCurrentMousePos() const
  {
    return m_CurrentMousePos;
  }

  Vec2i UserEvent::GetPreviousMousePos() const
  {
    return m_PreviousMousePos;
  }

  bool UserEvent::IsLeftMouseDown() const
  {
    return ( m_LeftMouseButtonDown );
  }

  bool UserEvent::IsRightMouseDown() const
  {
    return ( m_RightMouseButtonDown );
  }

  bool UserEvent::IsKeyDown(sf::Keyboard::Key key) const
  {
    return sf::Keyboard::isKeyPressed(key);
  }

  bool UserEvent::WasTextEntered() const
  {
    return ( m_TextWasEntered );
  }

  bool UserEvent::IsMouseOver(const sf::IntRect &bounds) const
  {
    return
      (
        ( m_CurrentMousePos.x >= bounds.left ) &&
        ( m_CurrentMousePos.x <= bounds.left + bounds.width ) &&
        ( m_CurrentMousePos.y >= bounds.top ) &&
        ( m_CurrentMousePos.y <= bounds.top + bounds.height )
      );
  }

  bool UserEvent::WasClosed() const
  {
    return m_WasClosed;
  }

  bool UserEvent::WasMouseMoved() const
  {
    return m_MouseWasMoved;
  }

  Key UserEvent::GetKey() const
  {
    return m_Key;
  }

  MouseButton UserEvent::GetMouseButton() const
  {
    return m_MouseButton;
  }

  sf::Uint32 UserEvent::GetTextUnicode() const
  {
    return m_TextUnicode;
  }

  EventType UserEvent::GetEventType() const
  {
    return m_EventType;
  }

}
