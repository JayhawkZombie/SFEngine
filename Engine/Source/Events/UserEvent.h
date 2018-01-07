#pragma once

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

#include <SFML\Graphics.hpp>

enum class UserEventType : std::uint32_t
{
  MousePress, //Pressing on a mouse button
  MouseRelease, //Releasing a mouse button
  MouseMovement, //Moving the mouse inside the bounds of an element
  MouseScrollVertical, //Scrolling a mouse wheel up/down
  MouseScrollHorizontal, //Scrolling a mouse wheel left/right
  KeyboardPress, //Pressing a key on the keyboard
  KeyboardRelease, //Releasing a key on the keyboard
  TextEntered,
  Unknown
};

class UserEvent
{
public:
  UserEvent() = default;
  ~UserEvent() = default;
  UserEvent(const UserEvent &event)
    :
    MouseButtonWasPressed(event.MouseButtonWasPressed),
    MouseButtonWasReleased(event.MouseButtonWasReleased),
    KeyWasPressed(event.KeyWasPressed),
    KeyWasReleased(event.KeyWasReleased),
    KeyRepeat(event.KeyRepeat),
    Key(event.Key),
    Button(event.Button),
    EventType(event.EventType)
  {}

  bool IsButtonPressed(const sf::Keyboard::Key key) const {
    return sf::Keyboard::isKeyPressed(key);
  }
  bool IsMouseButtonDown(const sf::Mouse::Button &button) const {
    return sf::Mouse::isButtonPressed(button);
  }
  bool WasMouseWheelScrolled() const {
    return MouseScrolled;
  }

  bool MouseButtonWasPressed = false;
  bool MouseButtonWasReleased = false;

  bool KeyWasPressed = false;
  bool KeyWasReleased = false;
  bool KeyRepeat = false;

  bool TextWasEntered = false;
  bool MouseScrolled = false;

  float MouseScrollDelta = 0.f;
  sf::Uint32 TextUnicode;

  sf::Keyboard::Key Key;
  sf::Mouse::Button Button;

  sf::Vector2i CurrentMousePosition = { 0, 0 };
  sf::Vector2i PreviousMousePosition = { 0, 0 };

  sf::Mouse::Wheel MouseWheenScrolled;

  UserEventType EventType;

  /* Serialization */

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(MouseButtonWasPressed, MouseButtonWasReleased);
    ar(KeyWasPressed, KeyWasReleased, KeyRepeat);
    ar(TextWasEntered, MouseScrolled);
    ar(MouseScrollDelta);
    ar(TextUnicode);
    ar(Key);
    ar(Button);
    ar(CurrentMousePosition, PreviousMousePosition);
    ar(MouseWheenScrolled);
    ar(EventType);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(MouseButtonWasPressed, MouseButtonWasReleased);
    ar(KeyWasPressed, KeyWasReleased, KeyRepeat);
    ar(TextWasEntered, MouseScrolled);
    ar(MouseScrollDelta);
    ar(TextUnicode);
    ar(Key);
    ar(Button);
    ar(CurrentMousePosition, PreviousMousePosition);
    ar(MouseWheenScrolled);
    ar(EventType);
  }

};
