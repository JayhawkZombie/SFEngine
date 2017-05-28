#ifndef SFEDITOR_WIDGET_H
#define SFEDITOR_WIDGET_H

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
#include <Include/Common.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////
#include <boost/signals2/slot.hpp>
#include <boost/signals2/signal.hpp>

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <memory>

namespace SFUI
{

  class Screen;
  class GenericContainer;
  class Expandable;
  class ExpandableList;

  namespace bsig = boost::signals2;
  using MouseButton = sf::Mouse::Button;
  using RenderTarget = sf::RenderTarget;

#define PTR_TYPEDEF(CLASS)\
using Ptr = std::shared_ptr<CLASS>;\
using WeakPtr = std::weak_ptr<CLASS>;\
using RPtr = CLASS*;\

  enum VerticalAlignment
  {
      Top    = 0b00000001
    , Bottom = 0b00000010
    , vCenter = 0b00000100
  };

  enum HorizontalAlignment
  {
      Left   = 0b00001000
    , Right  = 0b00010000
    , hCenter = 0b00100000
  };

  enum Alignment
  {
      TopLeft      = VerticalAlignment::Top     | HorizontalAlignment::Left
    , TopCenter    = VerticalAlignment::Top     | HorizontalAlignment::hCenter
    , TopRight     = VerticalAlignment::Top     | HorizontalAlignment::Right
    , CenterLeft   = VerticalAlignment::vCenter | HorizontalAlignment::Left
    , Centered     = VerticalAlignment::vCenter | HorizontalAlignment::hCenter
    , CenterRight  = VerticalAlignment::vCenter | HorizontalAlignment::Right
    , BottomLeft   = VerticalAlignment::Bottom  | HorizontalAlignment::Left
    , BottomCenter = VerticalAlignment::Bottom  | HorizontalAlignment::hCenter
    , BottomRight  = VerticalAlignment::Bottom  | HorizontalAlignment::Right
  };


  class Widget
  {
  public:
    friend class Screen;
    friend class GenericContainer;
    friend class Expandable;
    friend class ExpandableList;
    PTR_TYPEDEF(Widget);
    virtual void Render(std::shared_ptr<RenderTarget> Target) = 0;
    virtual void Update();
    sf::View View() const;

    virtual bool HandleEvent(const UserEvent &event);
    virtual void Hide();
    virtual void Show();
    virtual void Enable();
    virtual void Disable();
    virtual sf::IntRect Bounds() const;
    virtual void SetPosition(const Vec2i &v);
    virtual void Move(const Vec2i &v);
    virtual void SetSize(const Vec2i &v);
    virtual void SetFont(std::shared_ptr<sf::Font> Font);
    Vec2i GetGlobalPosition();
    Vec2i GetPosition() const;
    virtual Vec2i GetChildOffset() const;
    Vec2i GetSize() const;
    virtual std::shared_ptr<sf::RenderWindow> GetWindow() const;
    virtual Vec2i ToLocalCoords(Vec2i v);
    virtual void AlignInBounds(sf::IntRect bounds, Alignment alignment);
    virtual bool IsRespondingTo(EventType type) const;

    virtual void Connect(std::string slot, std::function<void(void)> ftn);
    virtual void Connect(std::string slot, std::function<void(Vec2i)> ftn);
    virtual void Connect(std::string slot, std::function<void(Vec2i, MouseButton)> ftn);

    enum State
    {
      Hidden   = 0b00000000001,
      Enabled  = 0b00000000010,
      Focused  = 0b00000000100,
      Active   = 0b00000001000,
      ReadOnly = 0b00000010000,
    };

    bool IsActive() const;
    bool IsVisible() const;
    bool IsHidden() const;
    bool IsFocused() const;
    bool IsEnabled() const;
    bool IsDisabled() const;

  protected:
    static bool BaseHandleEvent(Widget::RPtr widget, const UserEvent &event);
    
    std::function<void(void)> OnKilledCallback;
    std::function<void(void)> OnCreatedCallback;
    std::function<void(void)> OnInitCallback;
    std::function<void(Vec2i)> OnMouseEnterCallback;
    std::function<void(Vec2i)> OnMouseExitCallback;
    std::function<void(Vec2i, MouseButton)> OnMousePressedCallback;
    std::function<void(Vec2i, MouseButton)> OnMouseReleasedCallback;
    
    bsig::signal<void(void)> KilledSignal;
    bsig::signal<void(void)> CreatedSignal;
    bsig::signal<void(void)> InitSignal;
    bsig::signal<void(Vec2i)> MouseEnterSignal;
    bsig::signal<void(Vec2i)> MouseExitSignal;
    bsig::signal<void(Vec2i, MouseButton)> PressedSignal;
    bsig::signal<void(Vec2i, MouseButton)> ReleasedSignal;

    virtual void OnKilled();
    virtual void OnCreated();
    virtual void OnHover();
    virtual void OnEnter(Vec2i where);
    virtual void OnExit(Vec2i where);
    virtual void AddedTo(Screen *Scr);
    virtual void Initialize();
    virtual void Cleanup();

    virtual bool HandleMousePress(const UserEvent &event) = 0;
    virtual bool HandleMouseRelease(const UserEvent &event) = 0;
    virtual bool HandleMouseMovement(const UserEvent &event) = 0;
    virtual bool HandleKeyPressed(const UserEvent &event) = 0;
    virtual bool HandleKeyReleased(const UserEvent &event) = 0;
    virtual bool HandleTextEntered(const UserEvent &event) = 0;

    virtual void ChangeMousedOverWidget(Vec2i pos);

    int m_State = State::Active | State::Enabled;
    int m_RespondingToEvent = 0b0000000;
    bool m_IsVisible;
    bool m_IsEnabled;
    bool m_IsActive;
    bool m_IsFocused;

    bool m_RespondingToMouseMove;
    bool m_RespondingToMousePress;
    bool m_RespondingToMouseRelease;
    bool m_RespondingToKeyPress;
    bool m_RespondingToKeyRelease;
    bool m_RespondingToTextEnter;

    Widget();
    virtual ~Widget();

    RPtr    m_Parent;
    Screen *m_Screen;
    Vec2i   m_Position;
    Vec2i   m_GlobalPosition;
    Vec2i   m_Size;
    std::shared_ptr<sf::Font> m_Font;
    static Widget::RPtr MouseOverWidget;

    BoundingBox m_BoundingBox;
    Point m_PPosition;
  };

}

#endif // SFEDITOR_WIDGET_H