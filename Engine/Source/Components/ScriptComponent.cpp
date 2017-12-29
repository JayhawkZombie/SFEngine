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

#include "Components/ScriptComponent.h"
#include "Globals/GlobalHooks.h"
#include "chaiscript/chaiscript.hpp"
#include "Level/LevelObject.h"

inline std::string arglist(const std::vector<std::string> &args) {
  if (args.size() == 0)
    return "";

  if (args.size() == 1)
    return args[1];

  std::string arg_list = args[0] + ", ";
  auto it = args.begin(); ++it;
  for (it; it != args.end() - 1; ++it) {
    arg_list += (*it) + ", ";
  }
  arg_list += args.back();

  return arg_list;
}

ScriptComponent::ScriptComponent()
  : ComponentBase()
{
  ComponentName = "ScriptComponent";
}

ScriptComponent::~ScriptComponent()
{

}

void ScriptComponent::Execute(const std::string &command, const std::vector<std::string> &args)
{
  try
  {
    auto it = ComponentFunctions.find(command);
    if (it != ComponentFunctions.end()) {
      auto func = (*it).second;

      func(ComponentInstance);
    }
  }
  catch (chaiscript::exception::eval_error & err)
  {
    std::cerr << "Script evaluation error: " << err.what() << std::endl;
  }
}

void ScriptComponent::Create()
{
  ComponentInstance = ScriptEngine->eval<chaiscript::Boxed_Value&>(ComponentClassName + "()");
}

void ScriptComponent::CreateScriptFunction(const std::string &funcName, const std::string &signature)
{
  auto func = ScriptEngine->eval<std::function<void(chaiscript::Boxed_Value&)>>(signature);
  ComponentFunctions[funcName] = func;
}
