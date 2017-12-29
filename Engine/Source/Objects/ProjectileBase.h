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

#include "Level\LevelObject.h"

#include "PhysicsEngine.h"

class ProjectileBase
{
public:
  ProjectileBase();
  virtual ~ProjectileBase();

  virtual std::shared_ptr<ProjectileBase> Clone() = 0;

  virtual void OnObjectHit(LevelObject *objectHit) = 0;
  void SetOrigin(const sf::Vector2f &Point);
  void SetDirection(const sf::Vector2f &Dir);
  void SetVelocity(const sf::Vector2f &Vel);


  virtual void TickUpdate(const double &delta) = 0;
  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) = 0;
  virtual void Kill() = 0;
  virtual void SerializeOut(std::ofstream &out);
  virtual void SerializeIn(std::ifstream &in);
  virtual void SetPosition(const sf::Vector2f &pos);
  virtual void SetTexture(std::shared_ptr<sf::Texture> Texture);

  virtual void SetCollisionCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback);

  sf::Vector2f GetOrigin() const;
  sf::Vector2f GetDirection() const;
  sf::Vector2f GetVelocity() const;
protected:
  sf::Sprite m_Sprite;
  sf::Vector2f m_Origin;
  sf::Vector2f m_Direction;
  sf::Vector2f m_Velocity;
  std::shared_ptr<Collider2D> m_Collider;
};
