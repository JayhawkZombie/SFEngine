#include "PhysicsDemo.h"
#include "Physics\Collider.h"
#include <Thor\Math.hpp>
#include <Thor\Config.hpp>
#include <Thor\Particles.hpp>
#include <Thor\Shapes.hpp>

PhysicsDemoLevel::PhysicsDemoLevel()
  :
  m_PColorAnimation1(m_PColorGradient1),
  m_PFadeAnimation1(0.3f, 0.3f),
  m_PTorqueAffector1(100.f),
  m_PGravityAffector1(sf::Vector2f(0.f, 5.f)),
  BasicLevel(sf::Vector2u(1700, 900), sf::FloatRect(0, 0, 1700, 900)),
  m_TorchAnimator(m_TorchAnimationMap),
  m_StarField(Engine::WindowSize, 350u, sf::Color(0, 255, 255)),
  m_ParticlePath(Engine::SplinePath::Connected | Engine::SplinePath::Smooth | Engine::SplinePath::Cubic),
  m_PColorAnimation2(m_PColorGradient2),
  m_PFadeAnimation2(0.3f, 0.3f),
  m_PGravityAffector2(sf::Vector2f(0.f, 5.f))
{
  m_TorchTexture = std::make_shared<sf::Texture>();
  m_TorchTexture->loadFromFile("./Projects/PuzzleDemo/Assets/Textures/torchsheet.png");
  m_TorchObject = std::make_shared<Engine::LevelObject>();
  m_TorchObject->SetTexture(m_TorchTexture);
  m_TorchSprite.setTexture(*m_TorchTexture);

  TFrame.addFrame(1.f, { 0,0,128,128 });
  TFrame.addFrame(1.f, { 128,0,128,128 });
  TFrame.addFrame(1.f, { 0,128,128,128 });
  TFrame.addFrame(1.f, { 128,128,128,128 });
  TFrame.addFrame(1.f, { 256,0,128,128 });
  TFrame.addFrame(1.f, { 256,128,128,128 });
  TFrame.addFrame(1.f, { 384,0,128,128 });
  TFrame.addFrame(1.f, { 384,128,128,128 });
  TFrame.addFrame(1.f, { 0,256,128,128 });
  TFrame.addFrame(1.f, { 0,384,128,128 });
  TFrame.addFrame(1.f, { 128,256,128,128 });
  TFrame.addFrame(1.f, { 256,256,128,128 });
  TFrame.addFrame(1.f, { 128,384,128,128 });
  TFrame.addFrame(1.f, { 256,384,128,128 });
  TFrame.addFrame(1.f, { 384,256,128,128 });
  TFrame.addFrame(1.f, { 384,384,128,128 });
  TFrame.addFrame(1.f, { 512,0,128,128 });
  TFrame.addFrame(1.f, { 640,0,128,128 });
  TFrame.addFrame(1.f, { 512,128,128,128 });
  TFrame.addFrame(1.f, { 768,0,128,128 });
  TFrame.addFrame(1.f, { 640,128,128,128 });
  TFrame.addFrame(1.f, { 512,256,128,128 });
  TFrame.addFrame(1.f, { 640,256,128,128 });
  TFrame.addFrame(1.f, { 512,384,128,128 });
  TFrame.addFrame(1.f, { 768,128,128,128 });
  TFrame.addFrame(1.f, { 896,0,128,128 });
  TFrame.addFrame(1.f, { 896,128,128,128 });
  TFrame.addFrame(1.f, { 768,256,128,128 });
  TFrame.addFrame(1.f, { 640,384,128,128 });
  TFrame.addFrame(1.f, { 768,384,128,128 });
  TFrame.addFrame(1.f, { 896,256,128,128 });
  TFrame.addFrame(1.f, { 896,384,128,128 });
  TFrame.addFrame(1.f, { 0,512,128,128 });
  TFrame.addFrame(1.f, { 128,512,128,128 });
  TFrame.addFrame(1.f, { 0,640,128,128 });
  TFrame.addFrame(1.f, { 128,640,128,128 });
  TFrame.addFrame(1.f, { 0,768,128,128 });
  TFrame.addFrame(1.f, { 256,512,128,128 });
  TFrame.addFrame(1.f, { 128,768,128,128 });
  TFrame.addFrame(1.f, { 0,896,128,128 });
  TFrame.addFrame(1.f, { 256,640,128,128 });
  TFrame.addFrame(1.f, { 384,512,128,128 });
  TFrame.addFrame(1.f, { 512,512,128,128 });
  TFrame.addFrame(1.f, { 256,768,128,128 });
  TFrame.addFrame(1.f, { 128,896,128,128 });
  TFrame.addFrame(1.f, { 384,640,128,128 });
  TFrame.addFrame(1.f, { 256,896,128,128 });
  TFrame.addFrame(1.f, { 512,640,128,128 });
  TFrame.addFrame(1.f, { 384,768,128,128 });
  TFrame.addFrame(1.f, { 640,512,128,128 });
  TFrame.addFrame(1.f, { 512,768,128,128 });
  TFrame.addFrame(1.f, { 384,896,128,128 });
  TFrame.addFrame(1.f, { 768,512,128,128 });
  TFrame.addFrame(1.f, { 640,640,128,128 });
  TFrame.addFrame(1.f, { 768,640,128,128 });
  TFrame.addFrame(1.f, { 640,768,128,128 });
  TFrame.addFrame(1.f, { 512,896,128,128 });
  TFrame.addFrame(1.f, { 896,512,128,128 });
  TFrame.addFrame(1.f, { 640,896,128,128 });
  TFrame.addFrame(1.f, { 896,640,128,128 });
  TFrame.addFrame(1.f, { 768,768,128,128 });
  TFrame.addFrame(1.f, { 896,768,128,128 });
  TFrame.addFrame(1.f, { 768,896,128,128 });
  TFrame.addFrame(1.f, { 896,896,128,128 });

  m_TorchAnimationMap.addAnimation("Flame", TFrame, sf::seconds(2.6));
  m_TorchAnimator.animate(m_TorchSprite);
  m_TorchSprite.setPosition({ 0, 700 });

  m_ThemePtr = std::make_shared<tgui::Theme>("./Projects/PuzzleDemo/Assets/UIThemes/TransparentGray.theme");
  m_BackButton = m_ThemePtr->load("button");
  
  TGUI_ELEMENT_BUTTON_CREATE_HIDDEN
  (
    m_BackButton, 
    "PhysicsDemoBackButton", 
    m_ThemePtr, 
    sf::Vector2f(200, 35), 
    sf::Vector2f(10, 10), 
    "back", 12, 
    Engine::GUI
  );

  m_BackButton->connect("clicked", []() { Engine::LoadLevelByName("MainMenu"); });



  m_TorchParticleTexture.loadFromFile("./Projects/PuzzleDemo/Assets/Textures/superblurredparticle.png");
  m_PEmitter1.setEmissionRate(25.f);
  m_PEmitter1.setParticleLifetime(sf::seconds(2.f));

  m_PSystem1.setTexture(m_TorchParticleTexture);
  m_PSystem1.addEmitter(thor::refEmitter(m_PEmitter1));

  m_PEmitter1.setParticlePosition(sf::Vector2f(64.f, 764.f));
  m_PEmitter1.setParticleScale(sf::Vector2f(0.4f, 0.3f));
  m_PEmitter1.setParticleRotationSpeed(thor::randomDev(0.f, 15.f));
  m_PEmitter1.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 1), 15.f));

  m_PColorGradient1[0.f] = sf::Color(221, 62, 0);
  m_PColorGradient1[0.5f] = sf::Color(219, 32, 0);
  m_PColorGradient1[0.7f] = sf::Color(219, 105, 0);
  m_PColorGradient1[1.f] = sf::Color(63, 63, 63);

  m_PColorAnimation1 = thor::ColorAnimation(m_PColorGradient1);

  m_PSystem1.addAffector(thor::AnimationAffector(m_PColorAnimation1));
  m_PSystem1.addAffector(thor::AnimationAffector(m_PFadeAnimation1));
  //m_PSystem1.addAffector(thor::TorqueAffector(150.f));
  m_PSystem1.addAffector(thor::ForceAffector(sf::Vector2f(0.f, -50.f)));
  m_TorchParticleVelocity = thor::PolarVector2f(200.f, -90.f);


  m_StarField.setColor(sf::Color(0, 255, 255));

  Gravity->x = 0.f;
  Gravity->y = 0.2f;

  /************************************************************************/
  /*                     Set up bitmap fonts                              */
  /************************************************************************/
  std::ifstream BMPFile("./SFEngine/Source/CoreFiles/Fonts/BitmapFonts/MarvelBitmap.fnt");
  m_BMPFont.loadTexture("./SFEngine/Source/CoreFiles/Fonts/BitmapFonts/MarvelBitmap_0.png");

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

      m_BMPFont.setTextureRect({ x, y, width, height }, id);
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

      m_BMPFont.setKerning(amount, KerningString);
    }

  }
  BMPFile.close();
  m_BMPText.setBitmapFont(m_BMPFont);
  m_BMPText.setColor(sf::Color::White);
  m_BMPText.setString("Countdown...");


  /************************************************************************/
  /*                    Set up countdown timing sequence                  */
  /************************************************************************/
  m_CountdownSequence.AddSequences(
    [this]() { this->StartCountdown(); },
    []() {},
    [this]() {this->EndCountdown(); },
    {
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 5 -> 4 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 4 -> 3 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 3 -> 2 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 2 -> 1 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }  /* 1 -> 0 */
    }
  );



  /************************************************************************/
  /*                    Set up time dialation timing sequence             */
  /************************************************************************/
  m_TimeDialationSequence.AddSequences(
    []() {},
    []() {},
    []() {},
    {
      { 1000.f, [this]() { this->BeginTimeDialation(); }, [this]() { this->UpdateTimeDialation(); } , [this]() { this->EndTimeDialation(); } }
    }
  );



  auto bounds = m_BMPText.getGlobalBounds();
  m_BMPText.setPosition(sf::Vector2f((Engine::WindowSize.x - bounds.width) / 2.f, 150.f));

  m_PEmitter2.setEmissionRate(450.f);
  m_PEmitter2.setParticleLifetime(sf::seconds(8.f));

  m_PSystem2.setTexture(m_TorchParticleTexture);
  m_PSystem2.addEmitter(thor::refEmitter(m_PEmitter2));

  m_PEmitter2.setParticlePosition(sf::Vector2f(64.f, 764.f));
  m_PEmitter2.setParticleScale(sf::Vector2f(0.4f, 0.3f));
  m_PEmitter2.setParticleRotationSpeed(thor::randomDev(0.f, 15.f));
  m_PEmitter2.setParticleVelocity(thor::Distributions::circle(sf::Vector2f(0, 0), 900.f));
  m_PEmitter2.setParticlePosition(thor::Distributions::circle(sf::Vector2f(1700.f / 2.f, 700.f), 35.f));

  m_PColorGradient2[0.f] = sf::Color(0, 216, 255);
  m_PColorGradient2[0.5f] = sf::Color(132, 244, 255);
  m_PColorGradient2[0.7f] = sf::Color(168, 247, 255);
  m_PColorGradient2[1.f] = sf::Color(255, 255, 255);

  m_PColorAnimation2 = thor::ColorAnimation(m_PColorGradient2);

  m_PSystem2.addAffector(thor::AnimationAffector(m_PColorAnimation2));
  m_PSystem2.addAffector(thor::AnimationAffector(m_PFadeAnimation2));
  m_PSystem2.addAffector(thor::TorqueAffector(150.f));
  //m_PSystem2.addAffector(thor::ForceAffector(sf::Vector2f(0.f, -50.f)));
  m_TorchParticleVelocity = thor::PolarVector2f(200.f, -90.f);


  m_RenderedScene.create((unsigned int)(Engine::WindowSize.x), (unsigned int)(700));

  SPtrShared<Engine::Collider2D> phy_1_collider = std::make_shared<Engine::Collider2D>();
  
  auto exp_m1 = Engine::BuildExpandPolygonMesh(4, 175.f, 0.f, sf::Vector2f(700.f, 650.f), sf::Vector2f(0.f, 0.f), 1.f, 0.f, 9.f, sf::Color::Green);
 // auto exp_m2 = Engine::BuildExpandPolygonMesh(4, 95.f, 0.f, sf::Vector2f(300.f, 650.f), sf::Vector2f(0.f, 0.f), 1.f, 0.f, 3.f, sf::Color::Green);

  m_ExpandingPolygons.emplace_back(exp_m1);
 // m_ExpandingPolygons.emplace_back(exp_m2);

  phy_1_collider->SetMesh(exp_m1);
