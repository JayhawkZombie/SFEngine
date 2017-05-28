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
#include <UI/Widgets/Widget.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <iostream>

namespace SFUI
{
  Widget::RPtr Widget::MouseOverWidget = nullptr;

  Widget::Widget()
    : m_Position(0, 0), m_Size(0, 0), m_Parent(nullptr), m_IsVisible(true),
    m_IsActive(true), m_IsEnabled(true), m_IsFocused(false)
    , m_RespondingToMouseMove(true)
    , m_RespondingToMousePress(true)
    , m_RespondingToMouseRelease(true)
    , m_RespondingToKeyPress(true)
    , m_RespondingToKeyRelease(true)
    , m_RespondingToTextEnter(false)
  {
    m_RespondingToEvent |= (int)( EventType::KeyPressed )
                        | (int)( EventType::KeyReleased )
                        | (int)( EventType::MouseMoved )
                        | (int)( EventType::MousePressed )
                        | (int)( EventType::MouseReleased )
                        | (int)( EventType::TextEntered );
  }

  Widget::~Widget()
  {

  }

  void Widget::Update()
  {
  }

  sf::View Widget::View() const
  {
    sf::FloatRect bounds = static_cast<sf::FloatRect>(
      Bounds()
    );

    
    
    //Now get the bounds of our parent (if we have one)
    sf::FloatRect pBounds = static_cast<sf::FloatRect>(
      m_Parent ? m_Parent->Bounds() : Bounds()
    );

    sf::View view;
    view.reset(bounds);
    view.setViewport( 
    {
      bounds.left / pBounds.width,
      bounds.top / pBounds.height,
      bounds.width / pBounds.width,
      bounds.height / pBounds.height
    }
    );
    return view;
  }

  bool Widget::HandleEvent(const UserEvent &event)
  {
    return false;
  }

  void Widget::Hide()
  {
    m_IsVisible = false;
  }

  void Widget::Show()
  {
    m_IsVisible = true;
  }

  void Widget::Enable()
  {
    m_IsEnabled = true;
  }

  void Widget::Disable()
  {
    m_IsEnabled = false;
  }

  sf::IntRect Widget::Bounds() const
  {
    //Normally our bounds would just be our position + our size
    //  but if we have a parent widget that is a container
    //  then we need to offset by whatever the ChildOffset is
    //    (because our position is relative to our parent, not the global window)
    sf::IntRect bounds(m_Position, m_Size);
    if (m_Parent) {
      auto offset = m_Parent->GetChildOffset();
      bounds.left += offset.x;
      bounds.top += offset.y;
    }
    
    return bounds;
  }

  void Widget::SetPosition(const Vec2i & v)
  {
    m_Position = v;
  }

  void Widget::Move(const Vec2i & v)
  {
    m_Position += v;
  }

  void Widget::SetSize(const Vec2i & v)
  {
    m_Size = v;
  }

  void Widget::SetFont(std::shared_ptr<sf::Font> Font)
  {
    m_Font = Font;
  }

  Vec2i Widget::GetGlobalPosition()
  {

    Vec2i pos = m_Position;
    if (m_Parent)
      pos += m_Parent->GetGlobalPosition();

    return pos;
  }

  Vec2i Widget::GetPosition() const
  {
    return m_Position;
  }

  Vec2i Widget::GetChildOffset() const
  {
    //If our parent is a container that holds our positions relative to its corner
    //  we need to get whatever our offset is
    if (m_Parent)
      return m_Parent->GetChildOffset();
    
    return Vec2i(0, 0);
  }

  Vec2i Widget::GetSize() const
  {
    return m_Size;
  }

  std::shared_ptr<sf::RenderWindow> Widget::GetWindow() const
  {
    if (m_Parent)
      return m_Parent->GetWindow();

    return nullptr;
  }

  Vec2i Widget::ToLocalCoords(Vec2i v)
  {
    return ( v - GetGlobalPosition() );
  }

  void Widget::AlignInBounds(sf::IntRect bounds, Alignment alignment)
  {
    auto mBounds = Bounds();
    auto xDiff = (bounds.width - mBounds.width) / 2.f;
    auto yDiff = (bounds.height - mBounds.height) / 2.f;

    int vAlign = ( alignment & 0b0000111 );
    int hAlign = ( alignment & 0b0111000 );

    switch (vAlign)
    {
      case VerticalAlignment::Top:
        m_Position.y = bounds.top; break;
      case VerticalAlignment::vCenter:
        m_Position.y = bounds.top + static_cast<int>( yDiff / 2.f ); break;
      case VerticalAlignment::Bottom:
        m_Position.y = bounds.top + bounds.height - m_Size.y; break;
    }

    switch (hAlign)
    {
      case HorizontalAlignment::Left:
        m_Position.x = bounds.left; break;
      case HorizontalAlignment::hCenter:
        m_Position.x = bounds.left + static_cast<int>( xDiff ); break;
      case HorizontalAlignment::Right:
        m_Position.x = bounds.left + bounds.width - m_Size.x; break;
    }
  }

