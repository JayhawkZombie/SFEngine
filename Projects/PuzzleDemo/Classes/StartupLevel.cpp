#include "StartupLevel.h"
#include "Messaging/CoreMessager.h"
#include "Threading/ASyncLoader.h"
#include "Level1.h"

StartupLevel::StartupLevel()
  : BasicLevel(sf::Vector2u(1700, 900), sf::FloatRect(0, 0, 1700, 900))
{
  m_LightningSequence.AddSequences(
    [this]() {this->LightningSequenceStarted(); }, //CB for the lightning sequence starting
    []() {},
    [this]() {this->LightningSequenceEnded(); },   //CB for the lightning sequence ending
    {
      { 400.0, [this]() { this->LightningSequenceCB(0,  1,  2,  3);  }, []() {}, []() {} }, // 4 bolts strike the 'S' character
      { 400.0, [this]() { this->LightningSequenceCB(4,  5,  6,  7);  }, []() {}, []() {} }, // 4 bolts strike the 'F' character
      { 400.0, [this]() { this->LightningSequenceCB(8,  9,  10, 11); }, []() {}, []() {} }, // 4 bolts strike the 'E' character
      { 400.0, [this]() { this->LightningSequenceCB(12, 13, 14, 15); }, []() {}, []() {} }, // 4 bolts strike the 'N' character
      { 400.0, [this]() { this->LightningSequenceCB(16, 17, 18, 19); }, []() {}, []() {} }, // 4 bolts strike the 'G' character
      { 400.0, [this]() { this->LightningSequenceCB(20, 21, 22, 23); }, []() {}, []() {} }, // 4 bolts strike the 'I' character
      { 400.0, [this]() { this->LightningSequenceCB(24, 25, 26, 27); }, []() {}, []() {} }, // 4 bolts strike the 'N' character
      { 400.0, [this]() { this->LightningSequenceCB(28, 29, 30, 31); }, []() {}, []() {} }, // 4 bolts strike the 'E' character
      { 3500.0, []() {}, []() {}, []() {} }
    }
  );

  m_SpinnerTexture.loadFromFile("./Projects/PuzzleDemo/Assets/Textures/LoadingWhite.png");
  m_SpinnerSprite.setTexture(m_SpinnerTexture);

  m_spinnerFrames.addFrame(1.f, sf::IntRect(0,  0,  78, 78));
  m_spinnerFrames.addFrame(1.f, sf::IntRect(78, 0,  78, 78));
  m_spinnerFrames.addFrame(1.f, sf::IntRect(78, 78, 78, 78));
  m_spinnerFrames.addFrame(1.f, sf::IntRect(0,  78, 78, 78));

  m_AnimMap = thor::AnimationMap<sf::Sprite, std::string>();
  m_AnimMap.addAnimation("loading", m_spinnerFrames, sf::seconds(0.35f));
  m_animator = new thor::Animator<sf::Sprite, std::string>(m_AnimMap);
  m_SpinnerSprite.setPosition({ 1700.f - 200.f, 900.f - 200.f });


  m_SFMLShatterTexture.loadFromFile("./Projects/PuzzleDemo/Assets/Textures/sfml-logo-big.png");
  m_SFMLLogoFrame.addFrame(0.f, sf::IntRect(0, 0, 1001, 304));
  m_SFMLLogoMap.addAnimation("sfml-logo", m_SFMLLogoFrame, sf::seconds(5.f));
  m_SFMLBeforeShatter.setTexture(m_SFMLShatterTexture);
  m_SFMLAnimator = new thor::Animator<sf::Sprite, std::string>(m_SFMLLogoMap);

  m_SFMLBeforeShatter.setPosition({ 349.5, 298 });
  m_LoadingNextLevel = true;

  ASyncLevelStreamThread::Load(
  
    [this]() -> SPtrShared<BasicLevel>
    {
      try
      {
        this->m_NextLevel = std::make_shared<Level1>();
        this->m_LoadingNextLevel = false;
        return m_NextLevel;
      }
      catch (std::exception& e)
      {
        std::cerr << "Failed to load level Level1" << std::endl;
        return nullptr;
      }
    },
  "Level1"
  );


}

