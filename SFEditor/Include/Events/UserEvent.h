#ifndef SFEDITOR_USEREVENT_H
#define SFEDITOR_USEREVENT_H

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

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{
  using Vec2i       = sf::Vector2i;
  using Vec2f       = sf::Vector2f;
  using IntRect     = sf::IntRect;
  using Key         = sf::Keyboard::Key;
  using Mouse       = sf::Mouse;
  using MouseButton = sf::Mouse::Button;

  enum class EventType
  {
    MouseMoved,
    MousePressed,
    MouseReleased,
    KeyPressed,
    KeyReleased,
    Closed,
    TextEntered,
    GainedFocus,
    LostFocus,
    MouseEntered,
    MouseLeft
  };

  class UserEvent
  {
  public:
    UserEvent();
    UserEvent(const sf::Event &event, sf::RenderWindow *Win);
    UserEvent(const UserEvent &event) = default;
    void OffsetFrom(Vec2i Pos);
    Vec2i GetCurrentMousePos() const;
    Vec2i GetPreviousMousePos() const;
    bool IsLeftMouseDown() const;
    bool IsRightMouseDown() const;
    bool IsKeyDown(sf::Keyboard::Key key) const;
    bool WasTextEntered() const;
    bool IsMouseOver(const sf::IntRect &bounds) const;
    bool WasClosed() const;
    bool WasMouseMoved() const;
    Key GetKey() const;
    MouseButton GetMouseButton() const;
    sf::Uint32 GetTextUnicode() const;
    EventType GetEventType() const;

  protected:
    Vec2i m_CurrentMousePos     = Vec2i(0, 0);
    Vec2i m_PreviousMousePos    = Vec2i(0, 0);
    bool m_LeftMouseButtonDown  = false;
    bool m_RightMouseButtonDown = false;
    bool m_WasKeyPressed        = false;
    bool m_WasKeyReleased       = false;
    Key m_Key                   = sf::Keyboard::Unknown;
    sf::Uint32 m_TextUnicode    = 0;
    bool m_TextWasEntered       = false;
    bool m_WasClosed            = false;
    bool m_MouseWasMoved        = false;
    bool m_MousePressed         = false;
    bool m_MouseReleased        = false;
    sf::Mouse::Button m_MouseButton;
    EventType m_EventType;

  };

}

#endif // SFEDITOR_USEREVENT_H
