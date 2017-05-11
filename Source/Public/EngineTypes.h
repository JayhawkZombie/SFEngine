#ifndef SFEngine_EngineTypes_H
#define SFEngine_EngineTypes_H

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
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <deque>

/************************************************************************/
/*                        EngineTypes                                   */
/************************************************************************/
/* Typedefs for common/long type names                                  */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/29                                  */
/************************************************************************/

/************************************************************************/
/* Sorry                                                                */
/************************************************************************/
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

/************************************************************************/
/* End horrific pre-defined macro checks                                */
/************************************************************************/

#if defined ( _WIN32 ) || defined ( _WIN64 )
#  define SPLATFORM_WINDOWS
#elif defined ( __APPLE__ )
#  define SPLATFORM_OSX
#elif defined ( __linux )
#  define SPLATFORM_LINUX
#elif defined ( __unix )
#  define SPLATFORM_UNIX
#elif defined ( __ANDROID__ )
#  define SPLATFORM_ANDROID
#elif defined ( __posix )
#  define SPLATFORM_POSIX
#endif

/* Windows platform definitions */
#ifdef SPLATFORM_WINDOWS
#  include "WindowsDefs.h"

/* OSX platform definitions */
#elif  SPLATFORM_OSX
#include "OSXDefs.h"
#endif

#ifdef SPLATFORM_X64
#include "DefsX64.h"
#else
#include "DefsX86.h"
#endif
#endif

/************************************************************************/
/* Forward declarations                                                 */
/************************************************************************/
namespace SFEngine {
  class BasicLevel;
}

/************************************************************************/
/* SFML basic type typedefs                                             */
/************************************************************************/
using SVector2F   = sf::Vector2<SFLOAT>;
using SVector2I   = sf::Vector2i;
using SVector2U   = sf::Vector2u;
using SVector2U32 = sf::Vector2<UINT32>;
using SVector2U64 = sf::Vector2<UINT64>;
using SVector2C   = sf::Vector2<char>;
using SVector3F   = sf::Vector3<SFLOAT>;
using SVector3I   = sf::Vector3i;
using SVector3U   = sf::Vector3<unsigned int>;
using SVector3C   = sf::Vector3<char>;
using SFLOATRECT  = sf::FloatRect;
using SINTRECT    = sf::IntRect;
using SSprite     = sf::Sprite;

/************************************************************************/
/* Standard library typedefs                                            */
/************************************************************************/
using SString = ::std::string;

/* Ptr types */
template<typename T>             using SPtrShared = std::shared_ptr<T>;
template<typename T, typename U> using SPair      = std::pair<T, U>;
template<typename T>             using SPtrWeak   = std::weak_ptr<T>;
template<typename T>             using SPtrUnique = std::unique_ptr<T>;

/* STL types */
template<typename T, typename U> using STDMap          = std::map<T, U>;
template<typename T, typename U> using SharedSTDMap    = SPtrShared<STDMap<T, U>>;
template<typename T>             using STDQueue        = std::queue<T>;
template<typename T, typename U> using STDUnorderedMap = std::unordered_map<T, U>;
template<typename T, typename U> using STDPairQueue    = STDQueue<SPair<T, U>>;
template<typename T, typename U> using SharedSTDUnorderedMap = SPtrShared<STDUnorderedMap<T, U>>;
template<typename T>             using STDVector       = std::vector<T>;
template<typename T>             using STDVector2D     = STDVector<STDVector<T>>;
template<typename T, typename U> using SharedPairQueue = SPtrShared<STDPairQueue<T, U>>;
template<typename T>             using STDDeque        = std::deque<T>;


using SStringPair = SPair<SString, SString>;
using SSize_t     = std::size_t;
using FPtrVoid    = std::function<void(void)>;

/* Threading types */
using SThread = std::thread;
using SMutex  = std::mutex;
using SharedMutex             = SPtrShared<SMutex>;
using SConditionVariable      = std::condition_variable;
using SharedConditionVariable = SPtrShared<SConditionVariable>;
using SPtrSharedMutex         = SPtrShared<std::mutex>;
template<typename T> using SUniqueLock = std::unique_lock<T>;

/* Chrono types */
using SClockHigh = std::chrono::high_resolution_clock;
using SClockSys  = std::chrono::system_clock;
template<typename T, typename U> using STimeDuration = std::chrono::duration<T, U>;

/* Stream types */
using SStream   = ::std::stringstream;
using SOFStream = std::ofstream;
using SIFStream = std::ifstream;
using SOStream  = std::ostream;
using SIStream  = std::istream;

/************************************************************************/
/* SFML Resource type typdefs                                           */
/************************************************************************/

//Shapes
using SRectShape = sf::RectangleShape;
using SCircleShape = sf::CircleShape;

//Textures
using SharedTexture  = SPtrShared<sf::Texture>;
using STexture       = sf::Texture;
using RTexture       = sf::RenderTexture;
using SharedRTexture = SPtrShared<RTexture>;
using RTarget        = sf::RenderTarget;
using SStringTextureMap = STDMap<SString, SharedTexture>;

//Sound & Music
using SMusic      = sf::Music;
using SSound      = sf::Sound;
using SharedMusic = SPtrShared<SMusic>;
using SSoundBuffer          = sf::SoundBuffer;
using SharedSoundBuffer     = SPtrShared<SSoundBuffer>;
using SStringMusicMap       = STDMap<SString, SharedMusic>;
using SStringSoundBufferMap = STDMap<SString, SharedSoundBuffer>;

//Shaders
using SShader          = sf::Shader;
using SharedShader     = SPtrShared<SShader>;
using SStringShaderMap = STDMap<SString, SharedShader>;

//Fonts
using SFont          = sf::Font;
using SharedFont     = SPtrShared<SFont>;
using SStringFontMap = STDMap<SString, SharedFont>;

//Text & Strings
using SText       = sf::Text;
using SharedSText = SPtrShared<SText>;

//Time & Clocks
using STime  = sf::Time;
using SClock = sf::Clock;

/************************************************************************/
/* Engine typedefs                                                      */
/************************************************************************/
using SharedLevel = SPtrShared<SFEngine::BasicLevel>;

#endif // SFEngine_EngineTypes_H
