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

#include <unordered_set>
#include <unordered_map>
#include "ComponentBase.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"

typedef std::function<void(chaiscript::Boxed_Value&)> ScriptFunc;
class LevelObject;

class ScriptComponent : protected ComponentBase
{
public:
  ScriptComponent();
  ~ScriptComponent();

  void Execute(const std::string &command, const std::vector<std::string> &args);
  void Create();
  void CreateScriptFunction(const std::string &funcName, const std::string &signature);
protected:
  chaiscript::Boxed_Value ComponentInstance;
  std::string ComponentClassName;

  //Map the method name to a set containing the types of the arguments to be provided
  //  Empty set -> no arguments
  std::unordered_map<std::string, ScriptFunc> ComponentFunctions;
};