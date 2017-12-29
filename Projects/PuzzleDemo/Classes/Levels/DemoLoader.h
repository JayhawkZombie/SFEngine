#ifndef GAME_DEMO_LOADER_H
#define GAME_DEMO_LOADER_H

#include "ProjectIncludes.h"
#include "ThirdParty\SelbaWard\Sprite3d.hpp"
#include "Time\TimedSequence.h"

#include "Projects/PuzzleDemo/Classes/Objects/LoadingRing.h"
#include "Projects/PuzzleDemo/Classes/Objects/Flippable.h"
#include "Projects/PuzzleDemo/Classes/Objects/LoadingBar.h"

#include "ThirdParty\SelbaWard\BitmapFont.hpp"
#include "ThirdParty\SelbaWard\BitmapText.hpp"
#include "ThirdParty\SelbaWard\ProgressBar.hpp"

#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>

class DemoLoadLevel : public BasicLevel
{
public:
  DemoLoadLevel();
  ~DemoLoadLevel() override final;

  void CleanUp() override final;
  void OnEnd() override final;
  void OnBegin() override final;
  void OnShutDown() override final;
  void EventUpdate(sf::Event event) override final;
  void TickUpdate(const double &delta) override final;
  void HandleInputEvent(const UserEvent &evnt) override final;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override final;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override final;
  void SetNextLevel(std::shared_ptr<BasicLevel> NextLevel);
  std::string GetClass() const override final;

protected:
  sw::BitmapFont  m_BitmapFont;
  sw::BitmapText  m_BitmapText;
  LoadingBar      m_ProgressBar;

  sf::Texture m_PSystemTexture;

  thor::ParticleSystem m_PSystem1;
  thor::UniversalEmitter m_PEmitter1;
  thor::ColorGradient m_PColorGradient1;
  thor::ColorAnimation m_PColorAnimation1;
  thor::FadeAnimation m_PFadeAnimation1;
  thor::TorqueAffector m_PTorqueAffector1;
  thor::ForceAffector m_PGravityAffector1;

  thor::ParticleSystem m_PSystem2;
  thor::UniversalEmitter m_PEmitter2;
  thor::ColorGradient m_PColorGradient2;
  thor::ColorAnimation m_PColorAnimation2;
  thor::FadeAnimation m_PFadeAnimation2;
  thor::TorqueAffector m_PTorqueAffector2;
  thor::ForceAffector m_PGravityAffector2;

  SDOUBLE m_PSystem1Time;
  SDOUBLE m_PSystem2Time;

  SVector2F m_PSystem1Position;
  SVector2F m_PSystem2Position;

  std::shared_ptr<BasicLevel> m_NextLevel;
  SPtrSharedMutex m_LevelMutex;
  std::shared_ptr<sf::Texture> m_TestRingTexture;
  bool   m_LoadingNextLevel = true;
  double m_LoadingWaitCount = 0;
  bool   m_CanSwitchLevel = false;
  bool   m_TimingWaitCount = false;
  LoadingRing m_TestRing;
  Flippable   m_SFMLCard;
  STexture    m_SFMLCardFrontTexture;
  STexture    m_SFMLCardBackTexture;
};

#endif
