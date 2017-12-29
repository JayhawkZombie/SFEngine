#ifndef GAME_PUZZLE_OBJECT_LOADING_BAR_H
#define GAME_PUZZLE_OBJECT_LOADING_BAR_H

#include "ProjectIncludes.h"

#include "ThirdParty\SelbaWard\ProgressBar.hpp"

class LoadingBar : public LevelObject
{
public:
  LoadingBar();
  ~LoadingBar();

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
  void SetPosition(const sf::Vector2f &pos) override final;
  void SetSize(const sf::Vector2f &size) override final;
  void Reset() override final;

  void SetFillColor(sf::Color Color);
  void SetBackgroundColor(sf::Color Color);
  void SetFrameColor(sf::Color Color);
  void SetFrameThickness(float Thickness);

  void SetProgress(float Progress);
  void SetIndeterminate(bool Indeterminate);
  void SetFillRate(float PercPerMs);

  SFLOAT GetProgress() const;
protected:
  sf::Color m_FillColor;
  sf::Color m_BackgroundColor;
  sf::Color m_FrameColor;
  SFLOAT    m_FrameThickness;

  SFLOAT m_CurrentProgress;
  SFLOAT m_FillRate;
  SFLOAT m_FinalProgress;

  bool m_IsFilling;
  bool m_IsIncreasing = true;

  sw::ProgressBar m_ProgBar;
};

#endif
