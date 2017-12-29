#include "DemoLoader.h"

#include "Projects\PuzzleDemo\Classes\Level1.h"

DemoLoadLevel::DemoLoadLevel()
  : 
  m_PColorAnimation1(m_PColorGradient1),
  m_PColorAnimation2(m_PColorGradient2),
  m_PFadeAnimation1(0.1f, 0.1f),
  m_PFadeAnimation2(0.1f, 0.1f),
  m_PTorqueAffector1(100.f),
  m_PTorqueAffector2(100.f),
  m_PGravityAffector1(sf::Vector2f(0.f, 5.f)),
  m_PGravityAffector2(sf::Vector2f(0.f, 5.f)),
  BasicLevel(sf::Vector2u(1700, 900), sf::FloatRect(0, 0, 1700, 900))
{
  m_TestRing.SetColor(sf::Color::Green);
  m_TestRing.SetPosition(sf::Vector2f(150, 270));
  m_TestRing.SetRadius(60.f);
  m_SFMLCardFrontTexture = std::make_shared<sf::Texture>();
  m_SFMLCardFrontTexture->loadFromFile("./Projects/PuzzleDemo/Assets/Textures/Card Face - SFML.png");
  m_SFMLCardBackTexture = std::make_shared<sf::Texture>();
  m_SFMLCardBackTexture->loadFromFile("./Projects/PuzzleDemo/Assets/Textures/Card Back - SFML.png");
  m_SFMLCard.SetTextureFrontBack(m_SFMLCardFrontTexture, m_SFMLCardBackTexture, { 0, 0, 110, 150 }, { 0, 0 });
  
  m_SFMLCard.SetPosition(sf::Vector2f(150, 500));
  m_SFMLCard.SetDepth(40);
  m_SFMLCard.Center();
  m_LevelMutex = std::make_shared<std::mutex>();

  std::ifstream BMPFile("./SFEngine/Source/CoreFiles/Fonts/BitmapFonts/MarvelBitmap.fnt");

  m_BitmapFont.loadTexture("./SFEngine/Source/CoreFiles/Fonts/BitmapFonts/MarvelBitmap_0.png");

  //get the char count
  std::string discard, linestart, equal, val_id; int count;
  if (BMPFile) {
    BMPFile >> linestart >> val_id >> equal >> count; // "chars count = #"

    int id, x, y, width, height, xoffset, yoffset, xadvance, page, chnl;

    for (int i = 0; i < count; ++i) {
      BMPFile >> linestart >> val_id >> equal >> id; //"chars id = #"
      BMPFile >> val_id >> equal >> x;        //std::cout << val_id << " " << equal << " " << x << " ";             //"x = #"
      BMPFile >> val_id >> equal >> y;        //std::cout << val_id << " " << equal << " " << y << " ";      //"y = #"
      BMPFile >> val_id >> equal >> width;    //std::cout << val_id << " " << equal << " " << width << " ";      //"width = #"
      BMPFile >> val_id >> equal >> height;   //std::cout << val_id << " " << equal << " " << height << " ";      //"height = #"
      BMPFile >> val_id >> equal >> xoffset;  //std::cout << val_id << " " << equal << " " << xoffset << " ";      //xoffset = #
      BMPFile >> val_id >> equal >> yoffset;  //std::cout << val_id << " " << equal << " " << yoffset << " ";
      BMPFile >> val_id >> equal >> xadvance; //std::cout << val_id << " " << equal << " " << xadvance << " ";
      BMPFile >> val_id >> equal >> page;     //std::cout << val_id << " " << equal << " " << page << " ";
      BMPFile >> val_id >> equal >> chnl;     //std::cout << val_id << " " << equal << " " << chnl << std::endl;

      m_BitmapFont.setTextureRect({ x, y, width, height }, id);
    }

    //Kerning pairs
    int first, second, amount;
    int kerningCount;

    BMPFile >> linestart >> val_id >> equal >> kerningCount; //"kernings count = 91"
    std::string KerningString = "12";
    //std::cout << linestart << " " << equal << kerningCount << std::endl;
    for (int i = 0; i < kerningCount; ++i) {
      BMPFile >> linestart >> val_id >> equal >> first; //std::cout << linestart << val_id << equal << first << "(" << (char)(first) << ") ";
      BMPFile >> val_id >> equal >> second; //std::cout << val_id << equal << second << "(" << (char)(second) << ") ";
      BMPFile >> val_id >> equal >> amount; //std::cout << val_id << equal << amount << std::endl; //"kerning first = # second = # amount = #"

      KerningString[0] = (char)(first);
      KerningString[1] = (char)(second);

      m_BitmapFont.setKerning(amount, KerningString);
    }

  }
  BMPFile.close();
  m_BitmapText.setBitmapFont(m_BitmapFont);
  m_BitmapText.setColor(sf::Color::White);
  m_BitmapText.setString("Loading Level1");

  auto __siz = m_BitmapText.getGlobalBounds();

  m_BitmapText.setPosition({ (Engine::WindowSize.x - __siz.width) / 2.f, (Engine::WindowSize.y - __siz.height) / 2.f - 50.f });
  m_ProgressBar.SetSize({ 500, 35 });
  m_ProgressBar.SetBackgroundColor(sf::Color(0, 71, 5));
  m_ProgressBar.SetFillColor(sf::Color(0, 255, 21));
  m_ProgressBar.SetFrameColor(sf::Color(99, 99, 99));
  m_ProgressBar.SetFrameThickness(2.f);
  m_ProgressBar.SetProgress(0.f);
  m_ProgressBar.SetPosition({ (Engine::WindowSize.x - 500.f) / 2.f, (Engine::WindowSize.y - __siz.height) / 2.f + __siz.height + 50.f });
  m_ProgressBar.SetFillRate(0.023f);

  Engine::ASyncLevelStreamThread::Load(
    [this]() -> SPtrShared<Engine::BasicLevel>
  {
    try
    {
      std::cerr << "Loading level" << std::endl;
      SPtrShared<Engine::BasicLevel> Loading = std::make_shared<Level1>();

      this->m_LevelMutex->lock();
      this->m_NextLevel = Loading;
      this->m_LoadingNextLevel = false;
      this->m_TimingWaitCount = false;
      this->m_TestRing.Reset();
      this->m_TestRing.Fill(5000.f);
      std::cerr << "Done loading level" << std::endl;
      this->m_LevelMutex->unlock();
      return Loading;
    }
    catch (std::exception& e)
    {
      std::cerr << "Failed to load Level1 in thread" << std::endl;
      return nullptr;
    }
  } ,
    "MainMenu"
    );


  m_PSystemTexture.loadFromFile("./SFEngine/Source/CoreFiles/Textures/particle.png");

  m_PEmitter1.setEmissionRate(45.f);
  m_PEmitter1.setParticleLifetime(sf::seconds(5.f));

  m_PSystem1.setTexture(m_PSystemTexture);
  m_PSystem1.addEmitter(thor::refEmitter(m_PEmitter1));
  m_PColorGradient1[0.f] = sf::Color(221, 62, 0);
  m_PColorGradient1[0.5f] = sf::Color(219, 32, 0);
  m_PColorGradient1[1.f] = sf::Color(219, 105, 0);


  m_PEmitter2.setEmissionRate(45.f);
  m_PEmitter2.setParticleLifetime(sf::seconds(5.f));

  m_PSystem2.setTexture(m_PSystemTexture);
  m_PSystem2.addEmitter(thor::refEmitter(m_PEmitter2));
  m_PColorGradient2[0.f] = sf::Color(0, 219, 215);
  m_PColorGradient2[0.5f] = sf::Color(193, 0, 219);
  m_PColorGradient2[1.f] = sf::Color(160, 0, 0);

}

