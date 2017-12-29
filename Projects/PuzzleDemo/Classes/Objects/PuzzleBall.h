#ifndef GAME_PUZZLE_BALL_H
#define GAME_PUZZLE_BALL_H

#include "ProjectIncludes.h"

#include <Thor\Animations.hpp>
#include <SFML\Audio.hpp>

class PuzzleBall : public Engine::LevelObject
{
public:
  PuzzleBall();
  ~PuzzleBall();

  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void TickUpdate(const double &delta) override;
  void PhysicsUpdate() override;
  void OnShutDown() override;

  void OnGameStart() override;
  void OnGameEnd()   override;
  void OnKilled()    override;
  void OnSpawn()     override;

  void SetRadius(float rad);

protected:
  float m_Radius;

  thor::FrameAnimation m_NormalAnimation;
  thor::FrameAnimation m_DeathAnimation;
  thor::FrameAnimation m_SpawnAnimation;

  thor::AnimationMap<sf::CircleShape, std::string> m_AnimationMap;
  thor::Animator<sf::CircleShape, std::string>    *m_Animator;

  sf::Sound m_ShatterSound;        sf::SoundBuffer m_ShatterBuffer;
  sf::Sound m_ReverseShatterSound; sf::SoundBuffer m_ReverseShatterBuffer;

  sf::Texture m_NormalAnimationTexture;
  sf::Texture m_ExplosionTexture;
};

#endif
