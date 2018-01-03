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

#include "Engine/stdafx.h"
#include "GameObject.h"

#include <cereal/archives/portable_binary.hpp>

GameObject::~GameObject()
{

}

std::shared_ptr<BaseEngineInterface> GameObject::Clone() const
{
  return std::make_shared<GameObject>();
}

void GameObject::TickUpdate(const double &delta)
{

}

void GameObject::Render(std::shared_ptr<sf::RenderTarget> Target)
{

}

void GameObject::OnShutDown()
{

}

void GameObject::SerializeIn(std::ifstream &in)
{

}

void GameObject::SerializeOut(std::ofstream &out)
{

}

std::string GameObject::GetClass() const
{
  return std::string("GameObject");
}

void GameObject::ScriptInit()
{

}

bool GameObject::IsScriptReady()
{
  return m_HasInitializedScripts;
}

void GameObject::BeginPlay()
{

}

void GameObject::EndPlay()
{

}

void GameObject::Kill()
{

}

bool GameObject::CanBeSpawned()
{
  return m_IsReadyToSpawn;
}

sf::Vector2f GameObject::GetPosition() const
{
  return m_Position;
}

sf::Vector2f GameObject::GetSize() const
{
  return m_Size;
}

sf::Vector2f GameObject::GetVelocity() const
{
  return m_Velocity;
}

sf::Vector2f GameObject::GetAcceleration() const
{
  return m_Acceleration;
}

double GameObject::GetTimeSinceSpawned()
{
  return 0.0;
}

double GameObject::GetTimeSinceCreated()
{
  return 0.0;
}

void GameObject::SetTickInterval(double TickInterval)
{

}

double GameObject::GetTickInterval() const
{
  return 13.3;
}

void GameObject::TeleportTo(const sf::Vector2f &NewPosition)
{

}

void GameObject::SetFrozen(bool IsFrozen)
{

}

void GameObject::KillWithDeathSequence()
{

}

void GameObject::ForceKill()
{

}

void GameObject::Scale(const sf::Vector2f &ScaleFactors)
{

}

void GameObject::Animate(const std::string &AnimationName)
{

}

void GameObject::OnLeftMousePress()
{

}

void GameObject::OnRightMousePress()
{

}

void GameObject::OnLeftMouseRelease()
{

}

void GameObject::OnRightMouseRelease()
{

}

void GameObject::OnContinuedLeftMousePress()
{

}

void GameObject::OnContinuedRightMousePress()
{

}

void GameObject::OnKeyPressed(sf::Keyboard::Key key)
{

}

void GameObject::OnKeyReleased(sf::Keyboard::Key key)
{

}

void GameObject::OnKeyHeld(sf::Keyboard::Key key)
{

}

void GameObject::OnKeyComboPressed(const std::vector<sf::Keyboard::Key> &keys)
{

}

void GameObject::OnKeyComboReleased(const std::vector<sf::Keyboard::Key> &keys)
{

}

void GameObject::OnKeyComboHeld(const std::vector<sf::Keyboard::Key> &keys)
{

}

void GameObject::OnAnimationBegin(const std::string &AnimationName)
{

}

void GameObject::OnAnimationCompleted(const std::string &AnimationName)
{

}

void GameObject::OnBeginOverlap(GameObject *OverlappingObject)
{

}

void GameObject::OnContinuedOverlap(GameObject *OverlappingObject)
{

}

void GameObject::OnEndOverlap(GameObject *OverlappingObject)
{

}

void GameObject::OnHit(GameObject *Object)
{

}

void GameObject::OnHitSecondary(GameObject *Object)
{

}

void GameObject::EmitSound(const std::string &SoundName)
{

}

bool GameObject::HasAssociatedCollider()
{
  return false;
}

void GameObject::DisableCollider()
{

}

void GameObject::SleepCollider()
{

}

void GameObject::WakeCollider()
{

}

GameObject::EObjectColliderResponseSelectivity GameObject::GetColliderResponseSelectivity() const
{
  return m_ColliderSelectivity;
}

void GameObject::SetColliderResponseSelectivity(EObjectColliderResponseSelectivity Selectivity)
{
  m_ColliderSelectivity = Selectivity;
}

void GameObject::ResetCollider()
{

}

void GameObject::FreezeCollider()
{

}

void GameObject::UnfreezeCollider()
{

}

CEREAL_REGISTER_TYPE(GameObject);
