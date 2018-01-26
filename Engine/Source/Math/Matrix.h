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

#include <complex>
#include <array>

template<typename T>
class Matrix2_2
{
public:

  std::pair<std::complex<float>, std::complex<float>> Eigenvalues();

  T Det()
  {
    return ( ( m_Values[0] * m_Values[3] ) - ( m_Values[2] * m_Values[1] ) );
  }

  Matrix2_2 Inverse()
  {
    Matrix2_2 m = *this;
    m.m_Values[0] = m_Values[3];
    m.m_Values[1] = -m_Values[1];
    m.m_Values[2] = -m_Values[2];
    m.m_Values[3] = m_Values[0];

    m /= m.Det();
    return m;
  }

  Matrix2_2 Transpose()
  {
    Matrix2_2 m = *this;

    m.m_Values[1] = m_Values[2];
    m.m_Values[2] = m_Values[1];

    return m;
  }

  T operator()(unsigned int x, unsigned int y)
  {
    if (x > 1 || y > 1)
      throw std::out_of_range("Matrix bounds access out of range");

    return m_Values[2 * x + y];
  }

  template<typename U>
  Matrix2_2& operator /= (U val)
  {
    m_Values[0] /= val;
    m_Values[1] /= val;
    m_Values[2] /= val;
    m_Values[3] /= val;

    return *this;
  }

  template<typename U>
  Matrix2_2& operator *= (U val)
  {
    m_Values[0] *= val;
    m_Values[1] *= val;
    m_Values[2] *= val;
    m_Values[3] *= val;

    return *this;
  }

  Matrix2_2& operator += (Matrix2_2 m)
  {
    m_Values[0] += m.m_Values[0];
    m_Values[1] += m.m_Values[1];
    m_Values[2] += m.m_Values[2];
    m_Values[3] += m.m_Values[3];

    return *this;
  }

  Matrix2_2& operator -= (Matrix2_2 m)
  {
    m_Values[0] -= m.m_Values[0];
    m_Values[1] -= m.m_Values[1];
    m_Values[2] -= m.m_Values[2];
    m_Values[3] -= m.m_Values[3];

    return *this;
  }

  template<typename U>
  inline friend operator * (U val, Matrix2_2 & mat)
  {

  }

private:

  std::array<T, 4> m_Values;

};
