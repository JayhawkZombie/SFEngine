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

#include "Engine\Engine.h"

namespace Engine
{

  void SFEngine::HandleMouseMovement(const sf::Vector2i &mousePos)
  {
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = false;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.EventType = UserEventType::MouseMovement;
    UEvent.MouseScrolled = false;
    UEvent.MouseScrollDelta = 0.f;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }

  void SFEngine::HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.Button = b;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = true;
    UEvent.MouseButtonWasReleased = false;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.EventType = UserEventType::MousePress;
    UEvent.MouseScrolled = false;
    UEvent.MouseScrollDelta = 0.f;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }

  void SFEngine::HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.Button = b;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = true;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.EventType = UserEventType::MouseRelease;
    UEvent.MouseScrolled = false;
    UEvent.MouseScrollDelta = 0.f;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }

  void SFEngine::HandleMouseScroll(const sf::Vector2i &v, sf::Mouse::Wheel wheel, float delta)
  {
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = v;
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = false;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.MouseScrolled = true;
    UEvent.EventType = (wheel == sf::Mouse::Wheel::HorizontalWheel ? 
                        UserEventType::MouseScrollHorizontal : UserEventType::MouseScrollVertical);
    UEvent.MouseWheenScrolled = wheel;
    UEvent.MouseScrollDelta = delta;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }
}
