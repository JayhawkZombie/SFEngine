#include "Level1.h"

#include "../../TestProject/Classes/Levels/OakTree.h"
#include "../../TestProject/Classes/Levels/OakTreeChurchInterior.h"
#include "Levels\Stack.h"
#include "Levels\AITest.h"
#include "Levels\PhysicsDemo.h"

#include <Thor\Math.hpp>

namespace
{

  std::vector<std::string> ProgrammingSectionLabels = {
    "Engine - Kurt Slagle",
    "Engine - Nick Roudebush",
    "Engine - Colton Roemer",
    "Game / Engine - Cammy Vo",
    "Game / Engine - Austin Bailey"
  };

  std::vector<std::string> MusicSectionLabels = {
    "MainMenu Music - Chamber of Jewels - by Eric Matyas, www.soundimage.org",
    "Gem Demo Music - Castle of Despair - by Eric Matyas, www.soundimage.org",
    "Gem Demo Effect : Shatter - public domain, GCC2017 release",
    "Game Music     - By Shleby Scot"
  };
}

Level1::Level1()
  : 
  m_PColorAnimation1(m_PColorGradient1),
  m_PFadeAnimation1(0.3f, 0.3f),
  m_PTorqueAffector1(100.f),
  m_PGravityAffector1(sf::Vector2f(0.f, 5.f)),
  BasicLevel(sf::Vector2u( 1700, 900 ), sf::FloatRect(0, 0, 1700, 900 )),
  fader(0.1f, 0.1f),
  m_StarField(WindowSize, 1200u, sf::Color(0, 255, 255)),
  m_PColorAnimation2(m_PColorGradient2),
  m_PFadeAnimation2(0.3f, 0.3f),
  m_PTorqueAffector2(100.f),
  m_PGravityAffector2(sf::Vector2f(0.f, 5.f))
{
  if (m_BGMusicBuffer.loadFromFile("./Projects/PuzzleDemo/Assets/Sound/Chamber-of-Jewels.ogg"))
    m_BGMusic.setBuffer(m_BGMusicBuffer);

  //MainGUI = std::make_shared<tgui::Gui>(*Engine::currentRenderWindow);
  m_MenuTheme = std::make_shared<tgui::Theme>("./Projects/PuzzleDemo/Assets/UIThemes/TransparentGray.theme");
  font.loadFromFile("./Projects/TestProject/Fonts/Marvel-Regular.ttf");
  //MainGUI->setFont(font);

  OakTreeLevelPtr    = std::make_shared<OakTreeLevel>();
  OakTreeLevelPtr->SetID("oaktree");
  Levels["oaktree"] = OakTreeLevelPtr;
  OakTreeChurchInteriorLevelPtr = std::make_shared<OakTreeChurchInterior>();
  BallPuzzleLevelPtr = std::make_shared<BallStackLevel>();
  AITestLevelPtr     = std::make_shared<AITestLevel>();
  PhysicsDemoLevelPtr = std::make_shared<PhysicsDemoLevel>();

  //Create some buttons
  m_LevelSelectButon = m_MenuTheme->load("button");
  m_LevelSelectButon->setPosition({ 25, 300 });
  m_LevelSelectButon->setSize({ 200, 55 });
  m_LevelSelectButon->connect("clicked", [this]() {this->ShowLevelSelectScreen(); });
  m_LevelSelectButon->setText("select test level");
  m_LevelSelectButon->setTextSize(12);
  m_LevelSelectButon->hide();
  //MainGUI->add(NewGameButton, "NewGameButton");

  m_OptionsPanel = m_MenuTheme->load("panel");
  m_OptionsPanel->setSize({ 1700, 900 });

  m_LoadGameButton = m_MenuTheme->load("button");
  m_LoadGameButton->setPosition({ 25, 425 });
  m_LoadGameButton->setSize({ 200, 55 });
  m_LoadGameButton->setText("load game");
  m_LoadGameButton->setTextSize(12);
  m_LoadGameButton->disable();
  m_LoadGameButton->getRenderer()->setTextColor(sf::Color(180, 180, 180));
  m_LoadGameButton->hide();
  //MainGUI->add(m_LoadGameButton, "m_LoadGameButton");

  //m_AboutButton = m_MenuTheme->load("button");
  //m_AboutButton->setPosition({ 25, 550 });
  //m_AboutButton->setSize({ 200, 55 });
  //m_AboutButton->connect("clicked", [this]() {this->ShowAboutScreen(); });
  //m_AboutButton->setText("about");
  //m_AboutButton->setTextSize(12);
  //m_AboutButton->hide();
  //MainGUI->add(AboutButton, "AboutButton");

  m_OptionsButton = m_MenuTheme->load("button");
  m_OptionsButton->setPosition({ 25, 675 });
  m_OptionsButton->setSize({ 200, 55 });
  m_OptionsButton->connect("clicked", [this]()
  {
    this->ShowOptionsPanel();
  });

  m_OptionsButton->setText("options");
  m_OptionsButton->setTextSize(12);
  m_OptionsButton->hide();

  m_CloseButton = m_MenuTheme->load("button");
  m_CloseButton->setPosition({ 25, 800 });
  m_CloseButton->setSize({ 200, 55 });
  m_CloseButton->setText("quit");
  m_CloseButton->setTextSize(12);
  m_CloseButton->hide();
  m_CloseButton->connect("clicked", Shutdown);
  // MainGUI->add(CloseButton);

  tgui::Button::Ptr OptionsBack = m_MenuTheme->load("button");
  OptionsBack->setPosition({ 25, 425 });
  OptionsBack->setSize({ 200, 55 });
  OptionsBack->setText("back");
  OptionsBack->setTextSize(12);
  OptionsBack->connect("clicked", [this]()
  {
    this->HideOptionsPanel();
  });
  m_OptionsPanel->add(OptionsBack);

  m_MainPanel = m_MenuTheme->load("panel");
  m_MainPanel->setSize({ 1700, 900 });
  m_MainPanel->add(m_LevelSelectButon);
  m_MainPanel->add(m_LoadGameButton);
  m_MainPanel->add(m_OptionsButton);
  m_MainPanel->add(m_CloseButton);

  m_LevelSelectPanel = m_MenuTheme->load("panel");
  m_LevelSelectPanel->setSize({ 1700, 900 });
  
  tgui::Button::Ptr OakTreeLevel = m_MenuTheme->load("button");
  OakTreeLevel->setPosition({ 25, 450 });
  OakTreeLevel->setSize({ 200, 55 });
  OakTreeLevel->setText("Oak Tree");
  OakTreeLevel->setTextSize(12);
  OakTreeLevel->connect("clicked", [this]() { SwitchLevel(this->OakTreeLevelPtr); });
  m_LevelSelectPanel->add(OakTreeLevel);

  tgui::Button::Ptr BallLevel = m_MenuTheme->load("button");
  BallLevel->setPosition({ 25, 575 });
  BallLevel->setSize({ 200, 25 });
  BallLevel->setText("Ball Puzzle");
  BallLevel->setTextSize(12);
  BallLevel->connect("clicked", [this]() {SwitchLevel(this->BallPuzzleLevelPtr); });
  m_LevelSelectPanel->add(BallLevel);

  LevelSelectBack = m_MenuTheme->load("button");
  LevelSelectBack->setPosition({ 25, 825 });

  tgui::Button::Ptr PhysisDemoLevelButton = m_MenuTheme->load("button");
  PhysisDemoLevelButton->setPosition({ 25, 800 });
  PhysisDemoLevelButton->setSize({ 200,55 });
  PhysisDemoLevelButton->setText("PhysicsDemo");
  PhysisDemoLevelButton->setTextSize(10);
  PhysisDemoLevelButton->connect("clicked", [this]() {SwitchLevel(this->PhysicsDemoLevelPtr); });
  m_LevelSelectPanel->add(PhysisDemoLevelButton);

  tgui::Button::Ptr OakTreeChurchInteriorLevel = m_MenuTheme->load("button");
  OakTreeChurchInteriorLevel->setPosition({ 25, 700 });
  OakTreeChurchInteriorLevel->setSize({ 200,55 });
  OakTreeChurchInteriorLevel->setText("OakTree Church");
  OakTreeChurchInteriorLevel->setTextSize(10);
  OakTreeChurchInteriorLevel->connect("clicked", [this]() {SwitchLevel(this->OakTreeChurchInteriorLevelPtr); });
  m_LevelSelectPanel->add(OakTreeChurchInteriorLevel);

  LevelSelectBack = m_MenuTheme->load("button");
  LevelSelectBack->setPosition({ 25,  625 });
  LevelSelectBack->setSize({ 200, 55 });
  LevelSelectBack->setText("back");
  LevelSelectBack->setTextSize(12);
  LevelSelectBack->connect("clicked", [this]() {this->LevelSelectGoBack(); });
  m_LevelSelectPanel->add(LevelSelectBack);

  m_LevelSelectPanel->hide();

  m_OptionsPanel->hide();
  m_OptionsPanel->disable();

  //Engine::GUI->add(m_MainPanel);
  //Engine::GUI->add(m_OptionsPanel);
  //Engine::GUI->add(m_LevelSelectPanel);
  //MainGUI->add(MainPanel);
  //MainGUI->add(OptionsPanel);
  //MainGUI->add(LevelSelectPanel);

  TGUI_ELEMENT_BUTTON_CREATE_HIDDEN(
    ELEMENT_PTR        m_CreditsButton,
    ELEMENT_TEXT       "ToCreditsButton",
    ELEMENT_THEME      m_MenuTheme,
    ELEMENT_SIZE       sf::Vector2f(200, 55),
    ELEMENT_POSITION   sf::Vector2f(25, 550),
    ELEMENT_TEXT       "credits",
    ELEMENT_TEXT_SIZE  12,
    ELEMENT_PARENT_GUI m_MainPanel
  );
  m_CreditsButton->connect("clicked", [this]() {this->ShowAboutScreen(); });
  MakeCreditsPanel();

  texture.loadFromFile("./Projects/TestProject/Textures/particle.png");

  emitter.setEmissionRate(85.f);
  emitter.setParticleLifetime(sf::seconds(6));

  system.setTexture(texture);
  system.addEmitter(thor::refEmitter(emitter));

  emitter.setParticlePosition(sf::Vector2f(0, 0));
  emitter.setParticleScale(sf::Vector2f(0.4f, 0.3f));

  gradient[0.f] = sf::Color(0, 242, 255);
  gradient[0.5f] = sf::Color(0, 106, 112, 112);
  gradient[1.f] = sf::Color(0, 0, 0, 0);

  colorizer = new thor::ColorAnimation(gradient);

  system.addAffector(thor::AnimationAffector(*colorizer));
  system.addAffector(thor::AnimationAffector(fader));
  system.addAffector(thor::TorqueAffector(150.f));
  system.addAffector(thor::ForceAffector(sf::Vector2f(0.f, 50.f)));
  velocity = thor::PolarVector2f(200.f, -90.f);


  /*
   *      tgui::CheckBox::Ptr m_EnableVSync;
  tgui::SpinButton::Ptr m_FrameRateSpinButton;
  tgui::ComboBox::Ptr m_AALevelOptions;
   *
   **/

  m_EnableVSync = m_MenuTheme->load("checkbox");
  m_EnableVSync->setText("EnableVSync");
  m_EnableVSync->setPosition(sf::Vector2f(40.f, 100.f));
  m_EnableVSync->setSize(sf::Vector2f(15.f, 15.f));
  m_EnableVSync->setTextSize(16);
  m_OptionsPanel->add(m_EnableVSync);
  m_EnableVSync->connect("checked",
                         [this]()
  {
    this->fRateLabel->setText("Framerate Limit: <locked>");
    this->m_FrameRateSpinButton->disable();
  });

  m_EnableVSync->connect("unchecked",
                         [this]()
  {
    this->fRateLabel->setText("Framerate Limit: " + std::to_string(FramerateLimit));
    this->m_FrameRateSpinButton->enable();
  });

  m_FrameRateSpinButton = m_MenuTheme->load("spinbutton");
  m_FrameRateSpinButton->setValue(120);
  m_FrameRateSpinButton->setVerticalScroll(true);
  
  fRateLabel = m_MenuTheme->load("label");
  fRateLabel->setText("Framerate Limit: " + std::to_string(FramerateLimit));
  fRateLabel->setPosition({ 40.f, 150.f });
  fRateLabel->setSize({ 100.f, 35.f });
  fRateLabel->setTextSize(16);
  m_FrameRateSpinButton->connect("valuechanged", [this](int val) 
  { 
    if (val <= 30)
      val = 30;
    this->fRateLabel->setText("Framerate Limit: " + std::to_string(val));
    FramerateLimit = val;
    currentRenderWindow->setFramerateLimit(val);
  });

  m_ParticlePath.AddVertices({ 
    { 100.f, 550.f },
    { 150.f, 545.f },
    { 200.f, 560.f },
    { 30.f,  570.f },
    { 40.f,  800.f },
    { 600.f, 900.f },
    { 700.f, 510.f },
    { 800.f, 473.f },
    { 1200.f, 861.f },
    { 1093.f, 627.f },
    { 893.f, 549.f },
    { 729.f, 555.f },
    { 600.f, 460.f },
    { 230.f, 220.f },
    { 100.f, 550.f } });
  m_ParticlePath.SetInterpolationSteps(80);
  m_ParticlePath.MakeSmooth();
  m_ParticlePath.Update();


  m_ParticlePath2.AddVertices({
    { 700.f, 510.f },
    { 800.f, 473.f },
    { 1200.f, 861.f },
    { 1093.f, 627.f },
    { 893.f, 549.f },
    { 729.f, 555.f },
    { 600.f, 460.f },
    { 230.f, 220.f },
    { 100.f, 550.f },
    { 150.f, 545.f },
    { 200.f, 560.f },
    { 30.f,  570.f },
    { 40.f,  800.f },
    { 600.f, 900.f },
    { 700.f, 510.f } });
  m_ParticlePath2.SetInterpolationSteps(80);
  m_ParticlePath2.MakeSmooth();
  m_ParticlePath2.Update();

  /************************************************************************/
  /*                              PARTICLE SYSTEM 1                       */
  /************************************************************************/

  m_TorchParticleTexture.loadFromFile("./Projects/PuzzleDemo/Assets/Textures/superblurredparticle.png");
  m_PEmitter1.setEmissionRate(250.f);
  m_PEmitter1.setParticleLifetime(sf::seconds(2.5f));

  m_PSystem1.setTexture(m_TorchParticleTexture);
  m_PSystem1.addEmitter(thor::refEmitter(m_PEmitter1));

  m_PEmitter1.setParticlePosition(sf::Vector2f(64.f, 764.f));
  m_PEmitter1.setParticleScale(sf::Vector2f(0.6f, 0.6f));
  //m_PEmitter1.setParticleRotationSpeed(thor::randomDev(0.f, 15.f));

  m_PColorGradient1[0.f] = sf::Color(255, 229, 0);
  m_PColorGradient1[0.4f] = sf::Color(255, 59, 0);
  m_PColorGradient1[0.5f] = sf::Color(186, 55, 0);
  m_PColorGradient1[0.7f] = sf::Color(130, 2, 0);
  m_PColorGradient1[1.f] = sf::Color(63, 63, 63);

  m_PColorAnimation1 = thor::ColorAnimation(m_PColorGradient1);

  m_PSystem1.addAffector(thor::AnimationAffector(m_PColorAnimation1));
  m_PSystem1.addAffector(thor::AnimationAffector(m_PFadeAnimation1));
  m_PSystem1.addAffector(thor::TorqueAffector(150.f));
  m_PSystem1.addAffector(thor::ForceAffector(sf::Vector2f(0.f, -50.f)));


  /************************************************************************/
  /*                              PARTICLE SYSTEM 2                       */
  /************************************************************************/
  m_PEmitter2.setEmissionRate(250.f);
  m_PEmitter2.setParticleLifetime(sf::seconds(2.5f));

  m_PSystem2.setTexture(m_TorchParticleTexture);
  m_PSystem2.addEmitter(thor::refEmitter(m_PEmitter2));

  m_PEmitter2.setParticlePosition(sf::Vector2f(64.f, 764.f));
  m_PEmitter2.setParticleScale(sf::Vector2f(0.6f, 0.6f));
  //m_PEmitter2.setParticleRotationSpeed(thor::randomDev(0.f, 15.f));

  m_PColorGradient2[0.f] = sf::Color(0, 255, 255);
  m_PColorGradient2[0.4f] = sf::Color(0, 40, 186);
  m_PColorGradient2[0.5f] = sf::Color(64, 0, 155);
  m_PColorGradient2[0.7f] = sf::Color(78, 0, 104);
  m_PColorGradient2[1.f] = sf::Color(48, 48, 48);

  m_PColorAnimation2 = thor::ColorAnimation(m_PColorGradient2);

  m_PSystem2.addAffector(thor::AnimationAffector(m_PColorAnimation2));
  m_PSystem2.addAffector(thor::AnimationAffector(m_PFadeAnimation2));
  m_PSystem2.addAffector(thor::TorqueAffector(150.f));
  m_PSystem2.addAffector(thor::ForceAffector(sf::Vector2f(0.f, -50.f)));
}

