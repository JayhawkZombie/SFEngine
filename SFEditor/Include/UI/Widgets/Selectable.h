#ifndef SFEDITOR_SELECTABLE_H
#define SFEDITOR_SELECTABLE_H

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
#include <UI/Widgets/Clickable.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{
  struct SelectableOverlayColors
  {
    sf::Color ColorNormal = sf::Color::Transparent;
    sf::Color ColorHighlighted = sf::Color(0, 97, 255, 100);
    sf::Color ColorDisabled = sf::Color(81, 81, 81, 200);
    sf::Color ColorSelected = sf::Color(0, 57, 150, 100);
    sf::Color OutlineColor = sf::Color(67, 91, 130);
    float OutlineThickness = 1;
  };

  class Selectable : public Clickable
  {
  public:
    PTR_TYPEDEF(Selectable);

    Selectable(Widget::Ptr InnerWidget = nullptr, Widget::RPtr Parent = nullptr);
    virtual ~Selectable() override;

    static Selectable::Ptr Create(Widget::Ptr InnerWidget = nullptr, Widget::RPtr Parent = nullptr);
    
    virtual void Update() override;
    virtual void Render(std::shared_ptr<RenderTarget> Target) override;

    virtual void SetPosition(const Vec2i &v) override;
    virtual void SetSize(const Vec2i &v) override;
    virtual bool IsSelected() const;
    virtual void Select();
    virtual void Deselect();

    virtual void SetOverlayAttributes(const SelectableOverlayColors &attrs);
    virtual void SetUnderlayAttributes(const SelectableOverlayColors &attrs);
    virtual void SetWidget(Widget::Ptr widget);

    virtual void Connect(std::string slot, std::function<void(void)> ftn) override;
    
  protected:
    virtual void OnHover(Vec2i where) override;
    virtual void OnEnter(Vec2i where) override;
    virtual void OnExit(Vec2i where) override;
    virtual void OnPressed(Vec2i where) override;
    virtual void OnReleased(Vec2i where) override;

    virtual void OnSelected();
    virtual void OnDeselected();
    
    virtual void OnClicked() override;

    std::function<void(void)> m_OnSelectedCallback;
    std::function<void(void)> m_OnDeselectedCallback;

    bool m_Selected = false;
    bool m_Hovered = false;
    SelectableOverlayColors m_OverlayColors;
    SelectableOverlayColors m_UnderlayColors;
    sf::RectangleShape m_Overlay;
    sf::RectangleShape m_Underlay;
    Widget::Ptr m_InnerWidget;
  };

}

#endif // SFEDITOR_SELECTABLE_H