//  phy_2_collider->SetMesh(exp_m2);

  m_ExpandObjects.emplace_back(std::make_shared<Engine::LevelObject>());
  m_ExpandObjects.back()->AddCollider(phy_1_collider);
  LevelObjects["phy_1"] = m_ExpandObjects.back();


  segwall1 = Engine::BuildSegmentMesh('b', { 325, 0 }, { 475, 325 }); segwall1->is_bulletProof = true;
  segwall2 = Engine::BuildSegmentMesh('b', { 1675, 0 }, { 1675 - 450, 75 + 250 }); segwall2->is_bulletProof = true;
  segFlip = Engine::BuildSegmentMesh('b', { 470, 325 }, { 1230, 325 }); segFlip->is_bulletProof = true;

  for (int i = 0; i < 50; ++i) {
    SpawnNPoly(5, 15, 0.f, { 350.f + 25.f * i, 10.f }, { 0, 0 }, 7.f, 0.9f, sf::Color::Red);
  }
}

PhysicsDemoLevel::~PhysicsDemoLevel()
{

}

void PhysicsDemoLevel::CleanUp()
{

}

void PhysicsDemoLevel::OnEnd()
{
  m_CountdownSequence.Clear();
  m_CountdownSequence.Stop();
  m_TimeDialationSequence.Clear();
  m_TimeDialationSequence.Stop();
  m_FlipOpenSeq.Clear();
  m_FlipOpenSeq.Stop();
}

