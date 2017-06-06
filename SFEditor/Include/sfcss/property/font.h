#ifndef SFCSS_FONT_H
#define SFCSS_FONT_H

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
     * Font styling
     **/
    struct font_style
    {
      enum class font_style_ : cint_32 { normal__ = css::normal, italic__, oblique__, inherit__, initial__, unset__ };

      PRIVATE_VAR(font_style_, style);

      signal<void> changed;

      void operator=(font_style &fs) { style = fs.style; changed.emit(); }
      void operator=(font_style_ &fs) { style = fs; changed.emit(); }

      bool operator==(const font_style &fs) { return ( style == fs.style ); }
      bool operator!=(const font_style &fs) { return ( style != fs.style ); }
      bool operator==(const font_style_ &fs_) { return ( style != fs_ ); }
      bool operator!=(const font_style_ &fs_) { return ( style != fs_ ); }

      font_style_ operator()() const { return style; }

      font_style() : style(font_style::normal) {}
      font_style(const font_style &fs) : style(fs.style) {}
      font_style(const font_style_ fs_) : style(fs_) {}

      static constexpr font_style_ normal  = font_style_::normal__;
      static constexpr font_style_ italic  = font_style_::italic__;
      static constexpr font_style_ oblique = font_style_::oblique__;
      static constexpr font_style_ inherit = font_style_::inherit__;
      static constexpr font_style_ initial = font_style_::initial__;
      static constexpr font_style_ unset   = font_style_::unset__;

    };

    /*
     * The variant of the font
     **/
    struct font_variant
    {
      enum class _variant_ : cint_32 { normal__ = css::normal, none__ };

      PRIVATE_VAR(_variant_, variant);
      signal<void> changed;

      void operator=(const _variant_ &v) { variant = v; changed.emit(); }
      void operator=(const font_variant &v) { variant = v.variant; changed.emit(); }

      bool operator==(const font_variant &fv) { return ( variant == fv.variant ); }
      bool operator!=(const font_variant &fv) { return ( variant != fv.variant ); }
      bool operator==(const _variant_ &v) { return ( variant == v ); }
      bool operator!=(const _variant_ &v) { return ( variant != v ); }

      _variant_ operator()() const { return variant; }

      font_variant() : variant(font_variant::normal) {}
      font_variant(const font_variant &fv) = default;
      font_variant(const _variant_ &v) : variant(v) {}

      static constexpr _variant_ normal = _variant_::normal__;
      static constexpr _variant_ none   = _variant_::none__;

    };

    /*
     * The weight of the font
     **/
    struct font_weight
    {
      enum class font_weight_ : cint_32 { normal__ = 400, bold__ = 700, lighter__, bolder__ };

      PRIVATE_VAR(font_weight_, weight);
      signal<void> changed;

      void operator=(const font_weight &fw) { weight = fw.weight; changed.emit(); }
      void operator=(const font_weight_ &fw) { weight = fw; changed.emit(); }

      bool operator==(const font_weight &fw) { return ( weight == fw.weight ); }
      bool operator!=(const font_weight &fw) { return ( weight != fw.weight ); }
    
      bool operator==(const font_weight_ &fw) { return ( weight == fw ); }
      bool operator!=(const font_weight_ &fw) { return ( weight != fw ); }

      font_weight_ operator()() const { return weight; }

      font_weight() : weight(font_weight::normal) {}
      font_weight(const font_weight &) = default;
      font_weight(const font_weight_ &fw) : weight(fw) {}
    
      static constexpr font_weight_ normal  = font_weight_::normal__;
      static constexpr font_weight_ bold    = font_weight_::bold__;
      static constexpr font_weight_ lighter = font_weight_::lighter__;
      static constexpr font_weight_ bolder  = font_weight_::bolder__;

    };

    /*
     * The size of the font
     **/
    struct font_size
    {
      enum class font_size_ : cint_32 { xx_small__, x_small__, small__, medium__, large__, x_large__, xx_large__ };
      PRIVATE_VAR(font_size_, size);

      signal<void> changed;

      void operator=(const font_size_ &fs) { size = fs; changed.emit(); }
      void operator=(const font_size &fs) { size = fs.size; changed.emit(); }
      void operator=(cuint_32 fs) { size = static_cast<font_size_>( fs ); changed.emit(); }

      bool operator==(const font_size &fs) { return ( size == fs.size ); }
      bool operator!=(const font_size &fs) { return ( size != fs.size ); }

      bool operator==(const font_size_ &fs) { return ( size == fs ); }
      bool operator!=(const font_size_ &fs) { return ( size == fs ); }

      font_size_ operator()() const { return size; }

      font_size() : size(font_size::medium) {}
      font_size(const font_size &) = default;
      font_size(const font_size_ &fs) : size(fs) {}

      static constexpr font_size_ xx_small = font_size_::xx_small__;
      static constexpr font_size_ x_small  = font_size_::x_small__;
      static constexpr font_size_ small    = font_size_::small__;
      static constexpr font_size_ medium   = font_size_::medium__;
      static constexpr font_size_ large    = font_size_::large__;
      static constexpr font_size_ x_large  = font_size_::x_large__;
      static constexpr font_size_ xx_large = font_size_::xx_large__;
    };

    /*
     * Font property
     **/
    struct font
    {
      CSS_PTR_TYPEDEF(font);
      CREATE_SHARED_DEFAULT(font);

      font()
      {
        style.changed.connect([this]() { this->changed.emit(); }, "font");
        variant.changed.connect([this]() { this->changed.emit(); }, "font");
        weight.changed.connect([this]() { this->changed.emit(); }, "font");
        size.changed.connect([this]() { this->changed.emit(); }, "font");
      }

      signal<void> changed;
      font_style   style    = font_style::normal;
      font_variant variant  = font_variant::normal;
      font_weight  weight   = font_weight::normal;
      font_size    size     = font_size::medium;
      cuint_32     l_height = normal;
      sstring      family   = "";
    };

  }

}

#endif // SFCSS_FONT_H
