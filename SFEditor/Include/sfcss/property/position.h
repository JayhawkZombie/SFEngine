#ifndef SFCSS_POSITION_H
#define SFCSS_POSITION_H

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
	  * This is so that we can do this:
	  *
	  *    button.left.position = 3px; and have the class ALSO be aware that
	  *      we have assigned a length-based offset and not just some integer
	  *      (hence the temporary intermediate "pixel" class created by the "px" literal operator)
	  **/
	  struct pixel {
	    constexpr pixel(cuint_32 v) : x(v) {}
	    ~pixel() = default;
	    const cuint_32 x = 0;
	  };
	
	  struct absolute_length {
	    enum : cint_32 { none__ = -1, custom__ };
	    constexpr absolute_length(const cuint_32 &v) : val(v) {}
	    const cuint_32 val = 0;
	  };
	
	  struct percentage_length {
	   enum : cint_32 { none__ = -1, custom__ };
	    constexpr percentage_length(const cuint_32 &v) : val(v) {}
	    const cuint_32 val = 0;
	  };
	
	  struct pixel_length {
	    enum length_ : cuint_32 { relative__, absolute__ };

      PRIVATE_VAR(cuint_32, amount);
      PRIVATE_VAR(length_, type);
	
      signal<void> changed;

      cuint_32 amnt() const { return amount; }
      length_ length_type() const { return type; }

	    void operator=(const pixel_length &o) { type = o.type; amount = o.amount; changed.emit(); }
	    void operator=(const pixel &p) { type = pixel_length::absolute; amount = p.x; changed.emit(); }
	
	    static constexpr length_ relative = length_::relative__;
	    static constexpr length_ absolute = length_::absolute__;
	
	    pixel_length(const absolute_length &ab) : amount(ab.val), type(pixel_length::absolute) {}
	    pixel_length(const percentage_length &p) : amount(p.val), type(pixel_length::relative) {}
      pixel_length() : amount(0), type(pixel_length::absolute) {}
	  };
	
	  //pixel_length operator"" _perc(unsigned long long l) { return pixel_length(percentage_length(static_cast<cuint_32>(l))); }
	  //pixel_length operator"" _px(unsigned long long l) { return pixel_length(absolute_length(static_cast<cuint_32>(l))); }
	
	  struct position_left {
      signal<void> changed;
      position_left() : length(pixel_length(absolute_length(0))) {
        length.changed.connect([this]() { this->changed.emit(); }, "pos_left");
      }

      PRIVATE_VAR(pixel_length, length);
	    void operator=(const pixel_length &po) { length = po; changed.emit(); }

	    operator pixel_length() { return length; }
	    position_left(const pixel_length &p) : length(p) {}
	  };
	
	  constexpr absolute_length no_length(0);
	
	  struct position_top {
      signal<void> changed;
      position_top() : length(pixel_length(absolute_length(0))) {
        length.changed.connect([this]() { this->changed.emit(); }, "pos_top");
      }

      PRIVATE_VAR(pixel_length, length);
      void operator=(const pixel_length &po) { length = po; changed.emit(); }
	
	    operator pixel_length() { return length; }
	    position_top(const pixel_length &p) : length(p) {}
	  };
	
	  struct position_right {
      signal<void> changed;
      position_right() : length(pixel_length(absolute_length(0))) {
        length.changed.connect([this]() { this->changed.emit(); }, "pos_right");
      }

      PRIVATE_VAR(pixel_length, length);
      void operator=(const pixel_length &po) { length = po; changed.emit(); }
	
	    operator pixel_length() { return length; }
	    position_right(const pixel_length &p) : length(p) {}
	  };
	
	  struct position_bottom {
      signal<void> changed;
      position_bottom() : length(pixel_length(absolute_length(0))) {
        length.changed.connect([this]() { this->changed.emit(); }, "pos_bottom");
      }

      PRIVATE_VAR(pixel_length, length);
      void operator=(const pixel_length &po) { length = po; changed.emit(); }
	
	    operator pixel_length() { return length; }
	    position_bottom(const pixel_length &p) : length(p) {}
	  };
	
	  /*
	  * Position property
	  **/
	  struct position
	  {
      CSS_PTR_TYPEDEF(position);
      CREATE_SHARED_DEFAULT(position);
	    enum class pos_ : cint_32 { left__, center__, right__, top__, bottom__, perc__, len__, none__, custom__ };
	
      PRIVATE_VAR(pos_, pos_type);
      signal<void> changed;
	
      position_left   p_left;
      position_top    p_top;
      position_right  p_right;
      position_bottom p_bottom;

      position_left left()     const { return p_left;   }
      position_top top()       const { return p_top;    }
      position_right right()   const { return p_right;  }
      position_bottom bottom() const { return p_bottom; }

      void operator=(const pos_ &ptype) { pos_type = ptype; changed.emit(); }
	
      void operator=(const position_left &l)   { p_left = l;         p_bottom = no_length;  p_top = no_length; p_right = no_length; }
      void operator=(const position_top &t)    { p_left = no_length; p_bottom = no_length;  p_top = t;         p_right = no_length; }
      void operator=(const position_right &r)  { p_left = no_length; p_bottom = no_length;  p_top = no_length; p_right = r;         }
      void operator=(const position_bottom &b) { p_left = no_length; p_bottom = b;          p_top = no_length; p_right = no_length; }
      void operator=(const position &p)        { p_left = p.p_left;  p_bottom = p.p_bottom; p_top = p.p_top;   p_right = p.p_right; }
	
	    static constexpr pos_ Left   = pos_::left__;
	    static constexpr pos_ Center = pos_::center__;
	    static constexpr pos_ Right  = pos_::right__;
	    static constexpr pos_ Top    = pos_::top__;
	    static constexpr pos_ Bottom = pos_::bottom__;
	    static constexpr pos_ Perc   = pos_::perc__;
	    static constexpr pos_ Len    = pos_::len__;
	    static constexpr pos_ None   = pos_::none__;
	    static constexpr pos_ Custom = pos_::custom__;
    private: 
      void connect_all()
      {
        p_left.changed.connect([this]() { this->changed.emit(); }, "position");
        p_top.changed.connect([this]() { this->changed.emit(); }, "position");
        p_right.changed.connect([this]() { this->changed.emit(); }, "position");
        p_bottom.changed.connect([this]() { this->changed.emit(); }, "position");
      }

    public:
	    position() 
	      : pos_type(position::None), p_left(no_length), p_top(no_length), p_right(no_length), p_bottom(no_length) { connect_all(); }
	
	    position(const position_left &l) 
	      : pos_type(position::Left), p_left(l), p_top(no_length), p_right(no_length), p_bottom(no_length) { connect_all(); }
	
	    position(const position_top &t)
	      : pos_type(position::Top), p_top(t), p_left(no_length), p_right(no_length), p_bottom(no_length) { connect_all(); }
	    
	    position(const position_right &r)
	      : pos_type(position::Right), p_right(r), p_left(no_length), p_top(no_length), p_bottom(no_length) { connect_all(); }
	
	    position(const position_bottom &b)
	      : pos_type(position::Bottom), p_bottom(b), p_left(no_length), p_right(no_length), p_top(no_length) { connect_all(); }
	
	    position(const position_left &l, const position_top &t, const position_right &r, const position_bottom &b)
	      : pos_type(position::Custom), p_top(t), p_bottom(b), p_left(l), p_right(r) { connect_all(); }
	  };

   }

   priv::pixel_length operator"" _perc(unsigned long long l);
   priv::pixel_length operator"" _px(unsigned long long l);
}

#endif // SFCSS_POSITION_H
