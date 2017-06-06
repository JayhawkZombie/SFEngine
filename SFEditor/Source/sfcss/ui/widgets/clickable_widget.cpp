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
#include <sfcss/ui/widgets/clickable.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  clickable_widget::clickable_widget(css_widget::rptr parent)
    : css_widget({
      { sf::Event::Closed            , false }, { sf::Event::GainedFocus        , false },
      { sf::Event::KeyPressed        , false }, { sf::Event::KeyReleased        , false },
      { sf::Event::MouseButtonPressed, true  }, { sf::Event::MouseButtonReleased, true  },
      { sf::Event::MouseEntered      , false }, { sf::Event::MouseLeft          , false },
      { sf::Event::MouseMoved        , true  }, { sf::Event::LostFocus          , false }
      }, parent)
  {
    moused_over.connect(std::bind(&clickable_widget::on_mouse_over, this, std::placeholders::_1, std::placeholders::_2), m_id);
    mouse_left.connect(std::bind(&clickable_widget::on_mouse_exit, this, std::placeholders::_1), m_id);
    mouse_moved.connect(std::bind(&clickable_widget::on_moved, this, std::placeholders::_1, std::placeholders::_2), m_id);
    left_mouse_pressed.connect(std::bind(&clickable_widget::on_left_mouse_press, this, std::placeholders::_1), m_id);
    right_mouse_pressed.connect(std::bind(&clickable_widget::on_right_mouse_press, this, std::placeholders::_1), m_id);
    left_mouse_released.connect(std::bind(&clickable_widget::on_left_mouse_release, this, std::placeholders::_1), m_id);
    right_mouse_released.connect(std::bind(&clickable_widget::on_right_mouse_release, this, std::placeholders::_1), m_id);
  }

  css::clickable_widget::sptr clickable_widget::create(css_widget::rptr parent)
  {
    return nullptr;
  }

  void clickable_widget::update()
  {

  }

  void clickable_widget::on_moved(const Vec2 &event, const MouseState &ms_st)
  {

  }

  void clickable_widget::on_mouse_over(const Vec2 &event, const MouseState &ms_st)
  {
    if (ms_st.left_down && !ms_st.right_down)
      m_mouse_state = clickable_widget::left_down;
    else if (ms_st.right_down && !ms_st.left_down)
      m_mouse_state = clickable_widget::right_down;
    else if (ms_st.left_down && ms_st.right_down)
      m_mouse_state = clickable_widget::both_down;
    else
      m_mouse_state = clickable_widget::both_up;

    m_click_state = clickable_widget::hovered;

    if (ms_st.left_down || ms_st.right_down)
      m_click_state = clickable_widget::pressed;

    hover_on.emit(event);
  }

  void clickable_widget::on_mouse_exit(const Vec2 &event)
  {
    m_click_state = clickable_widget::rest;
    m_mouse_state = clickable_widget::both_up;
    hover_off.emit(event);
  }

  void clickable_widget::on_left_mouse_press(const Vec2 &event)
  {
    m_mouse_state = clickable_widget::left_down;
  }

  void clickable_widget::on_left_mouse_release(const Vec2 &event)
  {
    m_mouse_state = clickable_widget::both_up;

    left_clicked.emit(event);
  }

  void clickable_widget::on_right_mouse_release(const Vec2 &event)
  {
    m_mouse_state = clickable_widget::both_up;
    right_clicked.emit(event);
  }

  void clickable_widget::on_right_mouse_press(const Vec2 &event)
  {
    m_mouse_state = clickable_widget::right_down;
  }

}
