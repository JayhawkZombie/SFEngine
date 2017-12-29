#ifndef GAME_AI_TEST_H
#define GAME_AI_TEST_H

#include "ProjectIncludes.h"

#include "AI\BehaviorTree.h"
#include "Camera\2DCamera.h"

class AITestLevel : public BasicLevel
{
public:
  AITestLevel();
  ~AITestLevel() override;

  void TickUpdate(const double &delta)                             override final;
  void Render(std::shared_ptr<sf::RenderTarget> Target)            override final;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override final;

  void HandleInputEvent(const UserEvent &evnt) override final;
  void EventUpdate(sf::Event event) override final;
  void OnShutDown() override final;
  void OnBegin()    override final;
  void OnEnd()      override final;
  void ShowUI()     override final;
  void HideUI()     override final;
  void Reset()      override final;
  void UpdateObjectPhysics()   override final;
  std::string GetClass() const override final;

protected:
  BehaviorTree m_TestAITree;
  sf::CircleShape      m_AICircle;
  sf::Vector2f         m_AICicleVelocity;
  bool m_printTree = true;
  double m_AIUpdateDelta = 16.667;
};

#endif
