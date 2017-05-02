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
#include "Physics\ColliderPartitioner.h"
#include "Physics\Collider.h"
#include "Objects\GameObject.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <algorithm>

/************************************************************************/
/*                        ColliderPartitioner                           */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: (Name) - 2017/04/29                                       */
/************************************************************************/

namespace SFEngine
{
  //This is used to create the root node
  ColliderPartitioner::ColliderPartitioner(SVector2F Size, UINT32 MaxDepth, SVector2U MinDim)
    : m_Center({ Size.x / 2.f, Size.y / 2.f }), m_Depth(0), m_Bounds({ {0, 0}, Size }), ParentPartitioner(nullptr), m_MinDim(MinDim), m_MaxDepth(MaxDepth)
  {
    m_NWBounds = { 0.f, 0.f, Size.x / 2.f, Size.y / 2.f };
    m_NEBounds = { m_Center.x, 0.f, Size.x / 2.f, Size.y / 2.f };
    m_SEBounds = { m_Center, Size / 2.f };
    m_SWBounds = { 0, m_Center.y, Size.x / 2.f, Size.y / 2.f };
    m_BoundsShape.setPosition({ 0.f, 0.f });
    m_BoundsShape.setSize(Size);
    m_BoundsShape.setFillColor(sf::Color::Transparent);
    m_BoundsShape.setOutlineColor(sf::Color::White);
    m_BoundsShape.setOutlineThickness(-2);
  }
  
  //This one is used to create all of the child nodes
  ColliderPartitioner::ColliderPartitioner(SVector2F LTCorner, SVector2F Size, UINT32 MaxDepth, SVector2U MinDim, UINT32 MyDepth, ColliderPartitioner *Parent)
    : m_Bounds(LTCorner, Size), m_Center({ LTCorner.x + Size.x / 2.f, LTCorner.y + Size.y / 2.f }), ParentPartitioner(Parent), m_Depth(MyDepth), m_MaxDepth(MaxDepth), m_MinDim(MinDim)
  {
    m_NWBounds = { LTCorner.x, LTCorner.y, Size.x / 2.f, Size.y / 2.f };
    m_NEBounds = { m_Center.x, LTCorner.y, Size.x / 2.f, Size.y / 2.f };
    m_SEBounds = { m_Center.x, m_Center.y, Size.x / 2.f, Size.y / 2.f };
    m_SWBounds = { LTCorner.x, m_Center.y, Size.x / 2.f, Size.y / 2.f };
    m_BoundsShape.setPosition(LTCorner);
    m_BoundsShape.setSize(Size);
    m_BoundsShape.setFillColor(sf::Color::Transparent);
    m_BoundsShape.setOutlineColor(sf::Color::White);
    m_BoundsShape.setOutlineThickness(-2);
  }

  ColliderPartitioner::~ColliderPartitioner()
  {
    if (m_NW)
      m_NW.reset();
    if (m_SW)
      m_SW.reset();
    if (m_NE)
      m_NE.reset();
    if (m_SE)
      m_SE.reset();

    m_Colliders.clear();
  }

  void ColliderPartitioner::TickUpdate(const SFLOAT & TickDelta, SFLOATRECT LevelView)
  {
    //We only need to update those objects that are visible (ie whose bounds intersect the view)
    if (!m_Bounds.intersects(LevelView))
      return;

    GameObject *ColliderObject = nullptr;

    for (auto & collider : m_Colliders) {
      ColliderObject = collider->GetOwningObject();
      if (ColliderObject) 
        ColliderObject->TickUpdate(TickDelta);
    }
      
    if (m_NW)
      m_NW->TickUpdate(TickDelta, LevelView);
    if (m_NE)
      m_NE->TickUpdate(TickDelta, LevelView);
    if (m_SE)
      m_SE->TickUpdate(TickDelta, LevelView);
    if (m_SW)
      m_SW->TickUpdate(TickDelta, LevelView);
  }

