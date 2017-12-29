#ifndef GAME_DEMO_LOADING_RING_H
#define GAME_DEMO_LOADING_RING_H

#include "ProjectIncludes.h"
#include "ThirdParty/SelbaWard.hpp"

class LoadingRing : public LevelObject
{
public:
  LoadingRing();
  virtual ~LoadingRing() override;

  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void TickUpdate(const double &delta) override;
  void PhysicsUpdate() override;
  void OnShutDown() override;

  void OnGameStart() override;
  void OnGameEnd()   override;
  void OnKilled()    override;
  void OnSpawn()     override;

  void SetTexture(std::shared_ptr<sf::Texture> Texture) override final;
  void SetTextureRect(sf::IntRect myRect) override final;
  void SetRadius(float Radius);
  void SetHoleRatio(float Radius);
  void SetArcFill(float Size);
  void SetColor(sf::Color Color);
  void SetPosition(const sf::Vector2f &pos) override final;
  void Reset() override final;

  void SetFillRate(float PercPerMs);
  void Fill(float ms);
  void FillTo(float Perc, float ms);
  void Empty(float ms);

protected:
  double m_FillRate = 0.0;
  double m_FillPerc = 0.0;
  double m_TimeBetweenFills = 0.0;
  double m_CurrentTime = 0.0;

  bool m_IsFilling = false;
  bool m_FillingUp = false;
  float m_CurrentFillAmount = 0.f;
  float m_FinalFillAmount = 0.f;
  
  sw::Ring m_Ring;
};

#endif
