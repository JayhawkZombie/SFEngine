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

#include "Engine\Engine.h"

namespace Engine
{
  /*
    Syntax:

    cmd_string :: comm | null
    comm       :: tag " " comm | immed_comm
    tag        :: <string>
    comm       :: func_call | assignment
    immed_comm :: Quit | Exit | SimCrash

    commands:
      Core:
        "Core Quit" - Quit, normal shutdown
        "Core Shutdown" - Shutdown, do not notify other modules
        "Core Abort" - Crash
        "Core Clean" - Clean up, not implemented yet

      Render:
        "Render EnableVSync" - enable VSync
        "Render DisableVSyns" - disable VSync
        "Render EnableShaders" - enable shader
        "Render DisableShaders" - disable shader
  */
  //void SFEngine::CommandProcessor(const std::string &command)
  //{
  //  //first see if there was a tag
  //  std::cerr << "Command received: " << command << std::endl;
  //  try
  //  {
  //    ScriptEngine->eval(command);
  //  }
  //  catch (chaiscript::exception::eval_error &err)
  //  {    
  //    EngineScriptConsole->IssueResponse("Eval error : " + std::string(err.what()));
  //  }
  //}

  //void SFEngine::ProcessRenderCommand(const std::string & command)
  //{
  //}

  //void SFEngine::ProcessImmediateCommand(const std::string & command)
  //{
  //}

  //void SFEngine::ProcessEventCommand(const std::string & command)
  //{
  //}

}
