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

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

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
    if (m_Mesh)
      m_Mesh->update(Gravity);
  }

  void Collider2D::SetPosition(const SVector2F & Delta)
  {
    if (m_Mesh) {
      m_Mesh->pos = ::vec2d(Delta.x, Delta.y);
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
}
