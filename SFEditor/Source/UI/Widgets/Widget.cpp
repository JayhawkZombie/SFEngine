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

namespace SFUI
{
  Widget::Widget()
    : m_Position(0, 0), m_Size(0, 0), m_Parent(nullptr)
  {

  }

  Widget::~Widget()
  {

  }

  WidgetRenderer * Widget::Renderer()
  {
    return nullptr;
  }

  sf::View Widget::View() const
  {
    return sf::View();
  }

  bool Widget::HandleEvent(sf::Event event)
  {
    return false;
  }

  void Widget::Hide()
  {
    m_State &= State::Hidden;
  }

  void Widget::Show()
  {
    m_State &= ~State::Hidden;
  }

  void Widget::Enable()
  {
    m_State |= State::Enabled;
  }

  void Widget::Disable()
  {
    m_State &= ~State::Enabled;
  }

  sf::IntRect Widget::Bounds() const
  {
    return sf::IntRect(0, 0, 0, 0);
  }

  void Widget::SetPosition(const Vec2i & v)
  {
    m_Position = v;
  }

  void Widget::SetSize(const Vec2i & v)
  {
    m_Size = v;
  }

  Vec2i Widget::GetPosition() const
  {
    return m_Position;
  }

  Vec2i Widget::GetSize() const
  {
    return m_Size;
  }

  void Widget::Connect(std::string slot, bsig::signal<void(void)> ftn)
  {
    if (slot == "killed") {
      KilledSignal.connect(ftn);
    }
    else if (slot == "created") {
      CreatedSignal.connect(ftn);
    }
    else if (slot == "init") {
      InitSignal.connect(ftn);
    }
  }

  void Widget::Connect(std::string slot, bsig::signal<void(Vec2i)> ftn)
  {
    if (slot == "enter") {
      MouseEnterSignal.connect(ftn);
    }
    else if (slot == "exit") {
      MouseExitSignal.connect(ftn);
    }

  }

  void Widget::Connect(std::string slot, bsig::signal<void(Vec2i, MouseButton)> ftn)
  {
    if (slot == "pressed") {
      PressedSignal.connect(ftn);
    }
    else if (slot == "released") {
      ReleasedSignal.connect(ftn);
    }
  }

  bool Widget::IsActive() const
  {
    return ( (m_State & State::Active) != 0 );
  }

  bool Widget::IsVisible() const
  {
    return ( (m_State & State::Hidden) == 0 );
  }

  bool Widget::IsHidden() const
  {
    return ( (m_State & State::Hidden) != 0 );
  }

  bool Widget::IsFocused() const
  {
    return ( (m_State & State::Focused) != 0 );
  }

  bool Widget::IsEnabled() const
  {
    return ( (m_State & State::Enabled) != 0 );
  }

  bool Widget::IsDisabled() const
  {
    return ( (m_State & State::Enabled) == 0 );
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

}
