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
#include "Actors\Actor.h"
#include "Exceptions\Exceptions.hpp"

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
/*                                                                      */
/************************************************************************/

namespace SFEngine
{

  SPtrShared<GenericActor> GenericActor::Create()
  {
    try
    {
      SPtrShared<GenericActor> Actor = std::make_shared<GenericActor>();

      return Actor;
    }
    catch (EngineRuntimeError& e)
    {
    	
    }
  }

  GenericActor::GenericActor()
  {

  }

  GenericActor::~GenericActor()
  {

  }

  /************************************************************************/
  /* Required overrides                                                   */
  /************************************************************************/
  void GenericActor::TickUpdate(const SFLOAT &delta)
  {

  }

  void GenericActor::Render(SharedRTexture Target)
  {

  }

  void GenericActor::OnShutDown()
  {

  }

  void GenericActor::SerializeOut(SOFStream &out)
  {

  }

  void GenericActor::SerializeIn(SIFStream &in)
  {

  }

  void GenericActor::SetCollisionHandleCallback(std::function<void(GameObject *)> Callback)
  {

  }

  void GenericActor::HandleCollisionWithSegment(SegmentMesh *Segment) 
  { 
  
  }

  void GenericActor::SetSegmentCollisionCallback(std::function<void(SegmentMesh*)> Callback) 
  {
  
  }

  void GenericActor::HandleCollisionWithCollider(SPtrShared<Collider2D> Collider)
  {

  }

  void GenericActor::HandleCollisionWithObject(GameObject *Object)
  {

  }

  void GenericActor::HandleInputEvent(const UserEvent &evnt)
  {

  }

  bool GenericActor::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }

  /************************************************************************/
  /* Level "Event" Methods                                                */
  /************************************************************************/
  void GenericActor::OnGameStart()  { }
  void GenericActor::OnGameEnd()  { }
  void GenericActor::OnKilled()  { }
  void GenericActor::OnSpawn()  { }
  void GenericActor::Reset()  { }
  void GenericActor::Freeze()  { }
  void GenericActor::Unfreeze()  { }

  /************************************************************************/
  /* Collision handling methods                                           */
  /************************************************************************/


  /************************************************************************/
  /* Custom update methods                                                */
  /************************************************************************/
  void GenericActor::PhysicsUpdate()  { }
  void GenericActor::ScriptUpdate()  { }

  /************************************************************************/
  /* Setters                                                              */
  /************************************************************************/
  void GenericActor::SetPosition(const SVector2F &pos)  { }
  void GenericActor::SetSize(const SVector2F &size)  { }
  void GenericActor::SetTexture(SharedTexture mytexture)  { }
  void GenericActor::SetTextureRect(SINTRECT myRect)  { }

  /************************************************************************/
  /* Manipulators                                                         */
  /************************************************************************/
  void GenericActor::Move(const SVector2F &delta)  { }
  void GenericActor::Move(SFLOAT x, SFLOAT y)  { }
  void GenericActor::Move(INT32 x, INT32 y)  { }
  void GenericActor::MoveObject(const SVector2F &delta)  { }
  void GenericActor::AddCollider(SharedCollider2D Collider)  { }

} // namespace SFEngine
