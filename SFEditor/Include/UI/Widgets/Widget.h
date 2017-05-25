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
#include <Common.h>

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

  class WidgetRenderer;
  class Screen;
  namespace bsig = boost::signals2;
  using Vec2i = sf::Vector2i;
  using MouseButton = sf::Mouse::Button;
  using RenderTarget = sf::RenderTarget;

#define PTR_TYPEDEF(CLASS)\
using Ptr = std::shared_ptr<CLASS>;\
using WeakPtr = std::weak_ptr<CLASS>;\
using RPtr = CLASS*;\

  class GenericContainer;
  class Screen;

  class Widget
  {
  public:
    friend class Screen;
    friend class GenericContainer;
    PTR_TYPEDEF(Widget);
    virtual WidgetRenderer* Renderer() = 0;
    virtual sf::View View() const;

    virtual bool HandleEvent(sf::Event event) = 0;
    virtual void Hide();
    virtual void Show();
    virtual void Enable();
    virtual void Disable();
    virtual sf::IntRect Bounds() const;
    virtual void SetPosition(const Vec2i &v);
    virtual void SetSize(const Vec2i &v);
    Vec2i GetPosition() const;
    Vec2i GetSize() const;

    virtual void Connect(std::string slot, bsig::signal<void(void)> ftn);
    virtual void Connect(std::string slot, bsig::signal<void(Vec2i)> ftn);
    virtual void Connect(std::string slot, bsig::signal<void(Vec2i, MouseButton)> ftn);

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
    bsig::signal<void(void)> KilledSignal;
    bsig::signal<void(void)> CreatedSignal;
    bsig::signal<void(void)> InitSignal;
    bsig::signal<void(Vec2i)> MouseEnterSignal;
    bsig::signal<void(Vec2i)> MouseExitSignal;
    bsig::signal<void(Vec2i, MouseButton)> PressedSignal;
    bsig::signal<void(Vec2i, MouseButton)> ReleasedSignal;

    virtual void OnKilled() = 0;
    virtual void OnCreated() = 0;
    virtual void OnHover() = 0;
    virtual void OnEnter(Vec2i where) = 0;
    virtual void OnExit(Vec2i where) = 0;
    virtual void AddedTo(Screen *Scr) = 0;
    virtual void Initialize() = 0;
    virtual void Cleanup() = 0;

    int m_State = State::Active | State::Enabled;

    Widget();
    virtual ~Widget();

    RPtr    m_Parent;
    Screen *m_Screen;
    Vec2i   m_Position;
    Vec2i   m_Size;
  };

}

#endif // SFEDITOR_WIDGET_H