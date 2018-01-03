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

#include "Engine/stdafx.h"
#include "Objects/TriggerObject.h"
#include "Physics/Collider.h"

TriggerObject::TriggerObject(TriggerMethod Method)
  : m_TriggerMethod(Method)
{
}

TriggerObject::TriggerObject(
  TriggerMethod Method, 
  bool NotifyEveryFrame, 
  bool RestrictedTriggering, 
  std::function<void(void)> TriggerCB, 
  std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB,
  bool DoTriggerCheck
)
  : m_TriggerMethod(Method), m_NotifyEveryFrame(NotifyEveryFrame), m_RestrictedTriggering(RestrictedTriggering),
  m_TriggerCallback(TriggerCB), m_TriggerCheckCallback(TriggerCheckCB), m_DoTriggerCheck(DoTriggerCheck)
{
}

TriggerObject::~TriggerObject()
{
  m_Collider.reset();
}

TriggerObject::TriggerObject(const TriggerObject &)
{
}

void TriggerObject::Enable(bool MakeDefault)
{
  m_Enabled = true;
  if (MakeDefault)
    m_DefaultEnabled = true;
}

void TriggerObject::Disable(bool MakeDefault)
{
  m_Enabled = false;
  if (MakeDefault)
    m_DefaultEnabled = false;
}

void TriggerObject::Reset()
{
  m_Enabled              = m_DefaultEnabled;
  m_MinimumOverlap       = m_DefaultMinimumOverlap;
  m_NotifyEveryFrame     = m_DefaultNotifyEveryFrame;
  m_RestrictedTriggering = m_DefaultRestrictedTriggering;
  m_RestrictedTriggerIDs = m_DefaultRestrictedTriggerIDs;
  m_TriggerCallback      = m_DefaultTriggerCallback;
  m_TriggerCheckCallback = m_DefaultTriggerCheckCallback;
  m_DoPhysicalResponse   = m_DefaultDoPhysicalResponse;
}

void TriggerObject::SetCollider(std::shared_ptr<Collider2D> Collider)
{
  m_Collider = Collider;
}

void TriggerObject::SetTriggerMethod(TriggerMethod Method, bool MakeDefault)
{
  m_TriggerMethod = Method;
  if (MakeDefault)
    m_DefaultTriggerMethod = Method;
}

void TriggerObject::SetMinimumOverlap(const sf::Vector2f & Overlap, bool MakeDefault)
{
  m_MinimumOverlap = Overlap;
  if (MakeDefault)
    m_DefaultMinimumOverlap = Overlap;
}

void TriggerObject::SetNotifyEveryFrame(bool Notify, bool MakeDefault)
{
  m_NotifyEveryFrame = Notify;
  if (MakeDefault)
    m_DefaultNotifyEveryFrame = Notify;
}

void TriggerObject::SetRestrictedTriggerIDs(const std::vector<std::string>& IDs, bool MakeDefault)
{
  m_RestrictedTriggerIDs = IDs;
  m_RestrictedTriggering = true;

  if (MakeDefault) {
    m_DefaultRestrictedTriggering = true;
    m_DefaultRestrictedTriggerIDs = IDs;
  }
}
  
void TriggerObject::SetDefaults(TriggerMethod Method, bool NotifyEveryFrame, bool RestrictedTriggering, bool Sleeping, std::function<void(void)> TriggerCB, std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB)
{
  m_DefaultTriggerMethod        = Method;
  m_DefaultNotifyEveryFrame     = NotifyEveryFrame;
  m_DefaultRestrictedTriggering = RestrictedTriggering;
  m_DefaultTriggerCallback      = TriggerCB;
  m_DefaultTriggerCheckCallback = TriggerCheckCB;
  m_DefaultSleeping             = Sleeping;
}

void TriggerObject::EnablePhysicalResponse(bool MakeDefault)
{
  m_DoPhysicalResponse = true;
  if (MakeDefault)
    m_DefaultDoPhysicalResponse = true;
}

void TriggerObject::DisablePhysicalResponse(bool MakeDefault)
{
  m_DoPhysicalResponse = false;
  if (MakeDefault)
    m_DefaultDoPhysicalResponse = false;
}

void TriggerObject::SetTriggerCallback(std::function<void(void)> Callback, bool MakeDefault)
{
  m_TriggerCallback = Callback;
  if (MakeDefault)
    m_DefaultTriggerCallback = Callback;
}

void TriggerObject::SetTriggerCheckCallback(std::function<bool(std::shared_ptr<LevelObject>)> Callback, bool MakeDefault)
{
  m_TriggerCheckCallback = Callback;
  if (MakeDefault)
    m_DefaultTriggerCheckCallback = Callback;
}

std::string TriggerObject::GetClass() const
{
  return std::string("TriggerObject");
}

void TriggerObject::DoUnrestrictedTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> &Objects)
{
  for (auto & obj : Objects) {
    if ( /* Ensure we haven't already cached this object */
        std::find(m_CollidingCache.begin(), m_CollidingCache.end(), obj.second) == m_CollidingCache.end())
      CheckForTrigger(obj.second);
  }
}