Level1::~Level1()
{
  
}

void Level1::TickUpdate(const double & delta)
{
  static double particle_move_count = 0.0;
  static sf::Vector2f part_pos = sf::Vector2f(4.f, 764.f);
  particle_move_count += delta;

  static sf::Clock thorClock;
  m_WeatherSystem.TickUpdate(delta);

  static sf::Time time = sf::seconds(0);
  static sf::Clock _clock;

  auto pos = m_ParticlePath.GetNextPathPoint();
  auto pos2 = m_ParticlePath2.GetNextPathPoint();
  m_PEmitter1.setParticlePosition(thor::Distributions::circle(pos, 17.f));
  m_PEmitter2.setParticlePosition(thor::Distributions::circle(pos2, 21.f));

  part_pos = pos;

  auto __time = fClock.restart();

  m_PSystem1.update(__time);
  m_PSystem2.update(__time);
  m_StarField.move(sf::Vector2f(__time.asMilliseconds() * 0.05, 0.f));
}

void Level1::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void Level1::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  Texture->clear(sf::Color::Transparent);
  //Texture->draw(system);
  Texture->draw(m_StarField);

  if (m_DrawSplines) { 
    m_ParticlePath.Render(Texture);
    m_ParticlePath2.Render(Texture);
  }

  Texture->draw(m_PSystem1);
  Texture->draw(m_PSystem1);

  Texture->draw(m_PSystem2);
  Texture->draw(m_PSystem2);
  m_WeatherSystem.Render(Texture);
  //MainGUI->draw();
}

