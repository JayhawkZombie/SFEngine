#ifndef SFCSS_UI_NODE_H
#define SFCSS_UI_NODE_H

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
#include <sfcss/ui/ui.h>
#include <sfcss/renderering/renderers/widget_renderer.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  class widget_node
  {
  public:
    CSS_PTR_TYPEDEF(widget_node);
    widget_node(css_widget::sptr item, widget_node::rptr parent = nullptr);
    virtual ~widget_node() = default;

    virtual void update() = 0;
    virtual bool handle_event(const UserEvent &event) = 0;
    virtual void pre_render_update() = 0;
    virtual css_widget_renderer::sptr renderer() = 0;
    static widget_node::sptr create(css_widget::sptr item, widget_node::rptr parent);

    css_widget::sptr m_widget;
    widget_node::rptr m_parent;
    css_widget_renderer::sptr m_renderer;

  protected:
    virtual void animation_changed();
    virtual void background_changed();
    virtual void position_changed();
    virtual void width_changed();
    virtual void height_changed();
    virtual void font_changed();
    virtual void border_changed();
    virtual void visibility_changed();
    virtual void enabled_changed();
  };

}

#endif // SFCSS_UI_NODE_H