DemoLoadLevel::~DemoLoadLevel()
{
  m_TestRingTexture.reset();
}

void DemoLoadLevel::CleanUp()
{
}

void DemoLoadLevel::OnEnd()
{
  m_ProgressBar.Reset();
}

void DemoLoadLevel::OnBegin()
{
  m_SFMLCard.Flip(750.f);
  m_ProgressBar.SetProgress(100.f);
}

void DemoLoadLevel::OnShutDown()
{
}

void DemoLoadLevel::EventUpdate(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::W)
      m_TestRing.FillTo(1.f, 2000.f);
    else if (event.key.code == sf::Keyboard::S)
      m_TestRing.Empty(2000.f);
    else if (event.key.code == sf::Keyboard::C)
      m_TestRing.SetColor(sf::Color::White);
  }
}

void DemoLoadLevel::TickUpdate(const double & delta)
{
  static sf::Clock _clock;
  static int printcount = 0;
  static bool changed_text = false;
  printcount++;

  m_LevelMutex->lock();

  if (!m_LoadingNextLevel && m_ProgressBar.GetProgress() >= 99.f && !changed_text) {
    m_BitmapText.setString("Press mouse button to continue...");
    auto __siz = m_BitmapText.getGlobalBounds();
    m_BitmapText.setPosition({ (Engine::WindowSize.x - __siz.width) / 2.f, (Engine::WindowSize.y - __siz.height) / 2.f - 50.f });
    changed_text = true;
    m_CanSwitchLevel = true;
  }

  m_ProgressBar.TickUpdate(delta);
  //m_SFMLCard.TickUpdate(delta);
  m_LevelMutex->unlock();
}

void DemoLoadLevel::HandleInputEvent(const Engine::UserEvent & evnt)
{
  if (evnt.EventType == Engine::UserEventType::MousePress && m_CanSwitchLevel) {
    Engine::SwitchLevel(m_NextLevel);
  }
  else if (evnt.EventType == Engine::UserEventType::KeyboardPress) {
    if (evnt.Key == sf::Keyboard::W)
      m_TestRing.FillTo(1.f, 1500.f);
    else if (evnt.Key == sf::Keyboard::S)
      m_TestRing.Empty(1500.f);
    else if (evnt.Key == sf::Keyboard::C)
      m_TestRing.SetColor(sf::Color::White);
  }
}

void DemoLoadLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void DemoLoadLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  m_LevelMutex->lock();
  //m_SFMLCard.Render(Texture);

  if (!m_TimingWaitCount)
    m_ProgressBar.Render(Texture);
  else
    m_TestRing.Render(Texture);

  Texture->draw(m_BitmapText);
  m_LevelMutex->unlock();
}

void DemoLoadLevel::SetNextLevel(std::shared_ptr<Engine::BasicLevel> NextLevel)
{
  m_NextLevel = NextLevel;
}

std::string DemoLoadLevel::GetClass() const
{
  return std::string("DemoLoadLevel");
}