void Level1::OnShutDown()
{
}

void Level1::HandleInputEvent(const UserEvent & evnt)
{
  if (evnt.EventType == UserEventType::KeyboardPress) {
    if (evnt.Key == sf::Keyboard::Key::Escape)
      m_Paused = !m_Paused;
  }
}

void Level1::EventUpdate(sf::Event event)
{
  //Engine::GUI->handleEvent(event);
  if (event.type == sf::Event::KeyPressed)
    if (event.key.code == sf::Keyboard::S)
      m_DrawSplines = !m_DrawSplines;
}

void Level1::OnBegin()
{
  Messager::PostToActivityLog(
    SystemMessage(SystemMessageType::ActivityLog, InternalID, 0, "Level1 - OnBegin()")
  );

  m_BGMusic.setLoop(true);
  m_BGMusic.play();
  m_StarField.regenerate();
}

void Level1::OnEnd()
{
  Messager::PostToActivityLog(
    SystemMessage(SystemMessageType::ActivityLog, InternalID, 0, "Level1 - OnEnd()")
  );

  m_BGMusic.stop();

  GUI->remove(m_MainPanel);
  GUI->remove(m_OptionsPanel);
  GUI->remove(m_CreditsPanel);
  GUI->remove(m_LevelSelectPanel);
}

