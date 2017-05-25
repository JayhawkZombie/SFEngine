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
#include <UI/Window.h>
#include <UI/Rendering/Renderers/WidgetRenderer.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  Window::Window()
    : m_Window(nullptr), m_ConnectedWidget(nullptr), m_Open(false), m_Visible(false),
    m_Mutex(std::make_shared<std::mutex>())
  {

  }

  Window::Window(sf::RenderWindow *Win)
    : m_Window(Win), m_ConnectedWidget(nullptr), m_Open(false), m_Visible(false),
    m_Mutex(std::make_shared<std::mutex>())
  {

  }

  Window::~Window()
  {
    if (m_Window)
      m_Window.reset();
    m_Mutex.reset();
  }

  void Window::Create(Vec2i Size, std::string Title, sf::Uint32 Style)
  {
    if (m_Window)
      throw std::runtime_error("Window already exists");

    m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Size.x, Size.y), Title, Style);
    m_Window->setVisible(false);
  }

  void Window::Add(Widget::Ptr widget, std::string ID /*= ""*/)
  {

  }

  void Window::Remove(std::string ID)
  {

  }

  void Window::Remove(Widget::Ptr widget)
  {

  }

  void Window::Close()
  {

  }

  void Window::Open()
  {

  }

  void Window::Hide()
  {

  }

  void Window::Show()
  {

  }

  void Window::LaunchAndLink(Widget::Ptr Connection, std::function<void(boost::any)> DoneCB)
  {
    m_ConnectedWidget = Connection;


    m_Thread = std::thread(
      [CB = DoneCB, this]() -> void
      {
        this->MainLoop(CB);
      }
    );
  }

  void Window::Launch(std::function<void(boost::any)> DoneCB)
  {
    m_Thread = std::thread(
      [CB = DoneCB, this]() -> void
      {
        this->MainLoop(CB);
      }
    );
  }

  bool Window::IsOpen() const
  {
    bool b = false;
    m_Mutex->lock();
    b = m_Window && m_Window->isOpen();
    m_Mutex->unlock();
    return b;
  }

  void Window::MainLoop(std::function<void(boost::any)> DoneCB)
  {
    bool closed = false;

    sf::Event event;

    for ( ; ; ) {

      while (m_Window->pollEvent(event)) {
        HandleEvent(event);
        closed = event.type == sf::Event::Closed;
      }

      if (closed)
        break;

      m_Window->clear(sf::Color::Black);

      auto renderer = m_Screen->Renderer();
      renderer->Render(m_Window);
      m_Window->display();
    }

  }

  void Window::HandleEvent(sf::Event event)
  {
  }

}
