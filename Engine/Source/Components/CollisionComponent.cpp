#include "Components/CollisionComponent.h"
#include "ThirdParty/PhysicsEngine.h"


namespace Engine
{
  CollisionComponent::CollisionComponent()
  {
    ComponentName = "CollisionComponent";
  }

  CollisionComponent::~CollisionComponent()
  {
  }

  void CollisionComponent::CreateMesh(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh)
  {
    
  }

  std::shared_ptr<Collider2D> CollisionComponent::GetCollider()
  {
    return
      Enabled ? CollisionMesh : nullptr;
  }

}
