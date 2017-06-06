#ifndef SFCSS_WIDGET_H
#define SFCSS_WIDGET_H

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
#include <sfcss/utils/vec.h>
#include <sfcss/utils/box.h>
#include <sfcss/events/userevent.h>
#include <sfcss/types.h>
#include <sfcss/ui/signals/signal.hpp>
#include <sfcss/property/properties.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{
#define FWD_RENDERER(CLASS)\
class CLASS##_renderer;

#define FRIEND(CLASS)\
friend class CLASS;

  FWD_RENDERER(css_widget);

  class css_widget
  {
  public:
    FRIEND(css_widget);
    CSS_PTR_TYPEDEF(css_widget);
    css_widget(std::initializer_list<std::pair<const sf::Event::EventType, bool>> list, css_widget::rptr parent = nullptr);
    css_widget();
    virtual ~css_widget();
    css_widget(css_widget::sptr) = delete;
    css_widget(const css_widget &) = delete;
    css_widget(const css_widget &&) = delete;
    css_widget& operator=(const css_widget&) = delete;
    
    virtual void update() = 0;

    FloatRect bounds() const;

    void handle_event(const UserEvent &event);

    bool is_visible() const;
    bool is_enabled() const;
    bool is_focused() const;

    std::string class_() const;
    std::string id_() const;

    signal<void> pre_render;
    signal<void> post_render;
    signal<void, const Vec2 &, const MouseState &> moused_over;
    signal<void, const Vec2 &> left_mouse_pressed;
    signal<void, const Vec2 &> left_mouse_released;
    signal<void, const Vec2 &> right_mouse_pressed;
    signal<void, const Vec2 &> right_mouse_released;
    signal<void, const Vec2 &> mouse_left;
    signal<void, const Vec2 &, const MouseState &> mouse_moved;
    signal<void, const sf::Keyboard::Key &> key_pressed;
    signal<void, const sf::Keyboard::Key &> key_released;
    signal<void, const UserEvent &, const MouseState &> focused;
    signal<void, const UserEvent &> unfocused;
    signal<void, const UserEvent &> window_lost_focus;
    signal<void, const UserEvent &> window_gained_focus;
    signal<void, const sf::Uint32 &> text_entered;
    signal<void, css_widget::rptr> moved;
    signal<void, css_widget::rptr> resized;
    signal<const std::string &, const std::string &> id_changed;
    signal<const std::string &, const std::string &> class_changed;

    static std::vector<std::pair<css_widget::rptr, cint_32>> widget_ids;
    static cint_32 last_id_generated;
  protected:
    /* Parent widget (if it has one) */
    cint_32 m_id_num;
    css_widget::rptr m_parent;
    std::string m_class;
    std::string m_id;
    property_table::sptr m_properties;
   
    const std::map<sf::Event::EventType, bool> m_responding_to =
    {
      { sf::Event::Closed            , false }, { sf::Event::GainedFocus        , false },
      { sf::Event::KeyPressed        , false }, { sf::Event::KeyReleased        , false },
      { sf::Event::MouseButtonPressed, false }, { sf::Event::MouseButtonReleased, false },
      { sf::Event::MouseEntered      , false }, { sf::Event::MouseLeft          , false },
      { sf::Event::MouseMoved        , false }, { sf::Event::LostFocus          , false }
    };

    /* internal overridable event handlers */
    //virtual void on_mouse_over(const UserEvent &event) = 0;
    //virtual void on_mouse_exit(const UserEvent &event) = 0;
    //virtual void on_mouse_move(const UserEvent &event) = 0;
    //virtual void on_left_mouse_press(const UserEvent &event) = 0;
    //virtual void on_left_mouse_release(const UserEvent &event) = 0;
    //virtual void on_right_mouse_release(const UserEvent &event) = 0;
    //virtual void on_right_mouse_press(const UserEvent &event) = 0;
    //virtual void on_key_press(const UserEvent &event) = 0;
    //virtual void on_key_release(const UserEvent &event) = 0;

  };

}

#endif // SFCSS_WIDGET_H
