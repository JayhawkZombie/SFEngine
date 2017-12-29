#ifndef GAME_GEM_H
#define GAME_GEM_H

#include "ProjectIncludes.h"
#include "Time/TimedSequence.h"
#include "Weather/Lightning.h"

class ShatterGem : public LevelObject
{
public:
  ShatterGem(const sf::Vector2f &InitPos);
  ~ShatterGem();

  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void TickUpdate(const double &delta) override;
  void PhysicsUpdate() override;
  void OnShutDown() override;

  void OnGameStart() override;
  void OnGameEnd()   override;
  void OnKilled()    override;
  void OnSpawn()     override;

  void Shatter();
  void Reassemble();
  void Reset();

  bool IsDead() const;
protected:
  TimedSequence m_Sequencer;
  float m_ShatterFade = 0.f;

  LightningBolt m_Bolts[4];
  
  void RenderShatteredFragments();
  void UpdateShatteredFragments(const double &delta);

  std::vector<sf::VertexArray> m_ShatteredFragmentArrays;
  std::vector<sf::Vector2f>    m_ShatteredFragmentVelocities;

  std::vector<sf::IntRect> m_ShatterPieces;
  sf::Texture              m_ShatterTexture;
  sf::Texture              m_GemTexture;
  bool m_IsShattered = false;
  bool m_IsReversing = false;
  bool m_IsDead      = false;

  thor::FrameAnimation m_NormalAnimation;
  thor::FrameAnimation m_DeathAnimation;
  thor::FrameAnimation m_SpawnAnimation;

  thor::AnimationMap<sf::CircleShape, std::string> m_AnimationMap;
  thor::Animator<sf::CircleShape, std::string>    *m_Animator;

  sf::Sound m_ShatterSound;        sf::SoundBuffer m_ShatterBuffer;
  sf::Sound m_ReverseShatterSound; sf::SoundBuffer m_ReverseShatterBuffer;
};

#endif
