#ifndef GAME_PUZZLE_OBJECTS_LIGHTNING_H
#define GAME_PUZZLE_OBJECTS_LIGHTNING_H

#include "ProjectIncludes.h"

class LightningObject : public Engine::LevelObject
{
public:
  LightningObject();
  ~LightningObject();

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;

  void Spark(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
  
  std::function<void(void)> BoltDoneFunc;
  bool IsAlive() const;
protected:
  void UpdateBolt(const double &delta);
  void CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition);
  bool m_IsAlive = false;
  float m_SparkSpeed = 1.f;
  double m_currentFadeTime = 0.0;
  double m_TotalFadeTime = 900.0;
  unsigned char alpha = 255;
  std::vector<sf::VertexArray> m_Points;

};

#endif
