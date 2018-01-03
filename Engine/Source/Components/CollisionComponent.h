#pragma once

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

#include "ComponentBase.h"
#include "ThirdParty/PhysicsEngine.h"

class mvHit;
class Collider2D;
class CollisionComponent;

enum class ECollisionComponentMeshType
{
  RegPolygon,
  Ball,
  BallGo,
  ExpandPolygon,
  Block,
  WaveSeg,
  None
};

struct SCollisionMeshData
{
  ECollisionComponentMeshType Type;
  sf::Vector2f Position;
  sf::Vector2f Velocity;
  sf::Vector2f Size;
  float CoefficientOfRestitution;
  float DragCoefficient;
  float Mass;
  bool IsFree;
};

class CollisionComponent
{
public:

  CollisionComponent();
  ~CollisionComponent();

  CollisionComponent(const CollisionComponent &);
  CollisionComponent(CollisionComponent &&);

  void SetMesh(const SCollisionMeshData &Data);

  mvHit * GetMesh() const;

  ECollisionComponentMeshType GetMeshType() const;

  operator bool() const;

private:

  ECollisionComponentMeshType m_MeshType = ECollisionComponentMeshType::None;

  bool m_IsSleeping = false;
  bool m_IsHidden = false;
  
  /* True if we only want to use the mesh for testing overlaps
   * but NOT generate any HIT callbacks OR cause any mesh to think it
   * has collided with it
   * */
  bool m_UseOnlyForOverlapTesting = false;

  union 
  {
    regPolygon    polyMesh;
    ball          ballMesh;
    ball_go       ballGoMesh;
    expandPolygon expandMesh;
    block         blockMesh;
    waveSeg       waveMesh;
  };

};
