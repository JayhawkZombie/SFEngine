#ifndef SFCSS_BORDER_H
#define SFCSS_BORDER_H

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
#include <sfcss/sfml_types.h>
#include <sfcss/property/color.h>

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
	
	  /*
	   * Border property
	   **/
	  struct border_style {
	    enum class border_style_ : cint_32 { inherit__, none__, solid__, dashed__, dotted__, hidden__ };
      PRIVATE_VAR(border_style_, style);

      signal<void> changed;
	
      void operator=(const border_style_ &bs) { style = bs; changed.emit(); }
      void operator=(const border_style &bs) { style = bs.style; changed.emit(); }
	
	    bool operator==(const border_style &bs) { return ( style == bs.style ); }
	    bool operator!=(const border_style &bs) { return ( style != bs.style ); }
	
	    bool operator==(const border_style_ &bs) { return ( style == bs ); }
	    bool operator!=(const border_style_ &bs) { return ( style != bs ); }
	
	    border_style() : style(border_style::none)  {}
      border_style(const border_style &s) : style(s.style) {}
	    border_style(const border_style_ &bs) : style(bs) {}
	
	    static constexpr border_style_ inherit = border_style_::inherit__;
	    static constexpr border_style_ none    = border_style_::none__;
	    static constexpr border_style_ solid   = border_style_::solid__;
	    static constexpr border_style_ dashed  = border_style_::dashed__;
	    static constexpr border_style_ dotted  = border_style_::dotted__;
	    static constexpr border_style_ hidden  = border_style_::hidden__;
	  };
	
	  struct border_size
	  {
	    enum class border_size_ : cint_32 { thin__, medium__, thick__ };
      PRIVATE_VAR(border_size_, size);

      signal<void> changed;

      void operator=(const border_size &bs) { size = bs.size; changed.emit(); }
      void operator=(const border_size_ &bs) { size = bs; changed.emit(); }
	
	    bool operator==(const border_size &bs) { return ( size == bs.size ); }
	    bool operator!=(const border_size &bs) { return ( size != bs.size ); }
	
	    bool operator==(const border_size_ &bs) { return ( size == bs ); }
	    bool operator!=(const border_size_ &bs) { return ( size != bs ); }
	
      border_size() : size(border_size::thin) {}
	    border_size(const border_size &) = default;
	    border_size(const border_size_ &bs) : size(bs) {}
	
	    static constexpr border_size_ thin   = border_size_::thin__;
	    static constexpr border_size_ medium = border_size_::medium__;
	    static constexpr border_size_ thick  = border_size_::thick__;
	  };
	
	  struct border_left {
      border_left() : radius(0_px) {
        style.changed.connect([this]() { this->changed.emit(); }, "left");
        color.changed.connect([this]() { this->changed.emit(); }, "left");
        width.changed.connect([this]() { this->changed.emit(); }, "left");
        radius.changed.connect([this]() { this->changed.emit(); }, "left");
      }

      pixel_length radius;

      signal<void> changed;
	    priv::color  color = priv::color::transparent;
	    border_style style;
	    border_size  width;
	  };
	
	  struct border_right {
      border_right() : radius(0_px) {
        style.changed.connect([this]() { this->changed.emit(); }, "left");
        color.changed.connect([this]() { this->changed.emit(); }, "left");
        width.changed.connect([this]() { this->changed.emit(); }, "left");
        radius.changed.connect([this]() { this->changed.emit(); }, "left");
      }

      signal<void> changed;
	    priv::color  color = priv::color::transparent;
      pixel_length radius;
	    border_style style;
	    border_size  width;
	  };
	
	  struct border_top {
      border_top() : left_radius(0_px), right_radius(0_px) {
        style.changed.connect([this]() { this->changed.emit(); }, "right");
        color.changed.connect([this]() { this->changed.emit(); }, "right");
        width.changed.connect([this]() { this->changed.emit(); }, "right");
        left_radius.changed.connect([this]() { this->changed.emit(); }, "right");
        right_radius.changed.connect([this]() { this->changed.emit(); }, "right");
      }

      signal<void> changed;
	    priv::color  color = priv::color::transparent;
	    pixel_length left_radius;
	    pixel_length right_radius;
	    border_style style;
	    border_size  width;
	  };
	
	  struct border_bottom {
      border_bottom() : left_radius(0_px), right_radius(0_px) {
        style.changed.connect([this]() { this->changed.emit(); }, "right");
        color.changed.connect([this]() { this->changed.emit(); }, "right");
        width.changed.connect([this]() { this->changed.emit(); }, "right");
        left_radius.changed.connect([this]() { this->changed.emit(); }, "right");
        right_radius.changed.connect([this]() { this->changed.emit(); }, "right");
      }

      signal<void> changed;
      priv::color  color = priv::color::transparent;
      pixel_length left_radius;
      pixel_length right_radius;
      border_style style;
      border_size  width;
	  };
	
	  struct border
	  {
      CSS_PTR_TYPEDEF(border);
      CREATE_SHARED_DEFAULT(border);

      border()
      {
        left.changed.connect([this]() { this->changed.emit(); }, "border");
        top.changed.connect([this]() { this->changed.emit(); }, "border");
        right.changed.connect([this]() { this->changed.emit(); }, "border");
        bottom.changed.connect([this]() { this->changed.emit(); }, "border");
      }

      signal<void> changed;
	    border_left   left;
	    border_top    top;
	    border_right  right;
	    border_bottom bottom;
	  };
  }

}

#endif // SFCSS_BORDER_H
