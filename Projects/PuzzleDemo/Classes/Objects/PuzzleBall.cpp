#include "PuzzleBall.h"

PuzzleBall::PuzzleBall()
{
  m_ExplosionTexture.loadFromFile("./Projects/PuzzleDemo/Assets/Textures/explosion91.png");

  if (m_ShatterBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/Glass,Bottle,Break,Smash,Messy.ogg"))
    m_ShatterSound.setBuffer(m_ShatterBuffer);
  
  if (m_ReverseShatterBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/ReverseShatter.ogg"))
    m_ReverseShatterSound.setBuffer(m_ReverseShatterBuffer);

  //Add the explosion frames
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      m_DeathAnimation.addFrame(1.f, sf::IntRect(x * 256, y * 256, 256, 256));
    }
  }

  m_AnimationMap.addAnimation("death", m_DeathAnimation, sf::seconds(1.3f));
}

PuzzleBall::~PuzzleBall()
{
}

void PuzzleBall::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void PuzzleBall::TickUpdate(const double & delta)
{
}

void PuzzleBall::PhysicsUpdate()
{
}

void PuzzleBall::OnShutDown()
{
}

void PuzzleBall::OnGameStart()
{
}

void PuzzleBall::OnGameEnd()
{
}

void PuzzleBall::OnKilled()
{
}

void PuzzleBall::OnSpawn()
{
  
}

void PuzzleBall::SetRadius(float rad)
{
  m_Radius = rad;
}
