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

#include "Level\Level.h"
#include "Engine\Console.h"
#include "Physics\Collider.h"

void Level::TickUpdate(const double &delta)
{
  static double cumulative = 0.f;
  cumulative += delta;

#ifdef WITH_EDITOR

#endif
  TileMap->update(lvlData, 20);
  //Only want to update the physics 60 times per second, since it does not time itself ((((UGH))))
    
  for (auto & obj : LevelObjects)
    obj.second->TickUpdate(delta);

  if (cumulative > updateInterval) {

    if (DoUpdatePhysics && ( LevelObjects.size() > 0 || Segments.size() > 0) ) {
      UpdateObjectPhysics();

      for (auto & obj : LevelObjects) {
        obj.second->PhysicsUpdate();
      }
    }

    cumulative = 0.f;
  }

#ifdef WITH_EDITOR

#endif

}

void Level::UpdateObjectPhysics()
{
  static std::vector<PhysicsEngineBaseMeshType *> MeshVector;
  static std::vector<PhysicsEngineSegmentType *> SegVector;

  static std::vector<std::shared_ptr<Collider2D>> Colliders;
   

  MeshVector.clear();
  SegVector.clear();
  Colliders.clear();

  for (auto & obj : LevelObjects) {
    auto vec = obj.second->GetColliders();
    for (auto & mesh : vec) {
      Colliders.push_back(mesh);
    }
  }
    
  for (auto & seg : Segments)
    SegVector.push_back(seg.get());

  UpdatePhysics(Colliders, SegVector);
}
