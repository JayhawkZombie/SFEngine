#ifndef SFCSS_ANIMATION_H
#define SFCSS_ANIMATION_H

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
#include <sfcss/utils/vec.h>
#include <sfcss/utils/cubic_bezier.h>

#include <sfcss/ui/signals/signal.hpp>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace css
{
  namespace priv {

    /*
     * Direction of the animation
     **/
    struct animation_direction
    {
      CSS_PTR_TYPEDEF(animation_direction);

      signal<void> changed;

      enum class _anim_dir : cint_32 { normal__ = css::normal, reverse__, alternate__, alternate_reverse__, inherit__, initial__, unset__ };

      void operator=(const _anim_dir &i) { direction = i; changed.emit(); }
      void operator=(const cint_32 &i) { switch (i) { case css::normal:  direction = animation_direction::normal;
                                                                      case css::inherit: direction = animation_direction::inherit;
                                                                      default:           direction = animation_direction::normal; }
                                                         changed.emit(); }
      bool operator==(const animation_direction &d) { return ( d.direction == direction ); }
      bool operator!=(const animation_direction &d) { return ( d.direction != direction ); }

      bool operator==(const _anim_dir &dir) { return ( direction == dir ); }
      bool operator!=(const _anim_dir &dir) { return ( direction != dir ); }

      animation_direction(_anim_dir dir) : direction(dir) {}
      animation_direction() : direction(animation_direction::normal) {}
      animation_direction(const animation_direction &) = default;

      static constexpr _anim_dir normal            = _anim_dir::normal__;
      static constexpr _anim_dir reverse           = _anim_dir::reverse__;
      static constexpr _anim_dir alternate         = _anim_dir::alternate__;
      static constexpr _anim_dir alternate_reverse = _anim_dir::alternate_reverse__;
      static constexpr _anim_dir inherit           = _anim_dir::inherit__;
      static constexpr _anim_dir initial           = _anim_dir::initial__;
      static constexpr _anim_dir unset             = _anim_dir::unset__;

      PRIVATE_VAR(_anim_dir, direction)
    };

    /*
     * Fill mode for the animation
     **/
    struct animation_fill_mode
    {
      CSS_PTR_TYPEDEF(animation_fill_mode);
      enum class fill_mode { none__, forwards__, backwards__, both__ };

      PRIVATE_VAR(fill_mode, mode);

      signal<void> changed;

      void operator=(const fill_mode &m) { mode = m; changed.emit(); }
      void operator=(const animation_fill_mode &fm) { mode = fm.mode; changed.emit(); }

      bool operator==(const animation_fill_mode &fm) { return ( mode == fm.mode ); }
      bool operator!=(const animation_fill_mode &fm) { return ( mode != fm.mode ); }

      bool operator==(const fill_mode &fm) { return ( mode == fm ); }
      bool operator!=(const fill_mode &fm) { return ( mode != fm ); }

      animation_fill_mode(const fill_mode &m) : mode(m) {}
      animation_fill_mode() = default;
      animation_fill_mode(const animation_fill_mode &) = default;

      static constexpr fill_mode none      = fill_mode::none__;
      static constexpr fill_mode forwards  = fill_mode::forwards__;
      static constexpr fill_mode backwards = fill_mode::backwards__;
      static constexpr fill_mode both      = fill_mode::both__;
    };

    /*
     * Play state of the animation
     **/
    struct animation_play_state
    {
      CSS_PTR_TYPEDEF(animation_play_state);
      enum class play_state : cint_32 { running__, paused__ };

      PRIVATE_VAR(play_state, state);

      signal<void> changed;

      bool operator==(const animation_play_state &ps) { return ( state == ps.state ); }
      bool operator!=(const animation_play_state &ps) { return ( state != ps.state ); }

      bool operator==(const play_state &ps) { return ( state == ps ); }
      bool operator!=(const play_state &ps) { return ( state != ps ); }

      void operator=(const animation_play_state &ps) { state = ps.state; changed.emit(); }
      void operator=(const play_state &ps) { state = ps; changed.emit(); }

      animation_play_state() : state(animation_play_state::paused) {}
      animation_play_state(const play_state &ps) : state(ps) {}
      animation_play_state(const animation_play_state &) = default;

      static constexpr play_state running = play_state::running__;
      static constexpr play_state paused  = play_state::paused__;
    };

    /* animation property */
    struct animation
    {
      CSS_PTR_TYPEDEF(animation);
      CREATE_SHARED_DEFAULT(animation);

      animation()
      {
        direction.changed.connect([this]() { this->changed.emit(); }, "animation");
        fill_mode.changed.connect([this]() { this->changed.emit(); }, "animation");
        play_state.changed.connect([this]() { this->changed.emit(); }, "animation");
      }

      signal<void> changed;
      sstring     name = "";
      CubicBezier easing_curve        = CubicBezier::EaseInOut();
      cuint_32    iteration_count     = 1;
      ms                  duration    = 0_ms;
      ms                  delay       = 0_ms;
      animation_direction direction   = animation_direction::normal;
      animation_fill_mode fill_mode   = animation_fill_mode::forwards;
      animation_play_state play_state = animation_play_state::paused;
    };

  }
}

#endif // SFCSS_ANIMATION_H
