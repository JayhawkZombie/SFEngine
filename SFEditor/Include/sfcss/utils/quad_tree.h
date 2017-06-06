#ifndef SFCSS_QUAD_TREE_H
#define SFCSS_QUAD_TREE_H

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
#include <sfcss/types.h>
#include <sfcss/ui/widget.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  class quad_tree
  {
  public:
    CSS_PTR_TYPEDEF(quad_tree);
    quad_tree(const Vec2 &p, const float &h, const float &w, const cint_32 &depth = 0, const cint_32 &max_depth = 100);
    ~quad_tree();

    float width() const;
    float height() const;
    FloatRect bounds() const;

    bool insert(css_widget::sptr item);
    bool remove(css_widget::sptr item);
    bool remove(const std::string &id);
    void make_empty();
    bool empty() const;
    void pass_up(css_widget::sptr item);
    void get_from_child(css_widget::sptr item);
    bool point_in_bounds(const Vec2 &pt) const;
    bool rect_within_bounds(const FloatRect &rect) const;
    bool contains_id(const std::string &id) const;

    css_widget::sptr get_widget_under(const Vec2 &pt) const;

    signal<void, quad_tree::rptr> emptied;
    signal<void, cint_32> subdivided;
    signal<void, quad_tree::rptr> child_killed;

    cint_32 max_depth() const;
    cint_32 depth() const;
  private:
    void place_and_connect(css_widget::sptr item);
    bool subdivide();
    void undivide();
    void child_was_emptied(quad_tree::rptr child);
    void widget_was_moved(css_widget::rptr item);
    void widget_was_resized(css_widget::rptr item);
    void widget_id_changed(const std::string &before, const std::string &after);

    bool fits_in_nw(const FloatRect &rect) const;
    bool fits_in_ne(const FloatRect &rect) const;
    bool fits_in_se(const FloatRect &rect) const;
    bool fits_in_sw(const FloatRect &rect) const;

    quad_tree::sptr m_nw = nullptr;
    quad_tree::sptr m_ne = nullptr;
    quad_tree::sptr m_se = nullptr;
    quad_tree::sptr m_sw = nullptr;

    quad_tree::rptr m_parent = nullptr;

    FloatRect m_bounds    = { 0.f, 0.f, 0.f, 0.f };
    FloatRect m_nw_bounds = { 0.f, 0.f, 0.f, 0.f };
    FloatRect m_ne_bounds = { 0.f, 0.f, 0.f, 0.f };
    FloatRect m_se_bounds = { 0.f, 0.f, 0.f, 0.f };
    FloatRect m_sw_bounds = { 0.f, 0.f, 0.f, 0.f };

    Vec2 m_position = { 0.f, 0.f };
    float m_width = 0.f;
    float m_height = 0.f;
    bool m_subdivided = false;
    cint_32 m_max_depth = 1;
    cint_32 m_depth = 0;
    cint_32 m_id = 0;
    
    static std::vector<std::pair<quad_tree::rptr, cint_32>> tot_ids;
    static cint_32 last_id_generated;

    std::map<std::string, css_widget::sptr> m_widgets;
  };

}

#endif // SFCSS_QUAD_TREE_H
