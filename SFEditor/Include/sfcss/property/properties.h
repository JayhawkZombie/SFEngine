#ifndef SFCSS_PROPERTIES_H
#define SFCSS_PROPERTIES_H

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
#include <sfcss/utils/box.h>
#include <sfcss/utils/vec.h>
#include <sfcss/utils/cubic_bezier.h>
#include <sfcss/sfml_types.h>

#include <sfcss/property/animation.h>
#include <sfcss/property/color.h>
#include <sfcss/property/position.h>
#include <sfcss/property/font.h>
#include <sfcss/property/border.h>
#include <sfcss/property/background.h>
#include <sfcss/property/sizing.h>
#include <sfcss/property/visibility.h>
#include <sfcss/property/enabled.h>

#include <sfcss/ui/signals/signal.hpp>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{
  using line_height = cint_32;

  //enum class animation_direction : cint_32 { normal = css::normal, reverse, alternate, alternate_reverse, inherit, initial, unset };

  struct property_table
  {
    CSS_PTR_TYPEDEF(property_table);
    CREATE_SHARED_DEFAULT(property_table);

    property_table()
    {
      animation.second->changed.connect([this]() { this->animation_changed.emit(); }, "property_table");
      background.second->changed.connect([this]( ){this->background_changed.emit(); }, "property_table");
      position.second->changed.connect([this]() { this->position_changed.emit(); }, "property_table");
      border.second->changed.connect([this]() { this->background_changed.emit(); }, "property_table");
      width.second->changed.connect([this]() { this->width_changed.emit(); }, "property_table");
      height.second->changed.connect([this]() { this->height_changed.emit(); }, "property_table");
      font.second->changed.connect([this]() { this->font_changed.emit(); }, "property_table");
      visibility.second->changed.connect([this]() { this->visibility_changed.emit(); }, "property_table");
      enabled.second->changed.connect([this]() { this->enabled_changed.emit(); }, "property_table");
    }

    signal<void> animation_changed;
    signal<void> background_changed;
    signal<void> position_changed;
    signal<void> border_changed;
    signal<void> width_changed;
    signal<void> height_changed;
    signal<void> font_changed;
    signal<void> visibility_changed;
    signal<void> enabled_changed;

    pair<sstring, priv::animation::sptr>  animation   = { "animation" , priv::animation::create()      };
    pair<sstring, priv::background::sptr> background  = { "background", priv::background::create()     };
    pair<sstring, priv::position::sptr>   position    = { "position"  , priv::position::create()       };
    pair<sstring, priv::border::sptr>     border      = { "border"    , priv::border::create()         };
    pair<sstring, priv::width::sptr>      width       = { "width"     , priv::width::create()          };
    pair<sstring, priv::height::sptr>     height      = { "height"    , priv::height::create()         };
    pair<sstring, priv::font::sptr>       font        = { "font"      , priv::font::create()           };
    pair<sstring, priv::visibility::sptr> visibility  = { "visibility", priv::visibility::create()     };
    pair<sstring, priv::enabled_status::sptr> enabled = { "enabled"   , priv::enabled_status::create() };
  };


}

#endif // SFCSS_PROPERTIES_H