void TriggerObject::DoRestrictedTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> &Objects)
{
  for (auto & obj : Objects) {
    if (/* Ensure we are allowed to be triggered by this */
        std::find(m_RestrictedTriggerIDs.begin(), m_RestrictedTriggerIDs.end(), obj.first) != m_RestrictedTriggerIDs.end() &&
        /*Ensure we haven't already cached this object*/
        std::find(m_CollidingCache.begin(), m_CollidingCache.end(), obj.second) == m_CollidingCache.end() )
      CheckForTrigger(obj.second);
  }
}

bool TriggerObject::DidTrigger(std::shared_ptr<Collider2D> Collider)
{
  auto mesh    = Collider->GetMesh().lock();
  auto my_mesh = m_Collider->GetMesh().lock();

  return (my_mesh && mesh && my_mesh->hit(*mesh));
}

void TriggerObject::CheckForTrigger(std::shared_ptr<LevelObject> Object)
{
  auto colliders = Object->GetColliders();

  if (colliders.size() > 0) {
    for (auto & mesh : colliders)

      //If we have a registered TriggerCheck callback, we must call it to see if we are
      //  supposed to allow triggers by this object
      if (m_DoTriggerCheck) {
        if (m_TriggerCheckCallback(Object) && DidTrigger(mesh)) {

          //If we aren't supposed to notify every frame 
          //  AND we haven't already cached this object (first time we have collided with it)
          //then we can trigger the notification
          if (!m_NotifyEveryFrame && (m_CollidingCache.find(Object) != m_CollidingCache.end())) {
            m_TriggerCallback();
          }
          else if (m_NotifyEveryFrame)
            m_TriggerCallback();
            
          //Now cache this object so we can remember it
          m_CollidingCache.insert(Object);
        }
      } //if m_TriggerCheckCallback

    /** Here, then we don't have to check with a registered function 
      *   to check if the object is allowed to trigger us
      * If we did get triggered by the object's collider, 
      *  invoke the trigger callback
      */
    else if (DidTrigger(mesh)) {
      m_TriggerCallback();
      return;
    } //if mesh && DidTrigger(mesh)

  } //if colliders.size() > 0
}

void TriggerObject::CheckCachedObjects()
{
  for (auto & cached : m_CollidingCache) {
    auto colliders = cached->GetColliders();

    //Track if we *could have been* triggered by this object 
    //   (still = true if m_NotifyEveryFrame == false
    //    && we don't actually invoke the callback) 
    //       - we only care about a collision with one or more of the
    //         object's colliders
    bool Triggered = false;

    for (auto & mesh : colliders) {
      auto obj_mesh = mesh->GetMesh().lock();
      auto my_mesh = m_Collider->GetMesh().lock();

      //If we were hit by this mesh, check to see if we are supposed to be notifying every frame
      if (obj_mesh && my_mesh && my_mesh->hit(*obj_mesh)) {
        Triggered = true;

        //If we are, invoke the callback, otherwise don't
        if (m_NotifyEveryFrame) {
          m_TriggerCallback();
          break;
        }
      } //if (obj_mesh && my_mesh && my_mesh->hit(*obj_mesh))
    } //for auto & mesh : colliders

    //If there was no hit by this object, we should remove it from the cache
    if (!Triggered) {
      m_CollidingCache.erase(cached);
    }
  }
}

std::shared_ptr<TriggerObject> TriggerObject::Clone() const
{
  try
  {
    auto Trigger = std::make_shared<TriggerObject>(*this);

    return Trigger;
  }
  catch (EngineRuntimeError& e)
  {
    e.AddCause(ExceptionCause::ConstructionError);
    e.AddMessage(EXCEPTION_MESSAGE("Unable to construct copy of TriggerObject"));

    throw;
  }
}

void TriggerObject::TickUpdate(const double & TickDelta)
{
  if (!m_Enabled)
    return;

  if (m_Sleeping) {
    m_CurrentSleepingDuration += TickDelta;

    if (m_CurrentSleepingDuration >= m_SleepingDuration) {
      Wake();
      return;
    } //if m_CurrentSleepingDuration >= m_SleepingDuration
    else
      return;
  } //if m_Sleeping
  else {

  }
}

void TriggerObject::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  auto mesh = m_Collider->GetMesh().lock();

  if (mesh) {
    mesh->draw(*Target);
  }
}

void TriggerObject::DoTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> & Objects)
{
  if (!m_TriggerCallback || m_Sleeping || !m_Enabled)
    return;

  if (m_CollidingCache.size() > 0)
    CheckCachedObjects();

  if (m_RestrictedTriggering)
    DoRestrictedTriggerChecks(Objects);
  else
    DoUnrestrictedTriggerChecks(Objects);
}

void TriggerObject::Cleanup()
{
  if (m_Collider)
    m_Collider.reset();
}

void TriggerObject::Sleep(bool MakeDefault)
{
  /**
    * Set us to sleep for max double time
    * 
    * @todo: revise, can see problems with high sleeping times 
    *         & never being able to wake
    */
  m_Sleeping = true;
  m_SleepingDuration = std::numeric_limits<double>::max();

  if (MakeDefault)
    m_DefaultSleeping = true;
}

void TriggerObject::Wake()
{
  m_Sleeping = false;
  m_CurrentSleepingDuration = 0.0;
  m_Enabled = true;
}

void TriggerObject::SleepFor(double Ms)
{
  /**
    * @todo: revise, can see problems with high sleeping times 
    *         & never being able to wake
    */
  m_Sleeping = true;
  m_SleepingDuration = Ms;
}
