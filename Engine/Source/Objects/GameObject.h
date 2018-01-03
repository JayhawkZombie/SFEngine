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
#include "Time/RealTimeClock.h"

#include <atomic>

/*
 *  Basic interface for in-game object
 *  
 *  PlayerActors, static geometry, particle systems, etc
 *    all derive from this base class
 **/

class GameObject : public BaseEngineInterface
{
public:
  TYPEDEF_PARENT_CLASS(BaseEngineInterface);

  GameObject() = default;
  virtual ~GameObject() override;

  virtual std::shared_ptr<BaseEngineInterface> Clone() const override;
  virtual void TickUpdate(const double &delta) override;
  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  virtual void OnShutDown() override;
  virtual void SerializeIn(std::ifstream &in) override;
  virtual void SerializeOut(std::ofstream &out) override;

  virtual std::string GetClass() const override;

  virtual void ScriptInit();
  bool IsScriptReady();

  virtual void BeginPlay();
  virtual void EndPlay();
  virtual void Kill();

  bool CanBeSpawned();

  sf::Vector2f GetPosition() const;
  sf::Vector2f GetSize() const;
  sf::Vector2f GetVelocity() const;
  sf::Vector2f GetAcceleration() const;

  double GetTimeSinceSpawned();
  double GetTimeSinceCreated();

  void SetTickInterval(double TickInterval);
  double GetTickInterval() const;

  /*
   *  In-game event methods
   **/
  
  /* Whether or not this object can take any form of damage */
  bool bCanTakeDamage         = false;

  /* Whether or not this object can inflict any form of damage */
  bool bCanInflictDamage      = false;

  /* Whether or not this object can be killed in-game */
  bool bCanBeKilled           = true;

  /* Whether or not this object can be moved in-game */
  bool bCanBeMoved            = true;

  /* Whether or not this object can act as a player-controllable object */
  bool bCanBeControlled       = false;

  /* Whether or not this object can accept any input */
  bool bCanAcceptInput        = false;

  /* Whether or not this object should continue to update even when the game is paused */
  bool bCanUpdateWhilePaused  = false;

  /* Whether or not this object will issue and respond to hits */
  bool bWillRespondToHits     = true;

  /* Whether or not this object will issue and respond to overlap events */
  bool bWillRespondToOverlaps = true;

  /* Whether or not this object can active trigger objects */
  bool bCanActivateTriggers   = true;

  /*
   *  Methods that can be called in-game to change a generic object
   *  
   *  These WILL have side effects and will alter the in-game appearance of the object
   **/

  /* Teleport object to any point in space */
  void TeleportTo(const sf::Vector2f &NewPosition);

  /* Set object to frozen/not frozen (will not tick while frozen) */
  void SetFrozen(bool IsFrozen);

  /* Kill the object AND trigger its death sequence */
  void KillWithDeathSequence();

  /* Kill the object now and do NOT trigger its death sequence */
  void ForceKill();

  /* Uniformly scale the object */
  void Scale(const sf::Vector2f &ScaleFactors);

  /* Immediately begin applying an animation to this object */
  void Animate(const std::string &AnimationName);
  
  /*
   *  Event Handlers - used for invoking behavior from inputs
   *  
   *  Could be user input events or in-game "events"
   **/

  /* Called when the left mouse is initially pressed */
  virtual void OnLeftMousePress();

  /* Called when the right mouse is initially pressed */
  virtual void OnRightMousePress();

  /* Called when the left mouse is initially released */
  virtual void OnLeftMouseRelease();

  /* Called when the right mouse is initially released */
  virtual void OnRightMouseRelease();

  /* Called every tick while the left mouse is being held down */
  virtual void OnContinuedLeftMousePress();

  /* Called every tick while the right mouse is being held down */
  virtual void OnContinuedRightMousePress();

  /* Called when a key is initially pressed */
  virtual void OnKeyPressed(sf::Keyboard::Key key);

  /* Called when a key is initially released */
  virtual void OnKeyReleased(sf::Keyboard::Key key);

  /* Called every tick while a key is being held */
  virtual void OnKeyHeld(sf::Keyboard::Key key);

