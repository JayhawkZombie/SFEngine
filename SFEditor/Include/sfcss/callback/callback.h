#ifndef SFCSS_CALLBACK_H
#define SFCSS_CALLBACK_H

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

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <functional>

namespace css
{
  template<class css_ret> using noarg_callback = std::function<css_ret(void)>;
  template<class css_ret, class ... css_args_> using callback = std::function<css_ret(css_args_...)>;

  using default_callback = std::function<void(const sstring &)>;
  const default_callback default_callback_ftn = [](const sstring &str) -> void { return; };

  struct align_callbacks
  {
    default_callback content   = default_callback_ftn;
    default_callback items     = default_callback_ftn;
    default_callback self      = default_callback_ftn;
    default_callback shorthand = default_callback_ftn;
  };

  struct animation_callbacks
  {
    default_callback shorthand = default_callback_ftn;
    default_callback delay;
  };

  struct CallbackTable
  {
    align_callbacks align;

    
  };

}

#endif // SFCSS_CALLBACK_H
