#include "Flippable.h"

Flippable::Flippable()
{
}

Flippable::~Flippable()
{
}

void Flippable::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Target->draw(m_FlipSprite);
}

void Flippable::TickUpdate(const double & delta)
{
  static sf::Clock _clock;

  m_FlipSprite.setRotation({ 
    _clock.getElapsedTime().asSeconds() * 30.5f, 
    _clock.getElapsedTime().asSeconds() * 30.5f, 
    _clock.getElapsedTime().asSeconds() * 30.5f }
  );

}

void Flippable::PhysicsUpdate()
{
}

void Flippable::OnShutDown()
{
}

void Flippable::OnGameStart()
{
}

void Flippable::OnGameEnd()
{
}

void Flippable::OnKilled()
{
}

void Flippable::OnSpawn()
{
}

void Flippable::Flip(double duration, float HeightChange)
{
  m_FlipDuration = duration;
  sf::Vector3f rot = m_FlipSprite.getRotation3d();
  m_OriginalRotation = rot;
  rot.x = (rot.x > 180.f ? 0 : 360.f);
  m_FinalRotation = rot;
  m_RotationPerMS = (m_FinalRotation - m_OriginalRotation) / (float)(duration);
  m_HeightChangeDuringFlip = HeightChange;

  //Half of the height change will occur during the 1st half, and the rest during the other half
  m_HeightChangePerMS = HeightChange / (0.5f * (float)(duration));
}

void Flippable::SetTexture(std::shared_ptr<sf::Texture> Texture)
{
  m_Texture = Texture;
  m_FlipSprite.setTexture(*Texture);
  m_FlipSprite.setMeshDensity(10);
}

void Flippable::SetPosition(const sf::Vector2f & pos)
{
  m_FlipSprite.setPosition(pos);
  Position = pos;
}

void Flippable::SetSize(const sf::Vector2f & size)
{
  Size = size;
  auto vec = m_Texture->getSize();
  auto scale = sf::Vector2f(size.x / (float)(vec.x), size.y / (float)(vec.y));
  m_FlipSprite.setScale(scale);
}

void Flippable::SetTextureFrontBack(std::shared_ptr<sf::Texture> TextureFront, std::shared_ptr<sf::Texture> TextureBack, sf::IntRect FrontRect, sf::Vector2i BackOffset)
{
  m_FlipSprite.setTexture(*TextureFront);
  m_FlipSprite.setBackTexture(*TextureBack);

  auto tSize = TextureFront->getSize();

  m_FlipSprite.setOrigin3d(sf::Vector3f((float)tSize.x, (float)tSize.y, 0.f));
}

void Flippable::Center()
{
  m_FlipSprite.setOrigin(sf::Vector2f(m_FlipSprite.getLocalBounds().width, m_FlipSprite.getLocalBounds().height / 2.f));
}

void Flippable::SetDepth(float depth)
{
  m_FlipSprite.setDepth(depth);
}

void Flippable::SetOrigin(const sf::Vector2f & Origin)
{
  m_FlipSpriteOrigin = Origin;
  m_FlipSprite.setOrigin(Origin);
}

float Flippable::GetDepth() const
{
  return m_FlipSprite.getDepth();
}

void Flippable::Rotate(const sf::Vector3f & Delta)
{
  m_CurrentRotation += Delta;
  if (m_CurrentRotation.x < 0.f)
    m_CurrentRotation.x = 90.f;
  else if (m_CurrentRotation.x > 90.f)
    m_CurrentRotation.x = 0.f;

  if (m_CurrentRotation.y < 0.f)
    m_CurrentRotation.y = 90.f;
  else if (m_CurrentRotation.y > 90.f)
    m_CurrentRotation.y = 0.f;

  if (m_CurrentRotation.z < 0.f)
    m_CurrentRotation.z = 90.f;
  else if (m_CurrentRotation.z > 90.f)
    m_CurrentRotation.z = 0.f;

  m_FlipSprite.setRotation(m_CurrentRotation);
}

void Flippable::SetRotation(const sf::Vector3f & Rot)
{
  m_CurrentRotation = Rot;
  m_OriginalRotation = Rot;
  m_FlipSprite.setRotation(m_CurrentRotation);
}

void Flippable::Reset()
{
}

void Flippable::UpdateFlip(const double & Delta)
{
  m_CurrentFlipDuration += Delta;

  if (m_CurrentFlipDuration >= m_FlipDuration) {
    m_IsFlipping = false;
    m_CurrentRotation = m_FinalRotation;
    m_FlipSprite.setRotation(m_FinalRotation);
  }
  else {
    m_CurrentRotation += m_RotationPerMS * (float)(Delta);
    
    if (m_CurrentFlipDuration < m_FlipDuration / 2.f) {
      //apply an decrease in depth (closer to screen)
      m_CurrentHeight -= m_HeightChangePerMS;
      m_FlipSprite.setDepth(m_CurrentHeight);
    }
    else {
      //apply increase in depth (further from screen)
      m_CurrentHeight += m_HeightChangePerMS;
      m_FlipSprite.setDepth(m_CurrentHeight);
    }

  }
}
