#include "Lightning_C.h"

#include <random>

LightningObject::LightningObject()
{
}

LightningObject::~LightningObject()
{
}

void LightningObject::TickUpdate(const double & delta)
{
  UpdateBolt(delta);
}

void LightningObject::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  if (m_IsAlive) {
    for (auto & seg : m_Points)
      Target->draw(seg);
  }
}

void LightningObject::Spark(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition)
{
  m_IsAlive = true;
  m_Points.clear();
  CreateBolt(StartPosition, EndPosition);
  alpha = 255;
}

bool LightningObject::IsAlive() const
{
  return m_IsAlive;
}

void LightningObject::UpdateBolt(const double &delta)
{
  if (!m_IsAlive) {
    return;
  }

  m_currentFadeTime += delta;

  if (m_currentFadeTime >= m_TotalFadeTime) {
    m_IsAlive = false;
    m_currentFadeTime = 0.0;
    alpha = 0;
  }
  else {
    alpha = (unsigned char)(floor(255 * (1 - (m_currentFadeTime / m_TotalFadeTime))));
    for (auto & seg : m_Points) {
      seg[0].color.a = alpha;
      seg[1].color.a = alpha;
    }
  }
}

void LightningObject::CreateBolt(const sf::Vector2f &StartPosition, const sf::Vector2f &EndPosition)
{
  sf::Vector2f Tangent = EndPosition - StartPosition;
  sf::Vector2f Normal = sf::Vector2f(Tangent.y, -Tangent.x);

  float mag = std::sqrt((Tangent.x * Tangent.x) + (Tangent.y * Tangent.y));
  Normal /= mag;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1);

  sf::Vector2f DistanceVec = StartPosition - EndPosition;
  float Distance = std::sqrt((DistanceVec.x * DistanceVec.x) + (DistanceVec.y * DistanceVec.y));

  std::vector<float> Positions;
  Positions.push_back(0);
  for (std::size_t i = 0; i < (int)(Distance / 8); ++i) {
    Positions.push_back(__TO_FLOAT__(dis(gen)));
  }

  std::sort(Positions.begin(), Positions.end());

  const float sway = 70;
  const float jaggedness = 1.f / sway;

  std::uniform_real_distribution<> _dis(-sway, sway);
  sf::Vector2f prevPoint = StartPosition;
  float prevDisplacement = 0.f;

  for (std::size_t i = 1; i < Positions.size(); ++i) {
    float pos = Positions[i];
    float scale = (Distance * jaggedness) * (pos - Positions[i - 1]);

    float envelope = pos > 0.95f ? 20 * (1 - pos) : 1;

    float displ = __TO_FLOAT__(_dis(gen));
    displ -= (displ - prevDisplacement) * (1 - scale);
    displ *= envelope;

    sf::Vector2f postan = pos * Tangent;
    sf::Vector2f dispn = displ * Normal;

    sf::Vector2f point = StartPosition + postan + dispn;
    m_Points.push_back(sf::VertexArray(sf::Lines, 2));
    m_Points.back()[0].position = prevPoint; m_Points.back()[0].color = sf::Color(255, 229, 255);
    m_Points.back()[1].position = point;     m_Points.back()[1].color = sf::Color(255, 229, 255);

    prevPoint = point;
    prevDisplacement = displ;
  }

  m_Points.push_back(sf::VertexArray(sf::Lines, 2));
  m_Points.back()[0].position = prevPoint;   m_Points.back()[0].color = sf::Color(255, 229, 255);
  m_Points.back()[1].position = EndPosition; m_Points.back()[1].color = sf::Color(255, 229, 255);
}
