#ifndef GAME_LEVEL_STACK_H
#define GAME_LEVEL_STACK_H

#include "ProjectIncludes.h"
#include "Weather\WeatherSystem.h"
#include "Weather\Lightning.h"
#include "Time\TimedSequence.h"
#include "../Objects/PuzzleBall.h"
#include "../Objects/Gem.h"

class BallStackLevel : public Engine::BasicLevel
{
public:
  BallStackLevel();
  ~BallStackLevel() override;

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override final;

  void OnShutDown() override;
  void HandleInputEvent(const Engine::UserEvent &evnt) override;
  void EventUpdate(sf::Event event) override;
  void OnBegin() override;
  void OnEnd() override;
  void ShowUI() override;
  void HideUI() override;
  void Reset() override;
  void UpdateObjectPhysics() override;
  std::string GetClass() const override final;

protected:
  void HandleUserClick(sf::Vector2i Pos);
  void CheckBallAndBolt(std::weak_ptr<Engine::Collider2D> Collider);
  void LaunchBall();
  void SpawnBall();
  void KillBall();
  
  void SpawnGem(const sf::Vector2f &Pos);

  std::shared_ptr<PuzzleBall> m_CurrentBall;
  std::vector<std::shared_ptr<ShatterGem>> m_ShatterGems;
  sf::Color m_CurrentBallColor;
  sf::Color m_CurrentBoltColor;

  sf::Music m_BGMusic;
  sf::Sound m_TimeSlowDownSound; sf::SoundBuffer m_TimeSlowDownBuffer;
  sf::Sound m_TimeSpeedUpSound;  sf::SoundBuffer m_TimeSpeedUpBuffer;
  sf::Sound m_BallSpawnSound;    sf::SoundBuffer m_BallSpawnBuffer;

  std::shared_ptr<tgui::Gui> m_GameMenu;
  tgui::Button::Ptr m_DropBallButton;
  tgui::Panel::Ptr  m_PausePanel;
  tgui::Theme::Ptr  m_LevelTheme;
  sf::Font          m_MenuFont;

  Engine::TimedSequence   m_GameSequencer;
  Engine::UntimedSequence m_UntimedSequencer;

  std::shared_ptr<Engine::PhysicsEngineSegmentType> m_PipeLeftWall;
  std::shared_ptr<Engine::PhysicsEngineSegmentType> m_PipeWallRight;
  std::shared_ptr<Engine::PhysicsEngineSegmentType> m_PipeDropBlock;

  std::shared_ptr<Engine::LightningBolt> m_BallKillerBolt;

  bool      m_Paused = false;
  void ShowMenu();
  void HideMenu();
  tgui::Button::Ptr m_QuitButton;
};

#endif
