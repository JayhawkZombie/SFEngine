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

#include "Physics/Collider.h"
#include "Objects/GameObject.h"
#include "Physics/Occluder.h"

#include "PhysicsEngine.h"

/*
  Collider2D
*/

Collider2D::Collider2D()
  : m_MyObject(nullptr)
{
  m_Status.set(ColliderProp::HasPhysicalResponse);
  m_Status.set(ColliderProp::Enabled);
  m_Status.set(ColliderProp::NotifyEveryFrame);
  m_Status.set(ColliderProp::Active);
  m_Status.reset(ColliderProp::Sleeping);
  m_Status.reset(ColliderProp::CastShadows);
}

Collider2D::~Collider2D()
{
  m_Mesh.reset();
}

std::shared_ptr<Collider2D> Collider2D::Clone()
{
  auto Cloned = std::make_shared<Collider2D>();
  Cloned->m_Status = m_Status;
  if (m_Mesh) {
    Cloned->m_Mesh = std::shared_ptr<PhysicsEngineBaseMeshType>(m_Mesh->clone());
  }
  Cloned->m_CollisionCallback           = m_CollisionCallback;
  Cloned->m_AwakenCallback              = m_AwakenCallback;
  Cloned->m_NotifyOfCollisionEveryFrame = m_NotifyOfCollisionEveryFrame;
  Cloned->m_OverlapCallback             = m_OverlapCallback;
  Cloned->m_PositionChangeCallback      = m_PositionChangeCallback;
  Cloned->m_SleepCallback               = m_SleepCallback;
  Cloned->m_Status                      = m_Status;

  return Cloned;
}

void Collider2D::SetMesh(std::shared_ptr<PhysicsEngineBaseMeshType> MeshPtr)
{
  m_Mesh = MeshPtr;
}

sf::FloatRect Collider2D::GetGlobalBounds() const
{
  return sf::FloatRect(
    m_Mesh->pos.x, m_Mesh->pos.y,
    m_Mesh->siz.x, m_Mesh->siz.y
  );
}

std::shared_ptr<Collider2D> Collider2D::CreateCircularMesh
(
  MeshType type, 
  const sf::Vector2f & position, 
  const sf::Vector2f & velocity, 
  unsigned int radius, 
  float mass, 
  float coeffOfRest, 
  sf::Color color
)
{
  char bType;
  switch (type)
  {
    case MeshType::Ball:
      bType = 'B'; break;
    case MeshType::BallGo:
      bType = 'G'; break;
    default:
      bType = 'B'; break;
  }

  std::shared_ptr<PhysicsEngineBaseMeshType> Mesh 
    = BuildBallMesh(bType, position, velocity, radius, mass, coeffOfRest, color);

  std::shared_ptr<Collider2D> Collider = std::make_shared<Collider2D>();
  Collider->m_Mesh = Mesh;

  return Collider;
}

std::shared_ptr<Collider2D> Collider2D::CreatePolygonMesh
(
  unsigned int num_sides, 
  float radius, 
  float init_rotation, 
  const sf::Vector2f & InitialPosition, 
  const sf::Vector2f & InitialVelocity, 
  float mass, 
  float CoeffOfRest, 
  sf::Color color,
  bool CastShadows
)
{
  std::shared_ptr<PhysicsEngineBaseMeshType> Mesh
    = BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, color);

  std::shared_ptr<Collider2D> Collider = std::make_shared<Collider2D>();
  Collider->m_Mesh = Mesh;
  if (CastShadows)
    Collider->m_Status.set(ColliderProp::CastShadows);
  return Collider;
}

std::shared_ptr<Collider2D> Collider2D::CreateBlockMesh
(
  float Width, 
  float Height, 
  float IAngle, 
  const sf::Vector2f & Position, 
  const sf::Vector2f & Velocity, 
  float Mass, float CoeffOfRest, 
  sf::Color Color
)
{
  std::shared_ptr<PhysicsEngineBaseMeshType> Mesh = BuildBlockMesh(Width, Height, IAngle, Position, Velocity, Mass, CoeffOfRest, Color);
  std::shared_ptr<Collider2D> Collider = std::make_shared<Collider2D>();
  Collider->m_Mesh = Mesh;
  return Collider;
}

std::shared_ptr<Collider2D> Collider2D::CreateExpandingMesh
(
  unsigned int numSides, 
  float radiusWhenFull, 
  float IAngle, 
  const sf::Vector2f & InitialPosition,
  const sf::Vector2f & InitialVelocity,
  float Mass, 
  float CoeffOfRest, 
  float GrowSpeed,
  sf::Color Color
)
{
  std::shared_ptr<PhysicsEngineBaseMeshType> Polygon = BuildExpandPolygonMesh(numSides, radiusWhenFull, IAngle, InitialPosition, InitialVelocity, Mass, CoeffOfRest, GrowSpeed, Color);
  std::shared_ptr<Collider2D> Collider = std::make_shared<Collider2D>();
  Collider->m_Mesh = Polygon;
  return Collider;
}

void Collider2D::SetCollisionCallback(std::function<void(LevelObject*)> Callback, bool NotifyEveryFrame)
{
  m_NotifyOfCollisionEveryFrame = NotifyEveryFrame;
  m_Status |= (m_NotifyOfCollisionEveryFrame ?
                ColliderProp::NotifyEveryFrame :
                ColliderProp::SingleResponsePerObj
                );
  m_CollisionCallback = Callback;
}

void Collider2D::SetSegmentCallback(std::function<void(PhysicsEngineSegmentType *)> Callback)
{
  m_HitSegmentCallback = Callback;
}

void Collider2D::SetPositionChangeCallback(std::function<void(sf::Vector2f delta)> Callback)
{
  m_PositionChangeCallback = Callback;
}