  void ColliderPartitioner::UpdateObjectPhysics(SFLOATRECT LevelView)
  {
    STDDeque<CollisionRecord> ObjectRecords;
    PhysicsUpdate(LevelView, ObjectRecords);

    CollisionRecord Record;

    while (!ObjectRecords.empty()) {
      Record = ObjectRecords.front();

      Record
        .Collider1
        .m_ColliderNode->RepositionItem(Record.Collider1.m_Collider);
      Record
        .Collider2
        .m_ColliderNode->RepositionItem(Record.Collider2.m_Collider);
      ObjectRecords.pop_back();
    }
  }

  void ColliderPartitioner::RenderOnTexture(SFLOAT Alpha, SharedRTexture Texture, SFLOATRECT LevelView)
  {
    //Same idea as TickUpdate - only render those objects that are visible
    //  Some exceptions may be made for lights, which can "bleed" into other areas
    if (!m_Bounds.intersects(LevelView))
      return;

    GameObject *ColliderObject = nullptr;
    for (auto & collider : m_Colliders) {
      ColliderObject = collider->GetOwningObject();
      if (ColliderObject)
        ColliderObject->Render(Alpha, Texture);
    }

    if (m_NW)
      m_NW->RenderOnTexture(Alpha, Texture, LevelView);
    if (m_NE)
      m_NE->RenderOnTexture(Alpha, Texture, LevelView);
    if (m_SE)
      m_SE->RenderOnTexture(Alpha, Texture, LevelView);
    if (m_SW)
      m_SW->RenderOnTexture(Alpha, Texture, LevelView);

    if (m_DrawBounds)
      Texture->draw(m_BoundsShape);
  }

  /*************************************************************************/
  /* For every object we have, we will try to intersect their global rects */
  /* If this test passes, we will enqueue it to be fully tested later      */
  /*************************************************************************/
  void ColliderPartitioner::PhysicsUpdate(SFLOATRECT LevelView, STDDeque<CollisionRecord> &IntersectRecords)
  {
    SFLOATRECT Rect1, Rect2;

    for (auto i = m_Colliders.begin(); i != m_Colliders.end(); ++i) {
      Rect1 = (*i)->GetGlobalBounds();

      for (auto j = i; j != m_Colliders.end(); ++j) {
        Rect2 = (*j)->GetGlobalBounds();

        /************************************************************************/
        /* If these two globalBounds rects intersect, the colliders _MIGHT_     */
        /* be interacting, we will enqueue it to be fully tested later          */
        /************************************************************************/
        if (Rect1.intersects(Rect2))
          EnqueueIntersectionRecord(*i, (*i)->GetOwnerPartitioner(),
                                    *j, (*j)->GetOwnerPartitioner(), IntersectRecords);
      } // for j = i -> m_Colliders.end()

      /**************************************************************************/
      /* For each of our objects, we need to see if it can interact with        */
      /* anything that our child nodes own (if they exist)                      */
      /**************************************************************************/
      if (m_NW && m_NWBounds.intersects(Rect1))
        m_NW->CheckForCollisions(*i, IntersectRecords);
      if (m_NE && m_NEBounds.intersects(Rect1))
        m_NE->CheckForCollisions(*i, IntersectRecords);
      if (m_SE && m_SEBounds.intersects(Rect1))
        m_SE->CheckForCollisions(*i, IntersectRecords);
      if (m_SW && m_SWBounds.intersects(Rect1))
        m_SW->CheckForCollisions(*i, IntersectRecords);
    } // for i = m_Colliders.begin() -> m_Colliders.end()


    /************************************************************************/
    /* Just as we did for the specific objects above, we will see if any of */
    /* our child nodes are within view and can update - if so, tell them to */
    /************************************************************************/
    if (m_NW && m_NWBounds.intersects(LevelView))
      m_NW->PhysicsUpdate(LevelView, IntersectRecords);
    if (m_NE && m_NEBounds.intersects(LevelView))
      m_NE->PhysicsUpdate(LevelView, IntersectRecords);
    if (m_SE && m_SEBounds.intersects(LevelView))
      m_SE->PhysicsUpdate(LevelView, IntersectRecords);
    if (m_SW && m_SWBounds.intersects(LevelView))
      m_SW->PhysicsUpdate(LevelView, IntersectRecords);
  }

