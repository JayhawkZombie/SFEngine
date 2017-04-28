#ifndef SFEngine_DefsX64_H
#define SFEngine_DefsX64_H

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <cstdint>

/************************************************************************/
/*                            DefsX64                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

//64-bit definitions
#if defined (INT16_MIN) && defined (INT16_MAX)
#    define SINT_16_MAX INT16_MAX
#    define SINT_16_MIN INT16_MIN
typedef std::int16_t INT16;
typedef std::uint16_t UINT16;
#else
#    define SINT_16_MIN INT32_MIN
#    define SINT_16_MAX INT32_MAX
typedef std::int32_t INT16;
typedef std::uint32_t UINT16;
#endif

typedef std::uint32_t UINT32;
typedef std::uint64_t UINT64;
typedef std::int32_t  INT32;
typedef std::int64_t  INT64;
typedef float         SFLOAT;
typedef double        SDOUBLE;


#endif // SFEngine_DefsX64_H
