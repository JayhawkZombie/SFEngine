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
#include <sfcss/ui/tree/ui_node.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{



  widget_node::widget_node(css_widget::sptr item, widget_node::rptr parent /*= nullptr*/)
    : m_widget(item), m_parent(parent)
  {
    
  }

  void widget_node::update()
  {

  }

  bool widget_node::handle_event(const UserEvent &event)
  {
    return false;
  }

  void widget_node::pre_render_update()
  {

  }

  css::css_widget_renderer::sptr widget_node::renderer()
  {
    return m_renderer;
  }

  css::widget_node::sptr widget_node::create(css_widget::sptr item, widget_node::rptr parent)
  {
    return nullptr;
  }

  void widget_node::animation_changed()
  {

  }

  void widget_node::background_changed()
  {

  }

  void widget_node::position_changed()
  {

  }

  void widget_node::width_changed()
  {

  }

  void widget_node::height_changed()
  {

  }

  void widget_node::font_changed()
  {

  }

  void widget_node::border_changed()
  {

  }

  void widget_node::visibility_changed()
  {

  }

  void widget_node::enabled_changed()
  {

  }

}
