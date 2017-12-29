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

#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <string>
#include <chrono>
#include <random>
#include <cassert>
#include <unordered_map>
#include <bitset>


#include "Globals\GlobalHooks.h"
#include "EngineTypes.h"
#include "Utils\ReadIni.h"
#include "Utils\Convert.h"
#include "Utils\Encoders.h"
#include "Utils\Decoders.h"
#include "Utils\Vec.hpp"
#include "Utils\ListTemplates.h"
#include "Render\Render.h"
#include "Threading\ASyncLoader.h"
#include "Exceptions\Exceptions.h"

#include "Engine\ThirdParty\json\json.h"
#include "Engine\Source\Serialization\Serialization.h"

#include <SFML/OpenGL.hpp>


#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>

#ifdef _MSC_EXTENSIONS
#define SFENGINE_INTERNAL_DEPRECATED __declspec(deprecated)
#define SFENGINE_DEPRECATED __declspec(deprecated)
#define SFENGINE_INLINE __inline
#define SFENGINE_FORCEINLINE __forceinline

#define ASM __asm
#define ABSTRACT abstract

#else


#define SFENGINE_INTERNAL_DEPRECATED [[deprecated]]
#define SFENGINE_DEPRECATED [[deprecated]]
#define SFENGINE_INLINE inline
#define SFENGINE_FORCEINLINE inline

typedef asm __asm
#define abstract 


#endif
