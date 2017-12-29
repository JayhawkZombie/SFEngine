#include "Components/ScriptComponent.h"
#include "Globals/GlobalHooks.h"
#include "chaiscript/chaiscript.hpp"
#include "Level/LevelObject.h"

namespace Engine
{

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

}
