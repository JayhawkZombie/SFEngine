#ifndef SFCSS_SCREEN_H
#define SFCSS_SCREEN_H

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
#include <sfcss/utils/vec.h>

#include <sfcss/ui/tree/ui_tree.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{
  FWD_RENDERER(screen);

  class screen
  {
  public:
    FRIEND(screen_renderer);
    CSS_PTR_TYPEDEF(screen);
    screen(sf::RenderWindow &window);
    ~screen();
    static screen::sptr create(sf::RenderWindow &window);

    bool handle_event(const UserEvent &event);
    void update();

  private:

    widget_tree::sptr m_tree;
    
    sf::RenderWindow &m_window;
    void mouse_moved_within(const UserEvent &event);
    void mouse_moved_over(const UserEvent &event);
    void mouse_moved_off(const UserEvent &event);
    void left_mouse_was_pressed(const UserEvent &event);
    void left_mosue_was_released(const UserEvent &event);
    void right_mouse_was_pressed(const UserEvent &event);
    void right_mouse_was_released(const UserEvent &event);
    void key_was_pressed(const UserEvent &event);
    void key_was_released(const UserEvent &event);
  };

}

#endif // SFCSS_SCREEN_H
