#ifndef GAME_STARTUP_LEVEL_H
#define GAME_STARTUP_LEVEL_H

#include "ProjectIncludes.h"
#include "Objects\ProjectileBase.h"
#include "Weather\Lightning.h"
#include "Weather\WeatherSystem.h"
#include "Time\TimedSequence.h"
#include "Utils\UntimedSequence.h"

class StartupLevel : public BasicLevel
{
public:
  StartupLevel();
  ~StartupLevel() override final;

  void TickUpdate(const double &delta) override final;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override final;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override final;
  void OnShutDown() override final;
  void HandleInputEvent(const UserEvent &evnt) override final;
  void EventUpdate(sf::Event event) override final;
  void OnBegin() override final;
  void OnEnd() override final;

  void CleanUp() override final;
  void SetNextLevel(std::shared_ptr<BasicLevel> NextLevel);
  std::string GetClass() const override final;

protected:

  void TriggerCrawlingLightning();
  bool m_SequenceDone = false;
  bool m_Paused       = false;

  TimedSequence m_LightningSequence;
  void LightningSequenceStarted();
  void LightningSequenceEnded();

  //Stuff for the loading spinner in the bottom-right corner of the screen
  thor::AnimationMap<sf::Sprite, std::string> m_AnimMap;
  thor::Animator<sf::Sprite, std::string>    *m_animator;
  thor::FrameAnimation m_spinnerFrames;
  sf::Sprite  m_SpinnerSprite;
  sf::Texture m_SpinnerTexture;

  bool m_LightningSequenceDone = false;
  void LightningSequenceCB(int Bolt1, int Bolt2, int Bolt3, int Bolt4);
  std::vector<std::vector<sf::Vector2f>> m_LightningTraces;
  std::vector<sf::Vector2f> m_BoltStrikePositions;


  //Stuff for shattering the textures after the initial lightning letters
  bool  m_DrawShatters        = false;
  bool  m_LoadingNextLevel    = false;
  float m_SFMLFadeDuration    = 2000.f;
  float m_CurrentFadeDuration = 0.f;

  //Stuff for animating the sprites during the shattering process
  thor::AnimationMap<sf::Sprite, std::string> m_SFMLLogoMap;
  thor::Animator<sf::Sprite, std::string>    *m_SFMLAnimator;
  thor::FrameAnimation m_SFMLLogoFrame;
  sf::Texture m_SFMLShatterTexture;
  sf::Sprite  m_SFMLBeforeShatter;

  int ShatterDivisionX = 20;
  int ShatterDivisionY = 20;

  LightningBolt m_BoltTopLeft;
  LightningBolt m_BoltTopRight;
  LightningBolt m_BoltBottomLeft;
  LightningBolt m_BoltBottomRight;

  std::shared_ptr<LightningStorm> m_LightningStorm;
  CrawlingLightningBolt m_CrawlBolts[32];

  std::shared_ptr<BasicLevel> m_NextLevel;
};

#endif
