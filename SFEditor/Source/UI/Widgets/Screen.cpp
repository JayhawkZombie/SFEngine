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
#include <UI/Widgets/Screen.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <iostream>

namespace SFUI
{

  Screen::Screen()
  {
    m_RespondingToMouseMove = true;
    m_RespondingToMousePress = true;
    m_RespondingToMouseRelease = true;
    m_RespondingToKeyPress = true;
    m_RespondingToKeyRelease = true;
    m_RespondingToTextEnter = true;
  }

  bool Screen::HandleMousePress(const UserEvent &event)
  {
    UserEvent e(event);
    e.OffsetFrom(m_Position);

    auto bounds = Bounds();
    if (!event.IsMouseOver(bounds))
      return false;

    GenericContainer::HandleMousePress(e);

    return true;
  }

  bool Screen::HandleMouseRelease(const UserEvent &event)
  {
    UserEvent e(event);
    e.OffsetFrom(m_Position);

    auto bounds = Bounds();
    if (!event.IsMouseOver(bounds))
      return false;

    GenericContainer::HandleMouseRelease(e);
     

    return true;
  }

  bool Screen::HandleMouseMovement(const UserEvent &event)
  {
    UserEvent e(event);
    e.OffsetFrom(m_Position);

    auto bounds = Bounds();
    if (!event.IsMouseOver(bounds))
      return false;

    GenericContainer::HandleMouseMovement(e);

    return true;
  }

  bool Screen::HandleKeyPressed(const UserEvent &event)
  {
    UserEvent e(event);
    e.OffsetFrom(m_Position);

    GenericContainer::HandleKeyPressed(e);
    return true;
  }

  bool Screen::HandleKeyReleased(const UserEvent &event)
  {
    UserEvent e(event);
    e.OffsetFrom(m_Position);

    GenericContainer::HandleKeyReleased(e);
    return true;
  }

  bool Screen::HandleTextEntered(const UserEvent &event)
  {
    UserEvent e(event);
    e.OffsetFrom(m_Position);

    GenericContainer::HandleTextEntered(e);
    return true;
  }

  void Screen::AddedTo(Screen * Scr)
  {
  }

  void Screen::Initialize()
  {
  }

  void Screen::Cleanup()
  {
  }

  Screen::~Screen()
  {
  }

  Screen::Ptr Screen::Create(std::shared_ptr<RenderTarget> Target, Vec2i Size, Widget *parent)
  {
    Screen::Ptr screen(new Screen(Target));
    screen->SetSize(Size);

    screen->m_Parent = parent;
    if (parent)
      screen->SetPosition(parent->GetPosition());
    return screen;
  }

  void Screen::Render(std::shared_ptr<RenderTarget> Target)
  {
    if (!IsVisible())
      return;

    auto oldView = Target->getView();
    auto newview = View();

    m_Canvas->setView(newview);
    m_Canvas->clear(sf::Color::Transparent);
    
    for (auto & widget : m_Widgets)
      widget.second->Render(m_Canvas);

    m_Canvas->draw(m_TestText);
    m_Canvas->draw(m_EventText);

    m_Canvas->display();
    Target->draw(m_Sprite);
  }

  void Screen::Update()
  {
    if (!IsEnabled())
      return;

    for (auto & widget : m_Widgets)
      widget.second->Update();
  }

  bool Screen::HandleEvent(const UserEvent &event)
  {   
    return BaseHandleEvent(this, event);
  }

  sf::IntRect Screen::Bounds() const
  {
    return sf::IntRect(m_Position, m_Size);
  }

  Vec2i Screen::GetChildOffset() const
  {
    // We use a framebuffer for storing our child objects,
    //  so we can render them at their relative position and 
    //  render our sprite using that framebuffer as a texture
    //  wherever our position happens to be
    return Vec2i(0, 0);
  }

  Screen::Screen(std::shared_ptr<RenderTarget> Target)
  {
    m_Size = Vec2i(Target->getSize());
    m_TestText.setPosition({ 0.f, 0.f });
    m_TestText.setCharacterSize(32);
    m_TestText.setFillColor(sf::Color::White);
    m_TestText.setString("Widget Count: 0");

    auto siz = m_TestText.getGlobalBounds();
    m_EventText.setPosition({ siz.left, siz.top + siz.height + 30.f });
    m_EventText.setCharacterSize(32);
    m_EventText.setFillColor(sf::Color::White);
    m_EventText.setString("Event: None");
  }

  bool Screen::Add(Widget::Ptr widget, std::string ID)
  {
    if (ID == "")
      ID = std::to_string(SFUI::GenerateID());

    if (m_Widgets.find(ID) != m_Widgets.end()) {
      return false;
    }

    m_Widgets[ID] = widget;
    widget->m_Screen = this;
    widget->m_Parent = this;

    //Screens use their own framebuffer, so we don't need to move our children
    m_TestText.setString("Widget count: " + std::to_string(m_Widgets.size()));
    return true;
  }

  bool Screen::Remove(Widget::Ptr widget)
  {
    return GenericContainer::Remove(widget);
  }

  bool Screen::Remove(std::string ID)
  {
    return GenericContainer::Remove(ID);
  }

  bool Screen::RemoveAll()
  {
    return GenericContainer::RemoveAll();
  }

  bool Screen::HideAll()
  {
    return GenericContainer::HideAll();
  }

  bool Screen::ShowAll()
  {
    return GenericContainer::ShowAll();
  }

  std::shared_ptr<sf::RenderWindow> Screen::GetWindow() const
  {
    if (!m_Window)
      return m_Parent->GetWindow();

    return m_Window;
  }

  void Screen::Destroy()
  {
    m_Widgets.clear();
    m_Font.reset();
    Widget::Disable();
  }

  void Screen::SetFont(std::shared_ptr<sf::Font> Font)
  {
    m_Font = Font;
    for (auto & widget : m_Widgets)
      widget.second->SetFont(Font);

    m_TestText.setFont(*Font);
    m_EventText.setFont(*Font);
  }

  void Screen::SetWindow(std::shared_ptr<sf::RenderWindow> Win)
  {
    m_Window = Win;
  }

}
