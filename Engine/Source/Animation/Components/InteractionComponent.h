#ifndef SFENGINE_INTERACTION_COMPONENT_H
#define SFENGINE_INTERACTION_COMPONENT_H

#include "CollisionComponent.h"

namespace Engine
{

  class LevelObject;

  class InteractionComponent : protected ComponentBase
  {
  public:
    InteractionComponent();
    ~InteractionComponent();

  };

}

#endif