void Level1::HideUI()
{
  GUI->remove(m_MainPanel);
  GUI->remove(m_OptionsPanel);
  GUI->remove(m_CreditsPanel);
  GUI->remove(m_LevelSelectPanel);
}

void Level1::ShowUI()
{
  GUI->add(m_MainPanel);
  GUI->add(m_OptionsPanel);
  GUI->add(m_CreditsPanel);
  GUI->add(m_LevelSelectPanel);

  m_OptionsPanel->hide();
  m_OptionsPanel->disable();
  m_CreditsPanel->hide();
  m_CreditsPanel->disable();
  m_LevelSelectPanel->hide();
  m_LevelSelectPanel->disable();
  m_MainPanel->enable();

  m_LevelSelectButon->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
  m_LoadGameButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
  m_CreditsButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
  m_CloseButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
  m_OptionsButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
  m_MainPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(500));
}

std::string Level1::GetClass() const
{
  return std::string("Level1");
}

void Level1::MakeCreditsPanel()
{
  /*
  tgui::Button::Ptr    m_ToMainMenuButton;
  tgui::Label::Ptr     m_CreditsLabel;
  tgui::Scrollbar::Ptr m_CreditsScrollBar;
  tgui::Panel::Ptr     m_CreditsPanel;

  tgui::Label::Ptr     m_ProgrammingSectionLabel;
  tgui::Label::Ptr     m_DesignSectionLabel;
  tgui::Label::Ptr     m_MusicSectionLabel;
  */
  TGUI_ELEMENT_PANEL_CREATE(
    ELEMENT_PTR        m_CreditsPanel,
    ELEMENT_NAME       "CreditsPanel",
    ELEMENT_THEME      m_MenuTheme,
    ELEMENT_SIZE       sf::Vector2f(1700, 900),
    ELEMENT_POSITION   sf::Vector2f(0, 0),
    ELEMENT_PARENT_GUI GUI
  );
  m_CreditsPanel->hide();
  m_CreditsPanel->disable();

  TGUI_ELEMENT_BUTTON_CREATE(
    ELEMENT_PTR        m_ToMainMenuButton,
    ELEMENT_NAME       "ToMainMenu",
    ELEMENT_THEME      m_MenuTheme,
    ELEMENT_SIZE       sf::Vector2f(200, 55),
    ELEMENT_POSITION   sf::Vector2f(10, 10),
    ELEMENT_TEXT       "back",
    ELEMENT_TEXT_SIZE  12,
    ELEMENT_PARENT_GUI m_CreditsPanel
  );

  TGUI_CONNECT_MAKE_LAMBDA_MACRO(m_ToMainMenuButton, "clicked",
                                 TGUI_PANEL_SWITCH_TRANSITION_SHOW_LEFT_HIDE_RIGHT(
                                   ELEMENT_TO_SHOW  this->m_MainPanel, 
                                   ELEMENT_TO_HIDE  this->m_CreditsPanel, 
                                   ELEMENT_DURATION sf::milliseconds(500))
                                );

  TGUI_ELEMENT_LABEL_CREATE(
    ELEMENT_PTR        m_CreditsLabel,
    ELEMENT_NAME       "CreditsLabel",
    ELEMENT_THEME      m_MenuTheme,
    ELEMENT_SIZE       sf::Vector2f(400, 30),
    ELEMENT_POSITION   sf::Vector2f(650.f, 30.f),
    ELEMENT_TEXT       "Credits and Attribution",
    ELEMENT_TEXT_SIZE  20,
    ELEMENT_PARENT_GUI m_CreditsPanel
  );

  int i = 0;
  std::string _name = "";
  sf::Vector2f _pos = sf::Vector2f(40.f, 150.f);

  tgui::Label::Ptr ProgSectionLabel;
  TGUI_ELEMENT_LABEL_CREATE(
    ELEMENT_PTR        ProgSectionLabel, 
    ELEMENT_NAME       "progsectionlabel",
    ELEMENT_THEME      m_MenuTheme,
    ELEMENT_SIZE       sf::Vector2f(400.f, 75.f), 
    ELEMENT_POSITION   sf::Vector2f(15.f, 75.f), 
    ELEMENT_TEXT       "Programmers", 
    ELEMENT_TEXT_SIZE  16, 
    ELEMENT_PARENT_GUI m_CreditsPanel
  );
  ProgSectionLabel->setTextStyle(sf::Text::Underlined);

  for (auto & programmer : ProgrammingSectionLabels) {
    tgui::Label::Ptr label;
    _name = std::string("prog_label") + std::to_string(i++);

    TGUI_ELEMENT_LABEL_CREATE(
      ELEMENT_PTR        label, 
      ELEMENT_NAME       _name, 
      ELEMENT_THEME      m_MenuTheme, 
      ELEMENT_SIZE       sf::Vector2f(400.f, 25.f), 
      ELEMENT_POSITION   _pos,
      ELEMENT_TEXT       programmer, 
      ELEMENT_TEXT_SIZE  8, 
      ELEMENT_PARENT_GUI m_CreditsPanel
    );

    _pos += sf::Vector2f(0.f, 35.f);
  }

  _pos += sf::Vector2f(0.f, 55.f);

  tgui::Label::Ptr MusicSectionLabel = m_MenuTheme->load("label");
  TGUI_ELEMENT_LABEL_CREATE(
    ELEMENT_PTR        MusicSectionLabel,
    ELEMENT_NAME       "musicsectionlabel",
    ELEMENT_THEME      m_MenuTheme,
    ELEMENT_SIZE       sf::Vector2f(1200.f, 75.f),
    ELEMENT_POSITION   sf::Vector2f(15.f, _pos.y),
    ELEMENT_TEXT       "Music",
    ELEMENT_TEXT_SIZE  16,
    ELEMENT_PARENT_GUI m_CreditsPanel
  );
  MusicSectionLabel->setTextStyle(sf::Text::Underlined);

  i = 0;
  _pos += sf::Vector2f(0.f, 75.f);

  for (auto & music : MusicSectionLabels) {
    tgui::Label::Ptr label;
    _name = std::string("music_label") + std::to_string(i++);

    TGUI_ELEMENT_LABEL_CREATE(
      ELEMENT_PTR        label,
      ELEMENT_NAME       _name,
      ELEMENT_THEME      m_MenuTheme,
      ELEMENT_SIZE       sf::Vector2f(1200.f, 25.f),
      ELEMENT_POSITION   _pos,
      ELEMENT_TEXT       music,
      ELEMENT_TEXT_SIZE  8,
      ELEMENT_PARENT_GUI m_CreditsPanel
    );

    _pos += sf::Vector2f(0.f, 35.f);
  }
}

