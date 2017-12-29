#include "Gem.h"
#include "Physics/Collider.h"

namespace
{
  const sf::Vector2f GemScale = { 41.f / 408.f, 41.f / 408.f };
}

ShatterGem::ShatterGem(const sf::Vector2f &InitPos)
  : m_ShatteredFragmentArrays(100, sf::VertexArray(sf::Quads, 4)),
  m_ShatteredFragmentVelocities(100, sf::Vector2f(0, 0))
{
  //x : 0 -> 408, y : 0 -> 408
  //X coordinates to shatter into
  float X1 = 0,   X2 = 41,  X3 = 123, X4 = 164, X5 = 205,
        X6 = 246, X7 = 287, X8 = 328, X9 = 369, X10 = 410;

  float Y1 = 0,   Y2 = 41,  Y3 = 123, Y4 = 164, Y5 = 205,
        Y6 = 246, Y7 = 287, Y8 = 328, Y9 = 369, Y10 = 410;

  m_ShatterPieces = {
    //x : 0 -> 410, y = 0
    { 0, 0,   41, 41 }, { 41, 0,   41, 41 }, { 82, 0,   41, 41 }, { 123, 0,   41, 41 }, { 164, 0,   41, 41 }, { 205, 0,   41, 41 }, { 246, 0,   41, 41 }, { 287, 0,   41, 41 }, { 287, 0,   41, 41 }, { 328, 0,   41, 41 }, { 369, 0,   41, 41 },
    { 0, 41,  41, 41 }, { 41, 41,  41, 41 }, { 82, 41,  41, 41 }, { 123, 41,  41, 41 }, { 164, 41,  41, 41 }, { 205, 41,  41, 41 }, { 246, 41,  41, 41 }, { 287, 41,  41, 41 }, { 287, 41,  41, 41 }, { 328, 41,  41, 41 }, { 369, 41,  41, 41 },
    { 0, 82,  41, 41 }, { 41, 82,  41, 41 }, { 82, 82,  41, 41 }, { 123, 82,  41, 41 }, { 164, 82,  41, 41 }, { 205, 82,  41, 41 }, { 246, 82,  41, 41 }, { 287, 82,  41, 41 }, { 287, 82,  41, 41 }, { 328, 82,  82, 41 }, { 369, 82,  82, 41 },
    { 0, 123, 41, 41 }, { 41, 123, 41, 41 }, { 82, 123, 41, 41 }, { 123, 123, 41, 41 }, { 164, 123, 41, 41 }, { 205, 123, 41, 41 }, { 246, 123, 41, 41 }, { 287, 123, 41, 41 }, { 287, 123, 41, 41 }, { 328, 123, 41, 41 }, { 369, 123, 41, 41 },
    { 0, 164, 41, 41 }, { 41, 164, 41, 41 }, { 82, 164, 41, 41 }, { 123, 164, 41, 41 }, { 164, 164, 41, 41 }, { 205, 164, 41, 41 }, { 246, 164, 41, 41 }, { 287, 164, 41, 41 }, { 287, 164, 41, 41 }, { 328, 164, 14, 41 }, { 369, 164, 82, 41 },
    { 0, 205, 41, 41 }, { 41, 205, 41, 41 }, { 82, 205, 41, 41 }, { 123, 205, 41, 41 }, { 164, 205, 41, 41 }, { 205, 205, 41, 41 }, { 246, 205, 41, 41 }, { 287, 205, 41, 41 }, { 287, 205, 41, 41 }, { 328, 205, 41, 41 }, { 369, 205, 41, 41 },
    { 0, 246, 41, 41 }, { 41, 246, 41, 41 }, { 82, 246, 41, 41 }, { 123, 246, 41, 41 }, { 164, 246, 41, 41 }, { 205, 246, 41, 41 }, { 246, 246, 41, 41 }, { 287, 246, 41, 41 }, { 287, 246, 41, 41 }, { 328, 246, 41, 41 }, { 369, 246, 41, 41 },
    { 0, 287, 41, 41 }, { 41, 287, 41, 41 }, { 82, 287, 41, 41 }, { 123, 287, 41, 41 }, { 164, 287, 41, 41 }, { 205, 287, 41, 41 }, { 246, 287, 41, 41 }, { 287, 287, 41, 41 }, { 287, 287, 41, 41 }, { 328, 287, 41, 41 }, { 369, 287, 41, 41 },
    { 0, 328, 41, 41 }, { 41, 328, 41, 41 }, { 82, 328, 41, 41 }, { 123, 328, 41, 41 }, { 164, 328, 41, 41 }, { 205, 328, 41, 41 }, { 246, 328, 41, 41 }, { 287, 328, 41, 41 }, { 287, 328, 41, 41 }, { 328, 328, 41, 41 }, { 369, 328, 41, 41 },
    { 0, 369, 41, 41 }, { 41, 369, 41, 41 }, { 82, 369, 41, 41 }, { 123, 369, 41, 41 }, { 164, 369, 41, 41 }, { 205, 369, 41, 41 }, { 246, 369, 41, 41 }, { 287, 369, 41, 41 }, { 287, 369, 41, 41 }, { 328, 369, 41, 41 }, { 369, 369, 41, 41 }
  };

  for (std::size_t i = 0; i < 100; ++i) {
    m_ShatteredFragmentArrays[i][0].texCoords.x = __TO_FLOAT__(m_ShatterPieces[i].left);
    m_ShatteredFragmentArrays[i][0].texCoords.y = __TO_FLOAT__(m_ShatterPieces[i].top);

    m_ShatteredFragmentArrays[i][1].texCoords.x = __TO_FLOAT__(m_ShatterPieces[i].left) + __TO_FLOAT__(m_ShatterPieces[i].width);
    m_ShatteredFragmentArrays[i][1].texCoords.y = __TO_FLOAT__(m_ShatterPieces[i].top);

    m_ShatteredFragmentArrays[i][2].texCoords.x = __TO_FLOAT__(m_ShatterPieces[i].left) + __TO_FLOAT__(m_ShatterPieces[i].width);
    m_ShatteredFragmentArrays[i][2].texCoords.y = __TO_FLOAT__(m_ShatterPieces[i].top)  + __TO_FLOAT__(m_ShatterPieces[i].height);

    m_ShatteredFragmentArrays[i][3].texCoords.x = __TO_FLOAT__(m_ShatterPieces[i].left);
    m_ShatteredFragmentArrays[i][3].texCoords.y = __TO_FLOAT__(m_ShatterPieces[i].top) + __TO_FLOAT__(m_ShatterPieces[i].height);

    /*Position data for fragments*/
    m_ShatteredFragmentArrays[i][0].position.x = __TO_FLOAT__(m_ShatterPieces[i].left);
    m_ShatteredFragmentArrays[i][0].position.y = __TO_FLOAT__(m_ShatterPieces[i].top);

    m_ShatteredFragmentArrays[i][1].position.x = __TO_FLOAT__(m_ShatterPieces[i].left) + __TO_FLOAT__(GemScale.x * m_ShatterPieces[i].width);
    m_ShatteredFragmentArrays[i][1].position.y = __TO_FLOAT__(m_ShatterPieces[i].top);

    m_ShatteredFragmentArrays[i][2].position.x = __TO_FLOAT__(m_ShatterPieces[i].left) + __TO_FLOAT__(GemScale.x * m_ShatterPieces[i].width);
    m_ShatteredFragmentArrays[i][2].position.y = __TO_FLOAT__(m_ShatterPieces[i].top)  + __TO_FLOAT__(GemScale.y * m_ShatterPieces[i].height);

    m_ShatteredFragmentArrays[i][3].position.x = __TO_FLOAT__(m_ShatterPieces[i].left);
    m_ShatteredFragmentArrays[i][3].position.y = __TO_FLOAT__(m_ShatterPieces[i].top)  + __TO_FLOAT__(GemScale.y * m_ShatterPieces[i].height);
  }

  m_ShatterTexture.loadFromFile("./Projects/PuzzleDemo/Assets/Textures/gems/gem2_horizontal.png");
  m_GemTexture.loadFromFile("./Projects/PuzzleDemo/Assets/Textures/gems/gem2.png");

  Sprite.setTexture(m_GemTexture);
  Sprite.setPosition(InitPos);
  Sprite.setScale({ 41.f / 408.f, 41.f / 408.f });

  Position = InitPos;
  AddCollider(Engine::Collider2D::CreatePolygonMesh(4, 30.f, 3.141592653f / 2.f, Position + sf::Vector2f(41.f / 2.f, 41.f / 2.f), { 0, 0 }, 0.2f, 0.1f, sf::Color::Transparent));
}

