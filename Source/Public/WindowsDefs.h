#ifndef SFEngine_WindowsDefs_H
#define SFEngine_WindowsDefs_H

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

/************************************************************************/
/*                        WindowsDefs                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

#ifdef SPLATFORM_WINDOWS

#ifndef  __SPLATFORM_WINDOWS_H
#define  __SPLATFORM_WINDOWS_H

#    if defined ( _M_x64 ) || defined ( _M_ARM64 ) || defined ( _WIN64 )
#         define SARCH_X64
#    elif defined ( _X_Ix86 ) || defined ( _WIN32 )
#         define SARCH_X86
#    endif

#    include <windows.h>
#      if REG_DWORD == REG_DWORD_LITTLE_ENDIAN
#           define SARCH_LITTLE_ENDIAN
#           define LE_TO_HOST_ULONG(ULONGVAL) ULONGVAL
#           define BE_TO_HOST_ULONG(ULONGVAL) _byteswap_ulong(ULONGVAL)
#           define LE_TO_HOST_USHORT(USHORTVAL) USHORTVAL
#           define BE_TO_HOST_USHORT(USHORTVAL) _byteswap_ushort(USHORTVAL)
#           define LE_TO_HOST_UINT64(UINT64VAL) UINT64VAL
#           define BE_TO_HOST_UINT64(UINT64VAL) _byteswap_uint64(UINT64VAL)
#      elif REG_DWORD = REG_DWORD_BIG_ENDIAN
#           define SARCH_BIG_ENDIAN
#           define LE_TO_HOST_ULONG(ULONGVAL) _byteswap_ulong(ULONGVAL)
#           define BE_TO_HOST_ULONG(ULONGVAL) ULONGVAL
#           define LE_TO_HOST_USHORT(USHORTVAL) _byteswap_ushort(USHORTVAL)
#           define BE_TO_HOST_USHORT(USHORTVAL) USHORTVAL
#           define LE_TO_HOST_UINT64(UINT64VAL) _byteswap_uint64(UINT64VAL)
#           define BE_TO_HOST_UINT64(UINT64VAL) UINT64VAL
#      endif

#      if defined( _M_X64 ) || defined ( _M_ARM64 ) || defined ( _WIN64 )
#           define SPLATFORM_X64
#      elif defined ( _M_IX86 ) || defined ( _WIN32 )
#           define SPLATFORM_X86
#endif


#endif // __SPLATFORM_WINDOWS_H
#endif //SPLATFORM_WINDOWS

#ifdef _WINUSER_
#undef _WINUSER_
#endif // ifdef _WINUSER_

#endif // SFEngine_WindowsDefs_H
