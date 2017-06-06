#ifndef SFCSS_SIZING_H
#define SFCSS_SIZING_H

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

    struct width
    {
      CSS_PTR_TYPEDEF(width);
      CREATE_SHARED_DEFAULT(width);

      PRIVATE_VAR(pixel_length, amount);

      signal<void> changed;

      void operator=(const pixel_length &p) { amount = p; changed.emit(); }
      void operator=(const width &w) { amount = w.amount; changed.emit(); }

      cuint_32 operator()() const { return amount.amnt(); }
      width() : amount(no_length) {}
    };

    struct height
    {
      CSS_PTR_TYPEDEF(height);
      CREATE_SHARED_DEFAULT(height);

      PRIVATE_VAR(pixel_length, amount);

      signal<void> changed;

      void operator=(const pixel_length &p) { amount = p; changed.emit(); }
      void operator=(const height &h) { amount = h.amount; changed.emit(); }

      cuint_32 operator()() const { return amount.amnt(); }
      height() : amount(no_length) {}
    };

  }

}

#endif // SFCSS_SIZING_H