void PhysicsDemoLevel::OnBegin()
{
  m_TorchAnimator.play() << "Flame" << thor::Playback::loop("Flame");
  m_PEmitter1.setParticleLifetime(thor::Distributions::uniform(sf::seconds(0.3f), sf::seconds(2.3f)));
  m_PEmitter1.setParticleScale(sf::Vector2f(0.2f, 0.25f));
  _clock.restart();
 // m_Faller->SetPosition({ Engine::WindowSize.x / 2.f, 10.f });
  LevelObjects["phy_1"]->GetColliders()[0]->GetMesh().lock()->setPosition(::vec2d(700.f, 450.f));
  LevelObjects["phy_1"]->GetColliders()[0]->GetMesh().lock()->v = ::vec2d(0, 0);
  Engine::SetGravity(Gravity);

  Segments.clear();
  Segments.push_back(segwall1);
  Segments.push_back(segwall2);
  Segments.push_back(segFlip);

  //reset countdown sequence
  m_CountdownSequence.Clear();
  m_CountdownSequence.AddSequences(
    [this]() { this->StartCountdown(); },
    []() {},
    [this]() {this->EndCountdown(); },
    {
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 5 -> 4 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 4 -> 3 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 3 -> 2 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }, /* 2 -> 1 */
      { 1000.f, [this]() {this->UpdateCountdown(); }, []() {}, []() {} }  /* 1 -> 0 */
    }
    );

  m_TimeDialationSequence.Clear();


  m_BMPText.setString("Dynamic Physics and Time Dilation");
  
  Engine::SetGravity(Gravity);
  m_CountdownSeqNumber = 5;
  m_CountdownSequence.Start();
  auto bounds = m_BMPText.getGlobalBounds();
  m_BMPText.setPosition(sf::Vector2f((Engine::WindowSize.x - bounds.width) / 2.f, 150.f));
  //m_Faller->Freeze();
  m_ExplosionActive = false;
  m_IsSlowingTime = false;
  TimeScale = 1.0;
  m_PSystem2.clearParticles();
  TotalTimeSpentDialating = 0.0;
  m_FlipOpenSeq.Stop();

  Engine::AssignBoundaries(Engine::WindowSize.y, Engine::WindowSize.x);
}

