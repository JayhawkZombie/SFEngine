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

#include "Physics\QuadTree.h"
#include "Physics\Collider.h"

#include <iostream>

namespace Engine
{

  bool RectContainsRect(const sf::FloatRect &Outer, const sf::FloatRect &Inner)
  {
    //It must contain all 4 corners if it is inside the rectangle
    return
      (
        Outer.contains({ Inner.left, Inner.top }) &&
        Outer.contains({ Inner.left + Inner.width, Inner.top }) &&
        Outer.contains({ Inner.left, Inner.top + Inner.height }) &&
        Outer.contains({ Inner.left + Inner.width, Inner.top + Inner.height })
        );
  }

  QuadTree::QuadTree()
    : NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr), Divided(false), Center({ 0, 0 }), Height(0), Width(0), Depth(0), Parent(nullptr),
    Bounds({ 0, 0, 0, 0 })
  {

  }

  QuadTree::QuadTree(const sf::Vector2f &cen, float wid, float hei, QuadTree *prnt, std::size_t level)
    : NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr), Parent(prnt), Center(cen), Height(hei), Width(wid), Depth(level), Divided(false),
    Bounds(sf::FloatRect({ Center.x - Width / 2.f, Center.y - Height / 2.f, Width, Height }))
  {
    
  }

  QuadTree::~QuadTree()
  {
    if (NW)
      NW.reset();
    if (NE)
      NE.reset();
    if (SW)
      SW.reset();
    if (SE)
      SE.reset();

    for (auto & obj : ContainedObjects)
      obj.reset();
    ContainedObjects.clear();

    //for (auto & caster : ShadowCastingObjects)
    //  caster.reset();
    //ShadowCastingObjects.clear();

    for (auto & mesh : CollidingMeshes)
      mesh.reset();
    CollidingMeshes.clear();
  }

  void QuadTree::InsertObject(std::shared_ptr<Engine::LevelObject> Object)
  {
    //First, see if it fits in any of our children
    if (FitsInsideAnyChild(Object)) {

    }
  }

  //void QuadTree::InsertShadowCaster(std::shared_ptr<Engine::LightObject> Caster)
  //{
  //}

  void QuadTree::InsertCollidingMesh(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh)
  {
  }


  bool QuadTree::ShapeFitsInside(const sf::FloatRect &shape)
  {
    return false;
  }

  void QuadTree::PlaceInsideChild(const sf::FloatRect & rect)
  {
    

  }

  std::vector<std::shared_ptr<Engine::LevelObject>> QuadTree::GetContainedObjectsInRange(const sf::FloatRect &Region)
  {
    return std::vector<std::shared_ptr<Engine::LevelObject>>();
  }

  void QuadTree::GetColliderObjectsInRange(const sf::FloatRect &Region, std::vector<std::shared_ptr<Collider2D>> & Colliders)
  {
    if (IntersectsChild(Region, SW.get()))
      SW->GetColliderObjectsInRange(Region, Colliders);

    if (IntersectsChild(Region, SE.get()))
      SE->GetColliderObjectsInRange(Region, Colliders);

    if (IntersectsChild(Region, NE.get()))
      NE->GetColliderObjectsInRange(Region, Colliders);

    if (IntersectsChild(Region, NW.get()))
      NW->GetColliderObjectsInRange(Region, Colliders);

    for (auto & coll : ContainedObjects) {
      if (coll->GetGlobalBounds().intersects(Region)) {
        auto vec = coll->GetColliders();
        auto it = vec.end() - 1;
        for (auto & v : vec)
          Colliders.push_back(v);
      }
    }
  }

  std::vector<std::shared_ptr<Collider2D>> QuadTree::GetContainedCollidingMeshesInRange(const sf::FloatRect & Region)
  {
    return{};
  }

  void QuadTree::PlaceInSelf(std::shared_ptr<Engine::Collider2D> shape)
  {
    
  }

  void QuadTree::GetCollidersInRangeSelf(std::vector<std::shared_ptr<Engine::Collider2D>>& Colliders)
  {
  }

  void QuadTree::GetCollidersInRangeChild(std::vector<std::shared_ptr<Engine::Collider2D>> &Colliders, QuadTree *Child)
  {
  }

  bool QuadTree::IntersectsChild(const sf::FloatRect & Region, QuadTree * Child)
  {
    if (!Child)
      return false;

    return (Child->Bounds.intersects(Region));
  }

  int QuadTree::FitsInsideAnyChild(std::shared_ptr<Engine::LevelObject> LObject)
  {
    //will return true if the height and width and less than half ours
    auto bounds = LObject->GetGlobalBounds();

    //AND the center of us is not contained within the rect
    return ((bounds.width < Width / 2.f) && (bounds.height < Height / 2.f));
  }

  //int QuadTree::FitsInsideAnyChild(std::shared_ptr<Engine::LightObject> LObject)
  //{
  //  //will return true if the height and width and less than half ours
  //  auto bounds = LObject->GetGlobalBounds();

  //  //AND the center of us is not contained within the rect
  //  return ((bounds.width < Width / 2.f) && (bounds.height < Height / 2.f));
  //}

  int QuadTree::FitsInsideAnyChild(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh)
  {
    //will return true if the height and width and less than half ours
    auto bounds = sf::FloatRect(Mesh->pos.x, Mesh->pos.y, Mesh->siz.x, Mesh->siz.y);

    //AND the center of us is not contained within the rect
    return ((bounds.width < Width / 2.f) && (bounds.height < Height / 2.f));
  }

  int QuadTree::PlaceInChild(std::shared_ptr<QuadTree> Tree)
  {
    return false;
  }

  void QuadTree::Clear()
  {
    
  }

  void QuadTree::Render(sf::RenderWindow & window)
  {
    
  }

  void QuadTree::Subdivide()
  {
    
  }
}