ShatterGem::~ShatterGem()
{
  m_ShatterSound.resetBuffer();
}

void ShatterGem::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  if (!m_IsShattered) {
    Target->draw(Sprite);
    for (auto & coll : m_Colliders) {
      if (coll->GetMesh().lock())
        coll->GetMesh().lock()->draw(*Target);
    }
  }
  else {
    for (auto & seg : m_ShatteredFragmentArrays)
      Target->draw(seg, &m_ShatterTexture);
  }
}

void ShatterGem::TickUpdate(const double & delta)
{
  if (m_IsShattered)
    UpdateShatteredFragments(delta);
  m_Sequencer.TickUpdate(delta);

  static ::vec2d v2d_pos;
  v2d_pos = m_Colliders[0]->GetMesh().lock()->pos;

  Position = sf::Vector2f(v2d_pos.x - 30.f, v2d_pos.y - 30.f);
}

void ShatterGem::PhysicsUpdate()
{
  LevelObject::PhysicsUpdate();
}

void ShatterGem::OnShutDown()
{
}

void ShatterGem::OnGameStart()
{
  if (m_ShatterBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/Glass,Bottle,Break,Smash,Messy.ogg"))
    m_ShatterSound.setBuffer(m_ShatterBuffer);
}

void ShatterGem::OnGameEnd()
{
  m_ShatterSound.resetBuffer();
  m_ReverseShatterSound.resetBuffer();
}

void ShatterGem::OnKilled()
{
}

void ShatterGem::OnSpawn()
{
  Engine::Messager::PostToActivityLog(
    Engine::SystemMessage(Engine::SystemMessageType::ActivityLog, InternalID, 0, "PuzzleDemo/Gem - OnSpawn()")
  );

  m_Sequencer.AddSequence(5000, []() {}, []() {}, [this]() {this->Shatter(); });
  m_Sequencer.Start();
}

void ShatterGem::Shatter()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(-10, 10);

  m_IsShattered = true;
  m_IsReversing = false;

  for (auto & vel : m_ShatteredFragmentVelocities) {
    vel.x = static_cast<float>(dist(gen));
    vel.y = static_cast<float>(dist(gen));
  }

  sf::Vector2f _Position = Sprite.getPosition();

  for (std::size_t i = 0; i < 100; ++i) {
    m_ShatteredFragmentArrays[i][0].position = _Position;
    m_ShatteredFragmentArrays[i][1].position = _Position + sf::Vector2f(GemScale.x * m_ShatterPieces[i].width, 0);
    m_ShatteredFragmentArrays[i][2].position = _Position + sf::Vector2f(GemScale.x * m_ShatterPieces[i].width, GemScale.y * m_ShatterPieces[i].height);
    m_ShatteredFragmentArrays[i][3].position = _Position + sf::Vector2f(0,                                     GemScale.y * m_ShatterPieces[i].height);
  }

  m_ShatterSound.setVolume(80.f);
  m_ShatterSound.play();
  m_Sequencer.AddSequence(7500, []() {}, []() {}, [this]() {this->m_IsDead = true; });
}

