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
#include <UI/Widgets/FlatButton.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <iostream>

namespace SFUI
{
  FlatButton::Ptr FlatButton::Create(Widget * parent, std::shared_ptr<Label> label)
  {
    FlatButton::Ptr button = std::make_shared<FlatButton>(parent, label);
    return button;
  }

  SFUI::FlatButton::FlatButton::Ptr FlatButton::Create
  (
    Vec2i Pos, 
    Vec2i Size, 
    const std::string &Text, 
    unsigned int TextSize, 
    std::shared_ptr<sf::Font> Font, 
    Alignment TextAlignment, 
    sf::Color TextColorNormal, 
    sf::Color TextColorHighlighted,  
    sf::Color TextColorPressed, 
    Widget::RPtr Parent
  )
  {
    FlatButton::Ptr button = std::make_shared<FlatButton>(Parent, nullptr);

    button->SetPosition(Pos);
    button->SetSize(Size);
    button->SetTextSize(TextSize);
    button->SetText(Text);
    button->SetLabelAlignment(TextAlignment);
    button->SetTextColorNormal(TextColorNormal);
    button->SetTextColorHovered(TextColorHighlighted);
    button->SetTextColorPressed(TextColorPressed);

    return button;
  }

  void FlatButton::Render(std::shared_ptr<RenderTarget> Target)
  {
    auto oldview = Target->getView();

    auto newview = View();
    Target->setView(newview);
    m_Label->Render(Target);
    Target->setView(oldview);
  }

  void FlatButton::Update()
  {
    if (m_ClickState == Clickable::Hovered)
      m_Label->SetTextColor(m_TextColorHighlighted);
    else if (m_ClickState == Clickable::Pressed)
      m_Label->SetTextColor(m_TextColorPressed);
    else
      m_Label->SetTextColor(m_TextColorNormal);
  }

  void FlatButton::SetFont(std::shared_ptr<sf::Font> Font)
  {
    m_Label->SetFont(Font);
    m_Font = Font;
  }

  void FlatButton::SetText(const std::string &Text)
  {
    if (m_Label)
      m_Label->SetText(Text);
    else {
      m_Label = Label::Create(Text, this);
      m_Label->SetTextColor(m_TextColorNormal);
      m_Label->SetTextSize(m_LabelTextSize);
      m_Label->SetFont(m_Font);
      m_Label->AlignInBounds(Bounds(), (Alignment)m_LabelAlignment);
    }
  }

  void FlatButton::SetTextSize(std::uint32_t size)
  {
    m_LabelTextSize = size;
    m_Label->SetTextSize(size);
  }

  void FlatButton::SetTextColorNormal(sf::Color color)
  {
    m_TextColorNormal = color;
  }

  void FlatButton::SetTextColorHovered(sf::Color color)
  {
    m_TextColorHighlighted = color;
  }

  void FlatButton::SetTextColorPressed(sf::Color color)
  {
    m_TextColorPressed = color;
  }

  std::string FlatButton::GetText() const
  {
    return m_Label->GetText();
  }

  void FlatButton::SetLabelAlignment(Alignment alignment)
  {
    m_LabelAlignment = alignment;
    m_Label->AlignInBounds(Bounds(), alignment);
  }

  void FlatButton::SetLabelAlignment(VerticalAlignment vAlignment, HorizontalAlignment hAlignment)
  {
    m_LabelAlignment = ( vAlignment | hAlignment );
  }

  void FlatButton::Connect(std::string slot, std::function<void(Vec2i, MouseButton)> ftn)
  {
    if (slot == "clicked") {
      OnClickedCallback = ftn;
    }
    else {
      Widget::Connect(slot, ftn);
    }
  }

  FlatButton::FlatButton()
  {
    m_RespondingToEvent |= (int)( EventType::MouseMoved ) 
                        | (int)( EventType::MousePressed ) 
                        | (int)( EventType::MousePressed );
  }

  FlatButton::FlatButton(Widget * parent, std::shared_ptr<Label> label)
  {
    m_Parent = parent;
    m_RespondingToEvent |= (int)( EventType::MouseMoved ) 
                        | (int)( EventType::MousePressed ) 
                        | (int)( EventType::MousePressed );
    m_Label = ( label ? label : Label::Create("", this) );
  }

  FlatButton::~FlatButton()
  {
  }

  void FlatButton::OnKilled()
  {

  }

  void FlatButton::OnCreated()
  {

  }

  void FlatButton::OnHover(Vec2i where)
  {
    m_ClickState = Clickable::Hovered;
  }

  void FlatButton::OnEnter(Vec2i where)
  {
    m_ClickState = Clickable::Hovered;
    m_Label->SetTextColor(m_TextColorHighlighted);
  }

  void FlatButton::OnPressed(Vec2i where)
  {
    m_ClickState = Clickable::Pressed;
  }

  void FlatButton::OnReleased(Vec2i where)
  {
    m_ClickState = Clickable::Rest;
  }

  void FlatButton::OnExit(Vec2i where)
  {
    m_ClickState = Clickable::Rest;
    m_Label->SetTextColor(m_TextColorNormal);
  }

  void FlatButton::AddedTo(Screen *Scr)
  {

  }

  void FlatButton::Initialize()
  {

  }

  void FlatButton::Cleanup()
  {

  }

 /* bool FlatButton::HandleMousePress(const UserEvent &event)
  {
    __super::HandleMousePress(event);
    MouseOverWidget = this;
    return true;
  }

  bool FlatButton::HandleMouseRelease(const UserEvent &event)
  {
    __super::HandleMouseRelease(event);
    MouseOverWidget = this;
    if (OnClickedCallback)
      OnClickedCallback(event.GetCurrentMousePos(), event.GetMouseButton());
    return true;
  }

  bool FlatButton::HandleMouseMovement(const UserEvent &event)
  {
    __super::HandleMouseMovement(event);
    MouseOverWidget = this;
    if (m_ClickState != Clickable::Pressed) {
      m_ClickState = Clickable::Hovered;
    }
    return true;
  }

  bool FlatButton::HandleKeyPressed(const UserEvent &event)
  {
    return false;
  }

  bool FlatButton::HandleKeyReleased(const UserEvent &event)
  {
    return false;
  }

  bool FlatButton::HandleTextEntered(const UserEvent &event)
  {
    return false;
  }*/

}
