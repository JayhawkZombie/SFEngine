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



  Expandable::Expandable()
    : m_ExpandableSize(Vec2i(0, 0)), m_IsExpanded(false), m_UnexpandedSize(Vec2i(0, 0)), GenericContainer()
  {

  }

  Expandable::Expandable(Widget::RPtr parent)
    : m_ExpandableSize(Vec2i(0, 0)), m_IsExpanded(false), m_UnexpandedSize(Vec2i(0, 0)), GenericContainer()
  {
    m_Parent = parent;
  }

  Expandable::~Expandable()
  {

  }

  bool Expandable::HandleEvent(const UserEvent &event)
  {
    return ( m_IsExpanded && GenericContainer::HandleEvent(event) );
  }

  void Expandable::Update()
  {
    GenericContainer::Update();
  }

  void Expandable::Render(std::shared_ptr<RenderTarget> Target)
  {
    if (m_IsExpanded) {
      m_Canvas->clear(sf::Color::Transparent);
      
      for (auto & widget : m_Widgets)
        widget.second->Render(m_Canvas);

      m_Canvas->display();
      Target->draw(m_Sprite);
    }
  }

  void Expandable::SetExpandableSize(Vec2i size)
  {
    m_ExpandableSize = size;
  }

  void Expandable::SetUnexpandedSize(Vec2i size)
  {
    m_UnexpandedSize = size;
  }

  bool Expandable::IsExpanded() const
  {
    return m_IsExpanded;
  }

  void Expandable::Expand()
  {
    m_IsExpanded = true;
    m_Size = m_ExpandableSize;
  }

  void Expandable::Contract()
  {
    m_IsExpanded = false;
    m_Size = m_UnexpandedSize;
  }

  void Expandable::OnExpanded()
  {

  }

  void Expandable::OnContracted()
  {

  }

}