void PhysicsDemoLevel::HideUI()
{
  m_BackButton->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(250));
}

void PhysicsDemoLevel::ShowUI()
{
  m_BackButton->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(250));
}

void PhysicsDemoLevel::OnShutDown()
{

}

void PhysicsDemoLevel::EventUpdate(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::A) {
      for (auto & expander : m_ExpandingPolygons) {
        expander->Transform();
      }
    }
  }
}

void PhysicsDemoLevel::TickUpdate(const double &delta)
{
  static double particle_move_count = 0.0;
  static sf::Vector2f part_pos = sf::Vector2f(4.f, 764.f);

  if (m_IsSlowingTime) {
    TotalTimeSpentDialating += delta;
    if (TotalTimeSpentDialating >= 4000.0)
      TotalTimeSpentDialating = 4000.0;

    TimeScale = (1 - (TotalTimeSpentDialating / 4000.0));
    TimeScale = sqrt(TimeScale);
    //TimeScale *= TimeScale;

    if (TimeScale <= 0.001f) {
      m_IsSlowingTime = false;
      TotalTimeSpentDialating = 0.0;
      m_CountdownSequence.AddSequence(5000.0, []() { std::cerr << "Starting shatter timer...." << std::endl; }, []() {}, 
                                      [this]() { std::cerr << "Shattering time..." << std::endl; this->TotalTimeSpentDialating = 0.0; });
      m_CountdownSequence.Start();
    }
  }

  double d = delta * TimeScale;

  particle_move_count += d;

  auto time = _clock.restart();
  BasicLevel::TickUpdate(d);

  m_TorchAnimator.update(time * (float)TimeScale);
  m_TorchAnimator.animate(m_TorchSprite);
  m_FlipOpenSeq.TickUpdate(delta);
  //if (particle_move_count >= 50.0) {
  //  particle_move_count = 0.0;
  //  auto pos = m_ParticlePath.GetNextPathPoint();
  //  m_PEmitter1.setParticlePosition(thor::Distributions::circle(pos, 15.f));
  //  m_PSystem1.addAffector(thor::ForceAffector(pos - part_pos), sf::seconds(0.6f));
  //  m_PEmitter1.setParticleRotation(thor::randomDev(45.f, 32.f));
  // // m_PEmitter1.setParticleVelocity(pos - part_pos);
  //  m_PEmitter1.setParticleRotationSpeed(thor::randomDev(0.f, 45.f));

  //  part_pos = pos;
  //}
  //} 
  if (m_ExplosionActive) {
    sf::Time __t = time;
    __t *= (float)TimeScale;

    m_PSystem2.update(__t);
  }

  m_PEmitter1.setParticlePosition(thor::Distributions::circle(sf::Vector2f(64.f, 764.f), 35.f));
  m_PEmitter1.setParticleRotationSpeed(thor::randomDev(0.f, 45.f));
  
  m_PSystem1.update(time * (float)TimeScale);
  m_StarField.move(sf::Vector2f(time.asMilliseconds() * 0.05f, 0.f));

  m_CountdownSequence.TickUpdate(delta);
  m_TimeDialationSequence.TickUpdate(d);
}

