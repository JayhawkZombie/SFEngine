#ifndef SFEngine_ActorEnums_H
#define SFEngine_ActorEnums_H

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
#include "Enums\EnumTemplate.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        ActorEnums                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: (Name) - 2017/05/02                                           */
/************************************************************************/

namespace SFEngine
{

  enum class Illumination : UINT32
  {
    DefaultLit = 0b0000000000000000000000000000000000000001,
    Unlit      = 0b0000000000000000000000000000000000000010,
    Specular   = 0b0000000000000000000000000000000000000100,
    Normals    = 0b0000000000000000000000000000000000001000,
    Shadowed   = 0b0000000000000000000000000000000000010000
  };
  EnableBitMaskOperators(Illumination)

  enum class Interaction : UINT32
  {
    None      = 0b0000000000000000000000000000000000000001,
    Physical  = 0b0000000000000000000000000000000000000010,
    Reactive  = 0b0000000000000000000000000000000000000100,
    Detective = 0b0000000000000000000000000000000000001000
  };
  EnableBitMaskOperators(Interaction)
}

#endif // SFEngine_ActorEnums_H 
