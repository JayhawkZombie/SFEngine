#pragma once

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

#include "UI/PropertyAnimator.h"

class Widget
{
public:

  Widget();
  ~Widget();

  void BaseUpdate(double delta);
  bool BaseHandleEvent(const sf::Event &event);

  void Render(sf::RenderTarget &Target);

  virtual bool HandleEvent(const sf::Event &event);

  sf::Vector2f GetPosition() const;
  sf::Vector2f GetSize() const;
  sf::Color GetColor() const;
  sf::Color GetColorHighlighted() const;
  sf::Color GetColorPressed() const;
  sf::Color GetColorDisabled() const;
  sf::Color GetOutlineColor() const;
  float GetOutlineWidth() const;

  void SetPosition(const sf::Vector2f &Pos);
  void SetSize(const sf::Vector2f &Size);
  void SetColor(const sf::Color &Color);
  void SetColorHighlighted(const sf::Color &Color);
  void SetColorPressed(const sf::Color &Color);
  void SetColorDisabled(const sf::Color &Color);
  void SetOutlineColor(const sf::Color &Color);
  void SetOutlineWidth(float Width);

  void Move(const sf::Vector2f &Delta);

  bool IsMouseOver() const;
  bool IsLeftMousePressed() const;
  bool IsRightMousePressed() const;
  bool WasMouseOver() const;
  bool WasLeftMousePressed() const;
  bool WasRightMousePressed() const;

  void OnHighlighted(const std::function<void()> &Func);
  void OnUnhighlighted(const std::function<void()> &Func);
  void OnLeftMousePress(const std::function<void()> &Func);
  void OnLeftMouseRelease(const std::function<void()> &Func);
  void OnRightMousePress(const std::function<void()> &Func);
  void OnRightMouseRelease(const std::function<void()> &Func);
  void OnLongHover(const std::function<void()> &Func);

  bool IsVisible() const;
  bool IsEnabled() const;

protected:
  
  /*
   *  Base class notification methods
   **/
  virtual void NotifyMouseMoved();
  virtual void NotifyLeftMousePressed();
  virtual void NotifyLeftMouseReleased();
  virtual void NotiftRightMousePressed();
  virtual void NotifyRightMouseReleased();
  virtual void NotifyMousedOver();
  virtual void NotifyMouseLeft();
  virtual void NotifyKeyPressed(sf::Keyboard::Key key);
  virtual void NotifyKeyReleased(sf::Keyboard::Key key);
  virtual void NotifyTextEntered(uint32_t unicode);
  virtual void NotifyGainedMouseFocus();
  virtual void NotifyLostMouseFocus();
  virtual void NotifyGainedKeyboardFocus();
  virtual void NotifyLostKeyboardFocus();
  virtual void NotifyMoved();
  virtual void NotifyResized();
  virtual void NotifyEnabled();
  virtual void NotifyDisabled();
  virtual void NotifyLongHovered();

private:

  std::vector<std::unique_ptr<Widget>> m_Children;

  /*
   *  Base callbacks
   **/
  std::function<void()> m_MousedOverCallback = []() {};
  std::function<void()> m_MouseLeftCallback = []() {};
  std::function<void()> m_LeftPressCallback = []() {};
  std::function<void()> m_LeftReleaseCallback = []() {};
  std::function<void()> m_RightPressCallback = []() {};
  std::function<void()> m_RightReleaseCallback = []() {};
  std::function<void()> m_LongHoverCallback = []() {};

  sf::Vector2f m_Position = sf::Vector2f(0.f, 0.f);
  sf::Vector2f m_Size = sf::Vector2f(0.f, 0.f);

  sf::Color m_FillColor = sf::Color(94, 94, 94);
  sf::Color m_OutlineColor = sf::Color::Transparent;

  float m_OutlineWidth = 0.f;

  sf::Color m_ColorHighlighted = sf::Color(112, 112, 112);
  sf::Color m_ColorDisabled = sf::Color(58, 58, 58, 100);
  sf::Color m_ColorPressed = sf::Color(70, 70, 70);

  bool m_IsEnabled = true;
  bool m_IsVisible = true;

  bool m_IsMouseOver = false;
  bool m_WasMouseOver = false;
  bool m_IsLeftMousePressed = false;
  bool m_WasLeftMousePressed = false;
  bool m_IsRightMousePressed = false;
  bool m_WasRightMousePressed = false;

  double m_TimeHovered = 0.0;

};
