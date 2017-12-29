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

#include <cstdint>
#include <memory>
#include <mutex>

#include <SFML\Graphics.hpp>


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

using SVector2F   = sf::Vector2<SFLOAT>;
using SVector2I   = sf::Vector2i;
using SVector2U   = sf::Vector2u;
using SVector2U32 = sf::Vector2<UINT32>;
using SVector2U64 = sf::Vector2<UINT64>;
using SVector2C = sf::Vector2<char>;
using SVector3F = sf::Vector3<SFLOAT>;
using SVector3I = sf::Vector3i;
using SVector3U = sf::Vector3<unsigned int>;
using SVector3C = sf::Vector3<char>;

using SharedTexture = std::shared_ptr<sf::Texture>;

template<typename T>
using SPtrShared      = std::shared_ptr<T>;
using SPtrSharedMutex = SPtrShared<std::mutex>;
using STexture        = SPtrShared<sf::Texture>;
using STextureMap     = std::map<std::string, STexture>;

template<typename T>
using SPtrUnique = std::unique_ptr<T>;
using SClockHigh = std::chrono::high_resolution_clock;
using SClockSys  = std::chrono::system_clock;
