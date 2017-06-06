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
#include <UI/Widgets/Selectable.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{



  Selectable::Selectable(Widget::Ptr InnerWidget /*= nullptr*/, Widget::RPtr Parent /*= nullptr*/)
    : m_InnerWidget(InnerWidget)
  {
    m_Parent = Parent;
    m_RespondingToKeyPress = false;
    m_RespondingToKeyRelease = false;
    m_RespondingToMouseMove = true;
    m_RespondingToMousePress = true;
    m_RespondingToMouseRelease = true;
  }

  Selectable::~Selectable()
  {

  }

  SFUI::Selectable::Ptr Selectable::Create(Widget::Ptr InnerWidget /*= nullptr*/, Widget::RPtr Parent /*= nullptr*/)
  {
    Selectable::Ptr item = std::make_shared<Selectable>(InnerWidget, Parent);

    return item;
  }

  void Selectable::Update()
  {
    m_Underlay.setPosition(Vec2f(m_Position));
    m_Overlay.setPosition(Vec2f(m_Position));
    
    m_Underlay.setSize(Vec2f(m_Size));
    m_Overlay.setSize(Vec2f(m_Size));

    if (m_InnerWidget)
      m_InnerWidget->SetPosition(m_Position);

    if (m_Selected) {
      m_Overlay.setFillColor(m_OverlayColors.ColorSelected);
      m_Underlay.setFillColor(m_UnderlayColors.ColorSelected);
    }
    if (m_Hovered) {
      m_Overlay.setFillColor(m_OverlayColors.ColorHighlighted);
      m_Underlay.setFillColor(m_UnderlayColors.ColorHighlighted);
    }
    else if (!m_IsEnabled) {
      m_Overlay.setFillColor(m_OverlayColors.ColorDisabled);
      m_Underlay.setFillColor(m_UnderlayColors.ColorDisabled);
    }
  }

  void Selectable::Render(std::shared_ptr<RenderTarget> Target)
  {
    if (!IsVisible())
      return;

    sf::View oldView = Target->getView();
    sf::View newView;

    IntRect bnds = Bounds();
    Vec2i psize = m_Parent->GetSize();

    newView.reset(FloatRect(to_float(m_Position.x), to_float(m_Position.y), to_float(m_Size.x), to_float(m_Size.y)));
    newView.setViewport(
      FloatRect(
        m_Position.x / to_float(psize.x),
        m_Position.y / to_float(psize.y),
        m_Size.x / to_float(psize.x),
        m_Size.y / to_float(psize.y)
      )
    );

    Target->setView(newView);
    Target->draw(m_Underlay);
    if (m_InnerWidget)
      m_InnerWidget->Render(Target);
    Target->draw(m_Overlay);
    Target->setView(oldView);
  }

  void Selectable::SetPosition(const Vec2i & v)
  {
    __super::SetPosition(v);
    m_Overlay.setPosition(Vec2f(v));
    m_Underlay.setPosition(Vec2f(v));
  }

  void Selectable::SetSize(const Vec2i & v)
  {
    __super::SetSize(v);
    m_Overlay.setSize(Vec2f(v));
    m_Underlay.setSize(Vec2f(v));
  }

  bool Selectable::IsSelected() const
  {
    return m_Selected;
  }

  void Selectable::Select()
  {
    m_Selected = true;
  }

  void Selectable::Deselect()
  {
    m_Selected = false;
  }

  void Selectable::SetWidget(Widget::Ptr widget)
  {
    m_InnerWidget = widget;
    widget->m_Parent = this;
  }

  void Selectable::Connect(std::string slot, std::function<void(void)> ftn)
  {
    if (slot == "selected") {
      m_OnSelectedCallback = ftn;
    }
    else if (slot == "deselected") {
      m_OnDeselectedCallback = ftn;
    }
  }

  void Selectable::OnHover(Vec2i where)
  {
    m_Hovered = true;
  }

  void Selectable::OnEnter(Vec2i where)
  {
    m_Hovered = true;
  }

  void Selectable::OnExit(Vec2i where)
  {
    m_Hovered = false;
  }

  void Selectable::OnPressed(Vec2i where)
  {
    __super::OnPressed(where);
    m_ClickState = Clickable::Pressed;
  }

  void Selectable::OnReleased(Vec2i where)
  {
    __super::OnReleased(where);
    m_ClickState = Clickable::Rest;
  }

  void Selectable::OnSelected()
  {
    if (m_OnSelectedCallback)
      m_OnSelectedCallback();
  }

  void Selectable::OnDeselected()
  {
    if (m_OnDeselectedCallback)
      m_OnDeselectedCallback();
  }

  void Selectable::OnClicked()
  {
    m_Selected = !m_Selected;

    if (m_Selected)
      Selectable::OnSelected();
    else
      Selectable::OnDeselected();
  }

  void Selectable::SetOverlayAttributes(const SelectableOverlayColors &attrs)
  {
    m_OverlayColors = attrs;
    m_Overlay.setFillColor(attrs.ColorNormal);
    m_Overlay.setOutlineColor(attrs.OutlineColor);
    m_Overlay.setOutlineThickness(attrs.OutlineThickness);
  }

  void Selectable::SetUnderlayAttributes(const SelectableOverlayColors &attrs)
  {
    m_UnderlayColors = attrs;
    m_Underlay.setFillColor(attrs.ColorNormal);
    m_Underlay.setOutlineColor(attrs.OutlineColor);
    m_Underlay.setOutlineThickness(attrs.OutlineThickness);
  }

}
