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
#include <sfcss/utils/quad_tree.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  std::vector<std::pair<quad_tree::rptr, cint_32>> quad_tree::tot_ids;
  cint_32 quad_tree::last_id_generated = 0;

  quad_tree::quad_tree(const Vec2 &p, const float &h, const float &w, const cint_32 &depth, const cint_32 &max_depth)
    : m_width(w), m_height(h), m_position(p), m_depth(depth), m_max_depth(max_depth)
    , m_bounds(p.X(), p.Y(), w, h)
    , m_nw_bounds(p.X(),           p.Y(),           w / 2.f, h / 2.f)
    , m_ne_bounds(p.X() + w / 2.f, p.Y(),           w / 2.f, h / 2.f)
    , m_se_bounds(p.X() + w / 2.f, p.Y() + h / 2.f, w / 2.f, h / 2.f)
    , m_sw_bounds(p.X(),           p.Y() + h / 2.f, w / 2.f, h / 2.f)
  {
    m_id = -1;

    //Find an id that has been released
    for (auto & p : tot_ids) {
      if (p.first == nullptr) {
        m_id = p.second;
        p.first = this;
      }
    }
    
    //if no id was released, then make one and push it back
    if (m_id == -1) {
      m_id = ++last_id_generated;
      tot_ids.push_back(std::make_pair(this, m_id));
    }
  }

  quad_tree::~quad_tree()
  {
    //Find our id and set the pair's first item to nullptr so 
    // it can be used by another node
    for (auto & p : tot_ids) {
      if (p.first == this)
        p.first = nullptr;
    }
  }

  float quad_tree::width() const
  {
    return m_width;
  }

  float quad_tree::height() const
  {
    return m_height;
  }

  FloatRect quad_tree::bounds() const
  {
    return m_bounds;
  }

  bool quad_tree::insert(css_widget::sptr item)
  {
    if (m_depth > m_max_depth || m_widgets.find(item->id_()) != m_widgets.end())
      return false;
    auto bds = item->bounds();

    if (!rect_within_bounds(bds))
      return false;

    if (m_widgets.size() > 1) { //try to put it in a child
      if (!m_subdivided && !subdivide()) {
        place_and_connect(item);
        return true;
      }
      else {
        if (fits_in_nw(bds))
          return m_nw->insert(item);
        else if (fits_in_ne(bds))
          return m_ne->insert(item);
        else if (fits_in_se(bds))
          return m_se->insert(item);
        else if (fits_in_sw(bds))
          return m_sw->insert(item);
        else {
          place_and_connect(item); return true;
        }
      }
    } //if widgets.size() > 1
    else {
      place_and_connect(item);
      return true;
    }
  }

  bool quad_tree::remove(css_widget::sptr item)
  {
    auto it = m_widgets.find(item->id_());
    if (it != m_widgets.end()) {
      m_widgets.erase(it);

      if (m_widgets.empty())
        emptied.emit(this);

      return true;
    }
    else {
      if (!m_subdivided) return false;
      
      return ( m_nw->remove(item) || m_ne->remove(item) || m_se->remove(item) || m_sw->remove(item) );
    }
  }

  bool quad_tree::remove(const std::string &id)
  {
    auto it = m_widgets.find(id);
    if (it != m_widgets.end()) {
      m_widgets.erase(it);

      if (m_widgets.empty())
        emptied.emit(this);

      return true;
    }
    else {
      if (!m_subdivided) return false;

      return ( m_nw->remove(id) || m_ne->remove(id) || m_se->remove(id) || m_sw->remove(id) );
    }
  }

  void quad_tree::make_empty()
  {
    if (m_subdivided) {
      m_nw->make_empty();
      m_ne->make_empty();
      m_se->make_empty();
      m_sw->make_empty();
    }

    m_widgets.clear();
    //Signals not emitted here
  }

  bool quad_tree::empty() const
  {
    bool is_empty = m_widgets.empty();
    if (m_subdivided) {
      is_empty &= m_nw->empty();
      is_empty &= m_ne->empty();
      is_empty &= m_se->empty();
      is_empty &= m_sw->empty();
    }
    
    return is_empty;
  }

  void quad_tree::pass_up(css_widget::sptr item)
  {    
    if (m_parent) {
      item->moved.disconnect(std::to_string(m_id));
      item->resized.disconnect(std::to_string(m_id));

      m_parent->get_from_child(item);
    }
  }

  void quad_tree::get_from_child(css_widget::sptr item)
  {
    if (rect_within_bounds(item->bounds())) {
      insert(item);
    }
    else {
      pass_up(item);
    }
  }

  bool quad_tree::point_in_bounds(const Vec2 &pt) const
  {
    return m_bounds.contains((sf::Vector2f)pt);
  }

  bool quad_tree::rect_within_bounds(const FloatRect &rect) const
  {
    return ( rect.left >= m_bounds.left && rect.left + rect.width <= m_bounds.left + m_bounds.width &&
      rect.top >= m_bounds.top && rect.top + rect.height <= m_bounds.top + m_bounds.height );
  }

  bool quad_tree::contains_id(const std::string &id) const
  {
    if (m_widgets.find(id) != m_widgets.end())
      return true;
    else {
      if      (m_nw && m_nw->contains_id(id)) return true;
      else if (m_ne && m_ne->contains_id(id)) return true;
      else if (m_se && m_se->contains_id(id)) return true;
      else if (m_sw && m_sw->contains_id(id)) return true;
    }

    return false;
  }

  css::css_widget::sptr quad_tree::get_widget_under(const Vec2 &pt) const
  {
    if (!point_in_bounds(pt)) return nullptr;

    for (auto & widget : m_widgets) {
      auto bds = widget.second->bounds();

      if (bds.contains(pt))
        return widget.second;
    }

    if (m_subdivided) {
      if      (m_nw->point_in_bounds(pt)) return m_nw->get_widget_under(pt);
      else if (m_ne->point_in_bounds(pt)) return m_ne->get_widget_under(pt);
      else if (m_se->point_in_bounds(pt)) return m_se->get_widget_under(pt);
      else if (m_sw->point_in_bounds(pt)) return m_sw->get_widget_under(pt);
    }

    return nullptr;
  }

  cint_32 quad_tree::max_depth() const
  {
    return m_max_depth;
  }

  cint_32 quad_tree::depth() const
  {
    return m_depth;
  }

  void quad_tree::place_and_connect(css_widget::sptr item)
  {
    m_widgets[item->id_()] = item;
    item->moved.connect(std::bind(&quad_tree::widget_was_moved, this, std::placeholders::_1), std::to_string(m_id));
    item->resized.connect(std::bind(&quad_tree::widget_was_resized, this, std::placeholders::_1), std::to_string(m_id));
  }

  bool quad_tree::subdivide()
  {
    if (m_depth >= m_max_depth || m_subdivided)
      return false;

    m_nw = std::make_shared<quad_tree>(Vec2(m_nw_bounds.left, m_nw_bounds.top), m_nw_bounds.width, m_nw_bounds.height);
    m_ne = std::make_shared<quad_tree>(Vec2(m_ne_bounds.left, m_ne_bounds.top), m_ne_bounds.width, m_ne_bounds.height);
    m_se = std::make_shared<quad_tree>(Vec2(m_se_bounds.left, m_se_bounds.top), m_se_bounds.width, m_se_bounds.height);
    m_sw = std::make_shared<quad_tree>(Vec2(m_sw_bounds.left, m_sw_bounds.top), m_sw_bounds.width, m_sw_bounds.height);

    m_subdivided = true;
    return true;
  }

  void quad_tree::undivide()
  {
    if (m_subdivided) {
      m_subdivided = false;
      m_nw = nullptr;
      m_ne = nullptr;
      m_se = nullptr;
      m_sw = nullptr;
    }
  }

  void quad_tree::child_was_emptied(quad_tree::rptr child)
  {
    //Hmm, if all of the children are empty, we can delete them all
    if (m_nw->empty() && m_ne->empty() && m_se->empty() && m_sw->empty()) {
      undivide();
    }
  }

  void quad_tree::widget_was_moved(css_widget::rptr item)
  {
    if (!item) return;
    auto it = m_widgets.find(item->id_());

    //Well we know this widget fits in our bounds
    //  (widgets aren't supposed to be able to go out of their bounds anyway)
    //  so the worst that we should have to do is move it up
    //    We won't move it down unless we HAVE to
    
    if (it != m_widgets.end() && !rect_within_bounds(item->bounds())) {
      css_widget::sptr widget = ( *it ).second;
      pass_up(widget);
    }
    
  }

  void quad_tree::widget_was_resized(css_widget::rptr item)
  {
    //If it no longer fits inside us, we'll have to pass it off to our parent
    if (!item) return;

    auto it = m_widgets.find(item->id_());
    auto bds = item->bounds();

    if (it != m_widgets.end()) {
      css_widget::sptr widget = ( *it ).second;

      if (!rect_within_bounds(bds)) {
        pass_up(widget);
      }
      else {
        m_widgets.erase(it);
        insert(widget);
      }
    }
    else {
      //Pfffffff, this shouldn't ever happen
    }

  }

  void quad_tree::widget_id_changed(const std::string &before, const std::string &after)
  {
    auto it = m_widgets.find(before);
    if (it != m_widgets.end()) {
      css_widget::sptr item = ( *it ).second;
      m_widgets.erase(it);
      m_widgets[after] = item;
    }
  }

  bool quad_tree::fits_in_nw(const FloatRect &rect) const
  {
    return
      ( rect.left >= m_nw_bounds.left && rect.left + rect.width <= m_nw_bounds.left + m_nw_bounds.width
     && rect.top >= m_nw_bounds.top && rect.top + rect.height <= m_nw_bounds.top + m_nw_bounds.height );
  }

  bool quad_tree::fits_in_ne(const FloatRect &rect) const
  {
    return
      ( rect.left >= m_ne_bounds.left && rect.left + rect.width <= m_ne_bounds.left + m_ne_bounds.width
        && rect.top >= m_ne_bounds.top && rect.top + rect.height <= m_ne_bounds.top + m_ne_bounds.height );
  }

  bool quad_tree::fits_in_se(const FloatRect &rect) const
  {
    return
      ( rect.left >= m_se_bounds.left && rect.left + rect.width <= m_se_bounds.left + m_se_bounds.width
        && rect.top >= m_se_bounds.top && rect.top + rect.height <= m_se_bounds.top + m_se_bounds.height );
  }

  bool quad_tree::fits_in_sw(const FloatRect &rect) const
  {
    return
      ( rect.left >= m_sw_bounds.left && rect.left + rect.width <= m_sw_bounds.left + m_sw_bounds.width
        && rect.top >= m_sw_bounds.top && rect.top + rect.height <= m_sw_bounds.top + m_sw_bounds.height );
  }

}
