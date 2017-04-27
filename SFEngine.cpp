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
#include "Engine\Engine.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                      Engine main entry point                         */
/************************************************************************/
/* Main entry point for the application                                 */
/************************************************************************/

#pragma warning( disable : 4503 ) //Disable "decorated name length exceeded, name was truncated"
#pragma warning( disable : 4996 ) //Disable "strcpy may be unsafe"

//If doing engine tests, let Catch provide its own main and run the unit tests
//otherwise run the engine like normal
#if ENGINE_TESTS
#include "CoreTests\CoreTests.h"
#else

#ifdef _STDC_
#  error Compilation must be done as C++, not C.
#endif

//Compiler checks
#if !defined(__cplusplus)
#error A C++ Compiler must be used. Please compile using a C++14 compliant compiler
#else
#  ifdef __STDC_HOSTED__
#    if ( __STDC_HOSTED__ == 0 )
#      error C++ compiler must support entire required standard library
#    endif
#  endif
#  if (__cplusplus < 201103L)
/* Testing for Visual Studio */
#    ifdef _MSC_EXTENSIONS 
#      ifdef _MSVC_LANG
#        if _MSVC_LANG < 201402
#          error A C++14 Compliant compiler must be used
#        endif
#      else
#        ifdef _MSC_FULL_VER
#          if _MSC_FULL_VER < 12 // If version of visual studio is too old
#            #error Visual Studio 15 or newer must be used
#        endif
#      endif //_MSC_FULL_VER
#    endif //_MSVC_LANG
#    ifndef __STDCPP_THREADS__ 
#      error __STDCPP_THREADS__ must be defined - the Engine must be able to run with more than one thread of execution
#    endif // __STDCPP_THREADS__
#    ifdef _MANAGED 
#      error do not compile with /clr
#    endif // _MANAGED
#    ifndef _CPPUNWIND
#      error Enable /GX or /EH for proper exception handling model
#    endif // _CPPUNWIND
#    ifdef _DLL
#      error Engine must not be compiled as a DLL
#    endif // _DLL
#    ifdef _WINRT_DLL
#      error Must not be compiled as DLL
#    endif
#    ifndef _CPPRTTI
#      error Compile with _CPPRTTI (/GR) to allow run-time type information 
#    endif // _CPPRTTI, for "CPP Run Time Type Information"
#    ifndef _ARM 
#      ifndef _ISO_VOLATILE  
#        error Strict volatile semantics MUST be enforced
#      endif
#    endif // _ARM 
#   ifdef _DEBUG 
#     ifndef _MT
#       error Multithreaded Debug (/MTd) must be set
#     endif
#   endif // _DEBUG
/* Test for GCC */
#    elif defined ( __GNUG__ )
#      ifdef __OBJC__
#        error Objective-C compiler must not be used
#      endif
#      ifdef __NO_INLINE__
#        error Compiler must allow code inlining
#      endif
#      if ( __cplusplus < 201402L )
#        error A C++14 Compliant compiler must be used
#      endif
#      ifndef __GXX_RTTI
#        error Define __GXX_RTTI to allow run-time type information
#      endif
#      ifndef __EXCEPTIONS
#        error Exceptions must be enabled
#      endif
#    endif // _MSC_EXTENSIONS


#  endif // __cplusplus < 201103L
#endif

#ifndef SFML_STATIC
#  error SFML_STATIC must be defined
#endif

int main(int argc, char **argv)
{
  return SFEngine::Engine::Go(argc, argv);
}
#endif
