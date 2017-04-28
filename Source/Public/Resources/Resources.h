#ifndef SFEngine_Resources_H
#define SFEngine_Resources_H

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
#include "BasicIncludes.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                          Resources                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{
  /************************************************************************/
  /* Texture loading methods                                              */
  /************************************************************************/
  SharedTexture LoadTexture(const SString &path, const SString &ID);
  bool ReleaseTexture(const SString &ID);
  SFENGINE_DEPRECATED void ForceClearTextures();
  void ClearTextures();

  SharedFont LoadFont(const SString &path, const SString &ID);
  bool ReleaseFont(const SString &path);
  SFENGINE_DEPRECATED void ForceClearFonts();
  void ClearFonts();

  SharedShader LoadShader(const SString &path, const SString &ID);
  bool ReleaseShader(const SString &path);
  SFENGINE_DEPRECATED void ForceClearShaders();
  void ClearShaders();

  SharedSoundBuffer LoadSoundBuffer(const SString &path, const SString &ID);
  bool ReleaseSoundBuffer(const SString &path);
  SFENGINE_DEPRECATED void ForceClearSoundBuffers();
  void ClearSoundBuffers();

  void StreamMusic(const SString &path);
  void PauseMusic(const SString &path);
  void PlayMusic(const SString &path);

}

#endif // SFEngine_Resources_H
