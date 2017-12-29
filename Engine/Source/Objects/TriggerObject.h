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

#include "BasicIncludes.h"
#include "Level\LevelObject.h"

class Collider2D;
class LevelObject;

enum class TriggerMethod
{
  Touch_PhysicalResponse = 0,
  Touch_NoPhysicalResponse,
  MinimumOverlap_NoPhysicalResponse
};

/**
  *  TriggerObject
  *
  *  This object is not visible (though the Collider component can be visualized)
  *  Trigger a specific callback when its TriggerCallback is satisfied
  */
class TriggerObject
{
public:
  TriggerObject(TriggerMethod Method);
  TriggerObject(TriggerMethod, bool NotifyEveryFrame, bool RestrictedTriggering,
                std::function<void(void)> TriggerCB,
                std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB,
                bool DoTriggerCheck = false);
  ~TriggerObject();

  //Forbid implicit copy construction and assignment definitions
  //We [MUST] use a clone method

  //Do we even want to be able to clone trigger objects?
  TriggerObject(const TriggerObject &);
  TriggerObject(const TriggerObject &&) = delete;
  TriggerObject() = delete;

  virtual std::shared_ptr<TriggerObject> Clone() const;

  void TickUpdate(const double & TickDelta);
  void Render(std::shared_ptr<sf::RenderTarget> Target);
  void DoTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> &Objects);
  void Cleanup();

  void Sleep(bool MakeDefault = false);
  void Wake();
  void SleepFor(double Ms);

  void Enable(bool MakeDefault = true);
  void Disable(bool MakeDefault = true);
  void Reset();
  void SetCollider(std::shared_ptr<Collider2D> Collider);

  void SetTriggerMethod(TriggerMethod Method, bool MakeDefault = true);
  void SetMinimumOverlap(const sf::Vector2f &Overlap, bool MakeDefault = true);
  void SetNotifyEveryFrame(bool Notify, bool MakeDefault = true);

  //Set the object ID's that we should allow to trigger us (if we are restricted)
  void SetRestrictedTriggerIDs(const std::vector<std::string> &IDs, bool MakeDefault = true);

  //Set the default values to which members are set to when calling "Reset"
  void SetDefaults(TriggerMethod, bool NotifyEveryFrame, bool RestrictedTriggering, bool Sleeping,
                    std::function<void(void)> TriggerCB,
                    std::function<bool(std::shared_ptr<LevelObject>)> TriggerCheckCB);

  //Enable hard physical responses - this will completely prevent overlaps
  void EnablePhysicalResponse(bool MakeDefault = true);

  //Disable hard physical responses - object may not completely overlap
  void DisablePhysicalResponse(bool MakeDefault = true);

  //Assign the function to be called when a successful trigger has occurred
  void SetTriggerCallback(std::function<void(void)> Callback, bool MakeDefault = true);

  //Assign the function to be called to check whether a collision with an object
  //  should allow us to trigger out action
  void SetTriggerCheckCallback(std::function<bool (std::shared_ptr<LevelObject>)> Callback, bool MakeDefault = true);

  virtual std::string GetClass() const;

protected:
  void DoUnrestrictedTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> &Objects);
  void DoRestrictedTriggerChecks(std::map<std::string, std::shared_ptr<LevelObject>> &Objects);

  bool DidTrigger(std::shared_ptr<Collider2D> Object);
  void CheckForTrigger(std::shared_ptr<LevelObject> Object);

  void CheckCachedObjects();
  //Remember what objects we are currently hitting so we can properly
  // ignore repeated collisions and not notify every frame unless necessary
  std::set<std::shared_ptr<LevelObject>> m_CollidingCache;

  std::shared_ptr<Collider2D> m_Collider;
  TriggerMethod               m_TriggerMethod;
  sf::Vector2f                m_MinimumOverlap = sf::Vector2f(0, 0);
  bool                        m_Enabled = true;
  bool                        m_DoPhysicalResponse = false;
  bool                        m_Sleeping = false;
  bool                        m_DoTriggerCheck = false;
  double                      m_SleepingDuration = 0.0;
  double                      m_CurrentSleepingDuration = 0.0;

  //The function to call to check if this object is allowed to interact with us
  std::function<bool(std::shared_ptr<LevelObject>)> m_TriggerCheckCallback = [](auto ptr) -> bool { return false; };

  //The function to call when we are interacted with
  std::function<void(void)>   m_TriggerCallback = []() {};

  //If we should initiate a response/notification every frame we are "triggered" by another object
  bool m_NotifyEveryFrame = false;

  //If we want to restrict which object can actually trigger this
  //  Here we assign specific object classes to be able to trigger us
  bool m_RestrictedTriggering = true;

  //Vector of strings that represent the IDs of the objects that are allowed to trigger us
  std::vector<std::string> m_RestrictedTriggerIDs;

  //Stuff for default state
  TriggerMethod            m_DefaultTriggerMethod;
  sf::Vector2f             m_DefaultMinimumOverlap;
  bool                     m_DefaultEnabled;
  bool                     m_DefaultNotifyEveryFrame;
  bool                     m_DefaultRestrictedTriggering;
  bool                     m_DefaultDoPhysicalResponse;
  bool                     m_DefaultSleeping;
  std::vector<std::string> m_DefaultRestrictedTriggerIDs;
  std::function<bool (std::shared_ptr<LevelObject>)>  m_DefaultTriggerCheckCallback;
  std::function<void (void)> m_DefaultTriggerCallback;
};
