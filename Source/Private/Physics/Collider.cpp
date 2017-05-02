////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "Physics\Collider.h"
#include "Exceptions\Exceptions.hpp"
#include "Objects\GameObject.h"
#include "Physics\ColliderPartitioner.h"
#include "Globals.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <Plinth\all.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                              Collider                                */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/29                                  */
/************************************************************************/

namespace SFEngine
{

  UINT32 Collider2D::DefaultState = 
    ( Collider2D::Active 
    | Collider2D::Enabled 
    | Collider2D::HasPhysicalResponse 
    | Collider2D::NotifyOnTouch );

  /************************************************************************/
  /* Setters                                                              */
  /************************************************************************/

  SharedCollider2D Collider2D::Create(GameObject* Owner, UINT32 State)
  {
    try
    {
      SharedCollider2D Collider = std::make_shared<Collider2D>();
      Collider->m_Status = State;
      Collider->m_OwnerObject = Owner;
      return Collider;
    }
    catch (std::runtime_error& e)
    {
      std::string Message = "Failed to create Collider2D: " + std::string(e.what());
      ERR << EXCEPTION_MESSAGE(Message);
      throw;
    }
  }

  SharedCollider2D Collider2D::Clone()
  {
    SharedCollider2D Copy = std::make_shared<Collider2D>(m_Status);
    if (m_Mesh) {
      Copy->m_Mesh = std::shared_ptr<MeshBase>(m_Mesh->clone());
    }
    Copy->m_ColliderCollisionCallback = m_ColliderCollisionCallback;
    Copy->m_PrevColliderPos = m_PrevColliderPos;
    Copy->m_PrevVelocity = m_PrevVelocity;
    Copy->m_OwnerObject = m_OwnerObject;
    Copy->m_SegmentCollisionCallback = m_SegmentCollisionCallback;
    Copy->m_Type = m_Type;

    return Copy;
  }

  Collider2D::~Collider2D()
  {
    m_Mesh.reset();
  }

  void Collider2D::SetMesh(MeshBasePtr Mesh)
  {
    m_Mesh = Mesh;
    m_PrevColliderPos = m_Mesh->pos;
    m_PrevVelocity = m_Mesh->v;
  }

  void Collider2D::SetProperty(UINT32 Property)
  {
    if (Property <= Static) {
      m_Status |= Property;
    }
  }

  void Collider2D::SetCollisionCallback(std::function<void(GameObject*)> Callback)
  {
    SFENGINE_ASSERT(Callback);
    m_ColliderCollisionCallback = Callback;
  }

  void Collider2D::SetSegmentCollisionCallback(std::function<void(SegmentMesh*)> Callback)
  {
    SFENGINE_ASSERT(Callback);
    m_SegmentCollisionCallback = Callback;
  }

  void Collider2D::SetOwnerPartitioner(ColliderPartitioner * Partitioner)
  {
    m_OwnerPartitioner = Partitioner;
  }

  /************************************************************************/
  /* Getters                                                              */
  /************************************************************************/

  SPtrWeak<MeshBase> Collider2D::GetMesh() const
  {
    return m_Mesh;
  }

  bool Collider2D::IsActive() const
  {
    return ((m_Status & Collider2D::Active) != 0);
  }

  bool Collider2D::IsAwake() const
  {
    return (((m_Status & Collider2D::Active) != 0) && ((m_Status & Collider2D::Sleeping) == 0));
  }

  bool Collider2D::IsRespondingToCollisions() const
  {
    return ((m_Status & Collider2D::HasPhysicalResponse) != 0);
  }

  bool Collider2D::DoesCastShadows() const
  {
    return ((m_Status & Collider2D::CastShadows) != 0);
  }

  bool Collider2D::IsEnabled() const
  {
    return ((m_Status & Collider2D::Enabled) != 0);
  }

  bool Collider2D::IsStatic() const
  {
    return ((m_Status & Collider2D::Static) != 0);
  }
  bool Collider2D::GetProperty(UINT32 Property) const
  {
    if (Property <= Static)
      return ((m_Status & Property) != 0);
    
    return false;
  }

  GameObject* Collider2D::GetOwningObject() const
  {
    return m_OwnerObject;
  }

  SFLOATRECT Collider2D::GetGlobalBounds() const
  {
    if (!m_Mesh)
      return SFLOATRECT(0, 0, 0, 0);

    auto pos = m_Mesh->pos;
    auto size = m_Mesh->siz;

    return SFLOATRECT(pos.x, pos.y, size.x, size.y);
  }

  ColliderPartitioner * Collider2D::GetOwnerPartitioner() const
  {
    return m_OwnerPartitioner;
  }

  /************************************************************************/
  /* Private constructor                                                  */
  /************************************************************************/
  Collider2D::Collider2D(UINT32 State)
  {
    m_Status = State;
  }

