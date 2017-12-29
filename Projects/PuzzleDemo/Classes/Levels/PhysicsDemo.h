#ifndef GAME_LEVEL_PHYSICS_DEMO_H
#define GAME_LEVEL_PHYSICS_DEMO_H

#include "ProjectIncludes.h"
#include "Lights\LightingSystem.h"
#include "Time\TimedSequence.h"

#include "ThirdParty\SelbaWard\BitmapFont.hpp"
#include "ThirdParty\SelbaWard\BitmapText.hpp"
#include "ThirdParty\SelbaWard\ProgressBar.hpp"
#include "ThirdParty\SelbaWard\Starfield.hpp"

#include "Utils\SplinePath.h"

#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>

class PhysicsDemoLevel : public Engine::BasicLevel
{
public:

  PhysicsDemoLevel();
  ~PhysicsDemoLevel() override final;

  void CleanUp() override final;
  void OnEnd() override final;
  void OnBegin() override final;
  void HideUI()  override final;
  void ShowUI()  override final;
  void OnShutDown() override final;
  void EventUpdate(sf::Event event) override final;
  void TickUpdate(const double &delta) override final;
  void HandleInputEvent(const Engine::UserEvent &evnt) override final;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override final;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override final;
  void SetNextLevel(std::shared_ptr<Engine::BasicLevel> NextLevel);
  std::string GetClass() const override final;


protected:
  Engine::SplinePath m_ParticlePath;
  sw::Spline m_SPLINE;
  double TimeScale = 1.f;
  double TotalTimeSpentDialating = 0.0;
  bool m_IsSlowingTime = false;
  
  std::vector<SPtrShared<expandPolygon>> m_ExpandingPolygons;
  std::vector<SPtrShared<Engine::LevelObject>> m_ExpandObjects;

  Engine::TimedSequence m_FlipOpenSeq;
  void OpenFlipper();
  bool m_FlipperOpen = false;

  SPtrShared<Engine::PhysicsEngineSegmentType> segwall1;// = Engine::BuildSegmentMesh('b', { 25, 75 }, { 275, 225 });
  SPtrShared<Engine::PhysicsEngineSegmentType> segwall2;// = Engine::BuildSegmentMesh('b', { 1675 - 250, 75 + 150 }, { 1675, 75 });
  SPtrShared<Engine::PhysicsEngineSegmentType> segFlip;
  void ShatterCollider();
  sf::RenderTexture m_RenderedScene;

  bool m_ExplosionActive = false;
  thor::ParticleSystem m_PSystem2;
  thor::UniversalEmitter m_PEmitter2;
  thor::ColorGradient m_PColorGradient2;
  thor::ColorAnimation m_PColorAnimation2;
  thor::FadeAnimation m_PFadeAnimation2;
  thor::ForceAffector m_PGravityAffector2;

  Engine::TimedSequence m_CountdownSequence;
  Engine::TimedSequence m_TimeDialationSequence;
  bool m_TimeDialationBegan = false;
  void BeginTimeDialation();
  void UpdateTimeDialation();
  void EndTimeDialation();


  int m_CountdownSeqNumber = 5;
  void UpdateCountdown();
  void StartCountdown();
  void EndCountdown();

  SPtrShared<Engine::Collider2D> m_FallingCollider;
  SPtrShared<Engine::LevelObject> m_Faller;

  SPtrShared<Engine::PhysicsEngineSegmentType> m_ShatterRegionSegment;

  sw::BitmapFont m_BMPFont;
  sw::BitmapText m_BMPText;

  SPtrShared<Engine::Collider2D> m_TimeSlowRegion;

  sw::Starfield m_StarField;

  Engine::LightSystem m_LightSystem;

  SPtrShared<sf::Texture> m_TorchTexture;
  Engine::Light m_TorchLight;
  thor::AnimationMap<sf::Sprite, std::string> m_TorchAnimationMap;
  thor::Animator<sf::Sprite, std::string> m_TorchAnimator;
  SPtrShared<Engine::LevelObject> m_TorchObject;
  sf::Sprite m_TorchSprite;
  thor::FrameAnimation TFrame;

  SPtrShared<Engine::PhysicsEngineWaveSegment> m_Wave;

  thor::ParticleSystem m_PSystem1;
  
  thor::UniversalEmitter m_PEmitter1;
  thor::ColorGradient m_PColorGradient1;
  thor::ColorAnimation m_PColorAnimation1;
  thor::FadeAnimation m_PFadeAnimation1;
  thor::TorqueAffector m_PTorqueAffector1;
  thor::ForceAffector m_PGravityAffector1;
  sf::Texture m_TorchParticleTexture;
  thor::PolarVector2f m_TorchParticleVelocity;

  sf::Clock _clock;


  tgui::Button::Ptr m_BackButton;
  tgui::Theme::Ptr m_ThemePtr;
};

#endif