  void ColliderPartitioner::CheckForCollisions(SPtrShared<Collider2D> TestAgainst, STDDeque<CollisionRecord>& Records)
  {
    SFLOATRECT TestBounds = TestAgainst->GetGlobalBounds();

    /*******************************************************************************/
    /* We don't do our normal tests here, this is specifically                     */
    /* a request from our parent to see if this PARTICULAR collider hits something */
    /* that we own                                                                 */
    /*******************************************************************************/
    for (auto i = m_Colliders.begin(); i != m_Colliders.end(); ++i) {
      if ((*i)->GetGlobalBounds().intersects(TestBounds))
        EnqueueIntersectionRecord(TestAgainst, TestAgainst->GetOwnerPartitioner(), 
                                  *i, (*i)->GetOwnerPartitioner(), Records);
    }
    //Do the recursive thing and check our children
    if (m_NW && m_NWBounds.intersects(TestBounds))
      m_NW->CheckForCollisions(TestAgainst, Records);
    if (m_SW && m_SWBounds.intersects(TestBounds))
      m_SW->CheckForCollisions(TestAgainst, Records);
    if (m_NE && m_NEBounds.intersects(TestBounds))
      m_NE->CheckForCollisions(TestAgainst, Records);
    if (m_SE && m_SEBounds.intersects(TestBounds))
      m_SE->CheckForCollisions(TestAgainst, Records);
  }

  void ColliderPartitioner::RepositionItem(SPtrShared<Collider2D> Collider)
  {
    auto Rect = Collider->GetGlobalBounds();

    if (!EntirelyWithin(Rect, m_Bounds))
      GiveToParent(Collider);
    else {
      if (EntirelyWithin(Rect, m_NWBounds))
        GiveToNW(Collider);
      else if (EntirelyWithin(Rect, m_NEBounds))
        GiveToNE(Collider);
      else if (EntirelyWithin(Rect, m_SEBounds))
        GiveToSE(Collider);
      else if (EntirelyWithin(Rect, m_SWBounds))
        GiveToSW(Collider);
      //Well, then we don't need to reposition it - it can stay here
    }
  }

  void ColliderPartitioner::GiveToParent(SPtrShared<Collider2D> Collider)
  {
    std::remove_if(
      m_Colliders.begin(), 
      m_Colliders.end(), 
      [&Collider](auto p1) -> bool { return (p1 == Collider); }
    );
    ParentPartitioner->GetFromChild(Collider);
  }

  void ColliderPartitioner::GetFromChild(SPtrShared<Collider2D> Collider)
  {
    auto Rect = Collider->GetGlobalBounds();

    if (!EntirelyWithin(Rect, m_Bounds))
      GiveToParent(Collider);
    else {
      if (EntirelyWithin(Rect, m_NWBounds))
        GiveToNW(Collider);
      else if (EntirelyWithin(Rect, m_NEBounds))
        GiveToNE(Collider);
      else if (EntirelyWithin(Rect, m_SEBounds))
        GiveToSE(Collider);
      else if (EntirelyWithin(Rect, m_SWBounds))
        GiveToSW(Collider);
      else {
      //Well, then we don't need to reposition it - it can stay here
      // Need to check if we already own it? Could this be called again somehow?
        auto it = std::find(m_Colliders.begin(), m_Colliders.end(), Collider);
        if (it == m_Colliders.end()) m_Colliders.emplace_back(Collider);
      }
    }
  }

  void ColliderPartitioner::GiveToNW(SPtrShared<Collider2D> Collider)
  {
    std::remove_if(
      m_Colliders.begin(),
      m_Colliders.end(),
      [&Collider](auto p1) -> bool { return (p1 == Collider); }
    );

    PlaceInNW(Collider);
  }

