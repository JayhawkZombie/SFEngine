#ifndef SFEngine_DeviceState_H
#define SFEngine_DeviceState_H

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
#include "BasicIncludes.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        DeviceState                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

namespace SFEngine
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
    STDUnorderedMap<Keyboard::Key, bool> m_KeysDown;
    STDUnorderedMap<Keyboard::Key, bool> m_KeysDownLast;

    STDVector<Keyboard::Key> m_KeysReleasedVec;
    STDVector<Keyboard::Key> m_KeysPressedVec;
  };

  class MouseInputState
  {
  public:
    MouseInputState();
    ~MouseInputState() = default;

    void Update(const sf::Event &event);
    SVector2I GetPosition() const;
    SVector2I GetLastPosition() const;

    bool IsMouseButtonDown(const Mouse::Button &mouse) const;
    bool WasMouseButtonDown(const Mouse::Button &mouse) const;

  private:
    STDUnorderedMap<sf::Mouse::Button, bool> m_ButtonsDown;
    STDUnorderedMap<sf::Mouse::Button, bool> m_ButtonsDownLast;
    SVector2I m_Position;
    SVector2I m_LastPosition;
    STDVector<Mouse::Button> m_ButtonPressedVec;
    STDVector<Mouse::Button> m_ButtonsReleasedVec;
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

#endif // SFEngine_DeviceState_H 
