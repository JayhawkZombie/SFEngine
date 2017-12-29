#include "LoadingBar.h"


LoadingBar::LoadingBar()
  : 
  m_FillColor(sf::Color::White), 
  m_BackgroundColor(sf::Color::Blue), 
  m_FrameThickness(2.f), 
  m_FrameColor(sf::Color::Black),
  m_CurrentProgress(0.f)
{
  m_ProgBar.setShowBackgroundAndFrame(true);
  m_ProgBar.setShowBar(true);
}

LoadingBar::~LoadingBar()
{
}

void LoadingBar::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Target->draw(m_ProgBar);
}

void LoadingBar::TickUpdate(const double & delta)
{
  //Make sure we don't update TOO often
  //static double update_wait = 0.0;
  //update_wait += delta;
  //if (update_wait < 6.667)
  //  return;

  //update_wait = 0.0;

  if (m_IsFilling) {
    m_CurrentProgress += (float)(delta)* m_FillRate;

    if (m_IsIncreasing && m_CurrentProgress >= m_FinalProgress) {
      m_CurrentProgress = 100.f;
      m_IsFilling = false;
    }
    else if (!m_IsIncreasing && m_CurrentProgress <= m_FinalProgress) {
      m_CurrentProgress = m_FinalProgress;
      m_IsFilling = false;
    }
    m_ProgBar.setPercentage(m_CurrentProgress);
    //m_ProgBar.setPercentage(m_CurrentProgress);
  }
}

void LoadingBar::PhysicsUpdate()
{
}

void LoadingBar::OnShutDown()
{
}

void LoadingBar::OnGameStart()
{
}

void LoadingBar::OnGameEnd()
{
}

void LoadingBar::OnKilled()
{
}

void LoadingBar::OnSpawn()
{
}

void LoadingBar::SetTexture(std::shared_ptr<sf::Texture> Texture)
{
}

void LoadingBar::SetTextureRect(sf::IntRect myRect)
{
}

void LoadingBar::SetPosition(const sf::Vector2f & pos)
{
  m_ProgBar.setPosition(pos);
  Position = pos;
}

void LoadingBar::SetSize(const sf::Vector2f & size)
{
  m_ProgBar.setSize(size);
  Size = size;
}

void LoadingBar::Reset()
{
  m_FillRate = 0.f;
  m_FinalProgress = 0.f;
  m_IsFilling = false;
  m_CurrentProgress = 0.f;
}

void LoadingBar::SetFillColor(sf::Color Color)
{
  m_FillColor = Color;
  m_ProgBar.setColor(Color);
}

void LoadingBar::SetBackgroundColor(sf::Color Color)
{
  m_BackgroundColor = Color;
  m_ProgBar.setBackgroundColor(Color);
}

void LoadingBar::SetFrameColor(sf::Color Color)
{
  m_FrameColor = Color;
  m_ProgBar.setFrameColor(Color);
}

void LoadingBar::SetFrameThickness(float Thickness)
{
  m_FrameThickness = Thickness;
  m_ProgBar.setFrameThickness(Thickness);
}

void LoadingBar::SetProgress(float Progress)
{
  m_FinalProgress = Progress;
  m_IsFilling = true;
  m_IsIncreasing = (m_FinalProgress >= m_CurrentProgress);
}

void LoadingBar::SetIndeterminate(bool Indeterminate)
{
}

void LoadingBar::SetFillRate(float PercPerMs)
{
  m_FillRate = PercPerMs;
}

SFLOAT LoadingBar::GetProgress() const
{
  return m_CurrentProgress;
}
