#ifndef SFCSS_USEREVENT_H
#define SFCSS_USEREVENT_H

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
#include <sfcss/utils/vec.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <SFML/System.hpp>

namespace css
{

  struct MouseState
  {
    MouseState(const bool &ld, const bool &rd) : left_down(ld), right_down(rd) {}
    bool left_down = false;
    bool right_down = false;
  };

  class UserEvent
  {
  public:
    UserEvent() = default;
    UserEvent(const sf::Event &event, const sf::RenderWindow &win)
      : m_Type(event.type), m_PreviousMousePosition(0.f, 0.f), m_CurrentMousePosition(0.f, 0.f),
        m_Key(sf::Keyboard::Unknown), m_MouseButton(sf::Mouse::Button::Left), m_Unicode(0)
    {
      m_CurrentMousePosition = sf::Mouse::getPosition(win);
      switch (event.type) {
        case sf::Event::TextEntered:
          m_Unicode = event.text.unicode; break;
        case sf::Event::MouseButtonPressed:
          m_MouseButton = event.mouseButton.button; break;
        case sf::Event::MouseButtonReleased:
          m_MouseButton = event.mouseButton.button; break;
        case sf::Event::KeyPressed:
          m_Key = event.key.code; break;
        case sf::Event::KeyReleased:
          m_Key = event.key.code; break;
      }
    }
    UserEvent(const sf::Event &event, const sf::RenderWindow &win, const UserEvent &last)
      : m_Type(event.type), m_PreviousMousePosition(last.m_CurrentMousePosition)
    {
      m_CurrentMousePosition = sf::Mouse::getPosition(win);
    }
    UserEvent(const UserEvent &event)
      : m_MouseButton(event.m_MouseButton), 
        m_CurrentMousePosition(event.m_CurrentMousePosition), 
        m_Key(event.m_Key),
        m_PreviousMousePosition(event.m_PreviousMousePosition), 
        m_Type(event.m_Type)
    {}
    sf::Uint32 Text() const
    {
      return m_Unicode;
    }

    sf::Event::EventType Type() const { return m_Type; }
    sf::Keyboard::Key Key() const { return m_Key; }
    sf::Mouse::Button MouseButton() const { return m_MouseButton; }
    Vec2 CurrentMousePos() const { return m_CurrentMousePosition; }
    Vec2 PreviousMousePos() const { return m_PreviousMousePosition; }

    void TranslateOrigin(const Vec2 &delta) { m_CurrentMousePosition -= delta; m_PreviousMousePosition -= delta; }
    void UntranslateOrigin(const Vec2 &delta) { m_CurrentMousePosition += delta; m_PreviousMousePosition += delta; }
  private:
    sf::Mouse::Button m_MouseButton;
    sf::Keyboard::Key m_Key;
    sf::Event::EventType m_Type;
    Vec2 m_CurrentMousePosition;
    Vec2 m_PreviousMousePosition;
    sf::Uint32 m_Unicode;
  };

}

#endif // SFCSS_USEREVENT_H
