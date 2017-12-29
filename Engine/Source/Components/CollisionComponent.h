#ifndef SFENGINE_COLLISION_COMPONENT_H
#define SFENGINE_COLLISION_COMPONENT_H

#include "ComponentBase.h"
#include "ThirdParty/PhysicsEngine.h"

class mvHit;

namespace Engine
{

  class Collider2D;

  class CollisionComponent : protected ComponentBase
  {
  public:
    CollisionComponent();
    ~CollisionComponent();

    void CreateMesh(std::shared_ptr<::mvHit> Mesh);
    std::shared_ptr<Collider2D> GetCollider();

  protected:
    std::shared_ptr<Collider2D> CollisionMesh;
    bool Enabled = true;
  };

}

#endif
