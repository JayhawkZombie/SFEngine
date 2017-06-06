#ifndef SFCSS_BACKGROUND_H
#define SFCSS_BACKGROUND_H

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

#include <sfcss/property/position.h>
#include <sfcss/property/color.h>
#include <sfcss/property/position.h>

#include <sfcss/ui/signals/signal.hpp>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{

  namespace priv
  {

	  struct background_attachment
	  {
	    enum class bg_att_ : cint_32 { scroll__, fixed__, local__, inherit__ };
      PRIVATE_VAR(bg_att_, attachment);
	
      signal<void> changed;

      void operator=(const background_attachment &bga) { attachment = bga.attachment; changed.emit(); }
      void operator=(const bg_att_ &bga) { attachment = bga; changed.emit(); }
	
	    bool operator==(const background_attachment &bga) { return ( attachment == bga.attachment ); }
	    bool operator!=(const background_attachment &bga) { return ( attachment != bga.attachment ); }
	
	    bool operator==(const bg_att_ &bga) { return ( attachment == bga ); }
	    bool operator!=(const bg_att_ &bga) { return ( attachment != bga ); }
	
	    background_attachment() : attachment(background_attachment::scroll) {}
	    background_attachment(const background_attachment &) = default;
	    background_attachment(const bg_att_ &b) : attachment(b) {}
	
	    static constexpr bg_att_ scroll  = bg_att_::scroll__;
	    static constexpr bg_att_ fixed   = bg_att_::fixed__;
	    static constexpr bg_att_ local   = bg_att_::local__;
	    static constexpr bg_att_ inherit = bg_att_::inherit__;
	  };
	
	  struct background
	  {
      background()
      {
        attachment.changed.connect([this]() { this->changed.emit(); }, "background");
        color.changed.connect([this]() { this->changed.emit(); }, "background");
        position.changed.connect([this]() { this->changed.emit(); }, "background");
      }

      signal<void> changed;
      CSS_PTR_TYPEDEF(background);
      CREATE_SHARED_DEFAULT(background);
      background_attachment attachment = background_attachment::scroll;
      priv::color color = priv::color::transparent;
      priv::position position = priv::position(position_left(0_px), position_top(0_px), position_right(0_px), position_bottom(0_px));
	  };

  }

}

#endif // SFCSS_BACKGROUND_H
