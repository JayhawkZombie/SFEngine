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

#include "Objects\ProjectileBase.h"
#include "Physics\Collider.h"

namespace Engine
{

  ProjectileBase::ProjectileBase()
    : m_Origin({ 0,0 }), m_Direction({ 0,0 }), m_Velocity({ 0,0 })
  {
  }

  ProjectileBase::~ProjectileBase()
  {
  }

  void ProjectileBase::OnObjectHit(LevelObject * objectHit)
  {
  }

  void ProjectileBase::SetOrigin(const sf::Vector2f & Point)
  {
  }

  void ProjectileBase::SetDirection(const sf::Vector2f & Dir)
  {
  }

  void ProjectileBase::SetVelocity(const sf::Vector2f & Vel)
  {
  }

  void ProjectileBase::TickUpdate(const double & delta)
  {
  }

  void ProjectileBase::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
  }

  void ProjectileBase::Kill()
  {
  }

  void ProjectileBase::SerializeOut(std::ofstream & out)
  {
  }

  void ProjectileBase::SerializeIn(std::ifstream & in)
  {
  }

  void ProjectileBase::SetPosition(const sf::Vector2f & pos)
  {
  }

  void ProjectileBase::SetTexture(std::shared_ptr<sf::Texture> Texture)
  {
  }

  void ProjectileBase::SetCollisionCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback)
  {
  }

  sf::Vector2f ProjectileBase::GetOrigin() const
  {
    return m_Origin;
  }

  sf::Vector2f ProjectileBase::GetDirection() const
  {
    return m_Direction;
  }

  sf::Vector2f ProjectileBase::GetVelocity() const
  {
    return m_Velocity;
  }

}