StartupLevel::~StartupLevel()
{
  if (m_animator)
    delete m_animator;
}

void StartupLevel::TickUpdate(const double & delta)
{
  static sf::Clock thorClock;
  if (m_SequenceDone && !m_LoadingNextLevel) {
    SwitchLevel(m_NextLevel);
    return;
  }

  if (m_DrawShatters) {
    m_CurrentFadeDuration += (float)delta;

    if (m_CurrentFadeDuration >= m_SFMLFadeDuration)
      m_CurrentFadeDuration = (float)m_SFMLFadeDuration;
  }
  else
    m_CurrentFadeDuration = 0.f;

  m_SFMLBeforeShatter.setColor(sf::Color(255, 255, 255, 255 * (floor(m_CurrentFadeDuration / m_SFMLFadeDuration))));
  m_BoltTopLeft.TickUpdate(delta);
  m_BoltTopRight.TickUpdate(delta);
  m_BoltBottomLeft.TickUpdate(delta);
  m_BoltBottomRight.TickUpdate(delta);

  m_WeatherSystem.TickUpdate(delta);

  m_LightningSequence.TickUpdate(delta);
  for (int i = 0; i < 32; ++i)
    m_CrawlBolts[i].TickUpdate(delta);

  auto time = thorClock.restart();

  m_animator->update(time);
  m_animator->animate(m_SpinnerSprite);

  //m_SFMLAnimator->update(time);
  //m_SFMLAnimator->animate(m_SFMLBeforeShatter);
}

void StartupLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void StartupLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  Texture->clear(sf::Color::Transparent);
  m_BoltTopLeft.Render(Texture);
  m_BoltTopRight.Render(Texture);
  m_BoltBottomLeft.Render(Texture);
  m_BoltBottomRight.Render(Texture);

  Texture->draw(m_SpinnerSprite);

  if (m_DrawShatters)
    Texture->draw(m_SFMLBeforeShatter);

  if (m_DrawShatters)
    Texture->draw(m_SFMLBeforeShatter);

  m_WeatherSystem.Render(Texture);
  for (int i = 0; i < 32; ++i)
    m_CrawlBolts[i].Render(Texture);
}

void StartupLevel::OnShutDown()
{
}

void StartupLevel::HandleInputEvent(const UserEvent & evnt)
{

}

void StartupLevel::EventUpdate(sf::Event event)
{
  if (event.type == sf::Event::MouseButtonPressed) {
    Messager::PostToActivityLog(
      SystemMessage(SystemMessageType::ActivityLog, InternalID, 0, 
                            "StartupLevel - EventUpdate() - User Skipped Animation")
    );
    m_SequenceDone = true;
    m_LightningSequence.Clear();
    SwitchLevel(m_NextLevel);
  }
}

void StartupLevel::OnBegin()
{
  Messager::PostToActivityLog(
    SystemMessage(SystemMessageType::ActivityLog, InternalID, 0, "StartupLevel - OnBegin()")
  );

  TriggerCrawlingLightning();
  m_LightningSequence.Start();

  m_animator->play() << "loading" << thor::Playback::loop("loading");
}

void StartupLevel::OnEnd()
{
  Messager::PostToActivityLog(
    SystemMessage(SystemMessageType::ActivityLog, InternalID, 0, "StartupLevel - OnEnd()")
  );

  CleanUp();
}

void StartupLevel::CleanUp()
{
  m_BoltStrikePositions.clear();
  m_LightningTraces.clear();

  for (int i = 0; i < 32; ++i)
    m_CrawlBolts->Reset();

  if (m_animator) {
    m_animator->stop();
  }
}

