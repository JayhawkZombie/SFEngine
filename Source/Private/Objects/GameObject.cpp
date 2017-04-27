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
#include "Objects\GameObject.h"
#include "Exceptions\Exceptions.hpp"
#include "Globals.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        GameObject                                    */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

namespace SFEngine
{
  GameObject::~GameObject()
  {
  }

  SPtrShared<GameObject> GameObject::Create()
  {
    try
    {
      SPtrShared<GameObject> Object = std::make_shared<GameObject>();
      return Object;
    }
    catch (EngineRuntimeError& e)
    {
      ERR << "Failed to create game object : " << e.what() << std::endl;
      return nullptr;
    }
  }

  void GameObject::ScriptInit()
  {
  }

  /************************************************************************/
  /* Required overrides                                                   */
  /************************************************************************/
  SPtrShared<BaseEngineInterface> GameObject::Clone() const
  {
    try
    {
      SPtrShared<GameObject> Object = std::make_shared<GameObject>();
      return Object;
    }
    catch (EngineRuntimeError& e)
    {
      ERR << "Failed to clone GameObject: " << e.what() << std::endl;
      return nullptr;
    }
  }

  void GameObject::TickUpdate(const SFLOAT &delta)
  {
    static sf::Clock _Clock;
    auto _time = _Clock.restart();

    m_Animator.update(_time);
    m_Animator.animate(m_Sprite);
  }

  void GameObject::Render(SharedRTexture Target)
  {
    Target->draw(m_Sprite);
  }

  void GameObject::SerializeOut(SOFStream &out)
  {

  }

  void GameObject::SerializeIn(SIFStream &in)
  {

  }

  SString GameObject::GetClass() const
  {
    return SString("GameObject");
  }

  void GameObject::SetID(const SString &ID)
  {
    ItemID = ID;
  }

  void GameObject::OnShutDown()
  {
  }

  /************************************************************************/
  /* Level "Event" Methods                                                */
  /************************************************************************/
  void GameObject::OnGameStart()
  {

  }

  void GameObject::OnGameEnd()
  {

  }

  void GameObject::OnKilled()
  {

  }

  void GameObject::OnSpawn()
  {

  }

  void GameObject::Reset()
  {

  }

  void GameObject::Freeze()
  {

  }

  void GameObject::Unfreeze()
  {

  }

  /************************************************************************/
  /* Collision handling methods                                           */
  /************************************************************************/
  void GameObject::HandleCollisionWithObject(GameObject *Object)
  {

  }

  void GameObject::HandleCollisionWithSegment(SegmentMesh *Segment)
  {

  }

  void GameObject::HandleCollisionWithCollider(SPtrShared<Collider2D> Collider)
  {

  }

  void GameObject::SetCollisionHandleCallback(std::function<void(GameObject*)> Callback)
  {

  }

  void GameObject::SetSegmentCollisionCallback(std::function<void(SegmentMesh*)> Callback)
  {

  }

  /************************************************************************/
  /* Custom update methods                                                */
  /************************************************************************/
  void GameObject::PhysicsUpdate()
  {

  }

  void GameObject::ScriptUpdate()
  {

  }

  /************************************************************************/
  /* Getters                                                              */
  /************************************************************************/
  SharedTexture GameObject::GetTexture() const
  {
    return m_SpriteTexture;
  }

  SVector2F GameObject::GetSize() const
  {
    return m_Size;
  }

  SINTRECT GameObject::GetTextureRect() const
  {
    return m_TextureRect;
  }

  SFLOATRECT GameObject::GetGlobalBounds() const
  {
    return SFLOATRECT(0, 0, 0, 0);
  }

  bool GameObject::IsFrozen() const
  {
    return m_Frozen;
  }

  STDVector<SharedCollider2D> GameObject::GetColliders() const
  {
    static STDVector<SharedCollider2D> Colliders;
    Colliders.clear();

    for (auto & collider : m_Colliders) {
      if (collider->IsActive())
        Colliders.push_back(collider);
    }

    return Colliders;
  }

  /************************************************************************/
  /* Setters                                                              */
  /************************************************************************/
  void GameObject::SetPosition(const SVector2F &pos)
  {
    m_Position = pos;
  }

  void GameObject::SetSize(const SVector2F &size)
  {
    m_Size = size;
  }

  void GameObject::SetTexture(SharedTexture mytexture)
  {
    m_SpriteTexture = mytexture;
  }

  void GameObject::SetTextureRect(SINTRECT myRect)
  {
    m_TextureRect = myRect;
  }

  /************************************************************************/
  /* Manipulators                                                         */
  /************************************************************************/
  void GameObject::Move(const SVector2F &delta)
  {
    MoveObject(delta);
  }

  void GameObject::Move(SFLOAT x, SFLOAT y)
  {
    Move(SVector2F(SF_TOFLOAT(x), SF_TOFLOAT(y)));
  }

  void GameObject::Move(INT32 x, INT32 y)
  {
    Move(SVector2F(SF_TOFLOAT(x), SF_TOFLOAT(y)));
  }

  void GameObject::MoveObject(const SVector2F &delta)
  {
    for (auto & collider : m_Colliders)
      collider->Move(delta);

    m_Sprite.move(delta);
  }

  void GameObject::AddCollider(SharedCollider2D Collider)
  {
    m_Colliders.emplace_back(Collider);
  }

  /************************************************************************/
  /* Private constructors                                                 */
  /************************************************************************/
  GameObject::GameObject()
    :
    m_Animator(m_AnimationMap),
    m_TextureRect(SINTRECT(0, 0, 0, 0)),
    BaseEngineInterface()
  {
    
  }

} // namespace SFEngine
