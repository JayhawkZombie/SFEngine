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
#include <UI/Widgets/GenericContainer.h>
#include <UI/Globals.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  GenericContainer::GenericContainer()
    : m_Canvas(std::make_shared<sf::RenderTexture>()), m_SizeSet(false)
  {
  }

  GenericContainer::~GenericContainer()
  {
    m_Canvas.reset();
  }

  void GenericContainer::Update()
  {
    for (auto & widget : m_Widgets)
      widget.second->Update();
  }

  Vec2i GenericContainer::GetChildOffset() const
  {
    //The child should be offset by whatever our position is
    //  but just in case we are also inside of an additional container
    //  we should also add whatever our potential offset is ourself
    //  (ie for multi-level offsets, like a listbox inside of a popup window)
    
    if (m_Parent)
      return m_Position + m_Parent->GetChildOffset();

    return m_Position;
  }
  
  bool GenericContainer::Add(Widget::Ptr widget, std::string ID)
  {
    if (!widget)
      return false;

    if (ID == "") {
      ID = std::to_string(GenerateID());
    }

    widget->m_Parent = this;

    m_Widgets[ID] = widget;
    return true;
  }

  bool GenericContainer::Remove(Widget::Ptr widget)
  {
    for (auto & wid : m_Widgets) {
      if (wid.second == widget) {
        m_Widgets.erase(m_Widgets.find(wid.first));
        return true;
      }
    }

    return false;
  }

  bool GenericContainer::Remove(std::string ID)
  {
    auto it = m_Widgets.find(ID);
    if (it != m_Widgets.end()) {
      m_Widgets.erase(it);
      return true;
    }

    return false;
  }

  bool GenericContainer::RemoveAll()
  {
    m_Widgets.clear();
    return true;
  }

  bool GenericContainer::HideAll()
  {
    for (auto & widget : m_Widgets) {
      widget.second->Hide();
    }

    return true;
  }

  bool GenericContainer::ShowAll()
  {
    for (auto & widget : m_Widgets) {
      widget.second->Show();
    }

    return true;
  }

  void GenericContainer::SetSize(const Vec2i & v)
  {
    Widget::SetSize(v);
    m_Canvas->create(v.x, v.y);
    m_Sprite.setTexture(m_Canvas->getTexture());
  }

  void GenericContainer::SetPosition(const Vec2i & v)
  {
    Widget::SetPosition(v);
    m_Sprite.setPosition(static_cast<sf::Vector2f>( v ));
  }

  void GenericContainer::Move(const Vec2i & v)
  {
  }

  bool GenericContainer::HandleEvent(const UserEvent &event)
  {
    UserEvent e(event);
    e.OffsetFrom(m_Position);

    bool handled = false;
    for (auto & wid : m_Widgets) {
      if (Widget::BaseHandleEvent(wid.second.get(), e))
        return true;
    }

    return false;
  }

  bool GenericContainer::HandleMousePress(const UserEvent &event)
  {
    IntRect bounds;
    for (auto & wid : m_Widgets) {
      bounds = wid.second->Bounds();
      if (wid.second->IsRespondingTo(EventType::MousePressed) && event.IsMouseOver(bounds)) {
        wid.second->HandleMousePress(event);
        return true;
      }
    }
    
    ChangeMousedOverWidget(event.GetCurrentMousePos());
    return false;
  }

  bool GenericContainer::HandleMouseRelease(const UserEvent &event)
  {
    IntRect bounds;
    for (auto & wid : m_Widgets) {
      bounds = wid.second->Bounds();
      if (wid.second->IsRespondingTo(EventType::MouseReleased) && event.IsMouseOver(bounds)) {
        wid.second->HandleMouseRelease(event);
        return true;
      }
    }

    ChangeMousedOverWidget(event.GetCurrentMousePos());
    return false;
  }

  bool GenericContainer::HandleMouseMovement(const UserEvent &event)
  {
    IntRect bounds;
    for (auto & wid : m_Widgets) {
      bounds = wid.second->Bounds();
      if (wid.second->IsRespondingTo(EventType::MouseMoved) && event.IsMouseOver(bounds)) {
        wid.second->HandleMouseMovement(event);
        return true;
      }
    }

    ChangeMousedOverWidget(event.GetCurrentMousePos());
    return false;
  }

  bool GenericContainer::HandleKeyPressed(const UserEvent &event)
  {
    return false;
  }

  bool GenericContainer::HandleKeyReleased(const UserEvent &event)
  {
    return false;
  }

  bool GenericContainer::HandleTextEntered(const UserEvent &event)
  {
    return false;
  }

}
