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

#include "Widget.h"

Widget::Widget()
{

}

Widget::~Widget()
{

}

void Widget::BaseUpdate(double delta)
{
  if (IsVisible() && IsEnabled())
  {

  }
}

bool Widget::BaseHandleEvent(const sf::Event &event)
{
  if (!IsVisible() || !IsEnabled())
    return false;
}

void Widget::Render(sf::RenderTarget &Target)
{

}

bool Widget::HandleEvent(const sf::Event &event)
{
  return false;
}

sf::Vector2f Widget::GetPosition() const
{
  return m_Position;
}

sf::Vector2f Widget::GetSize() const
{
  return m_Size;
}

sf::Color Widget::GetColor() const
{
  return m_FillColor;
}

sf::Color Widget::GetColorHighlighted() const
{
  return m_ColorHighlighted;
}

sf::Color Widget::GetColorPressed() const
{
  return m_ColorPressed;
}

sf::Color Widget::GetColorDisabled() const
{
  return m_ColorDisabled;
}

sf::Color Widget::GetOutlineColor() const
{
  return m_OutlineColor;
}

float Widget::GetOutlineWidth() const
{
  return m_OutlineWidth;
}

void Widget::SetPosition(const sf::Vector2f &Pos)
{
  sf::Vector2f delta = Pos - m_Position;
  Move(delta);
}

void Widget::SetSize(const sf::Vector2f &Size)
{
  m_Size = Size;
  NotifyResized();
}

void Widget::SetColor(const sf::Color &Color)
{
  m_FillColor = Color;
}

void Widget::SetColorHighlighted(const sf::Color &Color)
{
  m_ColorHighlighted = Color;
}

void Widget::SetColorPressed(const sf::Color &Color)
{
  m_ColorPressed = Color;
}

void Widget::SetColorDisabled(const sf::Color &Color)
{
  m_ColorDisabled = Color;
}

void Widget::SetOutlineColor(const sf::Color &Color)
{
  m_OutlineColor = Color;
}

void Widget::SetOutlineWidth(float Width)
{
  m_OutlineWidth = Width;
}

void Widget::Move(const sf::Vector2f &Delta)
{
  for (auto & child : m_Children)
    child->Move(Delta);

  m_Position += Delta;

  NotifyMoved();
}

bool Widget::IsMouseOver() const
{
  return m_IsMouseOver;
}

bool Widget::IsLeftMousePressed() const
{
  return m_IsLeftMousePressed;
}

bool Widget::IsRightMousePressed() const
{
  return m_IsRightMousePressed;
}

bool Widget::WasMouseOver() const
{
  return m_WasMouseOver;
}

bool Widget::WasLeftMousePressed() const
{
  return m_WasLeftMousePressed;
}

bool Widget::WasRightMousePressed() const
{
  return m_WasRightMousePressed;
}

void Widget::OnHighlighted(const std::function<void()> &Func)
{
  m_MousedOverCallback = Func;
}

void Widget::OnUnhighlighted(const std::function<void()> &Func)
{
  m_MouseLeftCallback = Func;
}

void Widget::OnLeftMousePress(const std::function<void()> &Func)
{
  m_LeftPressCallback = Func;
}

void Widget::OnLeftMouseRelease(const std::function<void()> &Func)
{
  m_LeftReleaseCallback = Func;
}

void Widget::OnRightMousePress(const std::function<void()> &Func)
{
  m_RightPressCallback = Func;
}

void Widget::OnRightMouseRelease(const std::function<void()> &Func)
{
  m_RightReleaseCallback = Func;
}

void Widget::OnLongHover(const std::function<void()> &Func)
{
  m_LongHoverCallback = Func;
}

bool Widget::IsVisible() const
{
  return m_IsVisible;
}

bool Widget::IsEnabled() const
{
  return m_IsEnabled;
}

void Widget::NotifyMouseMoved()
{

}

void Widget::NotifyLeftMousePressed()
{

}

void Widget::NotifyLeftMouseReleased()
{

}

void Widget::NotiftRightMousePressed()
{

}

void Widget::NotifyRightMouseReleased()
{

}

void Widget::NotifyMousedOver()
{

}

void Widget::NotifyMouseLeft()
{

}

void Widget::NotifyKeyPressed(sf::Keyboard::Key key)
{

}

void Widget::NotifyKeyReleased(sf::Keyboard::Key key)
{

}

void Widget::NotifyTextEntered(uint32_t unicode)
{

}

void Widget::NotifyGainedMouseFocus()
{

}

void Widget::NotifyLostMouseFocus()
{

}

void Widget::NotifyGainedKeyboardFocus()
{

}

void Widget::NotifyLostKeyboardFocus()
{

}

void Widget::NotifyMoved()
{

}

void Widget::NotifyResized()
{

}

void Widget::NotifyEnabled()
{

}

void Widget::NotifyDisabled()
{

}

void Widget::NotifyLongHovered()
{

}
