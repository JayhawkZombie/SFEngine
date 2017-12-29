#include "MainMenu.h"

#include <Engine/Source/Level/Level.h>

MainMenu::MainMenu(const sf::Vector2u & LevelSize, const sf::FloatRect & DefaultView, bool showlines, const sf::Vector2f & GridSpacing)
  : fader(0.1f, 0.1f), BasicLevel(LevelSize, DefaultView, showlines, GridSpacing)
{
  MainGUI = std::make_shared<tgui::Gui>(*Engine::currentRenderWindow);
  MenuTheme = std::make_shared<tgui::Theme>("./Projects/TestProject/UIThemes/TransparentGray.theme");
  font.loadFromFile("./Projects/TestProject/Fonts/Marvel-Regular.ttf");
  MainGUI->setFont(font);

  OakTreeLevelptr = std::make_shared<OakTreeLevel>();

  NewGameLevel = std::make_shared<Engine::Level>(LevelSize, DefaultView, showlines, GridSpacing);

  //Create some buttons
  NewGameButton = MenuTheme->load("button");
  NewGameButton->setPosition({ 25, 25 });
  NewGameButton->setSize({ 200, 75 });
  NewGameButton->connect("clicked", [this]() {this->CreateNewGame(); });
  NewGameButton->setText("new game");
  NewGameButton->setTextSize(20);
  NewGameButton->hide();
  //MainGUI->add(NewGameButton, "NewGameButton");

  OptionsPanel = MenuTheme->load("panel");
  OptionsPanel->setSize({ 1700, 900 });

  LoadGameButton = MenuTheme->load("button");
  LoadGameButton->setPosition({ 25, 225 });
  LoadGameButton->setSize({ 200, 75 });
  LoadGameButton->setText("load game");
  LoadGameButton->setTextSize(20);
  LoadGameButton->disable();
  LoadGameButton->getRenderer()->setTextColor(sf::Color(180, 180, 180));
  LoadGameButton->hide();
  //MainGUI->add(LoadGameButton, "LoadGameButton");

  AboutButton = MenuTheme->load("button");
  AboutButton->setPosition({ 25, 425 });
  AboutButton->setSize({ 200, 75 });
  AboutButton->connect("clicked", [this]() {this->ShowAboutScreen(); });
  AboutButton->setText("about");
  AboutButton->setTextSize(20);
  AboutButton->hide();
  //MainGUI->add(AboutButton, "AboutButton");

  OptionsButton = MenuTheme->load("button");
  OptionsButton->setPosition({ 25, 625 });
  OptionsButton->setSize({ 200, 75 });
  OptionsButton->connect("clicked", [this]() 
                                    {
                                      this->MainPanel->disable(); 
                                      this->MainPanel->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, sf::milliseconds(500));
                                      this->OptionsPanel->enable(); 
                                      this->OptionsPanel->showWithEffect(tgui::ShowAnimationType::SlideFromRight, sf::milliseconds(500)); 
                                    });

  OptionsButton->setText("options");
  OptionsButton->setTextSize(20);
  
  CloseButton = MenuTheme->load("button");
  CloseButton->setPosition({ 25, 825 });
  CloseButton->setSize({ 200, 75 });
  CloseButton->setText("quit");
  CloseButton->setTextSize(20);
  CloseButton->hide();
  CloseButton->connect("clicked", Engine::Shutdown);
 // MainGUI->add(CloseButton);

  tgui::Button::Ptr OptionsBack = MenuTheme->load("button");
  OptionsBack->setPosition({ 25, 425 });
  OptionsBack->setSize({ 200, 75 });
  OptionsBack->setText("back");
  OptionsBack->setTextSize(20);
  OptionsBack->connect("clicked", [this]() 
                                  {
                                    this->OptionsPanel->disable(); 
                                    this->OptionsPanel->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(500)); 
                                    this->MainPanel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500)); 
                                    this->MainPanel->enable(); 
                                  });
  OptionsPanel->add(OptionsBack);

  MainPanel = MenuTheme->load("panel");
  MainPanel->setSize({ 1700, 900 });
  MainPanel->add(NewGameButton);
  MainPanel->add(LoadGameButton);
  MainPanel->add(AboutButton);
  MainPanel->add(OptionsButton);
  MainPanel->add(CloseButton);

  OptionsPanel->hide();
  OptionsPanel->disable();

  MainGUI->add(MainPanel);
  MainGUI->add(OptionsPanel);



  texture.loadFromFile("./Projects/TestProject/Textures/particle.png");
  emitter.setEmissionRate(85.f);
  emitter.setParticleLifetime(sf::seconds(6));

  system.setTexture(texture);
  system.addEmitter(thor::refEmitter(emitter));
  
  emitter.setParticlePosition(sf::Vector2f( 0, 0 ));
  emitter.setParticleScale(sf::Vector2f(0.4f, 0.3f));

  gradient[0.f] = sf::Color(0, 242, 255);
  gradient[0.5f] = sf::Color(0, 106, 112, 112);
  gradient[1.f] = sf::Color(0, 0, 0, 0);

  colorizer = new thor::ColorAnimation(gradient);

  system.addAffector(thor::AnimationAffector(*colorizer));
  system.addAffector(thor::AnimationAffector(fader));
  system.addAffector(thor::TorqueAffector(150.f));
  system.addAffector(thor::ForceAffector(sf::Vector2f(0.f, 100.f)));
  velocity = thor::PolarVector2f(200.f, -90.f);




  Engine::CurrentLevel = this;
  std::cerr << "Assigned current level" << std::endl;
}

MainMenu::~MainMenu()
{
  if (MainGUI)
    MainGUI.reset();
  delete colorizer;
}

void MainMenu::TickUpdate(const double & delta)
{
  static sf::Time _time = sf::seconds(0);
  static sf::Clock _clock;
  static bool shown = false;
  if (!shown) {
    shown = true;
    NewGameButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    LoadGameButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    AboutButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    CloseButton->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(500));
    MainPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(150));
  }
  emitter.setParticlePosition(thor::Distributions::rect({ 1700 / 2.f, 900 / 2.f }, { 1700 / 2.f, 900 / 2.f }));
  system.update(fClock.restart());
  MainGUI->updateTime(_clock.restart());
}

void MainMenu::Render(std::shared_ptr<sf::RenderTarget> Target)
{
}

void MainMenu::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  Texture->clear(sf::Color::Transparent);
  Texture->draw(system);
  MainGUI->draw();
}

void MainMenu::OnShutDown()
{
}

void MainMenu::HandleKeyPress(const sf::Keyboard::Key & key)
{
}

void MainMenu::HandleKeyRelease(const sf::Keyboard::Key & key)
{
}

void MainMenu::HandleWindowResized()
{
}

void MainMenu::HandleInputEvent(const Engine::UserEvent & evnt)
{
}

void MainMenu::EventUpdate(sf::Event event)
{
  MainGUI->handleEvent(event);
}

void MainMenu::OnBegin()
{
  std::cerr << "Main menu level exiting" << std::endl;
}

void MainMenu::CreateNewGame()
{
 // Engine::SwitchLevel(NewGameLevel);
  Engine::SwitchLevel(OakTreeLevelptr);
}

void MainMenu::LoadSaveGame()
{
}

void MainMenu::EraseSaveGame()
{
}

void MainMenu::ShowAboutScreen()
{
}
