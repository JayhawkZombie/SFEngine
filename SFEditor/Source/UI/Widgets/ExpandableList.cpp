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
#include <UI/Widgets/ExpandableList.h>
#include <UI/Widgets/Widget.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  ExpandableList::~ExpandableList()
  {

  }

  SFUI::ExpandableList::Ptr ExpandableList::Create(Widget::RPtr Parent /*= nullptr*/, int MaxItems /*= 100*/)
  {
    ExpandableList::Ptr list = std::make_shared<ExpandableList>(Parent, MaxItems);
    return list;
  }

  Vec2i ExpandableList::GetChildOffset() const
  {
    return Widget::GetChildOffset();
  }

  bool ExpandableList::Add(Widget::Ptr widget, std::string ID)
  {
    if (m_Widgets.size() >= m_MaxItems)
      return false;

    if (ID == "")
      ID = std::to_string(GenerateID());
    widget->m_Parent = this;

    auto size = widget->GetSize();
    int x = 0;
    int y = m_ListSize.y;
    widget->SetPosition(Vec2i(x, y));
    m_ListSize.y += size.y;
    m_Widgets[ID] = widget;
    
    return true;
  }

  bool ExpandableList::HandleEvent(const UserEvent &event)
  {
    return ( m_IsExpanded && Expandable::HandleEvent(event) );
  }

  void ExpandableList::Render(std::shared_ptr<RenderTarget> Target)
  {
    auto oldview = Target->getView();
    sf::View view;
    auto psize = m_Parent->GetSize();
    view.reset(FloatRect(m_Position.x, m_Position.y, m_Size.x, m_Size.y));
    view.setViewport(FloatRect(to_float(m_Position.x) / psize.x, 
                               to_float(m_Position.y) / psize.y,
                               to_float(m_Size.x)     / psize.x, 
                               to_float(m_Size.y)     / psize.y));
   
    m_Canvas->clear(m_BackgroundColor);
    
    m_Canvas->draw(m_BGRect);
    
    for (auto & wid : m_Widgets)
      wid.second->Render(m_Canvas);
    m_Canvas->display();

    Target->setView(view);
    m_Sprite.setScale(to_float(m_Size.x) / m_ExpandableSize.x, to_float(m_Size.y) / m_ExpandableSize.y);
    m_Sprite.setPosition(static_cast<Vec2f>( m_Position ));
    Target->draw(m_Sprite);
    Target->setView(oldview);
    
  }

  void ExpandableList::SetExpandableSize(Vec2i size)
  {
    if (m_SizeSet)
      return;

    m_SizeSet = true;
    m_ExpandableSize = size;
    m_Canvas->create(size.x, size.y);
  }

  void ExpandableList::SetUnexpandedSize(Vec2i size)
  {
    m_UnexpandedSize = size;
  }

  void ExpandableList::SetSize(const Vec2i & v)
  {
    __super::SetSize(v);
    m_BGRect.setSize(static_cast<sf::Vector2f>( v ));
    m_TexRect.setSize(static_cast<sf::Vector2f>( v ));
  }

  void ExpandableList::SetPosition(const Vec2i &v)
  {
    __super::SetPosition(v);
    m_Sprite.setPosition(static_cast<sf::Vector2f>( v ));
  }

  bool ExpandableList::IsExpanded() const
  {
    return m_IsExpanded;
  }

  void ExpandableList::Expand()
  {
    m_IsExpanded = true;
    m_Size = m_ExpandableSize;
  }

  void ExpandableList::Contract()
  {
    m_IsExpanded = false;
    m_Size = m_UnexpandedSize;
  }

  void ExpandableList::SetBackgroundColor(const sf::Color & color)
  {
    m_BackgroundColor = color;
    m_BGRect.setFillColor(color);
  }

  void ExpandableList::SetBackgroundOutlineColor(const sf::Color &color)
  {
    m_BGRect.setOutlineColor(color);
  }

  void ExpandableList::SetBackgroundOutlineThickness(int thickness)
  {
    m_BGRect.setOutlineThickness(static_cast<float>( thickness ));
  }

  bool ExpandableList::HandleMousePress(const UserEvent &event)
  {
    auto bounds = Bounds();
    if (!event.IsMouseOver(bounds))
      return false;

    UserEvent e(event);
    e.OffsetFrom(m_Position);
    return GenericContainer::HandleMousePress(e);
  }

  bool ExpandableList::HandleMouseRelease(const UserEvent &event)
  {
    auto bounds = Bounds();
    if (!event.IsMouseOver(bounds))
      return false;

    UserEvent e(event);
    e.OffsetFrom(m_Position);
    return GenericContainer::HandleMouseRelease(e);
  }

  bool ExpandableList::HandleMouseMovement(const UserEvent &event)
  {
    auto bounds = Bounds();
    if (!event.IsMouseOver(bounds))
      return false;

    UserEvent e(event);
    e.OffsetFrom(m_Position);
    return GenericContainer::HandleMouseMovement(e);
  }

  bool ExpandableList::HandleKeyPressed(const UserEvent &event)
  {
    return false;
  }

  bool ExpandableList::HandleKeyReleased(const UserEvent &event)
  {
    return false;
  }

  bool ExpandableList::HandleTextEntered(const UserEvent &event)
  {
    return false;
  }

  ExpandableList::ExpandableList(Widget::RPtr Expander /*= nullptr*/, int MaxItems /*= 100*/)
    : m_ListSize(Vec2i(0, 0)), m_ItemSpacing(Vec2i(0, 0)), m_NextItemPos(Vec2i(0, 0)), Expandable(Expander)
  {
    m_BGRect.setPosition(Vec2f(0.f, 0.f));
    m_RespondingToEvent |= (int)( EventType::KeyPressed )
                        | (int)( EventType::KeyReleased )
                        | (int)( EventType::MouseMoved )
                        | (int)( EventType::MousePressed )
                        | (int)( EventType::MouseReleased )
                        | (int)( EventType::TextEntered );
  }

  ExpandableList::ExpandableList()
    : m_ListSize(Vec2i(0, 0)), m_ItemSpacing(Vec2i(0, 0)), m_NextItemPos(Vec2i(0, 0)), Expandable(nullptr)
  {
    m_BGRect.setPosition(Vec2f(0.f, 0.f));
    m_RespondingToEvent |= (int)( EventType::KeyPressed )
                        | (int)( EventType::KeyReleased )
                        | (int)( EventType::MouseMoved )
                        | (int)( EventType::MousePressed )
                        | (int)( EventType::MouseReleased )
                        | (int)( EventType::TextEntered );
  }

}