void StartupLevel::SetNextLevel(std::shared_ptr<BasicLevel> NextLevel)
{
  m_NextLevel = NextLevel;
}

std::string StartupLevel::GetClass() const
{
  return std::string("StartupLevel");
}

void StartupLevel::TriggerCrawlingLightning()
{
  sf::Vector2f TopMid    = { 1700.f / 2.f, 0.f };
  sf::Vector2f TopLeft   = { 0.f,          0.f };
  sf::Vector2f TopRight  = { 1700.f,       0.f };
  sf::Vector2f BtmRight  = { 1700.f,       900.f };
  sf::Vector2f BtmLeft   = { 0.f,          900.f };
  sf::Vector2f LeftMid   = { 0.f,          900.f / 2.f };
  sf::Vector2f RightMid  = { 1700.f,       900.f / 2.f };
  sf::Vector2f BottomMid = { 1700.f / 2.f, 900.f };
  sf::Vector2f Center    = { 1700.f / 2.f, 900.f / 2.f };
  /*
  Letter layout
  S
  (0, 0)
  *___________________________* (214, 0)
  |      (22, 22)             |
  |     *____________________*| (214, 22)
  |     | (22, 44)
  |     |*____________________* (214, 44)
  |              (192, 66)    |
  |_____________________*     |
  (0, 88)                     |     |
  *____________________*|     |
  |                (192, 88)  |
  (0, 110)|*_________________________*| (214, 110)
  */

  sf::Vector2f S1  = { 0,   0 };
  sf::Vector2f S2  = { 214, 0 };
  sf::Vector2f S3  = { 214, 22 };
  sf::Vector2f S4  = { 22,  22 };
  sf::Vector2f S5  = { 22,  44 };
  sf::Vector2f S6  = { 214, 44 };
  sf::Vector2f S7  = { 214, 110 };
  sf::Vector2f S8  = { 0,   110 };
  sf::Vector2f S9  = { 0,   88 };
  sf::Vector2f S10 = { 192, 88 };
  sf::Vector2f S11 = { 192, 66 };
  sf::Vector2f S12 = { 0,   66 };

  sf::Vector2f F1  = { 0,   0 };
  sf::Vector2f F2  = { 214, 0 };
  sf::Vector2f F3  = { 214, 22 };
  sf::Vector2f F4  = { 22,  22 };
  sf::Vector2f F5  = { 22,  44 };
  sf::Vector2f F6  = { 214, 44 };
  sf::Vector2f F7  = { 214, 66 };
  sf::Vector2f F8  = { 22,  66 };
  sf::Vector2f F9  = { 22,  110 };
  sf::Vector2f F10 = { 0,   110 };

  sf::Vector2f E1  = { 0,   0 };
  sf::Vector2f E2  = { 214, 0 };
  sf::Vector2f E3  = { 214, 22 };
  sf::Vector2f E4  = { 22,  22 };
  sf::Vector2f E5  = { 22,  44 };
  sf::Vector2f E6  = { 214, 44 };
  sf::Vector2f E7  = { 214, 66 };
  sf::Vector2f E8  = { 22,  66 };
  sf::Vector2f E9  = { 22,  88 };
  sf::Vector2f E10 = { 214, 88 };
  sf::Vector2f E11 = { 214, 110 };
  sf::Vector2f E12 = { 0,   110 };

  sf::Vector2f N1 = { 0,    0 };
  sf::Vector2f N2 = { 214,  0 };
  sf::Vector2f N3 = { 214,  110 };
  sf::Vector2f N4 = { 192,  110 };
  sf::Vector2f N5 = { 192,  22 };
  sf::Vector2f N6 = { 22,   22 };
  sf::Vector2f N7 = { 22,   110 };
  sf::Vector2f N8 = { 0,    110 };

  sf::Vector2f G1  = { 0,   0 };
  sf::Vector2f G2  = { 214, 0 };
  sf::Vector2f G3  = { 214, 22 };
  sf::Vector2f G4  = { 22,  22 };
  sf::Vector2f G5  = { 22,  88 };
  sf::Vector2f G6  = { 192, 88 };
  sf::Vector2f G7  = { 192, 66 };
  sf::Vector2f G8  = { 80,  66 };
  sf::Vector2f G9  = { 80,  44 };
  sf::Vector2f G10 = { 214, 44 };
  sf::Vector2f G11 = { 214, 110 };
  sf::Vector2f G12 = { 0,   110 };

  sf::Vector2f I1 = { 0,  0 };
  sf::Vector2f I2 = { 22, 0 };
  sf::Vector2f I3 = { 22, 110 };
  sf::Vector2f I4 = { 0,  110 };

  float Scale = 1.f;

  sf::Vector2f STopLeft  = { 0, 318 };
  sf::Vector2f FTopLeft  = STopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 24, 0);
  sf::Vector2f ETopLeft  = FTopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 24, 0);
  sf::Vector2f NTopLeft  = ETopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 24, 0);
  sf::Vector2f GTopLeft  = NTopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 24, 0);
  sf::Vector2f ITopLeft  = GTopLeft  + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 24, 0);
  sf::Vector2f N2TopLeft = ITopLeft  + sf::Vector2f(Scale * 22,  0) + sf::Vector2f(Scale * 24, 0);
  sf::Vector2f E2TopLeft = N2TopLeft + sf::Vector2f(Scale * 214, 0) + sf::Vector2f(Scale * 24, 0);

  std::vector<sf::Vector2f> STrace = {
    //Letter S tracing
    STopLeft + Scale * S8,   STopLeft + Scale * S9,   STopLeft + Scale * S10,
    STopLeft + Scale * S11,  STopLeft + Scale * S12,  STopLeft + Scale * S1,
    STopLeft + Scale * S2,   STopLeft + Scale * S3,   STopLeft + Scale * S4,
    STopLeft + Scale * S5,   STopLeft + Scale * S6,   STopLeft + Scale * S7,
    STopLeft + Scale * S8
  };

  std::vector<sf::Vector2f> STrace2 = {
    //Letter S tracing, path 2
    STopLeft + Scale * S8,  STopLeft + Scale * S7,   STopLeft + Scale * S6,
    STopLeft + Scale * S5,  STopLeft + Scale * S4,   STopLeft + Scale * S3,
    STopLeft + Scale * S2,  STopLeft + Scale * S1,   STopLeft + Scale * S12,
    STopLeft + Scale * S11, STopLeft + Scale * S10,  STopLeft + Scale * S9,
    STopLeft + Scale * S8
  };

  std::vector<sf::Vector2f> FTrace = {
    FTopLeft + Scale * F10, FTopLeft + Scale * F9, FTopLeft + Scale * F8,
    FTopLeft + Scale * F7,  FTopLeft + Scale * F6, FTopLeft + Scale * F5,
    FTopLeft + Scale * F4,  FTopLeft + Scale * F3, FTopLeft + Scale * F2,
    FTopLeft + Scale * F1,  FTopLeft + Scale * F10
  };

  std::vector<sf::Vector2f> FTrace2 = {
    FTopLeft + Scale * F10, FTopLeft + Scale * F1, FTopLeft + Scale * F2,
    FTopLeft + Scale * F3,  FTopLeft + Scale * F4, FTopLeft + Scale * F5,
    FTopLeft + Scale * F6,  FTopLeft + Scale * F7, FTopLeft + Scale * F8,
    FTopLeft + Scale * F9,  FTopLeft + Scale * F10
  };

  std::vector<sf::Vector2f> ETrace = {
    ETopLeft + Scale * E12, ETopLeft + Scale * E11, ETopLeft + Scale * E10,
    ETopLeft + Scale * E9,  ETopLeft + Scale * E8,  ETopLeft + Scale * E7,
    ETopLeft + Scale * E6,  ETopLeft + Scale * E5,  ETopLeft + Scale * E4,
    ETopLeft + Scale * E3,  ETopLeft + Scale * E2,  ETopLeft + Scale * E1,
    ETopLeft + Scale * E12
  };

  std::vector<sf::Vector2f> ETrace2 = {
    ETopLeft + Scale * E12, ETopLeft + Scale * E1,  ETopLeft + Scale * E2,
    ETopLeft + Scale * E3,  ETopLeft + Scale * E4,  ETopLeft + Scale * E5,
    ETopLeft + Scale * E6,  ETopLeft + Scale * E7,  ETopLeft + Scale * E8,
    ETopLeft + Scale * E9,  ETopLeft + Scale * E10, ETopLeft + Scale * E11,
    ETopLeft + Scale * E12
  };

  std::vector<sf::Vector2f> NTrace = {
    NTopLeft + Scale * N7, NTopLeft + Scale * N8, NTopLeft + Scale * N1,
    NTopLeft + Scale * N2, NTopLeft + Scale * N3, NTopLeft + Scale * N4,
    NTopLeft + Scale * N5, NTopLeft + Scale * N6, NTopLeft + Scale * N7,
    NTopLeft + Scale * N8, NTopLeft + Scale * N1, NTopLeft + Scale * N2,
    NTopLeft + Scale * N3
  };

  std::vector<sf::Vector2f> NTrace2 = {
    NTopLeft + Scale * N4, NTopLeft + Scale * N3, NTopLeft + Scale * N2,
    NTopLeft + Scale * N1, NTopLeft + Scale * N8, NTopLeft + Scale * N7,
    NTopLeft + Scale * N6, NTopLeft + Scale * N5, NTopLeft + Scale * N4,
    NTopLeft + Scale * N3, NTopLeft + Scale * N2, NTopLeft + Scale * N1,
    NTopLeft + Scale * N8
  };

  std::vector<sf::Vector2f> GTrace = {
    GTopLeft + Scale * G12,
    GTopLeft + Scale * G1,  GTopLeft + Scale * G2,  GTopLeft + Scale * G3,
    GTopLeft + Scale * G4,  GTopLeft + Scale * G5,  GTopLeft + Scale * G6,
    GTopLeft + Scale * G7,  GTopLeft + Scale * G8,  GTopLeft + Scale * G9,
    GTopLeft + Scale * G10, GTopLeft + Scale * G11, GTopLeft + Scale * G12
  };

  std::vector<sf::Vector2f> GTrace2 = {
    GTopLeft + Scale * G1,
    GTopLeft + Scale * G12, GTopLeft + Scale * G11, GTopLeft + Scale * G10,
    GTopLeft + Scale * G9,  GTopLeft + Scale * G8,  GTopLeft + Scale * G7,
    GTopLeft + Scale * G6,  GTopLeft + Scale * G5,  GTopLeft + Scale * G4,
    GTopLeft + Scale * G3,  GTopLeft + Scale * G2,  GTopLeft + Scale * G1
  };

  std::vector<sf::Vector2f> ITrace = {
    ITopLeft + Scale * I4, ITopLeft + Scale * I1, ITopLeft + Scale * I2, ITopLeft + Scale * I3,
    ITopLeft + Scale * I4, ITopLeft + Scale * I1, ITopLeft + Scale * I2, ITopLeft + Scale * I3,
    ITopLeft + Scale * I4, ITopLeft + Scale * I1, ITopLeft + Scale * I2, ITopLeft + Scale * I3,
    ITopLeft + Scale * I4, ITopLeft + Scale * I1, ITopLeft + Scale * I2, ITopLeft + Scale * I3
  };

  std::vector<sf::Vector2f> ITrace2 = {
    ITopLeft + Scale * I4, ITopLeft + Scale * I3, ITopLeft + Scale * I2, ITopLeft + Scale * I1,
    ITopLeft + Scale * I4, ITopLeft + Scale * I3, ITopLeft + Scale * I2, ITopLeft + Scale * I1,
    ITopLeft + Scale * I4, ITopLeft + Scale * I3, ITopLeft + Scale * I2, ITopLeft + Scale * I1,
    ITopLeft + Scale * I4, ITopLeft + Scale * I3, ITopLeft + Scale * I2, ITopLeft + Scale * I1
  };

  std::vector<sf::Vector2f> N2Trace = {
    N2TopLeft + Scale * N7, N2TopLeft + Scale * N8, N2TopLeft + Scale * N1,
    N2TopLeft + Scale * N2, N2TopLeft + Scale * N3, N2TopLeft + Scale * N4,
    N2TopLeft + Scale * N5, N2TopLeft + Scale * N6, N2TopLeft + Scale * N7,
    N2TopLeft + Scale * N8, N2TopLeft + Scale * N1, N2TopLeft + Scale * N2,
    N2TopLeft + Scale * N3
  };

  std::vector<sf::Vector2f> N2Trace2 = {
    N2TopLeft + Scale * N4, N2TopLeft + Scale * N3, N2TopLeft + Scale * N2,
    N2TopLeft + Scale * N1, N2TopLeft + Scale * N8, N2TopLeft + Scale * N7,
    N2TopLeft + Scale * N6, N2TopLeft + Scale * N5, N2TopLeft + Scale * N4,
    N2TopLeft + Scale * N3, N2TopLeft + Scale * N2, N2TopLeft + Scale * N1,
    N2TopLeft + Scale * N8
  };

  std::vector<sf::Vector2f> E2Trace = {
    E2TopLeft + Scale * E12, E2TopLeft + Scale * E11, E2TopLeft + Scale * E10,
    E2TopLeft + Scale * E9,  E2TopLeft + Scale * E8,  E2TopLeft + Scale * E7,
    E2TopLeft + Scale * E6,  E2TopLeft + Scale * E5,  E2TopLeft + Scale * E4,
    E2TopLeft + Scale * E3,  E2TopLeft + Scale * E2,  E2TopLeft + Scale * E1,
    E2TopLeft + Scale * E12
  };

  std::vector<sf::Vector2f> E2Trace2 = {
    E2TopLeft + Scale * E12, E2TopLeft + Scale * E1,  E2TopLeft + Scale * E2,
    E2TopLeft + Scale * E3,  E2TopLeft + Scale * E4,  E2TopLeft + Scale * E5,
    E2TopLeft + Scale * E6,  E2TopLeft + Scale * E7,  E2TopLeft + Scale * E8,
    E2TopLeft + Scale * E9,  E2TopLeft + Scale * E10, E2TopLeft + Scale * E11,
    E2TopLeft + Scale * E12
  };

  m_LightningTraces.push_back(STrace);   m_LightningTraces.push_back(STrace);
  m_LightningTraces.push_back(STrace2);  m_LightningTraces.push_back(STrace2);
  m_LightningTraces.push_back(FTrace);   m_LightningTraces.push_back(FTrace);
  m_LightningTraces.push_back(FTrace2);  m_LightningTraces.push_back(FTrace2);
  m_LightningTraces.push_back(ETrace);   m_LightningTraces.push_back(ETrace);
  m_LightningTraces.push_back(ETrace2);  m_LightningTraces.push_back(ETrace2);
  m_LightningTraces.push_back(NTrace);   m_LightningTraces.push_back(NTrace);
  m_LightningTraces.push_back(NTrace2);  m_LightningTraces.push_back(NTrace2);
  m_LightningTraces.push_back(GTrace);   m_LightningTraces.push_back(GTrace);
  m_LightningTraces.push_back(GTrace2);  m_LightningTraces.push_back(GTrace2);
  m_LightningTraces.push_back(ITrace);   m_LightningTraces.push_back(ITrace);
  m_LightningTraces.push_back(ITrace2);  m_LightningTraces.push_back(ITrace2);
  m_LightningTraces.push_back(N2Trace);  m_LightningTraces.push_back(N2Trace);
  m_LightningTraces.push_back(N2Trace2); m_LightningTraces.push_back(N2Trace2);
  m_LightningTraces.push_back(E2Trace);  m_LightningTraces.push_back(E2Trace);
  m_LightningTraces.push_back(E2Trace2); m_LightningTraces.push_back(E2Trace2);

  m_BoltStrikePositions = {
    { STopLeft  }, { STopLeft  + Scale * sf::Vector2f(214, 0) }, { STopLeft.x,  STopLeft.y  + Scale * 110 }, { STopLeft.x  + Scale * 214, STopLeft.y  + Scale * 110 },
    { FTopLeft  }, { FTopLeft  + Scale * sf::Vector2f(214, 0) }, { FTopLeft.x,  FTopLeft.y  + Scale * 110 }, { FTopLeft.x  + Scale * 214, FTopLeft.y  + Scale * 110 },
    { ETopLeft  }, { ETopLeft  + Scale * sf::Vector2f(214, 0) }, { ETopLeft.x,  ETopLeft.y  + Scale * 110 }, { ETopLeft.x  + Scale * 214, ETopLeft.y  + Scale * 110 },
    { NTopLeft  }, { NTopLeft  + Scale * sf::Vector2f(214, 0) }, { NTopLeft.x,  NTopLeft.y  + Scale * 110 }, { NTopLeft.x  + Scale * 214, NTopLeft.y  + Scale * 110 },
    { GTopLeft  }, { GTopLeft  + Scale * sf::Vector2f(214, 0) }, { GTopLeft.x,  GTopLeft.y  + Scale * 110 }, { GTopLeft.x  + Scale * 214, GTopLeft.y  + Scale * 110 },
    { ITopLeft  }, { ITopLeft  + Scale * sf::Vector2f(22,  0) }, { ITopLeft.x,  ITopLeft.y  + Scale * 110 }, { ITopLeft.x  + Scale * 22,  ITopLeft.y  + Scale * 110 },
    { N2TopLeft }, { N2TopLeft + Scale * sf::Vector2f(214, 0) }, { N2TopLeft.x, N2TopLeft.y + Scale * 110 }, { N2TopLeft.x + Scale * 214, N2TopLeft.y + Scale * 110 },
    { E2TopLeft }, { E2TopLeft + Scale * sf::Vector2f(214, 0) }, { E2TopLeft.x, E2TopLeft.y + Scale * 110 }, { E2TopLeft.x + Scale * 214, E2TopLeft.y + Scale * 110 }
  };
}

