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

#ifdef WITH_EDITOR

/* If we're in an editor, include a few extra things necessary */

#else



#endif

/* Core forward declarations */
#include "CoreForward.h"

/* We can include SFML's headers */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

/* And a FEW basic C++ headers */

/* Basic integer types */
#include <cstdint>

/* Strings */
#include <string>

/* shared_ptr */
#include <memory>

/* Necessary STL structures */
#include <vector>

/* Function ptrs */
#include <functional>

const auto Lambda_VoidNoParams    = []()                          constexpr { return; };
const auto Lambda_VoidOneParam    = [](auto _1)                   constexpr { return; };
const auto Lambda_VoidTwoParams   = [](auto _1, auto _2)          constexpr { return; };
const auto Lambda_VoidThreeParams = [](auto _1, auto _2, auto _3) constexpr { return; };