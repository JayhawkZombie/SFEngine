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
#include "Events\EventHandler.h"
#include "Engine\Engine.h"
#include "Level\BasicLevel.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

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

  EventHandler::EventHandler()
  {
    ftnCallback_KeyPress = [this](const sf::Keyboard::Key &k) {};
    ftnCallback_KeyRelease = [this](const sf::Keyboard::Key &k) {};
    ftnCallback_TextEntered = [this](const sf::Uint32 &) {};
    ftnCallback_MouseExit = [this](const sf::Vector2i &v) {};
    ftnCallback_MouseOver = [this](const sf::Vector2i &v) {};
    ftnCallback_MouseMovement = [this](const sf::Vector2i &v) {};
    ftnCallback_MousePress = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) {};
    ftnCallback_MouseRelease = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) {};
    ftnCallback_MouseScroll = [this](const sf::Vector2i &v, sf::Mouse::Wheel, float) {};
    ftnCallback_WindowClosed = [this]() {};
    ftnCallback_WindowResized = [this]() {};
  }

  EventHandler::~EventHandler()
  {

  }

  void EventHandler::HandleMouseMovement(const sf::Vector2i &v)
  {
    ftnCallback_MouseMovement(v);
  }

  void EventHandler::HandleMouseOver(const sf::Vector2i &v)
  {
    ftnCallback_MouseOver(v);
  }

  void EventHandler::HandleMouseExit(const sf::Vector2i &v)
  {
    ftnCallback_MouseExit(v);
  }

  void EventHandler::HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    ftnCallback_MousePress(v, b);
  }

  void EventHandler::HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    ftnCallback_MouseRelease(v, b);
  }

  void EventHandler::HandleMouseScroll(const sf::Vector2i &v, sf::Mouse::Wheel wheel, float delta)
  {
    ftnCallback_MouseScroll(v, wheel, delta);
  }

  void EventHandler::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    ftnCallback_KeyPress(k);
  }

  void EventHandler::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    ftnCallback_KeyRelease(k);
  }

  void EventHandler::HandleTextEntered(const sf::Keyboard::Key &k)
  {
    ftnCallback_TextEntered(k);
  }


  void EventHandler::BindCallback(const Events &type, std::function<void(const sf::Vector2i &)> ftn)
  {
    switch (type)
    {
    case Events::MouseOver:
      ftnCallback_MouseOver = std::bind(ftn, std::placeholders::_1); break;
    case Events::MouseExit:
      ftnCallback_MouseExit = std::bind(ftn, std::placeholders::_1); break;
    case Events::MouseMoved:
      ftnCallback_MouseMovement = std::bind(ftn, std::placeholders::_1); break;
    }
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftn)
  {
    switch (type)
    {
    case Events::MouseDown:
      ftnCallback_MousePress = std::bind(ftn, std::placeholders::_1, std::placeholders::_2); break;
    case Events::MouseReleased:
      ftnCallback_MouseRelease = std::bind(ftn, std::placeholders::_1, std::placeholders::_2); break;
    }
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(const sf::Vector2i, sf::Mouse::Wheel, float)> ftn)
  {
    switch (type)
    {
    case Events::MouseScrolled:
      ftnCallback_MouseScroll = std::bind(ftn, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3); break;
    }
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(const sf::Keyboard::Key &)> ftn)
  {
    switch (type)
    {
    case Events::KeyPressed:
      ftnCallback_KeyPress = std::bind(ftn, std::placeholders::_1); break;
    case Events::KeyReleased:
      ftnCallback_KeyRelease = std::bind(ftn, std::placeholders::_1); break;
    }
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(void)> ftn)
  {
    switch (type)
    {
    case Events::WindowClosed:
      ftnCallback_WindowClosed = std::bind(ftn); break;
    case Events::WindowResized:
      ftnCallback_WindowResized = std::bind(ftn); break;
    }
  }

  void EventHandler::BindTextEnterHandler(std::function<void(const sf::Uint32&)> ftn)
  {
    ftnCallback_TextEntered = std::bind(ftn, std::placeholders::_1);
  }

  bool EventHandler::PollEvents(sf::RenderWindow *win, sf::Event &evnt, const bool &makeCallbacks)
  {
    auto Win = Engine::GetCurrentRenderWindow();
    auto CLevel = Engine::GetCurrentLevel();
    auto GUI = Engine::GUI();

    v2iMousePosArg = sf::Mouse::getPosition(*Win);
    while (win->pollEvent(evnt)) {
      //ImGui::SFML::ProcessEvent(evnt);
      if (CLevel)
        CLevel->EventUpdate(evnt);

      if (!GUI->handleEvent(evnt) && makeCallbacks) {
        switch (evnt.type)
        {
        case sf::Event::EventType::Closed:
          ftnCallback_WindowClosed(); return true;
        case sf::Event::KeyPressed:
          ftnCallback_KeyPress(evnt.key.code); return false;
        case sf::Event::KeyReleased:
          ftnCallback_KeyRelease(evnt.key.code); return false;
        case sf::Event::TextEntered:
          ftnCallback_TextEntered(evnt.text.unicode); return false;
        case sf::Event::MouseButtonPressed:
          ftnCallback_MousePress(v2iMousePosArg, evnt.mouseButton.button); return false;
        case sf::Event::MouseButtonReleased:
          ftnCallback_MouseRelease(v2iMousePosArg, evnt.mouseButton.button); return false;
        case sf::Event::MouseMoved:
          ftnCallback_MouseMovement(v2iMousePosArg); return false;
        case sf::Event::MouseWheelScrolled:
          ftnCallback_MouseScroll(v2iMousePosArg, evnt.mouseWheelScroll.wheel, evnt.mouseWheelScroll.delta); return false;
        case sf::Event::Resized:
          ftnCallback_WindowResized(); return false;
        }
      }
    }

    return false;
  }

  EventHandler::EventHandler(const EventHandler &handler)
  {

  }

} // namespace SFEngine
