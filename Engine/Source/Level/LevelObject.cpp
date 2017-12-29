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
#include "Actor\Actor.h"
#include "Physics\Collider.h"
#include "Physics\Occluder.h"

#include "chaiscript\chaiscript.hpp"

namespace Engine
{
  LevelObject::LevelObject()
    :
    m_Animator(m_AnimationMap)
  {
    
  }

  LevelObject::~LevelObject()
  {

  }
  


  LevelObject::LevelObject(const LevelObject & obj)
    : 
    m_Animator(m_AnimationMap),
    Position(obj.Position), 
    Size(obj.Size), 
    SpriteTexture(obj.SpriteTexture),
    Acceleration(obj.Acceleration), 
    AllowsActorOverlap(obj.AllowsActorOverlap),
    ObjectRect(obj.ObjectRect), 
    TextureRect(obj.TextureRect),
    RenderOutlined(obj.RenderOutlined), 
    Velocity(obj.Velocity),
    BaseEngineInterface()
  {
    
    for (auto & collider : obj.m_Colliders) {
      m_Colliders.push_back(collider->Clone());
    }

  }

  std::shared_ptr<BaseEngineInterface> LevelObject::Clone() const
  {
    auto Object = std::make_shared<LevelObject>(*this);

    for (auto & collider : m_Colliders) {
      Object->m_Colliders.push_back(collider->Clone());
    }

    return Object;
  }

  //Starting the chaiscript bindings, need to figure out which functions need scripted
  void LevelObject::BindScriptMethods(chaiscript::ModulePtr mptr)
  {
	  chaiscript::utility::add_class<Engine::LevelObject>(
		  *mptr,
		  "LevelObject",
		  { 
			  chaiscript::constructor<Engine::LevelObject()>() },
			  { 
          { chaiscript::fun(static_cast<void(LevelObject::*)(void)>(&LevelObject::OnKilled)), "OnKilled" },
          { chaiscript::fun(static_cast<void(LevelObject::*)(const sf::Vector2f &)>(&LevelObject::MoveObject)), "MoveObject" }
        }
	  );
  }

  void LevelObject::ScriptInit()
  {

  }

  void LevelObject::TickUpdate(const double &delta)
  {
    
  }

  void LevelObject::PhysicsUpdate()
  {
    if (m_IsFrozen)
      return;

    for (auto & collider : m_Colliders)
      collider->PhysicsUpdate();

	if (!(m_Colliders.size() > 0))
		return;

	  auto v = m_Colliders[0]->GetMesh().lock();
	  if (v) {
      Position = sf::Vector2f(v->pos.x, v->pos.y);
		  Sprite.setPosition({ v->pos.x - Size.x / 2.f, v->pos.y - Size.y / 2.f });
	  }
  }

