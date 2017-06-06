#ifndef SFCSS_EVENT_HANDLER_H
#define SFCSS_EVENT_HANDLER_H

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
#include <sfcss/events/userevent.h>
#include <sfcss/utils/box.h>
#include <sfcss/utils/vec.h>
#include <sfcss/common.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <functional>

#include <SFML/Graphics.hpp>

namespace css
{

  class EventHandler
  {

  public:
    EventHandler() = default;

    void HandleEvent(const UserEvent &event);

    std::function<void(const Vec2&)>  m_HandleMouseLeftPress    = DEFAULT_FUNCTION_1ARG;
    std::function<void(const Vec2 &)> m_HandleMouseLeftRelease  = DEFAULT_FUNCTION_1ARG;
    std::function<void(const Vec2 &)> m_HandleMouseRightPress   = DEFAULT_FUNCTION_1ARG;
    std::function<void(const Vec2 &)> m_HandleMouseRightRelease = DEFAULT_FUNCTION_1ARG;
    std::function<void(const Vec2 &)> m_HandleMouseOver = DEFAULT_FUNCTION_1ARG;
    std::function<void(const Vec2 &)> m_HandleMouseExit = DEFAULT_FUNCTION_1ARG;
    std::function<void(const Vec2 &)> m_HandleMouseMove = DEFAULT_FUNCTION_1ARG;
    std::function<void(const sf::Keyboard::Key &)> m_HandleKeyPressed  = DEFAULT_FUNCTION_1ARG;
    std::function<void(const sf::Keyboard::Key &)> m_HandleKeyReleased = DEFAULT_FUNCTION_1ARG;
    std::function<void(void)> m_HandleFocusGained = DEFAULT_FUNCTION_0ARG;
    std::function<void(void)> m_HandleFocusLost   = DEFAULT_FUNCTION_0ARG;
  };

}

#endif // SFCSS_EVENT_HANDLER_H
