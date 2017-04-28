#ifndef SFEngine_EventHandler_H
#define SFEngine_EventHandler_H

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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
#include <functional>

/************************************************************************/
/*                        EventHandler                                  */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  enum class Events
  {
    MouseDown
    , MouseReleased
    , MouseOver
    , MouseExit
    , MouseMoved
    , KeyPressed
    , KeyReleased
    , TextEntered
    , WindowResized
    , LostFocus
    , GainedFocus
    , WindowClosed
    , MouseScrolled
  };

  class EventHandler
  {
  public:
    friend class BaseEngineInterface;

    EventHandler();
    EventHandler(const EventHandler &);
    ~EventHandler();

    void BindCallback(const Events &type, std::function<void(const sf::Vector2i &)> ftn);
    void BindCallback(const Events &type, std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftn);
    void BindCallback(const Events &type, std::function<void(const sf::Keyboard::Key &)> ftn);
    void BindCallback(const Events &type, std::function<void(void)> ftn);
    void BindCallback(const Events &type, std::function<void(const sf::Vector2i, sf::Mouse::Wheel, float)> ftn);
    void BindTextEnterHandler(std::function<void(const sf::Uint32 &)> ftn);

    bool PollEvents(sf::RenderWindow *win, sf::Event &evnt, const bool &makeCallbacks);

    void HandleMouseMovement(const sf::Vector2i &v);
    void HandleMouseOver(const sf::Vector2i &v);
    void HandleMouseExit(const sf::Vector2i &v);
    void HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b);
    void HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b);
    void HandleMouseScroll(const sf::Vector2i &v, sf::Mouse::Wheel wheel, float delta);
    void HandleKeyPress(const sf::Keyboard::Key &k);
    void HandleKeyRelease(const sf::Keyboard::Key &k);
    void HandleTextEntered(const sf::Keyboard::Key &k);
  protected:
    sf::Vector2i v2iMousePosArg;
    sf::Mouse::Button enMouseButtonArg;
    sf::Keyboard::Key enKeyboardArg;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseMovement;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseOver;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseExit;
    std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftnCallback_MousePress;
    std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftnCallback_MouseRelease;
    std::function<void(const sf::Vector2i &, sf::Mouse::Wheel, float)> ftnCallback_MouseScroll;
    std::function<void(const sf::Keyboard::Key &)> ftnCallback_KeyPress;
    std::function<void(const sf::Keyboard::Key &)> ftnCallback_KeyRelease;
    std::function<void(const sf::Uint32 &)> ftnCallback_TextEntered;

    std::function<void(void)> ftnCallback_WindowClosed;
    std::function<void(void)> ftnCallback_WindowResized;
  };

}

#endif // SFEngine_EventHandler_H