  /* Called when a combination of keys is pressed */
  virtual void OnKeyComboPressed(const std::vector<sf::Keyboard::Key> &keys);

  /* Called when a combination of keys (that was previously pressed) is released */
  virtual void OnKeyComboReleased(const std::vector<sf::Keyboard::Key> &keys);

  /* Called when a combination of keys is held (after initially being pressed) */
  virtual void OnKeyComboHeld(const std::vector<sf::Keyboard::Key> &keys);

  /* In-game events (not initiated by a user) */

  /* Called when an animation begins */
  virtual void OnAnimationBegin(const std::string &AnimationName);

  /* Called when the animation is finished */
  virtual void OnAnimationCompleted(const std::string &AnimationName);

  /* Called when "OverlappingObject" initially begins to overlap this object */
  virtual void OnBeginOverlap(GameObject *OverlappingObject);

  /* Called every tick that the overlapping objects continue to overlap */
  virtual void OnContinuedOverlap(GameObject *OverlappingObject);

  /* Called immediately after the objects stop overlapping */
  virtual void OnEndOverlap(GameObject *OverlappingObject);

  /* Called when one object is "hit" by another
   *  
   * Hits cannot cause an overlap - they can (and often do) cause
   * an impulse that makes both objects change movement
   * (think throwing a object at a wall - they won't overlap
   *  but will "smack" and the object thrown will bounce off)
   * */
  virtual void OnHit(GameObject *Object);
  
  /* Called when an object hits another but only when that collision
   * is the result of an impulse from an initial hit
   * */
  virtual void OnHitSecondary(GameObject *Object);

  /*
   *  Cause the game object to emit an object
   **/
  void EmitSound(const std::string &SoundName);
  

  /*
   *  Physics-related methods
   *  
   *  Will alter the data used by the physics engine
   *  and will alter how the object is represented for collision tests
   **/
  bool HasAssociatedCollider();
  

  enum class EObjectColliderTypes
  {
    Box,
    Circle,
    NGon,
    None
  };

  /* Disable collision testing with associated collider (the collider
   * will not be destroyed and collision testing can be enabled again later
   **/
  void DisableCollider();
  
  /* Tell the collider to sleep - it will be woken up when another
   * object hits it (it will not wake up if it "wanders" into another object
   **/
  void SleepCollider();
  
  /* Wake the collider from a sleeping state */
  void WakeCollider();


  /* Describes how selective to be when checking if this object should be 
   * used for certain collision tests
   **/
  enum class EObjectColliderResponseSelectivity
  {
    PlayerOnly,
    DynamicObjectsOnly,
    NonPlayerObjectsOnly,
    AllObjects,
    NoObjects
  };
  EObjectColliderResponseSelectivity GetColliderResponseSelectivity() const;
  void SetColliderResponseSelectivity(EObjectColliderResponseSelectivity Selectivity);

  /* Reset the associated collider (if it exists)
   * Can be used in the case of a simulation blowing up to try to stabilize it
   **/
  void ResetCollider();

  /* Freeze the collider so it cannot move (it will still interact with other colliders if it 
   * was enabled to do so). The game object will be prevented from moving during this time 
   **/
  void FreezeCollider();

  /* Unfreeze the colliders (no effect if collider was not frozen) */
  void UnfreezeCollider();

protected:

  EObjectColliderResponseSelectivity m_ColliderSelectivity = EObjectColliderResponseSelectivity::NoObjects;

  bool m_IsFrozen = false;
  bool m_HasSetLifetime = false;
  double m_SetLifetime = -1.0;

  bool m_ShouldTickEveryFrame = false;
  double m_TickInterval = -1.0;

  std::atomic_bool m_HasInitializedScripts = false;
  std::atomic_bool m_IsReadyToSpawn = false;

  sf::Vector2f m_Position;
  sf::Vector2f m_Size;
  sf::Vector2f m_Velocity;
  sf::Vector2f m_Acceleration;

  TimePoint m_TimeWhenCreated;
  TimePoint m_TimeWhenSpawned;
};

struct GameObjectHandle
{

};
