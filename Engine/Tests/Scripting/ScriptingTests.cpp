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

#include "ScriptingTests.h"

void RunScriptingTests()
{
  std::cout << "** Scripting Tests\n\n";

  std::string test_script
  (u8R"(
        import core
        
        set player health to 100
        set player stamina to 100
    )");

  auto Runtime = Jinx::CreateRuntime();

  auto Bytecode = Runtime->Compile(test_script.c_str(), "test_script_1");

  /*
   *  Validate size data of compiled Bytecode
   **/
  auto bytecodesize = Bytecode->Size();
  const auto *bytecodedata = Bytecode->Ptr();

  std::cout << "\n------------------------------------\n" <<
               test_script                              << 
               "\n------------------------------------\n";

  std::cout << "Bytecode size: " << bytecodesize << "\n";
  std::cout << "Bytecode data:\n" 
            << "\n------------------------------------\n";

  for (std::size_t i = 0; i < bytecodesize; i++)
  {
    std::cout << bytecodedata[i];
  }

  std::cout << "\n------------------------------------\n";

  /*
   *  Test script execution
   **/

  auto script = Runtime->CreateScript(Bytecode);

  bool success = script->Execute();

  if (!success)
  {
    std::cout << "Script failed\n";
  }
  else
  {
    /*
     *  Get and print the values of the variables
     **/

    auto health = script->GetVariable("player health");
    auto stamina = script->GetVariable("player stamina");

    if (health.IsInteger())
    {
      auto health_val = health.GetInteger();
      std::cout << "Health: " << health_val << "\n";
    }

    if (stamina.IsInteger())
    {
      auto stamina_val = stamina.GetInteger();
      std::cout << "Stamina: " << stamina_val << "\n";
    }

  }

  /*
   *  Test scripting looping
   **/

  {
    std::cout << "** Script Loops + Var Tests\n\n";

    std::string source
    (
      u8R"(import core
           set testval to 0           

           loop x from 1 to 7
             increment testval by 1
             wait
           end
          )"
    );

    auto bcode = Runtime->Compile(source.c_str(), "loop_test");

    auto bsize = bcode->Size();
    const auto *bptr = bcode->Ptr();
    
    std::cout << "Bytecode Size: " << bsize << "\n";
    std::cout << "Bytecode Data:\n"
              << "\n------------------------------------\n";
    for (std::size_t i = 0; i < bsize; ++i)
    {
      std::cout << bptr[i];
    }

    std::cout << "\n------------------------------------\n";

    auto loop_script = Runtime->CreateScript(bcode);

    Jinx::Variant loop_var;
    std::size_t count = 1;

    do 
    {

      if (!loop_script->Execute())
      {
        std::cout << "Script error\n";
        break;
      }

      loop_var = loop_script->GetVariable("testval");

      if (loop_var.IsInteger())
      {
        auto loop_val = loop_var.GetInteger();

        std::cout << "[" << count++ << "]: testval = " << loop_val << "\n";
      }

    } while (!loop_script->IsFinished());

  } // end of loop script tests

}
