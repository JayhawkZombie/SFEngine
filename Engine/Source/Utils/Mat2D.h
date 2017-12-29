#pragma once

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

#include <math.h>
#include <cmath>
#include <algorithm>
#include <stdexcept>

class Mat2D
{
public:
  Mat2D()
    : a(1), b(1), c(1), d(1), e(1), f(1)
  {}
  Mat2D(const Mat2D &other)
    : a(other.a), b(other.b), c(other.c), d(other.d), e(other.e), f(other.f)
  {}
  Mat2D(const float &_a, const float &_b, const float &_c, const float &_d, const float &_e, const float &_f)
    :
    a(_a), b(_b), c(_c), d(_d), e(_e), f(_f)
  {}

  void SolveSystem() {
    //make sure the det is not zero

    float det = (a * d) - (c * b);

    //if (std::abs(det) < 0.0001)
    //  throw std::runtime_error("Matrix is singular or there is no stable numerical solution");

    /**
    * [  a   b   |   e  ]
    * [  c   d   |   f  ]
    *
    * if (abs(c) > abs(a)) swap row(1) & row(2)
    */
    if (std::abs(c) > std::abs(a)) {
      std::swap(a, c);
      std::swap(b, d);
      std::swap(e, f);
    }

    /**
    * [  a   b   |   e  ]
    * [  c   d   |   f  ]
    *
    *  r2 = r2 - (c/a) * r1
    */
    float factor = c / a;
    float r2c = factor * a;  c -= r2c;
    float r2d = factor * b;  d -= r2d;
    float r2f = factor * e;  f -= r2f;

    /**
    *  [  a          b          |          e         ] == became ==> [ a b | e ]
    *  [  0   d - (c / a) * b   |   f - (c / a) * e  ]               [ 0 d | f ]
    *
    * v = [ f - (c / d) * e ] / [ d - (c / a) * b ]
    */

    f /= d; d = 1;
    /**
    *  [  a  b  |  e  ]
    *  [  0  1  |  f  ]
    *
    *  b -= b * 1;
    *  e -= b * f; <-- do first
    */
    e -= b * f; b = 1;
    /**
    *  [  a  0  |  e  ]
    *  [  0  1  |  f  ]
    */
    e /= a; a = 1;
    /**
    *  [  1  0  |  e  ]
    *  [  0  1  |  f  ]
    *
    *   t = e
    *   v = f
    */

  }

  float a, b, c, d, e, f;

};