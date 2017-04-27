#ifndef SFEngine_Globals_H
#define SFEngine_Globals_H

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
#include <unordered_set>

/************************************************************************/
/*                            Globals                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

namespace SFEngine
{

#ifndef ____PI
#define ____PI 3.141592653f
#endif

#ifndef SF_TOFLOAT
#define SF_TOFLOAT(X)\
          static_cast<float>(X)
#endif
#define SF_TOINT(X)\
          static_cast<int>(X)

  class BasicLevel;

  extern bool   IsIDUsed(const UINT32 &ID);
  extern void   FreeID(const UINT32 &ID); //Make an ID available for use again
  extern UINT32 GenerateID();
  extern void   SetFramerateLimit(unsigned int Limit);
  extern void   SetVSyncEnabled(bool Enabled);
  extern void   LoadLevel(const SString &jsonPath);
  extern void   SwitchLevel(SharedLevel Level);
  extern void   SwitchLevel_RawPtr(BasicLevel *Level);
  extern void   LoadMainLevel();
  extern void   LoadLevelByName(const SString &Name);
}

#endif // SFEngine_Globals_H
