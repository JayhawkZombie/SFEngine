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

namespace
{
  struct KeyboardSC
  {
    KeyboardSC() = default;
    KeyboardSC(const KeyboardSC &other)
      : Keys(other.Keys), CB(other.CB), WasUsed(other.WasUsed) {}

    std::vector<sf::Keyboard::Key> Keys;
    std::function<void(void)> CB;
    bool WasUsed = false;
  };
  std::vector<KeyboardSC> KeyboardShortcuts;
}

void AddKeyboardShortcut(const std::vector<sf::Keyboard::Key> &keys, std::function<void(void)> callback)
{
  KeyboardSC SC;
  SC.Keys = keys;
  SC.CB = callback;
  SC.WasUsed = false;
  KeyboardShortcuts.push_back(SC);
}

void CheckKeyboardShortcuts()
{
  bool use = true;
  for (auto SC : KeyboardShortcuts) {
    for (auto & key : SC.Keys) {
      if (!sf::Keyboard::isKeyPressed(key)) {
        SC.WasUsed = false;
        use = false;
        break;
      }
    }
    if (use)
      SC.CB();
  }
}

void SFEngine::HandleTextEntered(const sf::Uint32 &unicode)
{
  UEvent.Key = sf::Keyboard::Unknown;
  UEvent.TextUnicode = unicode;
  UEvent.TextWasEntered = true;
  UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
  UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
  UEvent.MouseButtonWasPressed = false;
  UEvent.MouseButtonWasReleased = false;
  UEvent.EventType = UserEventType::TextEntered;
  UEvent.KeyRepeat = false;
  UEvent.KeyWasPressed = false;
  UEvent.KeyWasReleased = false;
  UEvent.MouseScrollDelta = 0.f;
  UEvent.MouseScrolled = false;

  if (CurrentLevel)
    CurrentLevel->HandleInputEvent(UEvent);

}

void SFEngine::HandleKeyPress(const sf::Keyboard::Key &k)
{
  UEvent.Key = k;
  UEvent.TextUnicode = k;
  UEvent.TextWasEntered = false;
  UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
  UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
  UEvent.MouseButtonWasPressed = false;
  UEvent.MouseButtonWasReleased = false;
  UEvent.EventType = UserEventType::KeyboardPress;
  UEvent.KeyRepeat = false;
  UEvent.KeyWasPressed = true;
  UEvent.KeyWasReleased = false;
  UEvent.MouseScrollDelta = 0.f;
  UEvent.MouseScrolled = false;

  if (CurrentLevel)
    CurrentLevel->HandleInputEvent(UEvent);

  CheckKeyboardShortcuts();
}

void SFEngine::HandleKeyRelease(const sf::Keyboard::Key &k)
{
  UEvent.Key = k;
  UEvent.TextUnicode = 0;
  UEvent.TextWasEntered = false;
  UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
  UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
  UEvent.MouseButtonWasPressed = false;
  UEvent.MouseButtonWasReleased = false;
  UEvent.EventType = UserEventType::KeyboardRelease;
  UEvent.KeyRepeat = false;
  UEvent.KeyWasPressed = false;
  UEvent.KeyWasReleased = true;
  UEvent.MouseScrollDelta = 0.f;
  UEvent.MouseScrolled = false;

  if (CurrentLevel)
    CurrentLevel->HandleInputEvent(UEvent);
}