void PhysicsDemoLevel::HandleInputEvent(const Engine::UserEvent &evnt)
{

}

void PhysicsDemoLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  
}

void PhysicsDemoLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  Texture->draw(m_PSystem1);
  Texture->draw(m_TorchSprite);
  Texture->draw(m_StarField);

  BasicLevel::RenderOnTexture(Texture);

  segwall1->draw(*Texture);
  segwall2->draw(*Texture);

  if (!m_FlipperOpen)
    segFlip->draw(*Texture);

  for (auto & ex : m_ExpandingPolygons)
    ex->draw(*Texture);

  if (m_ExplosionActive) {
    Texture->draw(m_PSystem2);
  }

  Texture->draw(m_BMPText);
  //m_ParticlePath.Render(Texture);
}

void PhysicsDemoLevel::SetNextLevel(std::shared_ptr<Engine::BasicLevel> NextLevel)
{

}

std::string PhysicsDemoLevel::GetClass() const
{
  return std::string("PhysicsDemo");
}

void PhysicsDemoLevel::OpenFlipper()
{
  if (Segments.size() > 2)
    Segments.erase(Segments.end() - 1);

  m_ExplosionActive = true;
  m_PSystem2.clearParticles();
 // segFlip->init_dn();
  m_FlipperOpen = true;
  m_IsSlowingTime = true;
}