  void ColliderPartitioner::GiveToNE(SPtrShared<Collider2D> Collider)
  {
    std::remove_if(
      m_Colliders.begin(),
      m_Colliders.end(),
      [&Collider](auto p1) -> bool { return (p1 == Collider); }
    );
    PlaceInNE(Collider);
  }

  void ColliderPartitioner::GiveToSE(SPtrShared<Collider2D> Collider)
  {
    std::remove_if(
      m_Colliders.begin(),
      m_Colliders.end(),
      [&Collider](auto p1) -> bool { return (p1 == Collider); }
    );
    PlaceInSE(Collider);
  }

  void ColliderPartitioner::GiveToSW(SPtrShared<Collider2D> Collider)
  {
    std::remove_if(
      m_Colliders.begin(),
      m_Colliders.end(),
      [&Collider](auto p1) -> bool { return (p1 == Collider); }
    );
    PlaceInSW(Collider);
  }

  void ColliderPartitioner::InsertItem(SPtrShared<Collider2D> Collider)
  {
    if (m_Depth == m_MaxDepth)
      PlaceInMe(Collider);
    else if (m_Colliders.size() == 0)
      PlaceInMe(Collider);
    else {
      if (m_Bounds.width <= m_MinDim.x || m_Bounds.height <= m_MinDim.y)
        PlaceInMe(Collider);
      else {
        auto Rect = Collider->GetGlobalBounds();
        
        if (EntirelyWithin(Rect, m_NWBounds))
          PlaceInNW(Collider);
        else if (EntirelyWithin(Rect, m_NEBounds))
          PlaceInNE(Collider);
        else if (EntirelyWithin(Rect, m_SEBounds))
          PlaceInSE(Collider);
        else if (EntirelyWithin(Rect, m_SWBounds))
          PlaceInSW(Collider);
        else {
          //UGh, guess we're putting it in our collection
          m_Colliders.emplace_back(Collider);
        }
      } // else (from: if (m_Bounds.width <= MinDim.x || m_Bounds.height <= MinDim.y)
    } // else (from: if (m_Colliders.size() == 0)
  }

  UINT32 ColliderPartitioner::GetSize() const
  {
    return m_Size;
  }

  UINT32 ColliderPartitioner::RecalcSize()
  {
    UINT32 Temp = 0;

    Temp = m_Colliders.size();

    if (m_NW)
      Temp += m_NW->RecalcSize();
    if (m_NE)
      Temp += m_NW->RecalcSize();
    if (m_SE)
      Temp += m_NE->RecalcSize();
    if (m_SW)
      Temp += m_SW->RecalcSize();

    m_Size = Temp;
    return Temp;
  }

  void ColliderPartitioner::BuildPartition(STDVector<SPtrShared<Collider2D>> Colliders)
  {
    /************************************************************************/
    /* So, we now need to look at our objects and see if any fit perfectly  */
    /* inside one of our child nodes - if so, subdivide into that child and */
    /* insert the item into it (as long as we have 1 or more items in our   */
    /* collection.  If our collection is empty, we will place the object in */
    /* our container instead and not subdivide                              */
    /************************************************************************/
    SFENGINE_ASSERT(m_Depth == 0);
    for (auto & Collider : Colliders)
      InsertItem(Collider);
  }

  void ColliderPartitioner::Subdivide()
  {
  }

  void ColliderPartitioner::SubdivideNW()
  {
    SFENGINE_ASSERT(m_NW == nullptr);

    m_NW = std::make_shared<ColliderPartitioner>(
      SVector2F(m_Bounds.left, m_Bounds.top),
      SVector2F(m_Bounds.width / 2.f, m_Bounds.height / 2.f),
      m_MaxDepth, m_MinDim, m_Depth + 1, this
    );

    SFENGINE_ASSERT(m_NW != nullptr);
  }