  bool Widget::IsRespondingTo(EventType type) const
  {
    switch (type)
    {
      case EventType::Closed:
        return false;
      case EventType::MouseMoved:
        return m_RespondingToMouseMove;
      case EventType::MousePressed:
        return m_RespondingToMousePress;
      case EventType::MouseReleased:
        return m_RespondingToMouseRelease;
      case EventType::KeyPressed:
        return m_RespondingToKeyPress;
      case EventType::KeyReleased:
        return m_RespondingToKeyRelease;
      case EventType::TextEntered:
        return m_RespondingToTextEnter;
      default:
        return false;
    }
  }

  void Widget::Connect(std::string slot, std::function<void(void)> ftn)
  {
    if (slot == "killed") {
      OnKilledCallback = ftn;
    }
    else if (slot == "created") {
      OnCreatedCallback = ftn;
    }
    else if (slot == "init") {
      OnInitCallback = ftn;
    }
  }

  void Widget::Connect(std::string slot, std::function<void(Vec2i)> ftn)
  {
    if (slot == "enter") {
      OnMouseEnterCallback = ftn;
    }
    else if (slot == "exit") {
      OnMouseExitCallback = ftn;
    }

  }

  void Widget::Connect(std::string slot, std::function<void(Vec2i, MouseButton)> ftn)
  {
    if (slot == "pressed") {
      OnMousePressedCallback = ftn;
    }
    else if (slot == "released") {
      OnMouseReleasedCallback = ftn;
    }
  }

  bool Widget::IsActive() const
  {
    return m_IsActive;
  }

  bool Widget::IsVisible() const
  {
    return m_IsVisible;
  }

  bool Widget::IsHidden() const
  {
    return !m_IsVisible;
  }

  bool Widget::IsFocused() const
  {
    return m_IsFocused;
  }

  bool Widget::IsEnabled() const
  {
    return m_IsEnabled;
  }

  bool Widget::IsDisabled() const
  {
    return !m_IsEnabled;
  }

  bool Widget::BaseHandleEvent(Widget::RPtr widget, const UserEvent &event)
  {
    if (!widget->IsVisible() || !widget->IsEnabled())
      return false;

    auto bounds = widget->Bounds();
    bool handled = false;

    switch (event.GetEventType())
    {
      case EventType::Closed:
        return false;
      case EventType::MouseMoved:
      {
        if (event.IsMouseOver(bounds)) {
          handled = widget->HandleMouseMovement(event);
        }
        else {
          if (MouseOverWidget == widget)
            widget->ChangeMousedOverWidget(event.GetCurrentMousePos());
        }
        break;
      }
      case EventType::KeyPressed:
      {
        handled = widget->HandleKeyPressed(event);
        break;
      }
      case EventType::KeyReleased:
      {
        handled = widget->HandleKeyReleased(event);
        break;
      }
      case EventType::MousePressed:
      {
        if (event.IsMouseOver(bounds)) {
          handled = widget->HandleMousePress(event);
        }
        else {
          if (MouseOverWidget == widget)
            widget->ChangeMousedOverWidget(event.GetCurrentMousePos());
        }
        break;
      }
      case EventType::MouseReleased:
      {
        if (event.IsMouseOver(bounds)) {
          handled = widget->HandleMouseRelease(event);
        }
        else {
          if (MouseOverWidget == widget)
            widget->ChangeMousedOverWidget(event.GetCurrentMousePos());
        }
        break;
      }
      case EventType::TextEntered:
      {
        handled = widget->HandleTextEntered(event);
        break;
      }
      default:
      {
        handled = false;
        if (MouseOverWidget == widget)
          widget->ChangeMousedOverWidget(event.GetCurrentMousePos());
        break;
      }
    } // switch (event.GetEventType())

    return handled;
  }


  void Widget::OnKilled()
  {
  }

  void Widget::OnCreated()
  {
  }

  void Widget::OnHover()
  {
  }

  void Widget::OnEnter(Vec2i where)
  {
  }

  void Widget::OnExit(Vec2i where)
  {
  }

  void Widget::AddedTo(Screen * Scr)
  {
  }

  void Widget::Initialize()
  {
  }

  void Widget::Cleanup()
  {
  }

  bool Widget::HandleMousePress(const UserEvent &event)
  {
    ChangeMousedOverWidget(event.GetCurrentMousePos());
    return this->HandleMousePress(event);
  }

  bool Widget::HandleMouseRelease(const UserEvent &event)
  {
    ChangeMousedOverWidget(event.GetCurrentMousePos());
    return this->HandleMouseRelease(event);
  }

  bool Widget::HandleMouseMovement(const UserEvent &event)
  {
    ChangeMousedOverWidget(event.GetCurrentMousePos());
    return this->HandleMouseMovement(event);
  }

  bool Widget::HandleKeyPressed(const UserEvent &event)
  {
    return this->HandleKeyPressed(event);
  }

  bool Widget::HandleKeyReleased(const UserEvent &event)
  {
    return this->HandleKeyReleased(event);
  }

  bool Widget::HandleTextEntered(const UserEvent &event)
  {
    return this->HandleTextEntered(event);
  }

  void Widget::ChangeMousedOverWidget(Vec2i pos)
  {
    if (!MouseOverWidget || (MouseOverWidget != this)) {
      if (MouseOverWidget)
        MouseOverWidget->OnExit(pos);
      MouseOverWidget = this;
      MouseOverWidget->OnEnter(pos);
    }
  }

}
