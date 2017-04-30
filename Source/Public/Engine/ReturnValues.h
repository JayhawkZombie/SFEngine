#ifndef SFEngine_ReturnValues_H
#define SFEngine_ReturnValues_H

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
/*                        ReturnValues                                  */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{
  enum Error
  {
    INIT_NO_SFML = 1
    , INIT_CONTEXT_CREATION
    , GL_CORE_MAJOR
    , GL_CORE_MINOR
    , GL_NO_SHADERS
    , GL_BAD_EXTENSION
    , GL_SHADER_COMPILE
    , GL_INVALID_CONTEXT
    , THREAD_WORKER
    , THREAD_WORKER_UNRESPONSIVE
    , THREAD_WORKER_STARVED
    , THREAD_LOGGER
    , THREAD_LOGGER_UNRESPONSIVE
    , THREAD_LOGGER_STARVED
    , THREAD_RENDERER
    , THREAD_RENDERER_UNRESPONSIVE
    , THREAD_RENDERER_STARVED
    , RUNTIME_NULLPTR
    , RUNTIME_ENGINE_NOCURRENGINE
    , RUNTIME_ENGINE_NOCURRWINDOW
    , RUNTIME_MEMORY_ALLOC
    , RUNTIME_UNKNOWN_ERROR
    , NO_STARTING_LEVEL
  };

  enum Warning
  {
    GL_NO_AA = Error::RUNTIME_UNKNOWN_ERROR + 1
    ,
  };

  enum Success
  {
    GAMELOOP_SUCCESS = 0
    , INIT_SUCCESS
    , STARTUP_SUCCESS
    , RENDER_SUCCESS

    ,
  };
}

#endif // SFEngine_ReturnValues_H 