  void ColliderPartitioner::SubdivideNE()
  {
    SFENGINE_ASSERT(m_NE == nullptr);

    m_NE = std::make_shared<ColliderPartitioner>(
      SVector2F(m_Center.x, m_Bounds.top),
      SVector2F(m_Bounds.width / 2.f, m_Bounds.height / 2.f),
      m_MaxDepth, m_MinDim, m_Depth + 1, this
    );

    SFENGINE_ASSERT(m_NE != nullptr);
  }

  void ColliderPartitioner::SubdivideSE()
  {
    SFENGINE_ASSERT(m_SE == nullptr);

    m_SE = std::make_shared<ColliderPartitioner>(
      SVector2F(m_Center.x, m_Center.y),
      SVector2F(m_Bounds.width / 2.f, m_Bounds.height / 2.f),
      m_MaxDepth, m_MinDim, m_Depth + 1, this
    );

    SFENGINE_ASSERT(m_SE != nullptr);
  }

  void ColliderPartitioner::SubdivideSW()
  {
    SFENGINE_ASSERT(m_SW == nullptr);

    m_SW = std::make_shared<ColliderPartitioner>(
      SVector2F(m_Bounds.left, m_Center.y),
      SVector2F(m_Bounds.width / 2.f, m_Bounds.height / 2.f),
      m_MaxDepth, m_MinDim, m_Depth + 1, this
    );

    SFENGINE_ASSERT(m_SW != nullptr);
  }

  void ColliderPartitioner::PlaceInNW(SPtrShared<Collider2D> Collider)
  {
    if (!m_NW)
      SubdivideNW();

    m_NW->InsertItem(Collider);
  }

  void ColliderPartitioner::PlaceInNE(SPtrShared<Collider2D> Collider)
  {
    if (!m_NE)
      SubdivideNE();

    m_NE->InsertItem(Collider);
  }

  void ColliderPartitioner::PlaceInSE(SPtrShared<Collider2D> Collider)
  {
    if (!m_SE)
      SubdivideSE();

    m_SE->InsertItem(Collider);
  }

  void ColliderPartitioner::PlaceInSW(SPtrShared<Collider2D> Collider)
  {
    if (!m_SW)
      SubdivideSW();

    m_SW->InsertItem(Collider);
  }

  void ColliderPartitioner::PlaceInMe(SPtrShared<Collider2D> Collider)
  {
    /************************************************************************/
    /* Let the collider know that we are node containing it                 */
    /* This will be used later when ew need to reposition colliders that    */
    /* moved - if we have a pointer to the node they USED to be on, that    */
    /* means we can just tell that node to "reposition" its old item        */
    /************************************************************************/
    Collider->SetOwnerPartitioner(this);
    m_Colliders.emplace_back(Collider);
  }

  void ColliderPartitioner::BringChildrenUp()
  {
    /************************************************************************/
    /* This can happen whenever a node becomes empty or it dies             */
    /* We essentially have a free node and if there are any children, we    */
    /* need to tell them they can move up a level to fill in the empty spot */
    /************************************************************************/
  }

  void ColliderPartitioner::EnqueueIntersectionRecord(
    SPtrShared<Collider2D> Collider1,
    ColliderPartitioner *ownerCollider1,
    SPtrShared<Collider2D> Collider2,
    ColliderPartitioner *ownerCollider2,
    STDDeque<CollisionRecord> &Records )
  {
    RecordPairItem ColliderPair1;
    ColliderPair1.m_Collider = Collider1;
    ColliderPair1.m_ColliderNode = ownerCollider1;

    RecordPairItem ColliderPair2;
    ColliderPair2.m_Collider = Collider2;
    ColliderPair2.m_ColliderNode = ownerCollider2;
    
    CollisionRecord record;
    record.Collider1 = ColliderPair1;
    record.Collider2 = ColliderPair2;
    Records.emplace_back(record);
  }

} // namespace SFEngine
