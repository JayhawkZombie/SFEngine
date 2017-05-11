#ifndef SFEngine_ColliderPartitioner_H
#define SFEngine_ColliderPartitioner_H

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
#include "BasicIncludes.h"
#include "Physics\Collider.h"
#include "Physics\PartitionNode.h"
#include "Physics\PartitionerRecord.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <deque>

/************************************************************************/
/*                        ColliderPartitioner                           */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/29                                  */
/************************************************************************/

namespace SFEngine
{
  /************************************************************************/
  /*  Basically, a quad tree (but that name is so overused).  and here we ONLY care
   *  about the interactions between colliders, since the colliders have
   *  a way to inform their owner objects of collisions
   * 
   *   ______________
   *   | NW  *  NE  |
   *   |     *      |
   *   |************|
   *   | SW  *  SE  |
   *   |_____*______|
   * 
   * 
  /************************************************************************/

  class ColliderPartitioner
  {
  public:
    ColliderPartitioner() = delete;
    ColliderPartitioner(const ColliderPartitioner &&) = delete;
    ColliderPartitioner(SVector2F Size, UINT32 MaxDepth, SVector2U MinDim);
    ColliderPartitioner(SVector2F LTCorner, SVector2F Size, UINT32 MaxDepth, SVector2U MinDim, UINT32 MyDepth, ColliderPartitioner *Parent);
    ~ColliderPartitioner();
    void TickUpdate(const SFLOAT &TickDelta, SFLOATRECT LevelView);
    void UpdateObjectPhysics(SFLOATRECT LevelView);
    void RenderOnTexture(SFLOAT Alpha, SharedRTexture Texture, SFLOATRECT LevelView);
    void PhysicsUpdate(SFLOATRECT LevelView, STDDeque<CollisionRecord> &IntersectRecords);
    void CheckForCollisions(SPtrShared<Collider2D> TestAgainst, STDDeque<CollisionRecord> &Records);
    void RepositionItem(SPtrShared<Collider2D> Collider);
    void InsertItem(SPtrShared<Collider2D> Collider);
    UINT32 GetSize() const;

  private:
    /************************************************************************/
    /* Recalculate the size of the tre after a physics update               */
    /* Will also cause nodes to begin a death countdown if they have become */
    /* empty as well as all their children                                  */
    /************************************************************************/
    UINT32 RecalcSize();
    void BuildPartition(STDVector<SPtrShared<Collider2D>> Colliders);
    void Subdivide();
    void SubdivideNW();
    void SubdivideNE();
    void SubdivideSE();
    void SubdivideSW();

    void GiveToParent(SPtrShared<Collider2D> Collider);
    void GetFromChild(SPtrShared<Collider2D> Collider);
    void GiveToNW(SPtrShared<Collider2D> Collider);
    void GiveToNE(SPtrShared<Collider2D> Collider);
    void GiveToSE(SPtrShared<Collider2D> Collider);
    void GiveToSW(SPtrShared<Collider2D> Collider);

    void PlaceInNW(SPtrShared<Collider2D> Collider);
    void PlaceInNE(SPtrShared<Collider2D> Collider);
    void PlaceInSE(SPtrShared<Collider2D> Collider);
    void PlaceInSW(SPtrShared<Collider2D> Collider);
    void PlaceInMe(SPtrShared<Collider2D> Collider);

    void BringChildrenUp();
    void EnqueueIntersectionRecord(
      SPtrShared<Collider2D> Collider1, 
      ColliderPartitioner *ownerCollider1, 
      SPtrShared<Collider2D> Collider2, 
      ColliderPartitioner *ownerCollider2,
      STDDeque<CollisionRecord> &Records);

    sf::RectangleShape m_BoundsShape;
    sf::RectangleShape m_NWBox, m_NEBox, m_SEBox, m_SWBox;
#ifdef _DEBUG
    bool m_DrawBounds = true;
#else
    bool m_DrawBounds = false;
#endif
    UINT32     m_MaxDepth = 10;
    UINT32     m_Size = 0; //Holds our size + size of all children
    SVector2U  m_MinDim = SVector2U(10, 10);
    SFLOATRECT m_Bounds;
    SFLOATRECT m_NWBounds, m_NEBounds, m_SEBounds, m_SWBounds;
    SVector2F  m_Center;
    UINT32     m_Depth = 0;
    ColliderPartitioner *ParentPartitioner = nullptr;
    SPtrShared<ColliderPartitioner> m_NW, m_SW, m_SE, m_NE;
    STDVector<SPtrShared<Collider2D>> m_Colliders;
  };

}

#endif // SFEngine_ColliderPartitioner_H 
