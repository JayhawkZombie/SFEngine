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
#include "Globals/GlobalHooks.h"
#include "Weather/WeatherSystem.h"
#include "Objects/TriggerObject.h"
#include "ThirdParty/PhysicsEngine.h"
#include "ThirdParty/SelbaWard/TileMap.hpp"
#include "Objects/GameObject.h"

#include <Box2D/Box2D.h>

class BasicLevel : public BaseEngineInterface
{
public:
  TYPEDEF_PARENT_CLASS(BaseEngineInterface);
  BasicLevel();

  //Oh gawd no please don't every try this
  BasicLevel(const BasicLevel &) = delete;
  BasicLevel(const BaseEngineInterface &Copy);
  BasicLevel& operator=(const BasicLevel &) = delete;
  BasicLevel(const sf::FloatRect &DefaultView);
  virtual ~BasicLevel();

  static std::shared_ptr<BasicLevel> DefaultEmptyLevel();

  virtual std::shared_ptr<BaseEngineInterface> Clone() const override;
  virtual void TickUpdate(const double &delta) override;

  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  virtual void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture);

  virtual void OnShutDown() override;

  virtual std::uint32_t GetInternalID() const override { return InternalID; }
  virtual void SetInternalD(const std::uint32_t &ID) override { InternalID = ID; }
  virtual void SerializeOut(std::ofstream &out);
  virtual void SerializeIn(std::ifstream &in);
  virtual void HandleInputEvent(const UserEvent &evnt) override;
  virtual void HandleKeyPress(const sf::Keyboard::Key &key);
  virtual void HandleKeyRelease(const sf::Keyboard::Key &key);
  virtual void HandleWindowResized();
  virtual void LoadLevel(const std::string &lvlfile);
  virtual void Init();
  virtual void OnBegin();
  virtual void OnEnd();
  virtual void HideUI();
  virtual void ShowUI();
  virtual void Reset();
  virtual void RequestLevelSwitch(const std::string &LevelName);
  virtual void SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position);
  virtual void SpawnObject(std::shared_ptr<GameObject> Object, const sf::Vector2f &Position);

  virtual bool SpawnAutoGeneratedObject(std::shared_ptr<GameObject> Object, std::string IDPrePend = "");
  
  virtual void CleanUp();
  virtual std::string GetClass() const override;

  b2Vec2 WorldGravity = b2Vec2(0.f, -10.f);
  b2World World;

  bool DoUpdatePhysics = true;
  float updateInterval = 16.667f;
  virtual void UpdateObjectPhysics();

  sf::FloatRect CurrentView;

  ::vec2d *Gravity;
  std::map<std::string, std::shared_ptr<GameObject>> m_GameObjects;
  std::map<std::string, std::shared_ptr<Triggerable>> m_TriggerObjects;
  WeatherSystem m_WeatherSystem;

  std::vector<SegmentPtr> Segments;
  std::vector<WaveSegmentPtr> Waves;
  std::map<std::string, std::shared_ptr<sf::Texture>> Textures;
  std::map<std::string, std::shared_ptr<Animation>> Animations;
  std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundBuffers;

  /*
   *  Save / Loading testing
   **/

  std::vector<std::shared_ptr<mvHit>> MVHits;
  std::vector<std::shared_ptr<lineSeg>> SegHits;

  void Save(const std::string &Filename);
  void Load(const std::string &Filename);

public:

  /* Serialization */

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(cereal::base_class<Super>(this));
    ar(DoUpdatePhysics, updateInterval);
    ar(CurrentView);
    
    ar(m_GameObjects);
    ar(m_TriggerObjects);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(cereal::base_class<Super>(this));
    ar(DoUpdatePhysics, updateInterval);
    ar(CurrentView);

    ar(m_GameObjects);
    ar(m_TriggerObjects);
  }
  
#ifdef WITH_EDITOR

#endif

  virtual void SpawnBall
  (
    char BallType,
    const sf::Vector2f & InitialPosition,
    const sf::Vector2f & InitialVelocity,
    unsigned int Radius,
    float Mass,
    float CoeffecientOfRest,
    const sf::Color & Color
  );

  virtual void SpawnSquare
  (
    float radius,
    float init_rotation,
    const sf::Vector2f & InitialPosition,
    const sf::Vector2f & InitialVelocity,
    float mass,
    float CoeffOfRest,
    const sf::Color & Color
  );

  virtual void SpawnRect
  (
    float radius,
    float init_rotation,
    const sf::Vector2f & InitialPosition,
    const sf::Vector2f & InitialVelocity,
    float mass,
    float CoeffOfRest,
    const sf::Color & Color
  );

  virtual void SpawnTriangle
  (
    float radius,
    float init_rotation,
    const sf::Vector2f & InitialPosition,
    const sf::Vector2f & InitialVelocity,
    float mass,
    float CoeffOfRest,
    const sf::Color & Color
  );
  virtual void SpawnNPoly
  (
    unsigned int num_sides,
    float radius,
    float init_rotation,
    const sf::Vector2f & InitialPosition,
    const sf::Vector2f & InitialVelocity,
    float mass,
    float CoeffOfRest,
    const sf::Color & Color
  );

  virtual void SpawnWave
  (
    char type,
    const sf::Vector2i &TopLeftCorner,
    const sf::Vector2i &BottomRightCorner,
    float radius,
    bool IsHard,
    unsigned int NumWavePts,
    float ampRight,
    float waveLenRight,
    float rFreqRight,
    float ampLeft,
    float waveLenLeft,
    float rFreqLeft,
    float elev,
    float airDen,
    float depth,
    float fluidDen
  );

  void SpawnTrigger
  (
    const std::string &Name,
    const sf::Vector2f &Where,
    const sf::Vector2f &Size,
    std::function<void(void)> TriggerCB,
    std::function<void(std::shared_ptr<GameObject>)> CheckCB,
    bool NotifyEveryFrame,
    bool DoPhysicalResponse,
    bool RestrictTriggers,
    std::vector<std::string> RestrictedTriggers = {}
  );
};

