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

#include "Engine/stdafx.h"

#include "Engine\Engine.h"
#include "Exceptions\Exceptions.h"
#include "Engine/ReturnValues.h"

#include <boost/stacktrace.hpp>

void TerminateHandler()
{
  boost::stacktrace::safe_dump_to("crash_trace.dump");
}

uint32_t SFEngine::Go(int argc, char **argv)
{
  CurrentEngine = this;
  std::set_terminate(TerminateHandler);

  UINT32 result = 0;
  try
  {
    result = Init(argc, argv);
    return result;
  }
  catch (EngineRuntimeError &err)
  {
    std::cerr << "There was a critical error, and it could not be recovered from\n";
    std::string err_string = err.UnwindTrace();

    std::cerr << "The following stack trace was provided: \n\n" << err_string << std::endl;
    return Error::RUNTIME_UNKNOWN_ERROR;
  }
}
