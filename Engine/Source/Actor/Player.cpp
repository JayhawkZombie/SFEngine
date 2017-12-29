#include "Actor\Player.h"

namespace Engine
{

  Player::Player(const std::string &texfile, const std::string &texID)
    : GenericActor(texfile, texID)
  {

    
  }

  Player::Player()
  {
    
  }

  Player::~Player()
  {

  }

  void Player::KeyRightPressed()
  {

  }

  void Player::KeyUpPressed()
  {

  }

  void Player::KeyDownPressed()
  {

  }

  void Player::KeyLeftPressed()
  {

  }

  void Player::ForcePosition(float x, float y)
  {
    
  }

  void Player::SerializeOut(std::ofstream &out)
  {

  }

  void Player::SerializeIn(std::ifstream & in)
  {
  }

  Player::Player(const Player & p)
    : GenericActor()
  {
  }

  std::shared_ptr<BaseEngineInterface> Player::Clone() const
  {
    auto Player = std::make_shared<Engine::Player>(*this);
    return Player;
  }

  void Player::TickUpdate(const double &delta)
  {
    
  }

  void Player::Render(std::shared_ptr<sf::RenderTarget> Target)
  {

    
  }

  void Player::OnShutDown()
  {

  }

  void Player::HandleInputEvent(const UserEvent & evnt)
  {
  }

  bool Player::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }

  void Player::KeyWasPressed(const sf::Keyboard::Key &k)
  {
    
  }

  void Player::KeyWasReleased(const sf::Keyboard::Key &k)
  {
    
  }

  void Player::MoveTo(const sf::Vector2f &pos)
  {
    
  }

  void Player::TryToMove(const sf::Vector2f &amount)
  {
    
  }
}
