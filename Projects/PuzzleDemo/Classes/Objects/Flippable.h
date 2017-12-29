#ifndef GAME_DEMO_FLIPPABLE_H
#define GAME_DEMO_FLIPPABLE_H

#include "ProjectIncludes.h"
#include "Time\TimedSequence.h"
#include "ThirdParty\SelbaWard.hpp"

class Flippable : public Engine::LevelObject
{
public:
  Flippable();
  ~Flippable() override final;

  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void TickUpdate(const double &delta) override;
  void PhysicsUpdate() override;
  void OnShutDown() override;

  void OnGameStart() override;
  void OnGameEnd()   override;
  void OnKilled()    override;
  void OnSpawn()     override;

  void Flip(double duration, float HeightChange = 0.f);
  void SetTexture(std::shared_ptr<sf::Texture> Texture) override;
  void SetPosition(const sf::Vector2f &pos) override final;
  void SetSize(const sf::Vector2f &size) override final;
  void SetTextureFrontBack(std::shared_ptr<sf::Texture> TextureFront, std::shared_ptr<sf::Texture> TextureBack, sf::IntRect FrontRect, sf::Vector2i BackOffset);
  void Center();
  void SetDepth(float depth);
  void SetOrigin(const sf::Vector2f &Origin);
  float GetDepth() const;

  void Rotate(const sf::Vector3f &Delta);
  void SetRotation(const sf::Vector3f &Rot);
  void Reset() override final;

protected:
  void UpdateFlip(const double &Delta);

  double m_FlipDuration;
  double m_CurrentFlipDuration;

  sf::Vector3f m_OriginalRotation;
  sf::Vector3f m_FinalRotation;
  sf::Vector3f m_CurrentRotation;
  sf::Vector2f m_FlipSpriteOrigin;
  sf::Vector3f m_RotationPerMS;

  float m_HeightChangeDuringFlip = 0.f;
  float m_HeightChangePerMS = 0.f;
  float m_CurrentHeight = 0.f;

  bool m_IsFlipping = false;
  sw::Sprite3d m_FlipSprite;
  Engine::TimedSequence m_FlippingSequence;
  std::shared_ptr<sf::Texture> m_Texture;
};

#endif
