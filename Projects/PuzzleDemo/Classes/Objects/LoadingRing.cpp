#include "LoadingRing.h"

LoadingRing::LoadingRing()
{
  m_CurrentFillAmount = 0.f;
  m_Ring.setSectorSize(0.f);
  m_Ring.setSectorOffset(0.25f);
  m_FillingUp = false;
  m_FinalFillAmount = 1.f;
  m_FillingUp = false;
}

LoadingRing::~LoadingRing()
{
}

void LoadingRing::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Target->draw(m_Ring);
}

void LoadingRing::TickUpdate(const double &delta)
{
  if (m_IsFilling) {
    m_CurrentTime += (float)(delta);
    m_CurrentFillAmount += (float)(delta * m_FillRate);

    if (m_FillingUp && m_CurrentFillAmount >= m_FinalFillAmount) {
      m_CurrentFillAmount = m_FinalFillAmount;
      m_IsFilling = false;
    }
    else if (!m_FillingUp && m_CurrentFillAmount <= m_FinalFillAmount) {
      m_CurrentFillAmount = m_FinalFillAmount;
      m_IsFilling = false;
    }

    m_Ring.setSectorSize(m_CurrentFillAmount);
  }
  else
    m_CurrentTime = 0.0;
}

void LoadingRing::PhysicsUpdate()
{

}

void LoadingRing::OnShutDown()
{

}

void LoadingRing::OnGameStart()
{

}

void LoadingRing::OnGameEnd()
{

}

void LoadingRing::OnKilled()
{

}

void LoadingRing::OnSpawn()
{

}

void LoadingRing::SetTexture(std::shared_ptr<sf::Texture> Texture)
{
  m_Ring.setTexture(*Texture);
}

void LoadingRing::SetTextureRect(sf::IntRect myRect)
{
  m_Ring.setTextureRect(myRect);
}

void LoadingRing::SetRadius(float Radius)
{
  m_Ring.setRadius(Radius);
}

void LoadingRing::SetHoleRatio(float Radius)
{
  m_Ring.setHole(Radius);
}

void LoadingRing::SetArcFill(float _Size)
{
  m_Ring.setSectorSize(_Size);
}

void LoadingRing::SetColor(sf::Color Color)
{
  m_Ring.setColor(Color);
}

void LoadingRing::SetPosition(const sf::Vector2f & pos)
{
  m_Ring.setPosition(pos);
}

void LoadingRing::Reset()
{
  m_IsFilling = false;
  m_FillingUp = true;
  m_CurrentTime = 0.0;
  m_CurrentFillAmount = 0.f;
  m_FillRate = 0.0;
  m_TimeBetweenFills = 0.0;
}

void LoadingRing::SetFillRate(float PercPerMs)
{
  m_FillRate = PercPerMs;
  m_TimeBetweenFills = 1.f / m_FillRate;
}

void LoadingRing::Fill(float ms)
{
  m_FinalFillAmount = 1.f;
  m_FillRate = (m_FinalFillAmount - m_CurrentFillAmount) / ms;
  m_IsFilling = true;
  m_FillingUp = (m_FillRate > 0.f);
}

void LoadingRing::FillTo(float Perc, float ms)
{
  m_FinalFillAmount = Perc;
  m_FillRate = (m_FinalFillAmount - m_CurrentFillAmount) / ms;
  m_IsFilling = true;
  m_FillingUp = (m_FillRate > 0.f);
}

void LoadingRing::Empty(float ms)
{
  m_FinalFillAmount = 0.f;
  m_FillRate = (m_FinalFillAmount - m_CurrentFillAmount) / ms;
  m_IsFilling = true;
  m_FillingUp = false;
}

