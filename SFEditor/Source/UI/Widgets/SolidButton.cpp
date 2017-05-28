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
#include <UI/Widgets/SolidButton.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <iostream>

namespace SFUI
{
  SolidButton::SolidButton(Widget * parent, std::shared_ptr<Label> label)
    : FlatButton(parent, label)
  {
  }

  SolidButton::~SolidButton()
  {
  }

  void SolidButton::Update()
  {
    __super::Update();
    switch (m_ClickState)
    {
      case Clickable::Rest:
        m_BGShape.setFillColor(m_BGColorNormal);
        break;
      case Clickable::Hovered:
        m_BGShape.setFillColor(m_BGColorHighlighted);
        break;
      case Clickable::Pressed:
        m_BGShape.setFillColor(m_BGColorPressed);
        break;
    }
  }

  void SolidButton::Render(std::shared_ptr<RenderTarget> Target)
  {
    auto oldview = Target->getView();
    auto newview = View();

    Target->setView(newview);
    Target->draw(m_BGShape);
    __super::Render(Target);
    Target->setView(oldview);
  }

  SolidButton::Ptr SolidButton::Create(Widget * parent, std::shared_ptr<Label> label)
  {
    SolidButton::Ptr button = std::make_shared<SolidButton>(parent, label);
    return button;
  }

  void SolidButton::SetSize(const Vec2i & v)
  {
    m_BGShape.setSize(static_cast<sf::Vector2f>( v ));
    __super::SetSize(v);
  }

  void SolidButton::SetPosition(const Vec2i & v)
  {
    __super::SetPosition(v);
    m_BGShape.setPosition(static_cast<sf::Vector2f>( v ));
  }

  void SolidButton::SetBackgroundColorNormal(const sf::Color & color)
  {
    m_BGColorNormal = color;
  }

  void SolidButton::SetBackgroundColorHighlighted(const sf::Color & color)
  {
    m_BGColorHighlighted = color;
  }

  void SolidButton::SetBackgroundColorPressed(const sf::Color & color)
  {
    m_BGColorPressed = color;
  }

  void SolidButton::OnHover()
  {
  }

  void SolidButton::OnEnter(Vec2i where)
  {
    __super::OnEnter(where);
    m_BGShape.setFillColor(m_BGColorHighlighted);
  }

  void SolidButton::OnExit(Vec2i where)
  {
    __super::OnExit(where);
    m_ClickState = Clickable::Rest;
    m_BGShape.setFillColor(m_BGColorNormal);
  }

  bool SolidButton::HandleMousePress(const UserEvent &event)
  {
    m_BGShape.setFillColor(m_BGColorPressed);
    __super::HandleMousePress(event);
    return true;
  }

  bool SolidButton::HandleMouseRelease(const UserEvent &event)
  {
    m_BGShape.setFillColor(m_BGColorNormal);
    __super::HandleMouseRelease(event);
    return true;
  }

  bool SolidButton::HandleMouseMovement(const UserEvent &event)
  {
    m_BGShape.setFillColor(m_BGColorHighlighted);
    __super::HandleMouseMovement(event);
    return true;
  }

  bool SolidButton::HandleKeyPressed(const UserEvent &event)
  {
    return false;
  }

  bool SolidButton::HandleKeyReleased(const UserEvent &event)
  {
    return false;
  }

  bool SolidButton::HandleTextEntered(const UserEvent &event)
  {
    return false;
  }

}
