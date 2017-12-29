#ifndef SFENGINE_COMPONENT_BASE_H
#define SFENGINE_COMPONENT_BASE_H

#include "../Globals/GlobalHooks.h"

namespace Engine
{
  class ComponentBase
  {
  public:
    ComponentBase();
    virtual ~ComponentBase();

    std::string ComponentName = "ComponentBase";
    std::uint32_t ComponentID;
  };

}

#define ENTITY_COMPONENT_BEGIN(NAME)                             \
class NAME##Component                                            \
: public Engine::ComponentBase                                   \
{                                                                \



#define ENTITY_COMPONENT_END(NAME) \
} NAME;                           


#define ENTITY_PART(TYPE, NAME)                                   \
  public: TYPE var_##NAME;                                        \
          TYPE Get##NAME##() const { return var_##NAME; }         \
          void Set##NAME##(const TYPE &v) { var_##NAME = v; }     \

#define ENTITY_PART_VECTOR(TYPE, NAME)                                          \
  public: std::vector<TYPE> var_##NAME##Vector;                                 \
          auto Get##NAME##s() { return var_##NAME##Vector; }                    \
          void Add##NAME##(const TYPE &t) { var_##NAME##Vector.push_back(t); }  \

#define ENTITY_VECTOR_GETTER(TYPE, NAME)         \
  public: std::vector<TYPE> Get##NAME##s() { return NAME##.Get##NAME##s(); }    \

#endif
