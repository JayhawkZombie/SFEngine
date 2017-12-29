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

#include "ThirdParty/PhysicsEngine.h"

#include <functional>
#include <bitset>

namespace Engine
{

  enum class MeshType : std::uint32_t
  {
    Base,
    Ball,
    BallGo,
    Polygon,
    Block,
    ExpandPolygon
  };

  enum ColliderProp : std::uint32_t
  {
    Active               = 0,
    Sleeping             = 1,
    Enabled              = 2,
    CanBeAwoken          = 3,
    HasPhysicalResponse  = 4,
    NotifyEveryFrame     = 5,
    SingleResponsePerObj = 6,
    NotifyOfOverlap      = 7,
    CastShadows          = 8,
    NotifyOnTouch        = 9,
    Static               = 10
  };

  class LevelObject;
  class Occluder2D;

  class Collider2D
  {
  public:
    Collider2D();
    Collider2D(const Collider2D &Copy) = delete;
    ~Collider2D();

    std::shared_ptr<Collider2D> Clone();

    void SetMesh(std::shared_ptr<PhysicsEngineBaseMeshType> MeshPtr);
    sf::FloatRect GetGlobalBounds() const;

    static std::shared_ptr<Collider2D> CreateCircularMesh
    (
      MeshType type,
      const sf::Vector2f &position,
      const sf::Vector2f &velocity,
      unsigned int radius,
      float mass,
      float coeffOfRest,
      sf::Color color = sf::Color::Transparent
    );

    static std::shared_ptr<Collider2D> CreatePolygonMesh
    (
      unsigned int num_sides,
      float radius,
      float init_rotation,
      const sf::Vector2f & InitialPosition,
      const sf::Vector2f & InitialVelocity,
      float mass,
      float CoeffOfRest,
      sf::Color color = sf::Color::Transparent,
      bool CastShadows = false
    );

    static std::shared_ptr<Collider2D> CreateBlockMesh
    (
      float Width,
      float Height,
      float IAngle,
      const sf::Vector2f &Position,
      const sf::Vector2f &Velocity,
      float Mass,
      float CoeffOfRest,
      sf::Color Color = sf::Color::Transparent
    );

    static std::shared_ptr<Collider2D> CreateExpandingMesh
    (
      unsigned int numSides,
      float radiusWhenFull,
      float IAngle,
      const sf::Vector2f &InitialPosition,
      const sf::Vector2f &InitialVelocity,
      float Mass,
      float CoeffOfRest,
      float GrowSpeed,
      sf::Color Color
    );

    void SetCollisionCallback(std::function<void(LevelObject*)> Callback, bool NotifyEveryFrame = true);
    void SetSegmentCallback(std::function<void(PhysicsEngineSegmentType *)> Callback);
    void SetPositionChangeCallback(std::function<void(sf::Vector2f delta)> Callback);
    void SetSleepCallback(std::function<void(void)> Callback);
    void SetAwakenCallback(std::function<void(void)> Callback);
    void SetOverlapCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback);
    void SetTouchCallback(std::function<void(LevelObject*)> Callback);
    void SetColliderStatus(ColliderProp Status);

    void Update(const ::vec2d &gravity);

    void Sleep();
    void Awaken();
    void EnableCollisions();
    void DisableCollision();
    void Makestatic();
    void MakeNonstatic();

    bool IsAwake() const;
    bool IsEnabled() const;
    bool HasPhyicalResponse() const;
    bool NotifyOnTouch() const;
    bool IsActive() const;
    bool DoesCastShadows() const;
    bool IsStatic() const;

    void Move(const sf::Vector2f &Delta);
    void SetPosition(const sf::Vector2f &Position);
    void SetRespondsToOverlaps(bool b);
    void SetNotifyOnTouch(bool b);

    sf::Vector2f GetPosition() const;

    bool HandleCollision(std::weak_ptr<Collider2D> Collider);
    bool HandleCollision(std::weak_ptr<Occluder2D> Occluder);
    bool HandleCollisionWithSegment(PhysicsEngineSegmentType* Collider);
    bool HandleTouch(std::weak_ptr<Collider2D> Collider);

    std::vector<::vec2d> GetVertices();

    std::weak_ptr<PhysicsEngineBaseMeshType> GetMesh();
    void SetObjectPtr(LevelObject *Object);
    LevelObject* GetObjectPtr() const;
    void PhysicsUpdate();

  protected:
    std::shared_ptr<PhysicsEngineBaseMeshType> m_Mesh;
    bool m_NotifyOfCollisionEveryFrame = true; //If true, a notification will be issues every frame two objects are overlapping
    std::bitset<32> m_Status;
    LevelObject *m_MyObject;
    std::function<void(LevelObject*)> m_CollisionCallback;
    std::function<void(LevelObject*)> m_TouchCallback;
    std::function<void(PhysicsEngineSegmentType *)> m_HitSegmentCallback;
    std::function<void(std::weak_ptr<Collider2D>)> m_OverlapCallback;
    std::function<void(sf::Vector2f)> m_PositionChangeCallback;
    std::function<void(void)> m_SleepCallback;
    std::function<void(void)> m_AwakenCallback;
  };

}
