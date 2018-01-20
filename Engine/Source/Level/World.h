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

#include "Engine/BaseEngineInterface.h"

#include <Box2D/Box2D.h>

struct WorldCollisionCacheData
{
  b2Fixture *FixtureA;
  b2Fixture *FixtureB;
};

class WorldCollisionCache
{
public:

  void AddBeginContact(b2Contact *Contact);
  void AddEndContact(b2Contact *Contact);
  void Clear();

private:

  std::deque<WorldCollisionCacheData> m_EndOverlapCache;
  std::deque<WorldCollisionCacheData> m_BeginOverlapCache;

};

class WorldCollisionListener : public b2ContactListener
{
public:
  WorldCollisionListener(WorldCollisionCache &Cache);
  ~WorldCollisionListener();

  void BeginContact(b2Contact* contact) override;
  void EndContact(b2Contact* contact) override;
  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:

  WorldCollisionCache & m_Cache;

};



class World : public BaseEngineInterface
{
public:
  TYPEDEF_PARENT_CLASS(BaseEngineInterface);

  World();
  ~World();

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override {}

  std::string GetClass() const override { return std::string("World"); }

protected:

  b2World m_B2World;
  b2Vec2 m_Gravity;

  /* Serialization */

public:

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(cereal::base_class<Super>(this));
    ar(m_Gravity);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(cereal::base_class<Super>(this));
    ar(m_Gravity);
  }

};
