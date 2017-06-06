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
#include <sfcss/ui/widgets/screen.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{



  screen::screen(sf::RenderWindow &window)
   :  m_window(window), m_tree(widget_tree::create())
  {
    
  }

  screen::~screen()
  {
    m_tree.reset();
  }

  css::screen::sptr screen::create(sf::RenderWindow &window)
  {
    screen::sptr scr = std::make_shared<screen>(window);
    return scr;
  }

  bool screen::handle_event(const UserEvent &event)
  {
    return true;
  }

  void screen::update()
  {

  }

  void screen::mouse_moved_over(const UserEvent &event)
  {
    //Have to call down the event tree and see what happened
  }

  void screen::mouse_moved_off(const UserEvent &event)
  {

  }

  void screen::mouse_moved_within(const UserEvent &event)
  {

  }

  void screen::left_mouse_was_pressed(const UserEvent &event)
  {

  }

  void screen::left_mosue_was_released(const UserEvent &event)
  {

  }

  void screen::right_mouse_was_released(const UserEvent &event)
  {

  }

  void screen::right_mouse_was_pressed(const UserEvent &event)
  {

  }

  void screen::key_was_pressed(const UserEvent &event)
  {

  }

  void screen::key_was_released(const UserEvent &event)
  {

  }

}
