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

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  Window::Window()
    : m_Window(nullptr), m_ConnectedWidget(nullptr), m_Open(false), m_Visible(false), m_Texture(nullptr)
  {

  }

  Window::Window(sf::RenderWindow *Win)
    : m_Window(Win), m_ConnectedWidget(nullptr), m_Open(false), m_Visible(false)
  {
    auto size = Win->getSize();
    Win->setActive(true);
    m_Texture = std::make_shared<sf::RenderTexture>();
    m_Texture->create(size.x, size.y);
    m_Sprite.setTexture(m_Texture->getTexture());
    m_Screen = Screen::Create(m_Texture, Vec2i(size), this);
  }

  Window::~Window()
  {
    m_Window = nullptr;
  }

  void Window::Update()
  {
    if (m_Visible && m_Window)
      m_Screen->Update();
  }

  void Window::Render(std::shared_ptr<RenderTarget> Target)
  {
    if (!m_Visible || !m_Window)
      return;

    m_Texture->clear(sf::Color::Transparent);
    m_Screen->Render(m_Texture);
    m_Texture->display();
    Target->draw(m_Sprite);
  }

  void Window::Render()
  {
    if (!m_Visible || !m_Window)
      return;

    m_Texture->clear(sf::Color::Transparent);
    m_Screen->Render(m_Texture);
    m_Texture->display();
    m_Window->draw(m_Sprite);
  }

  void Window::Add(Widget::Ptr widget, std::string ID /*= ""*/)
  {
    if (m_Screen)
      m_Screen->Add(widget, ID);
  }

  void Window::Remove(std::string ID)
  {
    if (m_Screen)
      m_Screen->Remove(ID);
  }

  void Window::Remove(Widget::Ptr widget)
  {
    if (m_Screen)
      m_Screen->Remove(widget);
  }

  void Window::Close()
  {
    if (m_Screen)
      m_Screen->RemoveAll();
  }

  void Window::Open()
  {

  }

  void Window::Hide()
  {
    m_Visible = false;
  }

  void Window::Show()
  {
    m_Visible = true;
  }

  void Window::SetWindow(sf::RenderWindow * Win)
  {
    m_Window = Win;
    auto size = Win->getSize();
    if (!m_Texture)
      m_Texture = std::make_shared<sf::RenderTexture>();

    m_Texture->create(size.x, size.y);
    m_Sprite.setTexture(m_Texture->getTexture());
  }

  bool Window::IsOpen() const
  {
    return m_Window && m_Window->isOpen();
  }

  bool Window::HandleEvent(const UserEvent &event)
  {
    if (m_Screen->IsActive() && m_Screen->IsVisible())
      return m_Screen->HandleEvent(event);
    return false;
  }

  void Window::SetFont(std::shared_ptr<sf::Font> Font)
  {
    m_Font = Font;
    m_Screen->SetFont(Font);
  }

  void Window::OnKilled()
  {
  }

  void Window::OnCreated()
  {
  }

  void Window::OnHover(Vec2i where)
  {
  }

  void Window::OnEnter(Vec2i where)
  {
  }

  void Window::OnExit(Vec2i where)
  {
  }

  void Window::AddedTo(Screen * Scr)
  {
  }

  void Window::Initialize()
  {
  }

  void Window::Cleanup()
  {
  }

  bool Window::HandleMousePress(const UserEvent &event)
  {
    return true;
  }

  bool Window::HandleMouseRelease(const UserEvent &event)
  {
    return true;
  }

  bool Window::HandleMouseMovement(const UserEvent &event)
  {
    return true;
  }

  bool Window::HandleKeyPressed(const UserEvent &event)
  {
    return true;
  }

  bool Window::HandleKeyReleased(const UserEvent &event)
  {
    return true;
  }

  bool Window::HandleTextEntered(const UserEvent &event)
  {
    return true;
  }

}
