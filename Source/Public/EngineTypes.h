#ifndef SFEngine_EngineTypes_H
#define SFEngine_EngineTypes_H

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

/************************************************************************/
/*                        EngineTypes                                   */
/************************************************************************/
/* Typedefs for common/long type names                                  */
/*                                                                      */
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
template<typename T>             using SPtrShared = std::shared_ptr<T>;
template<typename T, typename U> using SPair      = std::pair<T, U>;

using SStringPair = SPair<SString, SString>;
using SStream     = ::std::stringstream;
using SSize_t     = std::size_t;
using SThread     = std::thread;
using SMutex      = std::mutex;
using FPtrVoid    = std::function<void(void)>;
using SharedMutex = SPtrShared<SMutex>;
using SConditionVariable      = std::condition_variable;
using SharedConditionVariable = SPtrShared<SConditionVariable>;
template<typename T>
using SPtrWeak        = std::weak_ptr<T>;
using SPtrSharedMutex = SPtrShared<std::mutex>;
template<typename T>
using SPtrUnique = std::unique_ptr<T>;
using SClockHigh = std::chrono::high_resolution_clock;
using SClockSys  = std::chrono::system_clock;
template<typename T, typename U>
using STimeDuration = std::chrono::duration<T, U>;
template<typename T>
using STDVector = std::vector<T>;
using SOFStream = std::ofstream;
using SIFStream = std::ifstream;
using SOStream = std::ostream;
using SIStream = std::istream;

template<typename T, typename U>
using STDMap = std::map<T, U>;
template<typename T, typename U>
using SharedSTDMap = SPtrShared<STDMap<T, U>>;
template<typename T>
using STDQueue = std::queue<T>;
template<typename T, typename U>
using STDUnorderedMap = std::unordered_map<T, U>;
template<typename T, typename U>
using STDPairQueue = STDQueue<SPair<T, U>>;
template<typename T, typename U>
using SharedSTDUnorderedMap = SPtrShared<STDUnorderedMap<T, U>>;

template<typename T, typename U>
using SharedPairQueue = SPtrShared<STDPairQueue<T, U>>;

template<typename T>
using SUniqueLock = std::unique_lock<T>;

/************************************************************************/
/* SFML Resource type typdefs                                           */
/************************************************************************/

//Shapes
using SRectShape = sf::RectangleShape;
using SCircleShape = sf::CircleShape;

//Textures
using SharedTexture = std::shared_ptr<sf::Texture>;
using STexture = sf::Texture;
using RTexture = sf::RenderTexture;
using SharedRTexture = SPtrShared<RTexture>;
using RTarget = sf::RenderTarget;
using SStringTextureMap = std::map<SString, SharedTexture>;

//Sound & Music
using SMusic = sf::Music;
using SSound = sf::Sound;
using SharedMusic = SPtrShared<SMusic>;
using SSoundBuffer = sf::SoundBuffer;
using SharedSoundBuffer = SPtrShared<SSoundBuffer>;
using SStringMusicMap = std::map<SString, SharedMusic>;
using SStringSoundBufferMap = std::map<SString, SharedSoundBuffer>;

//Shaders
using SShader = sf::Shader;
using SharedShader = SPtrShared<SShader>;
using SStringShaderMap = std::map<SString, SharedShader>;

//Fonts
using SFont = sf::Font;
using SharedFont = SPtrShared<SFont>;
using SStringFontMap = std::map<SString, SharedFont>;

//Text & Strings
using SText = sf::Text;
using SharedSText = SPtrShared<SText>;

//Time & Clocks
using STime = sf::Time;
using SClock = sf::Clock;



/************************************************************************/
/* Engine typedefs                                                      */
/************************************************************************/
using SharedLevel = SPtrShared<SFEngine::BasicLevel>;

#endif // SFEngine_EngineTypes_H