void StartupLevel::LightningSequenceStarted()
{
}

void StartupLevel::LightningSequenceEnded()
{
  m_LightningSequenceDone = true;
  m_DrawShatters = true;
  m_SequenceDone = true;
  //m_LightningSequence.AddSequence(2500.0, []() {}, [this]() { this->m_SequenceDone = true; });
}

void StartupLevel::LightningSequenceCB(int Bolt1, int Bolt2, int Bolt3, int Bolt4)
{
  m_BoltTopLeft.Spark(    { 0.f,    0.f },   m_BoltStrikePositions[Bolt1]);
  m_BoltTopRight.Spark(   { 1700.f, 0.f },   m_BoltStrikePositions[Bolt2]);
  m_BoltBottomLeft.Spark( { 0.f,    900.f }, m_BoltStrikePositions[Bolt3]);
  m_BoltBottomRight.Spark({ 1700.f, 900.f }, m_BoltStrikePositions[Bolt4]);

  m_CrawlBolts[Bolt1].Spark(m_LightningTraces[Bolt1]);
  m_CrawlBolts[Bolt2].Spark(m_LightningTraces[Bolt2]);
  m_CrawlBolts[Bolt3].Spark(m_LightningTraces[Bolt3]);
  m_CrawlBolts[Bolt4].Spark(m_LightningTraces[Bolt4]);
}
