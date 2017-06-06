#ifndef SFCSS_COLOR_H
#define SFCSS_COLOR_H

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
	   * Color property
	   **/
    struct color_value {
      color_value() : v(0) {}
      color_value(const cuint_8 &val) : v(val) {}

      signal<void> changed;

      void operator=(const color_value &va) { v = va.v; changed.emit(); }
      void operator=(const cuint_8 &val) { v = val; changed.emit(); }

      PRIVATE_VAR(cuint_8, v);
    };

	  struct rgb {
	    color_value r;
      color_value g;
      color_value b;
      color_value a;

      signal<void> changed;
	
	    rgb() : r(cuint_8(0)), g(cuint_8(0)), b(cuint_8(0)), a(cuint_8(255)) 
      {
        r.changed.connect([this]() { this->changed.emit(); }, "rgb");
        g.changed.connect([this]() { this->changed.emit(); }, "rgb");
        b.changed.connect([this]() { this->changed.emit(); }, "rgb");
        a.changed.connect([this]() { this->changed.emit(); }, "rgb");
      }
	    rgb(const cuint_8 &r_, const cuint_8 &g_, const cuint_8 &b_, const cuint_8 &a_) : r(r_), g(g_), b(b_), a(a_) 
      {
        r.changed.connect([this]() { this->changed.emit(); }, "rgb");
        g.changed.connect([this]() { this->changed.emit(); }, "rgb");
        b.changed.connect([this]() { this->changed.emit(); }, "rgb");
        a.changed.connect([this]() { this->changed.emit(); }, "rgb");
      }
	
      void operator=(const rgb &r_) { r = r_.r; g = r_.g; b = r_.b; a = r_.a; changed.emit(); }
	  };
	
	  struct color
	  {
      CSS_PTR_TYPEDEF(color);
      CREATE_SHARED_DEFAULT(color);
	    enum class color_ : cint_32 
	    { black__, white__, blue__, green__, yellow__, purple__, red__, gray__, light_gray__, dark_gray__, 
	      transparent__,
	      custom__ = cint_32_max };
	    static std::map<color_, rgb> colormap;
	
      signal<void> changed;

      rgb value;
	
	    void operator=(const rgb &c)    { value = c; changed.emit(); }
	    void operator=(const color &c)  { value = c.value; changed.emit(); }
	    void operator=(const color_ &c) { value = colormap.at(c); changed.emit(); }
	
	    color() : value(rgb(255, 255, 255, 255)) {}
	    color(const color &r) : value(r.value) {}
	    color(const color_ &c) : value(colormap.at(c)) {}
	
	    static constexpr color_ black       = color_::black__;
	    static constexpr color_ white       = color_::white__;
	    static constexpr color_ blue        = color_::blue__;
	    static constexpr color_ green       = color_::green__;
	    static constexpr color_ yellow      = color_::yellow__;
	    static constexpr color_ purple      = color_::purple__;
	    static constexpr color_ red         = color_::red__;
	    static constexpr color_ gray        = color_::gray__;
	    static constexpr color_ light_gray  = color_::light_gray__;
	    static constexpr color_ dark_gray   = color_::dark_gray__;
	    static constexpr color_ transparent = color_::transparent__;
	
	  };
  }

}

#endif // SFCSS_COLOR_H
