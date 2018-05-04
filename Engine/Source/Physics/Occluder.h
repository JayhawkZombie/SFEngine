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

#include "BasicIncludes.h"
#include "PhysicsEngine.h"

class LightSystem;

struct Point {
  ::vec2d pt;
  float angle;
};

class Occluder2D
{
public:
  friend class LightSystem;

  Occluder2D() = default;
  ~Occluder2D() = default;

  void SetOccluder(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh) {
    m_OccluderMesh = Mesh;
  }

  std::vector<::vec2d> GetVertices() {
    return {  };
  }

  void Move(const sf::Vector2f &delta) {
    if (m_OccluderMesh)
      m_OccluderMesh->pos += ::vec2d(delta.x, delta.y);
  }

  void SetPosition(const sf::Vector2f &Position) {
    if (m_OccluderMesh)
      m_OccluderMesh->pos = ::vec2d(Position.x, Position.y);
  }

  std::weak_ptr<PhysicsEngineBaseMeshType> GetMesh() {
    return m_OccluderMesh;
  }

  bool HandleCollision(std::weak_ptr<Collider2D> Collider) {
    return false;
  }

protected:
  bool m_CastSoftShadow = false;
  std::shared_ptr<PhysicsEngineBaseMeshType> m_OccluderMesh;

  std::vector<::vec2d> m_SortingPoints;

};