void PhysicsDemoLevel::ShatterCollider()
{
}

void PhysicsDemoLevel::BeginTimeDialation()
{
  //m_BMPText.setString("Time dialation...");
  m_IsSlowingTime = true;
  m_ExplosionActive = true;
  //auto bounds = m_BMPText.getGlobalBounds();
  //m_BMPText.setPosition(sf::Vector2f((Engine::WindowSize.x - bounds.width) / 2.f, 150.f));
}

void PhysicsDemoLevel::UpdateTimeDialation()
{
}

void PhysicsDemoLevel::EndTimeDialation()
{
  //m_BMPText.setString("Time frozen...");
  m_IsSlowingTime = false;
  
  //auto bounds = m_BMPText.getGlobalBounds();
  //m_BMPText.setPosition(sf::Vector2f((Engine::WindowSize.x - bounds.width) / 2.f, 150.f));
}

void PhysicsDemoLevel::UpdateCountdown()
{
 // m_BMPText.setString("Countdown:    " + std::to_string(--m_CountdownSeqNumber) + "  ...");
  //auto bounds = m_BMPText.getGlobalBounds();
 // m_BMPText.setPosition(sf::Vector2f((Engine::WindowSize.x - bounds.width) / 2.f, 150.f));
}

void PhysicsDemoLevel::StartCountdown()
{
 // m_BMPText.setString("Countdown:    5  ...");
 // auto bounds = m_BMPText.getGlobalBounds();
  
  Engine::SetGravity(Gravity);
 // m_BMPText.setPosition(sf::Vector2f(   (Engine::WindowSize.x - bounds.width) / 2.f, 150.f ));
}

void PhysicsDemoLevel::EndCountdown()
{
 // m_BMPText.setString("GO");
  //m_Faller->Unfreeze();
  
  Engine::SetGravity(Gravity);
  auto bounds = m_BMPText.getGlobalBounds();
  m_BMPText.setPosition(sf::Vector2f((Engine::WindowSize.x - bounds.width) / 2.f, 150.f));

  m_FlipOpenSeq.AddSequences(
    []() {}, []() {}, [this]() { this->OpenFlipper(); },
    {
      { 2000, []() {}, []() {}, []() {}}
    }
    );
  m_FlipOpenSeq.Start();
}
