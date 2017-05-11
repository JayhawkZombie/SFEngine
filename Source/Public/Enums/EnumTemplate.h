#ifndef SFEngine_EnumTemplate_H
#define SFEngine_EnumTemplate_H

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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "BasicIncludes.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        EnumTemplate                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/02                                  */
/************************************************************************/

namespace SFEngine
{

  template<typename T, bool = std::is_enum<T>::value>
  struct is_flag;

  template<typename T>
  struct is_flag<T, true> : std::false_type { };

  template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
  T operator | (T lhs, T rhs)
  {
    using T_t = typename std::underlying_type<T>::type;
    return static_cast<T>(static_cast<T_t>(lhs) | static_cast<T_t>(rhs));
  }

  template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
  T operator & (T lhs, T rhs)
  {
    using T_t = typename std::underlying_type<T>::type;
    return static_cast<T>(static_cast<T_t>(lhs) & static_cast<T_t>(rhs));
  }

  template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
  T operator ~ (T val)
  {
    using T_t = typename std::underlying_type<T>::type;
    return static_cast<T>(~static_cast<T_t>(val));
  }

  template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
  bool test(T enumV, T flag)
  {
    using T_t = typename std::underlying_type<T>::type;
    return ( ( enumV & flag ) != 0 );
  }

  template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
  void set(T & enumV, T flag)
  {
    using T_t = typename std::underlying_type<T>::type;
    enumV |= flag;
  }

  template<typename T, typename std::enable_if<is_flag<T>::value>::type* = nullptr>
  void unset(T & enumV, T flag)
  {
    using T_t = typename std::underlying_type<T>::type;
    enumV &= (~flag);
  }

#define EnableBitMaskOperators(E_CLASS)  \
template<> struct is_flag<E_CLASS> : std::true_type { };
  
}

#endif // SFEngine_EnumTemplate_H 
