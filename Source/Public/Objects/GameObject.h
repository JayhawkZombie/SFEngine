#ifndef SFEngine_GameObject_H
#define SFEngine_GameObject_H

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
#include "Engine\BaseEngineInterface.h"
#include "Physics\Collider.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include "DependencyInterface.h"
#include <Thor\Animations.hpp>
#include <Thor\Particles.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                         GameObject                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  class GameObject : public BaseEngineInterface
  {
  public:
    GameObject();
    virtual ~GameObject() override;
    static SPtrShared<GameObject> Create();

    virtual void ScriptInit();

    /************************************************************************/
    /* Required overrides                                                   */
    /************************************************************************/
    virtual SPtrShared<BaseEngineInterface> Clone() const override;
    virtual void TickUpdate(const SFLOAT &delta) override;
    virtual void Render(SharedRTexture Target) override;
    virtual void SerializeOut(SOFStream &out) override;
    virtual void SerializeIn(SIFStream &in) override;
    virtual SString GetClass() const override;
    virtual void SetID(const SString &ID) override;
    virtual void OnShutDown() override;

    /************************************************************************/
    /* Level "Event" Methods                                                */
    /************************************************************************/
    virtual void OnGameStart();
    virtual void OnGameEnd();
    virtual void OnKilled();
    virtual void OnSpawn();
    virtual void Reset();
    virtual void Freeze();
    virtual void Unfreeze();

    /************************************************************************/
    /* Collision handling methods                                           */
    /************************************************************************/
    virtual void HandleCollisionWithObject(GameObject *Object);
    virtual void HandleCollisionWithSegment(SegmentMesh *Segment);
    virtual void HandleCollisionWithCollider(SPtrShared<Collider2D> Collider);
    virtual void SetCollisionHandleCallback(std::function<void(GameObject*)> Callback);
    virtual void SetSegmentCollisionCallback(std::function<void(SegmentMesh*)> Callback);

    /************************************************************************/
    /* Custom update methods                                                */
    /************************************************************************/
    virtual void PhysicsUpdate();
    virtual void ScriptUpdate();

    /************************************************************************/
    /* Getters                                                              */
    /************************************************************************/
    SharedTexture GetTexture()      const;
    SVector2F     GetSize()         const;
    SINTRECT      GetTextureRect()  const;
    SFLOATRECT    GetGlobalBounds() const;
    bool          IsFrozen()        const;
    STDVector<SharedCollider2D> GetColliders() const;

    /************************************************************************/
    /* Setters                                                              */
    /************************************************************************/
    virtual void SetPosition(const SVector2F &pos);
    virtual void SetSize(const SVector2F &size);
    virtual void SetTexture(SharedTexture mytexture);
    virtual void SetTextureRect(SINTRECT myRect);

    /************************************************************************/
    /* Manipulators                                                         */
    /************************************************************************/
    virtual void Move(const SVector2F &delta);
    virtual void Move(SFLOAT x, SFLOAT y);
    virtual void Move(INT32 x, INT32 y);
    virtual void MoveObject(const SVector2F &delta);
    virtual void AddCollider(SharedCollider2D Collider);

  protected:
    /************************************************************************/
    /* Instance Variables                                                   */
    /************************************************************************/
    bool m_Frozen = false;
    SVector2F m_Position = { 0.f, 0.f };
    SVector2F m_Size = { 0.f, 0.f };

    //Animation data
    thor::AnimationMap<SSprite, SString> m_AnimationMap;
    thor::Animator<SSprite, SString> m_Animator;
    STDUnorderedMap<SString, thor::FrameAnimation> m_FrameAnimations;

    //Physics data
    STDVector<SharedCollider2D> m_Colliders;
    std::function<void(GameObject *)> m_HandleCollisionWithObject;
    std::function<void(SegmentMesh*)> m_HandleSegmentWithSegment;

    //Graphical data
    SSprite m_Sprite;
    SharedTexture m_SpriteTexture;
    SINTRECT m_TextureRect;
  };

}

#endif // SFEngine_GameObject_H 
