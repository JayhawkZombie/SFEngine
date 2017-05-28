#ifndef SFEDITOR_EXPANDABLELIST_H
#define SFEDITOR_EXPANDABLELIST_H

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
#include <UI/Widgets/Expandable.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  class ExpandableList : public Expandable
  {
  public:
    PTR_TYPEDEF(ExpandableList);
    ExpandableList();
    ExpandableList(Widget::RPtr Expander = nullptr, int MaxItems = 100);
    virtual ~ExpandableList() override;

    static ExpandableList::Ptr Create(Widget::RPtr Parent = nullptr, int MaxItems = 100);

    virtual Vec2i GetChildOffset() const override;
    virtual bool Add(Widget::Ptr widget, std::string ID /* = "" */) override;
    virtual bool HandleEvent(const UserEvent &event) override;
    virtual void Render(std::shared_ptr<RenderTarget> Target) override;
    virtual void SetExpandableSize(Vec2i size) override;
    virtual void SetUnexpandedSize(Vec2i size) override;
    virtual void SetSize(const Vec2i &v) override;
    virtual void SetPosition(const Vec2i &v) override;
    virtual bool IsExpanded() const override;
    virtual void Expand() override;
    virtual void Contract() override;

    virtual void SetBackgroundColor(const sf::Color &color);
    virtual void SetBackgroundOutlineColor(const sf::Color &color);
    virtual void SetBackgroundOutlineThickness(int thickness);

  protected:
    virtual bool HandleMousePress(const UserEvent &event) override;
    virtual bool HandleMouseRelease(const UserEvent &event) override;
    virtual bool HandleMouseMovement(const UserEvent &event) override;
    virtual bool HandleKeyPressed(const UserEvent &event) override;
    virtual bool HandleKeyReleased(const UserEvent &event) override;
    virtual bool HandleTextEntered(const UserEvent &event) override;

    int m_MaxItems;
    sf::RectangleShape m_BGRect;
    sf::Color m_BackgroundColor;
    Vec2i m_ListSize;
    Vec2i m_ItemSpacing;
    Vec2i m_NextItemPos;
  };

}

#endif // SFEDITOR_EXPANDABLELIST_H
