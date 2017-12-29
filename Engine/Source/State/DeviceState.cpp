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

#include "State\DeviceState.h"
#include "Globals\GlobalHooks.h"

namespace Engine
{

  InputDeviceState::InputDeviceState(const InputDeviceState &State)
  {

  }

  void InputDeviceState::Update(const sf::Event & event)
  {
    m_KeyState.Update(event);
    m_MouseState.Update(event);
  }

  bool InputDeviceState::IsKeyDown(const Keyboard::Key & key) const
  {
    return m_KeyState.IsKeyDown(key);
  }

  bool InputDeviceState::IsKeyUp(const Keyboard::Key & key) const
  {
    return !m_KeyState.IsKeyDown(key);
  }

  bool InputDeviceState::WasKeyDown(const Keyboard::Key & key) const
  {
    return m_KeyState.WasKeyDown(key);
  }

  bool InputDeviceState::WasKeyReleased(const Keyboard::Key & key) const
  {
    return (!m_KeyState.IsKeyDown(key) && m_KeyState.WasKeyDown(key));
  }

  bool InputDeviceState::IsMouseButtonDown(const Mouse::Button & mouse) const
  {
    return m_MouseState.IsMouseButtonDown(mouse);
  }

  bool InputDeviceState::IsMouseButtonUp(const Mouse::Button & mouse) const
  {
    return !m_MouseState.IsMouseButtonDown(mouse);
  }

  bool InputDeviceState::WasMouseButtonReleased(const Mouse::Button & mouse) const
  {
    return (m_MouseState.WasMouseButtonDown(mouse) && !m_MouseState.IsMouseButtonDown(mouse));
  }

  KeyboardInputState::KeyboardInputState()
  {
    m_KeysPressedVec.resize(Keyboard::KeyCount);
    m_KeysReleasedVec.resize(Keyboard::KeyCount);
  }

  void KeyboardInputState::Update(const sf::Event & event)
  {
    //Keys released last frame, clear them out of the map
    for (auto & key : m_KeysReleasedVec) {
      m_KeysDown[key] = false;
      m_KeysDownLast[key] = false;
    }
    //Keys pressed last frame, add them to m_KeysDownLast
    for (auto & key : m_KeysPressedVec) {
      m_KeysDownLast[key] = true;
    }

    m_KeysPressedVec.clear();
    m_KeysReleasedVec.clear();

    if (event.type == sf::Event::KeyPressed) {
      Keyboard::Key key = event.key.code;
      m_KeysDown[key] = true;
      m_KeysDownLast[key] = false;
      m_KeysPressedVec.push_back(key);
    }
    else if (event.type == sf::Event::KeyReleased) {
      Keyboard::Key key = event.key.code;
      m_KeysDownLast[key] = true;
      m_KeysDown[key] = false;
      m_KeysReleasedVec.push_back(key);
    }
  }

  bool KeyboardInputState::IsKeyDown(const Keyboard::Key & key) const
  {
    return m_KeysDown.at(key);
  }

  bool KeyboardInputState::WasKeyDown(const Keyboard::Key & key) const
  {
    return m_KeysDownLast.at(key);
  }

  MouseInputState::MouseInputState()
  {
    m_ButtonPressedVec.resize(6);
    m_ButtonsReleasedVec.resize(6);
  }

  void MouseInputState::Update(const sf::Event & event)
  {
    for (auto & button : m_ButtonPressedVec) {
      m_ButtonsDownLast[button] = true;
    }
    for (auto & button : m_ButtonsReleasedVec) {
      m_ButtonsDownLast[button] = false;
      m_ButtonsDown[button] = false;
    }

    m_ButtonPressedVec.clear();
    m_ButtonsReleasedVec.clear();

    if (currentRenderWindow)
      m_Position = sf::Mouse::getPosition(*currentRenderWindow);
    else
      m_Position = sf::Mouse::getPosition();

    if (event.type == sf::Event::MouseButtonPressed) {
      Mouse::Button button = event.mouseButton.button;
      m_ButtonsDown[button] = true;
      m_ButtonsDownLast[button] = false;
      
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
      Mouse::Button button = event.mouseButton.button;
      m_ButtonsDownLast[button] = true;
      m_ButtonsDown[button] = false;
    }
  }

  sf::Vector2i MouseInputState::GetPosition() const
  {
    return m_Position;
  }

  sf::Vector2i MouseInputState::GetLastPosition() const
  {
    return m_LastPosition;
  }

  bool MouseInputState::IsMouseButtonDown(const Mouse::Button &mouse) const
  {
    return m_ButtonsDown.at(mouse);
  }

  bool MouseInputState::WasMouseButtonDown(const Mouse::Button &mouse) const
  {
    return m_ButtonsDownLast.at(mouse);
  }

}
