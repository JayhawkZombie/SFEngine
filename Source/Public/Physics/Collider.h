#ifndef SFEngine_Collider_H
#define SFEngine_Collider_H

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


/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "BasicIncludes.h"
#include "DependencyInterface.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                           Collider                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

namespace SFEngine
{
  class GameObject;

  /************************************************************************/
  /* Enum for the type of mesh that we want to make                       */
  /************************************************************************/
  enum class MeshType : std::uint32_t
  {
    Base,
    Ball,
    BallGo,
    Polygon,
    Block,
    ExpandPolygon
  };

  class Collider2D
  {
  public:
    Collider2D() = default;
    Collider2D(UINT32 State);
    SPtrShared<Collider2D> Clone();
    static SPtrShared<Collider2D> Create(GameObject* Owner, UINT32 State = DefaultState);
    static UINT32 DefaultState;
    ~Collider2D();

    /************************************************************************/
    /* State enumeration                                                    */
    /************************************************************************/
    enum State
    {
      Active               = 0b01,                                  // 1/32
      Sleeping             = 0b010,                                 // 2/32
      Enabled              = 0b0100,                                // 3/32
      CanBeAwoken          = 0b01000,                               // 4/32
      HasPhysicalResponse  = 0b010000,                              // 5/32
      NotifyEveryFrame     = 0b0100000,                             // 7/32
      SingleResponsePerObj = 0b01000000,                            // 8/32
      NotifyOfOverlap      = 0b010000000,                           // 9/32
      CastShadows          = 0b0100000000,                          // 10/32
      NotifyOnTouch        = 0b01000000000,                         // 11/32
      Static               = 0b010000000000                         // 12/32
    };


    /************************************************************************/
    /* Setters                                                              */
    /************************************************************************/
    void SetMesh(MeshBasePtr Mesh);
    void SetProperty(UINT32 Property);
    void SetCollisionCallback(std::function<void(GameObject *)> Callback);
    void SetSegmentCollisionCallback(std::function<void(SegmentMesh *)> Callback);

    /************************************************************************/
    /* Getters                                                              */
    /************************************************************************/
    SPtrWeak<MeshBase> GetMesh() const;
    bool IsActive() const;
    bool IsAwake() const;
    bool IsRespondingToCollisions() const;
    bool DoesCastShadows() const;
    bool IsEnabled() const;
    bool IsStatic() const;
    bool GetProperty(UINT32 Property) const;
    GameObject* GetOwningObject() const;
    SFLOATRECT GetGlobalBounds() const;

    /************************************************************************/
    /* Property manipulators                                                */
    /************************************************************************/
    void Sleep();
    void Wake();
    void Move(const SVector2F &Delta);
    void Update(const ::vec2d &Gravity);
    void SetPosition(const SVector2F &Delta);
    bool HandleCollision(SPtrWeak<Collider2D> Collider);
    bool HandleCollisionWithSegment(SPtrWeak<SegmentMesh> Segment);

  protected:    
    MeshType m_Type;
    UINT32 m_Status;
    MeshBasePtr m_Mesh;
    GameObject* m_OwnerObject;

    /************************************************************************/
    /* Callback methods                                                     */
    /************************************************************************/
    std::function<void(GameObject *)> m_ColliderCollisionCallback;
    std::function<void(SegmentMesh *)> m_SegmentCollisionCallback;
  };

  using SharedCollider2D = SPtrShared<Collider2D>;
  using WeakCollider2D = SPtrWeak<Collider2D>;
  using CollideVector = std::vector<SPtrShared<Collider2D>>;

}

#endif // SFEngine_Collider_H