void Level1::ShowOptionsPanel()
{
  this->m_MainPanel->disable();
  this->m_MainPanel->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::milliseconds(250));
  this->m_OptionsPanel->enable();
  this->m_OptionsPanel->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::milliseconds(250));
  m_EnableVSync->enable();
}

void Level1::HideOptionsPanel()
{
  this->m_OptionsPanel->disable();
  this->m_OptionsPanel->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(250));
  this->m_MainPanel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(250));
  this->m_MainPanel->enable();
  m_EnableVSync->disable();
}

void Level1::CreateNewGame()
{
}

void Level1::LoadSaveGame()
{
}

void Level1::EraseSaveGame()
{
}

void Level1::ShowAboutScreen()
{
  TGUI_PANEL_SWITCH_TRANSITION_SHOW_LEFT_HIDE_RIGHT(
    ELEMENT_TO_SHOW  m_CreditsPanel,
    ELEMENT_TO_HIDE  m_MainPanel,
    ELEMENT_DURATION sf::milliseconds(500)
  );
}

void Level1::ShowLevelSelectScreen()
{
  m_MainPanel->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::milliseconds(500));
  m_MainPanel->disable();

  m_LevelSelectPanel->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::milliseconds(500));
  m_LevelSelectPanel->enable();
}

void Level1::LevelSelectGoBack()
{
  m_MainPanel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
  m_MainPanel->enable();

  m_LevelSelectPanel->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(500));
  m_LevelSelectPanel->disable();
}

