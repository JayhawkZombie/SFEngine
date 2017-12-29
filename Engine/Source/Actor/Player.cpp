////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "Actor\Player.h"

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
  auto player = std::make_shared<Player>(*this);
  return player;
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
