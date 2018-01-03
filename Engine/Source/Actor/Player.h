#pragma once

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

#include "Actor\Actor.h"

class Player : public GenericActor
{
public:
  TYPEDEF_PARENT_CLASS(GenericActor);

  Player();
  Player(const std::string &texfile, const std::string &texID);
  virtual ~Player();

  //Forbid implicit copy construction and assignment definitions
  //We [MUST] use a clone method
  Player(const Player &p);
  Player& operator=(const Player &) = delete;
  virtual std::shared_ptr<BaseEngineInterface> Clone() const override;

  virtual void TickUpdate(const double &delta) override;
  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  virtual void OnShutDown() override;
  virtual void SerializeOut(std::ofstream &out) override;
  virtual void SerializeIn(std::ifstream &in) override;

  virtual void KeyRightPressed();
  virtual void KeyUpPressed();
  virtual void KeyDownPressed();
  virtual void KeyLeftPressed();
  virtual void ForcePosition(float x, float y);

  virtual void HandleInputEvent(const UserEvent &evnt);

  virtual void MoveTo(const sf::Vector2f &pos);

  virtual std::string GetClass() const override {
    return "Player";
  }
protected:
  void KeyWasPressed(const sf::Keyboard::Key &k);
  void KeyWasReleased(const sf::Keyboard::Key &k);

  void TryToMove(const sf::Vector2f &amount);

  sf::RectangleShape TestShape;
};
