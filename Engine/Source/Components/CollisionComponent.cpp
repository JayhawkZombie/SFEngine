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

#include "Engine/stdafx.h"

#include "Components/CollisionComponent.h"
#include "ThirdParty/PhysicsEngine.h"

mvHit * CollisionComponent::GetMesh() const
{
  switch (m_MeshType)
  {
    case ECollisionComponentMeshType::Ball:
    {
      return ( mvHit * ) ( std::addressof(ballMesh) );
    }

    case ECollisionComponentMeshType::BallGo:
    {
      return ( mvHit * ) ( std::addressof(ballGoMesh) );
    }

    case ECollisionComponentMeshType::Block:
    {
      return ( mvHit * ) ( std::addressof(blockMesh) );
    }

    case ECollisionComponentMeshType::ExpandPolygon:
    {
      return ( mvHit * ) ( std::addressof(expandMesh) );
    }

    case ECollisionComponentMeshType::RegPolygon:
    {
      return ( mvHit * ) ( std::addressof(polyMesh) );
    }

    case ECollisionComponentMeshType::WaveSeg:
    {
      return ( mvHit * ) ( std::addressof(waveMesh) );
    }

    default:
    {
      return nullptr;
    }
  }
}


CollisionComponent::CollisionComponent()
{
  ballMesh = ball();
}


CollisionComponent::CollisionComponent(const CollisionComponent &Component)
  : m_IsHidden(Component.m_IsHidden)
  , m_IsSleeping(Component.m_IsSleeping)
  , m_MeshType(Component.m_MeshType)
  , m_UseOnlyForOverlapTesting(Component.m_UseOnlyForOverlapTesting)
{
  switch (Component.m_MeshType)
  {
    case ECollisionComponentMeshType::Ball:
    {
      ballMesh = Component.ballMesh;
      break;
    }

    case ECollisionComponentMeshType::BallGo:
    {
      ballGoMesh = Component.ballGoMesh;
      break;
    }

    case ECollisionComponentMeshType::Block:
    {
      blockMesh = Component.blockMesh;
      break;
    }

    case ECollisionComponentMeshType::ExpandPolygon:
    {
      expandMesh = Component.expandMesh;
      break;
    }

    case ECollisionComponentMeshType::RegPolygon:
    {
      polyMesh = Component.polyMesh;
      break;
    }

    case ECollisionComponentMeshType::WaveSeg:
    {
      waveMesh = Component.waveMesh;
      break;
    }

    default:
    {
      ballMesh = ball();
    }
  }
}


CollisionComponent::CollisionComponent(CollisionComponent &&Component)
  : m_IsHidden(Component.m_IsHidden)
  , m_IsSleeping(Component.m_IsSleeping)
  , m_MeshType(Component.m_MeshType)
  , m_UseOnlyForOverlapTesting(Component.m_UseOnlyForOverlapTesting)
{
  switch (Component.m_MeshType)
  {
    case ECollisionComponentMeshType::Ball:
    {
      ballMesh = std::move(Component.ballMesh);
      break;
    }

    case ECollisionComponentMeshType::BallGo:
    {
      ballGoMesh = std::move(Component.ballGoMesh);
      break;
    }

    case ECollisionComponentMeshType::Block:
    {
      blockMesh = std::move(Component.blockMesh);
      break;
    }

    case ECollisionComponentMeshType::ExpandPolygon:
    {
      expandMesh = std::move(Component.expandMesh);
      break;
    }

    case ECollisionComponentMeshType::RegPolygon:
    {
      polyMesh = std::move(Component.polyMesh);
      break;
    }

    case ECollisionComponentMeshType::WaveSeg:
    {
      waveMesh = std::move(Component.waveMesh);
      break;
    }

    default:
    {
      ballMesh = ball();
    }
  }
}

CollisionComponent::~CollisionComponent()
{
  //Fuck you VisualStudio - I want to DEFAULT this destructor
}

void CollisionComponent::SetMesh(const SCollisionMeshData &Data)
{
  switch (Data.Type)
  {
    case ECollisionComponentMeshType::Ball:
    case ECollisionComponentMeshType::BallGo:
    case ECollisionComponentMeshType::Block:
    case ECollisionComponentMeshType::ExpandPolygon:
    case ECollisionComponentMeshType::RegPolygon:
    case ECollisionComponentMeshType::WaveSeg:
    default:
      return;
  }
}

ECollisionComponentMeshType CollisionComponent::GetMeshType() const
{
  return m_MeshType;
}

CollisionComponent::operator bool() const
{
  return ( m_MeshType != ECollisionComponentMeshType::None &&
           ! m_IsHidden && !m_IsSleeping 
         );
}
