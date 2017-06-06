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
#include <sfcss/ui/widget.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  std::vector<std::pair<css_widget::rptr, cint_32>> css_widget::widget_ids;
  cint_32 css_widget::last_id_generated = 0;

  css_widget::css_widget(std::initializer_list<std::pair<const sf::Event::EventType, bool>> list, css_widget::rptr parent)
    : m_responding_to(list), m_properties(property_table::create()), m_parent(parent)
  {
    m_id_num = -1;
    for (auto & p : widget_ids) {
      if (p.first == nullptr) {
        p.first = this;
        m_id_num = p.second;
      }
    }

    if (m_id_num == -1)
      m_id_num = ++last_id_generated;
    
    m_id = std::to_string(m_id_num);

    //The only things we need for the widget tree to be able to position us
    // is to know our size and position, anything else can just be used by the renderer
    m_properties->width_changed.connect([this]() { this->resized.emit(this); }, "owner_widget");
    m_properties->height_changed.connect([this]() { this->resized.emit(this); }, "owner_widget");
    m_properties->position_changed.connect([this]() { this->moved.emit(this); }, "owner_widget");
  }

  css_widget::css_widget()
  {
    m_id_num = -1;
    for (auto & p : widget_ids) {
      if (p.first == nullptr) {
        p.first = this;
        m_id_num = p.second;
      }
    }

    if (m_id_num == -1)
      m_id_num = ++last_id_generated;

    m_id = std::to_string(m_id_num);
  }

  css_widget::~css_widget()
  {
    for (auto & p : widget_ids) {
      if (p.first == this)
        p.first = nullptr;
    }
  }

  void css_widget::update()
  {

  }

  FloatRect css_widget::bounds() const
  {
    return { 0.f, 0.f, 0.f, 0.f };
  }

  void css_widget::handle_event(const UserEvent &event)
  {
    MouseState ms_sts(sf::Mouse::isButtonPressed(sf::Mouse::Left), sf::Mouse::isButtonPressed(sf::Mouse::Right));
    switch (event.Type())
    {
      case sf::Event::GainedFocus:
        window_gained_focus.emit(event);
        break;
      case sf::Event::LostFocus:
        window_lost_focus.emit(event);
        break;
      case sf::Event::KeyPressed:
        key_pressed.emit(event.Key());
        break;
      case sf::Event::KeyReleased:
        key_released.emit(event.Key());
        break;
      case sf::Event::MouseButtonPressed:
        if (event.MouseButton() == sf::Mouse::Left)
          left_mouse_pressed.emit(event.CurrentMousePos());
        else
          right_mouse_pressed.emit(event.CurrentMousePos());
        break;
      case sf::Event::MouseButtonReleased:
        if (event.MouseButton() == sf::Mouse::Left)
          left_mouse_released.emit(event.CurrentMousePos());
        else
          right_mouse_released.emit(event.CurrentMousePos());
        break;
      case sf::Event::TextEntered:
        text_entered.emit(event.Text());
      default:
        return;
    }
  }

  bool css_widget::is_visible() const
  {
    auto ptr = m_properties->visibility;
    return ( ptr.second && ( *ptr.second == priv::visibility::visible ) );
  }

  bool css_widget::is_enabled() const
  {
    auto ptr = m_properties->enabled;
    return ( ptr.second && ( *ptr.second == priv::enabled_status::enabled ) );
  }

  bool css_widget::is_focused() const
  {
    return false;
  }

  std::string css_widget::class_() const
  {
    return m_class;
  }

  std::string css_widget::id_() const
  {
    return m_id;
  }

}