void Collider2D::SetSleepCallback(std::function<void(void)> Callback)
{
  m_SleepCallback = Callback;
}

void Collider2D::SetAwakenCallback(std::function<void(void)> Callback)
{
  m_AwakenCallback = Callback;
}

void Collider2D::SetOverlapCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback)
{
  m_OverlapCallback = Callback;
}

void Collider2D::SetTouchCallback(std::function<void(LevelObject*)> Callback)
{
  m_TouchCallback = Callback;
}

void Collider2D::SetColliderStatus(ColliderProp Status)
{
  m_Status = Status;
}

void Collider2D::Update(const::vec2d & gravity)
{
  if (m_Mesh)
    m_Mesh->update(gravity);
}

void Collider2D::Sleep()
{
  m_Status.set(ColliderProp::Sleeping);
}

void Collider2D::Awaken()
{
  m_Status.set(ColliderProp::Active);
  m_Status.reset(ColliderProp::Sleeping);
}

void Collider2D::EnableCollisions()
{
  m_Status.set(ColliderProp::Enabled);
}

void Collider2D::DisableCollision()
{
  m_Status.reset(ColliderProp::Enabled);
}

void Collider2D::Makestatic()
{
  m_Status.set(ColliderProp::Static);
}

void Collider2D::MakeNonstatic()
{
  m_Status.reset(ColliderProp::Static);
}

bool Collider2D::IsAwake() const
{
  return !m_Status.test(ColliderProp::Sleeping);
}

bool Collider2D::IsEnabled() const
{
  return m_Status.test(ColliderProp::Enabled);
}

bool Collider2D::HasPhyicalResponse() const
{
  return m_Status.test(ColliderProp::HasPhysicalResponse);
}

bool Collider2D::NotifyOnTouch() const
{
  return m_Status.test(ColliderProp::NotifyOnTouch);
}

bool Collider2D::IsActive() const
{
  return m_Status.test(ColliderProp::Active);
}

bool Collider2D::DoesCastShadows() const
{
  return m_Status.test(ColliderProp::CastShadows);
}

bool Collider2D::IsStatic() const
{
  return m_Status.test(ColliderProp::Static);
}

void Collider2D::Move(const sf::Vector2f & Delta)
{
  if (m_Mesh) {
    m_Mesh->pos += ::vec2d(Delta.x, Delta.y);
  }
}

void Collider2D::SetPosition(const sf::Vector2f & Position)
{
  if (m_Mesh) {
    m_Mesh->pos = { Position.x, Position.y };
  }
}

void Collider2D::SetRespondsToOverlaps(bool b)
{
  if (b) {
    m_Status.set(ColliderProp::NotifyOfOverlap);
    m_Status.reset(ColliderProp::HasPhysicalResponse);
  }
  else {
    m_Status.set(ColliderProp::HasPhysicalResponse);
    m_Status.reset(ColliderProp::NotifyOfOverlap);
  }
}

void Collider2D::SetNotifyOnTouch(bool b)
{
  if (b) {
    m_Status.set(ColliderProp::NotifyOnTouch);
    m_Status.reset(ColliderProp::HasPhysicalResponse);
  }
  else {
    m_Status.set(ColliderProp::HasPhysicalResponse);
    m_Status.reset(ColliderProp::NotifyOnTouch);
  }
}

sf::Vector2f Collider2D::GetPosition() const
{
  if (m_Mesh) {
    return sf::Vector2f(
      m_Mesh->pos.x, m_Mesh->pos.y
    );
  }
  else
    return sf::Vector2f(0, 0);
}

bool Collider2D::HandleCollision(std::weak_ptr<Collider2D> Collider)
{
  if (m_Status.test(ColliderProp::Active) && m_Status.test(ColliderProp::Enabled)) {
    /*if (m_MyObject) {
      m_MyObject->HandleCollisionWithCollider(Collider.lock());
      m_MyObject->HandleCollisionWithObject(Collider.lock()->m_MyObject);
    }*/
    if (m_CollisionCallback) {
      m_CollisionCallback(Collider.lock()->m_MyObject);
    }
        
  }

  return m_Status.test(ColliderProp::HasPhysicalResponse);
}

bool Collider2D::HandleCollision(std::weak_ptr<Occluder2D> Occluder)
{
  return false;
}

bool Collider2D::HandleCollisionWithSegment(PhysicsEngineSegmentType *Collider)
{
  if (m_Status.test(ColliderProp::Active) && m_Status.test(ColliderProp::Enabled)) {
    /*if (m_MyObject)
      m_MyObject->HandleCollisionWithSegment(Collider);*/
    if (m_HitSegmentCallback)
      m_HitSegmentCallback(Collider);
  }

  return m_Status.test(ColliderProp::HasPhysicalResponse);
}

bool Collider2D::HandleTouch(std::weak_ptr<Collider2D> Collider)
{
  if (m_Status.test(ColliderProp::Active) && m_Status.test(ColliderProp::Enabled)) {
    if (m_TouchCallback)
      m_TouchCallback(Collider.lock()->GetObjectPtr());
  }

  return m_Status.test(ColliderProp::NotifyOnTouch);
}

std::vector<::vec2d> Collider2D::GetVertices()
{
  if (m_Mesh)
    return m_Mesh->get_verts();

  return { };
}

std::weak_ptr<PhysicsEngineBaseMeshType> Collider2D::GetMesh()
{
  return m_Mesh;
}

void Collider2D::SetObjectPtr(LevelObject * Object)
{
  m_MyObject = Object;
}

LevelObject * Collider2D::GetObjectPtr() const
{
  return m_MyObject;
}

void Collider2D::PhysicsUpdate()
{
}