  void LevelObject::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    Target->draw(Sprite);
  }

  void LevelObject::OnShutDown()
  {

  }

  void LevelObject::SerializeOut(std::ofstream &out)
  {

  }

  void LevelObject::SerializeIn(std::ifstream &in)
  {

  }

  void LevelObject::SetPosition(const sf::Vector2f &pos)
  {
    sf::Vector2f delta = Position - pos;
    Position = pos;
    Sprite.setPosition(Position);

    for (auto & collider : m_Colliders)
      collider->SetPosition(pos);
  }

	void LevelObject::SetSize(const sf::Vector2f & size)
	{
			Size = size;
	}

	void LevelObject::SetTexture(std::shared_ptr<sf::Texture> mytexture)
	{
			SpriteTexture = mytexture;
			Sprite.setTexture(*(SpriteTexture));
	}

  void LevelObject::SetTextureRect(sf::IntRect myRect)
  {
    Sprite.setTextureRect(myRect);
  }

  sf::Vector2i LevelObject::getTopRight() const
  {
	  return{ (int)Position.x + Sprite.getTextureRect().width, (int)Position.y };
  }

  sf::Vector2i LevelObject::getTopLeft() const
  {
	  return{(int)Position.x,(int)Position.y};
  }

  sf::Vector2i LevelObject::getBottomLeft() const
  {
	  return{ (int)Position.x,(int)Position.y + Sprite.getTextureRect().height };
  }

  sf::Vector2i LevelObject::getBottomRight() const
  {
	  return{ (int)Position.x + Sprite.getTextureRect().width,(int)Position.y + Sprite.getTextureRect().height };
  }

  std::shared_ptr<sf::Texture> LevelObject::GetTexture() const
  {
    return SpriteTexture;
  }

  sf::Vector2f LevelObject::GetSize() const
  {
    return Size;
  }

  sf::IntRect LevelObject::GetTextureRect() const
  {
    return TextureRect;
  }

  void LevelObject::HandleCollisionWithObject(LevelObject * Object)
  {
    if (m_HandleCollisionWithObject)
      m_HandleCollisionWithObject(Object);
  }

  void LevelObject::SetCollisionHandleCallback(std::function<void(LevelObject*)> Callback)
  {
    m_HandleCollisionWithObject = Callback;
  }

  void LevelObject::HandleCollisionWithCollider(SPtrShared<Collider2D> Collider)
  {
  }

  void LevelObject::HandleCollisionWithSegment(PhysicsEngineSegmentType *Segment)
  {
    if (m_HandleSegmentWithSegment)
      m_HandleSegmentWithSegment(Segment);

    //auto pos = Segment->pos;
    //auto diff = Position - sf::Vector2f(pos.x, pos.y);

    //sf::Vector2f move = { 0, 0 };
    //
    //auto right = Position.x + Size.x;
    //auto top = Position.y + Size.y;
    //
    ////If the distance from our right to the segment is less than our size
    //// we need to be pushed back a bit
    //// 
    ////Case for when we aproach from the left
    //if (Position.x <= pos.x && right > pos.x)
    //  move.x = 1.2f * (pos.x - Position.x);
    //else if (pos.x <= right && Position.x < pos.x)
    //  move.x = 1.2f * (right - pos.x);

    //if (pos.y >= Position.y && top > pos.y)
    //  move.y = 1.2f * (pos.y - Position.y);
    //else if (top >= pos.y && Position.y <= pos.y)
    //  move.y = 1.2f * (top - pos.y);

    //MoveObject(move);
  }

  void LevelObject::SetSegmentCollisionCallback(std::function<void(PhysicsEngineSegmentType*)> Callback)
  {
    m_HandleSegmentWithSegment = Callback;
  }

  void LevelObject::HandleInputEvent(const UserEvent & evnt)
  {
  }

  void LevelObject::SetID(const std::string & ID)
  {
    BaseEngineInterface::SetID(ID);
  }

  void LevelObject::OnGameStart()
  {
  }

  void LevelObject::OnGameEnd()
  {
  }

  void LevelObject::OnKilled()
  {
  }

  void LevelObject::OnSpawn()
  {
  }

  void LevelObject::Reset()
  {
  }

  void LevelObject::Freeze()
  {
    m_IsFrozen = true;
  }

  void LevelObject::Unfreeze()
  {
    m_IsFrozen = false;
  }

  bool LevelObject::IsFrozen() const
  {
    return m_IsFrozen;
  }

  sf::FloatRect LevelObject::GetGlobalBounds() const
  {
	  return sf::FloatRect(
		  Position,
		  Size
	  );
  }

  void LevelObject::Move(const sf::Vector2f & delta)
  {
    for (auto & collider : m_Colliders)
      collider->Move(delta);
    for (auto & occluder : m_Occluders)
      occluder->Move(delta);
	  Position += delta;
    Sprite.move(delta);
  }

  void LevelObject::Move(float x, float y)
  {
    Move(sf::Vector2f(x, y));
  }

  void LevelObject::Move(int x, int y)
  {
    Move(sf::Vector2f((float)x, (float)y));
  }

  void LevelObject::MoveObject(const sf::Vector2f &delta)
  {
    Move(delta);
  }

  std::vector<std::shared_ptr<Collider2D>> LevelObject::GetColliders() const
  {
    std::vector<std::shared_ptr<Collider2D>> RetColls;
    for (auto & coll : m_Colliders) {
      if (coll->IsAwake() && coll->IsEnabled())
        RetColls.push_back(coll);
    }

    return RetColls;
  }

  void LevelObject::AddCollider(std::shared_ptr<Collider2D> Collider)
  {
    m_Colliders.push_back(Collider);
    m_Colliders.back()->SetObjectPtr(this);
  }

  std::vector<std::shared_ptr<Collider2D>> LevelObject::GetOccluders() const
  {
    static std::vector<std::shared_ptr<Collider2D>> _Occluders;
    _Occluders.clear();

    for (auto & collider : m_Colliders) {
      if (collider->DoesCastShadows())
        _Occluders.push_back(collider);
    }

    return _Occluders;
  }

  void LevelObject::AddOccluder(std::shared_ptr<Collider2D> Collider)
  {
    AddCollider(Collider);
  }

  void LevelObject::AddFrameAnimation(const std::string & ID, const std::vector<sf::IntRect>& Frames, sf::Time Duration)
  {
    m_FrameAnimations[ID] = {};
    for (auto & frame : Frames) {
      m_FrameAnimations[ID].addFrame(1.f, frame);
    }

    m_AnimationMap.addAnimation(ID, m_FrameAnimations[ID], Duration);
  }

}
