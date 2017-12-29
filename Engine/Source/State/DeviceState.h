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

#include "Events\UserEvent.h"
#include <unordered_map>
#include <SFML\System.hpp>

namespace Engine
{
  using sf::Keyboard;
  using sf::Mouse;

  class KeyboardInputState
  {
  public:
    KeyboardInputState();
    ~KeyboardInputState() = default;

    void Update(const sf::Event &event);

    bool IsKeyDown(const Keyboard::Key &key) const;
    bool WasKeyDown(const Keyboard::Key &key) const;

  private:
    std::unordered_map<Keyboard::Key, bool> m_KeysDown;
    std::unordered_map<Keyboard::Key, bool> m_KeysDownLast;

    std::vector<Keyboard::Key> m_KeysReleasedVec;
    std::vector<Keyboard::Key> m_KeysPressedVec;
  };

  class MouseInputState
  {
  public:
    MouseInputState();
    ~MouseInputState() = default;

    void Update(const sf::Event &event);
    sf::Vector2i GetPosition() const;
    sf::Vector2i GetLastPosition() const;

    bool IsMouseButtonDown(const Mouse::Button &mouse) const;
    bool WasMouseButtonDown(const Mouse::Button &mouse) const;

  private:
    std::unordered_map<sf::Mouse::Button, bool> m_ButtonsDown;
    std::unordered_map<sf::Mouse::Button, bool> m_ButtonsDownLast;
    sf::Vector2i m_Position;
    sf::Vector2i m_LastPosition;
    std::vector<Mouse::Button> m_ButtonPressedVec;
    std::vector<Mouse::Button> m_ButtonsReleasedVec;
  };

  class TouchInputState
  {

  };

  class JoystickInputState
  {

  };

  class InputDeviceState
  {
  public:
    InputDeviceState() = default;
    InputDeviceState(const InputDeviceState &);
    ~InputDeviceState() = default;

    void Update(const sf::Event &event);

    bool IsKeyDown(const Keyboard::Key &key) const;
    bool IsKeyUp(const Keyboard::Key &key) const;
    bool WasKeyDown(const Keyboard::Key &key) const;
    bool WasKeyReleased(const Keyboard::Key &key) const;
    bool IsMouseButtonDown(const Mouse::Button &mouse) const;
    bool IsMouseButtonUp(const Mouse::Button &mouse) const;
    bool WasMouseButtonReleased(const Mouse::Button &mouse) const;

  protected:
    KeyboardInputState m_KeyState;
    MouseInputState    m_MouseState;
  };

}