  /************************************************************************/
  /* Property manipulators                                                */
  /************************************************************************/
  void Collider2D::Sleep()
  {
    m_Status |= Sleeping;
  }

  void Collider2D::Wake()
  {
    m_Status &= ~Sleeping;
  }

  void Collider2D::Move(const SVector2F & Delta)
  {
    if (m_Mesh) {
      m_Mesh->pos += ::vec2d(Delta.x, Delta.y);
    }
  }

  void Collider2D::Update(const::vec2d & Gravity)
  {
    if (m_Mesh) {
      m_PrevColliderPos = m_Mesh->pos;
      m_Mesh->update(Gravity);
    }
  }

  void Collider2D::SetPosition(const SVector2F & Delta)
  {
    if (m_Mesh) {
      m_Mesh->pos = ::vec2d(Delta.x, Delta.y);
      m_PrevColliderPos = m_Mesh->pos;
    }
  }

  bool Collider2D::HandleCollision(SPtrWeak<Collider2D> Collider)
  {
    if (IsEnabled() && IsAwake() && IsRespondingToCollisions()) {
      if (m_ColliderCollisionCallback && Collider.lock())
        m_ColliderCollisionCallback(Collider.lock()->GetOwningObject());
      return true;
    }

    return false;
  }

  bool Collider2D::HandleCollisionWithSegment(SPtrWeak<SegmentMesh> Segment)
  {
    if (IsEnabled() && IsAwake() && IsRespondingToCollisions()) {
      if (m_SegmentCollisionCallback)
        m_SegmentCollisionCallback(Segment.lock().get());
    }

    return false;
  }
  void Collider2D::RememberPrevPosition()
  {
    m_PrevColliderPos = m_Mesh->pos;
  }
  void Collider2D::InterpolateState(SFLOAT Alpha)
  {
    if (m_Mesh) {

      //m_Mesh->setPosition(
      //  plinth::Tween::linear(m_PrevColliderPos, m_Mesh->pos, Alpha)
      //);
      //::vec2d nPos{ 0, 0 };
      //::vec2d oPos = m_PrevColliderPos;
      //nPos = plinth::Tween::linear(m_PrevColliderPos, m_Mesh->pos, Alpha);
      //m_Mesh->setPosition(nPos);
      //m_PrevColliderPos = nPos;
      //m_Mesh->v = plinth::Tween::linear(m_PrevVelocity, m_Mesh->v, Alpha);

      //::vec2d nVel{ 0, 0 };
      //::vec2d oVel = m_PrevVelocity;
      //nVel = plinth::Tween::linear(m_PrevVelocity, m_Mesh->v, Alpha);
      //m_Mesh->v = nVel;
      //m_PrevVelocity = m_Mesh->v;
    }
  }

  void Collider2D::Render(SFLOAT Alpha, SharedRTexture Texture)
  {
    if (DoInterpolateRender) {
      ::vec2d Interp = (m_PrevColliderPos) * (1.f - Alpha) + (Alpha * m_Mesh->pos);
      m_PrevColliderPos = m_Mesh->pos;
      m_Mesh->setPosition(Interp);
    }

    m_Mesh->draw(*Texture);

    if (DoInterpolateRender) {
      m_Mesh->setPosition(m_PrevColliderPos);
    }
  }

  void Collider2D::Reset()
  {
    if (m_Mesh) {
      m_Mesh->setPosition(m_InitialPositon);
      m_Mesh->v = m_InitialVelocity;
    }
  }

  /************************************************************************/
  /* Static automatic creation methods for certain meshes                 */
  /************************************************************************/
  SPtrShared<Collider2D> Collider2D::CreateCircularMesh
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
    BallMeshPtr Mesh = BuildBallMesh2D('b', position, velocity, radius, mass, coeffOfRest, color);
    SPtrShared<Collider2D> Collider = std::make_shared<Collider2D>();
    Collider->m_InitialPositon = Mesh->pos;
    Collider->m_InitialVelocity = ::vec2d(velocity.x, velocity.y);
    Collider->SetMesh(Mesh);

    return Collider;
  }

  SPtrShared<Collider2D> Collider2D::CreatePolygonMesh
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
    PolyMeshPtr Mesh = BuildPolygonMesh2D(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, color);
    SPtrShared<Collider2D> Collider = std::make_shared<Collider2D>();
    Collider->m_InitialPositon = ::vec2d(InitialPosition.x, InitialPosition.y);
    Collider->m_PrevColliderPos = ::vec2d(InitialPosition.x, InitialPosition.y);
    Collider->m_InitialVelocity = ::vec2d(InitialVelocity.x, InitialVelocity.y);
    Collider->m_Status = DefaultState;
    Collider->SetMesh(Mesh);

    return Collider;
  }

}