void ShatterGem::Reassemble()
{
  for (auto & vel : m_ShatteredFragmentVelocities) {
    vel.x *= -1;
    vel.y *= -1;
  }
  m_IsReversing = true;
  m_IsShattered = true;
  m_ReverseShatterSound.play();

  m_Sequencer.AddSequence(7500, []() {}, []() {}, [this]() {this->Reset(); });
}

void ShatterGem::Reset()
{
  m_IsShattered = false;
  m_IsReversing = false;
}

bool ShatterGem::IsDead() const
{
  return m_IsDead;
}

void ShatterGem::RenderShatteredFragments()
{
}

void ShatterGem::UpdateShatteredFragments(const double &delta)
{
  for (std::size_t i = 0; i < 100; ++i) {
    m_ShatteredFragmentArrays[i][0].position += (float)(delta * delta * 0.005f) * m_ShatteredFragmentVelocities[i];
    m_ShatteredFragmentArrays[i][1].position += (float)(delta * delta * 0.005f) * m_ShatteredFragmentVelocities[i];
    m_ShatteredFragmentArrays[i][2].position += (float)(delta * delta * 0.005f) * m_ShatteredFragmentVelocities[i];
    m_ShatteredFragmentArrays[i][3].position += (float)(delta * delta * 0.005f) * m_ShatteredFragmentVelocities[i];
  }
}
