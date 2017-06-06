#ifndef SFCSS_VISIBILITY_H
#define SFCSS_VISIBILITY_H

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

    struct visibility
    {
      CSS_PTR_TYPEDEF(visibility);
      CREATE_SHARED_DEFAULT(visibility);

      enum vis_ : cint_32 { visible__, hidden__, collapse__, inherit__, initial__, unset__ };

      PRIVATE_VAR(vis_, vis);

      signal<void> changed;

      void operator=(const vis_ &v) { vis = v; changed.emit(); }
      void operator=(const visibility &v) { vis = v.vis; changed.emit(); }

      bool operator==(const visibility &v) { return ( vis == v.vis ); }
      bool operator!=(const visibility &v) { return ( vis != v.vis ); }

      bool operator==(const vis_ &v) { return ( vis == v ); }
      bool operator!=(const vis_ &v) { return ( vis != v ); }

      vis_ operator()() const { return vis; }

      static constexpr vis_ visible = vis_::visible__;
      static constexpr vis_ hidden = vis_::hidden__;
      static constexpr vis_ collapse = vis_::collapse__;
      static constexpr vis_ inherit = vis_::inherit__;
      static constexpr vis_ initial = vis_::initial__;
      static constexpr vis_ unset = vis_::unset__;

      visibility() : vis(visibility::visible) {}
      visibility(const visibility &v) : vis(v.vis) {}
      visibility(const vis_ &v) : vis(v) {}
    };

  }

}

#endif // SFCSS_VISIBILITY_H
