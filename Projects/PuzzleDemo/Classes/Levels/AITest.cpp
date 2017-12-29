#include "AITest.h"

AITestLevel::AITestLevel()
  : BasicLevel(sf::Vector2u(1700, 900), sf::FloatRect(0, 0, 1700, 900))
{
  //AI -> ball, maintains it's position within a specific region

  m_AICircle.setPosition({ 500, 500 });
  m_AICircle.setRadius(20.f);
  m_AICircle.setFillColor(sf::Color::Red);

  auto AIRoot = std::make_shared<BehaviorNode>();

  AIRoot->m_ConditionCheck = [this]()->bool 
  {   
    auto v = this->m_AICircle.getPosition(); 
    auto m = sf::Mouse::getPosition(*currentRenderWindow);  
    return (abs(v.x - m.x) < 500 && abs(m.y - v.y) < 500);   
  };

   m_TestAITree.Execute();
}

AITestLevel::~AITestLevel()
{
  m_TestAITree.Cleanup();
}

void AITestLevel::TickUpdate(const double & delta)
{
  static double _dur = 0.0;
  _dur += delta;

  
    m_TestAITree.TickUpdate(delta);
  m_AICircle.move((float)delta * m_AICicleVelocity);
}

void AITestLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Target->draw(m_AICircle);
}

void AITestLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  Texture->draw(m_AICircle);
}

void AITestLevel::OnShutDown()
{
}

void AITestLevel::HandleInputEvent(const UserEvent & evnt)
{
  if (evnt.EventType == UserEventType::KeyboardPress) {
    if (evnt.Key == sf::Keyboard::P)
      m_printTree = !m_printTree;
    else if (evnt.Key == sf::Keyboard::W)
      m_AICicleVelocity.y = -1;
    else if (evnt.Key == sf::Keyboard::A)
      m_AICicleVelocity.x = -1;
    else if (evnt.Key == sf::Keyboard::S)
      m_AICicleVelocity.y = 1;
    else if (evnt.Key == sf::Keyboard::D)
      m_AICicleVelocity.x = 1;
  }
}

void AITestLevel::EventUpdate(sf::Event event)
{
}

void AITestLevel::OnBegin()
{
}

void AITestLevel::OnEnd()
{
}

void AITestLevel::ShowUI()
{
}

void AITestLevel::HideUI()
{
}

void AITestLevel::Reset()
{
}

void AITestLevel::UpdateObjectPhysics()
{
}

std::string AITestLevel::GetClass() const
{
  return std::string();
}
