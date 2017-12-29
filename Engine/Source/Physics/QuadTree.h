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

#include "Level\LevelObject.h"
#include "Lights\LightObject.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Engine
{
  const std::size_t MaxDepth = 6;

  class Collider2D;

  class QuadTree
  {
  public:
    QuadTree();
    QuadTree(const sf::Vector2f &cen, float wid, float hei, QuadTree *prnt, std::size_t level = 0);
    ~QuadTree();

    void InsertObject(std::shared_ptr<Engine::LevelObject> Object);
    //void InsertShadowCaster(std::shared_ptr<Engine::LightObject> Caster);
    void InsertCollidingMesh(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh);

    void Render(sf::RenderWindow &window);
    void Subdivide();
    void Clear();
    bool ShapeFitsInside(const sf::FloatRect &shape);
    void PlaceInsideChild(const sf::FloatRect &rect);

    std::vector<std::shared_ptr<Engine::LevelObject>> GetContainedObjectsInRange(const sf::FloatRect &Region);
    void GetColliderObjectsInRange(const sf::FloatRect &Region, std::vector<std::shared_ptr<Collider2D>> &Colliders);
    //std::vector<std::shared_ptr<Engine::LightObject>> GetContainedShadowCastingObjectsInRange(const sf::FloatRect &Region);
    std::vector<std::shared_ptr<Collider2D>> GetContainedCollidingMeshesInRange(const sf::FloatRect &Region);

  private:
    void PlaceInSelf(std::shared_ptr<Engine::Collider2D> shape);
    void GetCollidersInRangeSelf(std::vector<std::shared_ptr<Engine::Collider2D>> &Colliders);
    void GetCollidersInRangeChild(std::vector<std::shared_ptr<Engine::Collider2D>> &Colliders, QuadTree *Child);
    inline bool IntersectsChild(const sf::FloatRect &Region, QuadTree *Child);
    int FitsInsideAnyChild(std::shared_ptr<Engine::LevelObject> LObject);
    //int FitsInsideAnyChild(std::shared_ptr<Engine::LightObject> LightObject);
    int FitsInsideAnyChild(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh);
    int PlaceInChild(std::shared_ptr<QuadTree> Tree);
  public:

    sf::Vector2f Center;
    std::size_t Depth = 0;
    sf::FloatRect Bounds;
    float Width = 0;
    float Height = 0;
    bool Divided = false;

    std::shared_ptr<QuadTree> NW;
    std::shared_ptr<QuadTree> NE;
    std::shared_ptr<QuadTree> SW;
    std::shared_ptr<QuadTree> SE;
    QuadTree *Parent;
    
    std::vector<std::shared_ptr<Collider2D>> ContainedColliders;

    std::vector<std::shared_ptr<Engine::LevelObject>> ContainedObjects;
    //std::vector<std::shared_ptr<Engine::LightObject>> ShadowCastingObjects;
    std::vector<std::shared_ptr<PhysicsEngineBaseMeshType>> CollidingMeshes;
  };
}
