#ifndef SFENGINE_SCRIPT_COMPONENT_H
#define SFENGINE_SCRIPT_COMPONENT_H

#include <unordered_set>
#include <unordered_map>
#include "ComponentBase.h"
#include "chaiscript/chaiscript.hpp"

namespace Engine
{

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

}

#endif
