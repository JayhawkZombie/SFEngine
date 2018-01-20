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

#include <type_traits>
#include <algorithm>

/* Must be in a namespace to avoid unwanted use by template auto deduction */

namespace type
{

  struct no__ { };
  template<typename T> no__ operator+(const T&);
  template<typename T> no__ operator+(const T&, const T&);
  template<typename T> no__ operator-(const T&);
  template<typename T> no__ operator-(const T&, const T&);
  template<typename T> no__ operator+=(T &, const T&);
  template<typename T> no__ operator-=(T &, const T&);
  template<typename T, typename ARG> no__ operator*(const T&, ARG);
  template<typename T, typename ARG> no__ operator*(ARG, const T &);
  template<typename T, typename ARG> no__ operator/(const T&, ARG);
  template<typename T, typename ARG> no__ operator/(ARG, const T &);
  template<typename T, typename ARG> no__ operator*=(T &, ARG);
  template<typename T, typename ARG> no__ operator/=(T &, ARG);

  template<typename T> no__ operator<(const T&, const T&);
  template<typename T> no__ operator>(const T&, const T&);
  template<typename T> no__ operator<=(const T&, const T&);
  template<typename T> no__ operator>=(const T&, const T&);
  template<typename T> no__ operator==(const T&, const T&);
  template<typename T> no__ operator!=(const T&, const T&);

  template<typename T>
  struct has_operator_unary_plus
  {
    enum { value = !std::is_same<decltype(*( T * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_operator_binary_plus
  {
    enum { value = !std::is_same<decltype(*( T * )(0) + *( ARG * )(0)), no__>::value };
  };

  template<typename T>
  struct has_operator_unary_minus
  {
    enum { value = !std::is_same<decltype(*( T * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_operator_binary_minus
  {
    enum { value = !std::is_same<decltype(*( T * )(0) - *( ARG * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_operator_mult
  {
    enum { value = !std::is_same<decltype(*( T * )(0) * *( ARG * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_operator_div
  {
    enum { value = !std::is_same<decltype(*( T * )(0) / *( ARG * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_compound_assignment_plus
  {
    enum { value = !std::is_same<decltype(*( T * )(0) += *( ARG * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_compound_assignment_minus
  {
    enum { value = !std::is_same<decltype(*( T * )(0) -= *( ARG * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_compound_assignment_mult
  {
    enum { value = !std::is_same<decltype(*( T * )(0) *= *( ARG * )(0)), no__>::value };
  };

  template<typename T, typename ARG>
  struct has_compound_assignment_div
  {
    enum { value = !std::is_same<decltype(*( T * )(0) /= *( ARG * )(0)), no__>::value };
  };

  template<typename T>
  struct has_operator_assign
  {
    enum { value = std::is_copy_assignable_v<T> };
  };

  template<typename T>
  struct has_operator_equality
  {
    enum { value = !std::is_same<decltype(*( T * )(0) == *( T * )(0)), no__>::value };
  };

  template<typename T>
  struct has_operator_not_equal
  {
    enum { value = !std::is_same<decltype(*( T * )(0) != *( T * )(0)), no__>::value };
  };

  template<typename T>
  struct has_operator_less
  {
    enum { value = !std::is_same<decltype(*( T * )(0) < *( T * )(0)), no__>::value };
  };

  template<typename T>
  struct has_operator_greater
  {
    enum { value = !std::is_same<decltype(*( T * )(0) > *( T * )(0)), no__>::value };
  };

  template<typename T>
  struct has_operator_less_equal
  {
    enum { value = !std::is_same<decltype(*( T * )(0) <= *( T * )(0)), no__>::value };
  };

  template<typename T>
  struct has_operator_greater_equal
  {
    enum { value = !std::is_same<decltype(*( T * )(0) >= *( T * )(0)), no__>::value };
  };

}
