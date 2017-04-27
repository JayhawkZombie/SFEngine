#ifndef SFEngine_Actor_H
#define SFEngine_Actor_H

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
#include "Objects\GameObject.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                              Actor                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

namespace SFEngine
{

  class GenericActor : public GameObject
  {
  public:
    GenericActor();
    static SPtrShared<GenericActor> Create();
    virtual ~GenericActor() override;

    /************************************************************************/
    /* Required overrides                                                   */
    /************************************************************************/
    virtual void TickUpdate(const SFLOAT &delta) override;
    virtual void Render(SharedRTexture Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(SOFStream &out) override;
    virtual void SerializeIn(SIFStream &in) override;
    virtual void SetSegmentCollisionCallback(std::function<void(SegmentMesh*)> Callback) override;
    virtual void SetCollisionHandleCallback(std::function<void(GameObject *)> Callback) override;
    virtual void HandleCollisionWithCollider(SPtrShared<Collider2D> Collider) override;
    virtual void HandleCollisionWithObject(GameObject *Object) override;
    virtual void HandleCollisionWithSegment(SegmentMesh *Segment) override;
    virtual void HandleInputEvent(const UserEvent &evnt) override;
    virtual bool WantsInputEvent(const Events &evnt) const;


    /************************************************************************/
    /* Level "Event" Methods                                                */
    /************************************************************************/
    virtual void OnGameStart() override;
    virtual void OnGameEnd() override;
    virtual void OnKilled() override;
    virtual void OnSpawn() override;
    virtual void Reset() override;
    virtual void Freeze() override;
    virtual void Unfreeze() override;

    /************************************************************************/
    /* Custom update methods                                                */
    /************************************************************************/
    virtual void PhysicsUpdate() override;
    virtual void ScriptUpdate() override;

    /************************************************************************/
    /* Setters                                                              */
    /************************************************************************/
    virtual void SetPosition(const SVector2F &pos) override;
    virtual void SetSize(const SVector2F &size) override;
    virtual void SetTexture(SharedTexture mytexture) override;
    virtual void SetTextureRect(SINTRECT myRect) override;

    /************************************************************************/
    /* Manipulators                                                         */
    /************************************************************************/
    virtual void Move(const SVector2F &delta) override;
    virtual void Move(SFLOAT x, SFLOAT y) override;
    virtual void Move(INT32 x, INT32 y) override;
    virtual void MoveObject(const SVector2F &delta) override;
    virtual void AddCollider(SharedCollider2D Collider) override;

  protected:
  };

}

#endif // SFEngine_Actor_H 
