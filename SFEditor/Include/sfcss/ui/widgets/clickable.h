#ifndef SFCSS_CLICKABLE_H
#define SFCSS_CLICKABLE_H

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

  class clickable_widget : public css_widget
  {
  public:
    FRIEND(clickable_widget_renderer);
    CSS_PTR_TYPEDEF(clickable_widget);
    clickable_widget(css_widget::rptr parent = nullptr);
    virtual ~clickable_widget() override = default;

    static clickable_widget::sptr create(css_widget::rptr parent);
    virtual void update() override;

    signal<void, const Vec2 &> left_clicked;
    signal<void, const Vec2 &> right_clicked;
    signal<void, const Vec2 &> hover_on;
    signal<void, const Vec2 &> hover_off;

  protected:

    enum state_ : cint_32 { rest__, hovered__, pressed__ };
    state_ m_click_state = clickable_widget::rest;

    enum mouse_state_ : cint_32 { left_down__, right_down__, left_up__, right_up__, both_down__, both_up__ };
    mouse_state_ m_mouse_state = clickable_widget::both_up__;

  public:

    static constexpr state_ rest    = state_::rest__;
    static constexpr state_ hovered = state_::hovered__;
    static constexpr state_ pressed = state_::pressed__;

    static constexpr mouse_state_ left_down = mouse_state_::left_down__;
    static constexpr mouse_state_ left_up = mouse_state_::left_up__;
    static constexpr mouse_state_ right_down = mouse_state_::right_down__;
    static constexpr mouse_state_ right_up = mouse_state_::right_up__;
    static constexpr mouse_state_ both_up = mouse_state_::both_up__;
    static constexpr mouse_state_ both_down = mouse_state_::both_down__;
  
  protected:
    void on_moved(const Vec2 &event, const MouseState &ms_st);
    void on_mouse_over(const Vec2 &event, const MouseState &ms_st);
    void on_mouse_exit(const Vec2 &event);
    void on_left_mouse_press(const Vec2 &event);
    void on_left_mouse_release(const Vec2 &event);
    void on_right_mouse_release(const Vec2 &event);
    void on_right_mouse_press(const Vec2 &event);
    //void on_key_press(const UserEvent &event) override;
    //void on_key_release(const UserEvent &event) override;

  };

}

#endif // SFCSS_CLICKABLE_H
