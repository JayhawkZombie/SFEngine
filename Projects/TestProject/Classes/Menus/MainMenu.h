#ifndef TESTPROJECT_MAIN_MENU_H
#define TESTPROJECT_MAIN_MENU_H

#include <Engine/Source/Level/BasicLevel.h>
#include <Engine/Source/Globals/GlobalHooks.h>

#include <TGUI\TGUI.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>

#include "../Levels/OakTree.h"

class MainMenu : public BasicLevel
{
public:
  MainMenu() = delete;
  MainMenu(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
  ~MainMenu();
  void TickUpdate(const double &delta) override;

  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture);

  void OnShutDown() override;

  void HandleKeyPress(const sf::Keyboard::Key &key) override;
  void HandleKeyRelease(const sf::Keyboard::Key &key) override;
  void HandleWindowResized() override;
  void HandleInputEvent(const UserEvent &evnt) override;

  void EventUpdate(sf::Event event) override;

  void OnBegin() override;

protected:
  sf::Font font;
  std::shared_ptr<tgui::Gui> MainGUI;
  tgui::Theme::Ptr MenuTheme;

  std::shared_ptr<BasicLevel> NewGameLevel;

  std::shared_ptr<OakTreeLevel> OakTreeLevelptr;

  tgui::Panel::Ptr MainPanel;
  tgui::Panel::Ptr OptionsPanel;

  tgui::Button::Ptr NewGameButton;
  tgui::Button::Ptr LoadGameButton;
  tgui::Button::Ptr OptionsButton;
  tgui::Button::Ptr AboutButton;
  tgui::Button::Ptr CloseButton;

  thor::UniversalEmitter emitter;
  thor::ParticleSystem system;
  thor::ColorGradient gradient;
  thor::ColorAnimation *colorizer;
  thor::FadeAnimation fader;
  sf::Texture texture;
  sf::Clock fClock;
  thor::PolarVector2f velocity;


  void CreateNewGame();
  void LoadSaveGame();
  void EraseSaveGame();

  void ShowAboutScreen();

};

#endif
