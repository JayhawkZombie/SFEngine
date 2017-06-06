#ifndef SFCSS_ENABLED_H
#define SFCSS_ENABLED_H

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

    struct enabled_status
    {
      CSS_PTR_TYPEDEF(enabled_status);
      CREATE_SHARED_DEFAULT(enabled_status);

      enum enab_ : cint_32 { enabled__, disabled__, inherit__, initial__, unset__ };

      PRIVATE_VAR(enab_, en);

      signal<void> changed;

      void operator=(const enab_ &e) { en = e; changed.emit(); }

      bool operator==(const enabled_status &e) { return ( en == e.en ); }
      bool operator!=(const enabled_status &e) { return ( en != e.en ); }

      bool operator==(const enab_ &e) { return ( en == e ); }
      bool operator!=(const enab_ &e) { return ( en != e ); }

      enab_ operator()() const { return en; }

      static constexpr enab_ enabled = enab_::enabled__;
      static constexpr enab_ disabled = enab_::disabled__;
      static constexpr enab_ inherit = enab_::inherit__;
      static constexpr enab_ initial = enab_::initial__;
      static constexpr enab_ unset = enab_::unset__;

      enabled_status() : en(enabled_status::enabled) {}
      enabled_status(const enab_ &e) : en(e) {}
      enabled_status(const enabled_status &e) : en(e.en) {}
    };

  }

}

#endif // SFCSS_ENABLED_H
