#ifndef GAME_PUZZLE_LEVEL_1_H
#define GAME_PUZZLE_LEVEL_1_H

#include "ProjectIncludes.h"
#include "Objects/ProjectileBase.h"

#include "Weather/WeatherSystem.h"
#include "Weather/Lightning.h"
#include "Time/TimedSequence.h"
#include "Utils/SplinePath.h"

class Level1 : public BasicLevel
{
public:
  Level1();
  ~Level1() override final;

  void TickUpdate(const double &delta) override final;

  void Render(std::shared_ptr<sf::RenderTarget> Target) override final;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override final;

  void OnShutDown() override final;

  void HandleInputEvent(const UserEvent &evnt) override final;

  void EventUpdate(sf::Event event) override final;

  void OnBegin() override final;
  void OnEnd()   override final;
  void HideUI()  override final;
  void ShowUI()  override final;

  std::string GetClass() const override final;
  
protected:
  void MakeCreditsPanel();
  void ShowOptionsPanel();
  void HideOptionsPanel();

  bool m_DrawSplines = false;

  SplinePath m_ParticlePath;
  SplinePath m_ParticlePath2;
  sw::Starfield m_StarField;

  sf::Shader BlurShader;
  sf::Sprite BlurSprite;
  sf::Sprite FinalSprite;
  sf::RenderTexture BlurBuffer;
  sf::RenderTexture BlurBuffer2;

  thor::ParticleSystem m_PSystem1;
  thor::UniversalEmitter m_PEmitter1;
  thor::ColorGradient m_PColorGradient1;
  thor::ColorAnimation m_PColorAnimation1;
  thor::FadeAnimation m_PFadeAnimation1;
  thor::TorqueAffector m_PTorqueAffector1;
  thor::ForceAffector m_PGravityAffector1;


  thor::ParticleSystem m_PSystem2;
  thor::UniversalEmitter m_PEmitter2;
  thor::ColorGradient m_PColorGradient2;
  thor::ColorAnimation m_PColorAnimation2;
  thor::FadeAnimation m_PFadeAnimation2;
  thor::TorqueAffector m_PTorqueAffector2;
  thor::ForceAffector m_PGravityAffector2;


  sf::Texture m_TorchParticleTexture;
  thor::PolarVector2f m_TorchParticleVelocity;


  tgui::CheckBox::Ptr m_EnableVSync;
  tgui::SpinButton::Ptr m_FrameRateSpinButton;
  tgui::ComboBox::Ptr m_AALevelOptions;
  tgui::Label::Ptr fRateLabel;

  sf::Font font;
  std::shared_ptr<tgui::Gui> m_MainGUI;
  tgui::Theme::Ptr m_MenuTheme;
  tgui::Panel::Ptr m_MainPanel;
  tgui::Panel::Ptr m_OptionsPanel;
  tgui::Panel::Ptr m_LevelSelectPanel;

  tgui::Button::Ptr m_NewGameButton;
  tgui::Button::Ptr m_LevelSelectButon;
  tgui::Button::Ptr m_LoadGameButton;
  tgui::Button::Ptr m_OptionsButton;
  tgui::Button::Ptr m_AboutButton;
  tgui::Button::Ptr m_CloseButton;
  tgui::Button::Ptr m_CreditsButton;

  tgui::Button::Ptr    m_ToMainMenuButton;
  tgui::Label::Ptr     m_CreditsLabel;
  tgui::Scrollbar::Ptr m_CreditsScrollBar;
  tgui::Panel::Ptr     m_CreditsPanel;

  tgui::Label::Ptr     m_ProgrammingSectionLabel;
  tgui::Label::Ptr     m_DesignSectionLabel;
  tgui::Label::Ptr     m_MusicSectionLabel;

  thor::UniversalEmitter emitter;
  thor::ParticleSystem system;
  thor::ColorGradient gradient;
  thor::ColorAnimation *colorizer;
  thor::FadeAnimation fader;
  sf::Texture texture;
  sf::Clock fClock;
  thor::PolarVector2f velocity;

  sf::SoundBuffer m_BGMusicBuffer;
  sf::Sound m_BGMusic;

  //Pointers for levels
  std::shared_ptr<BasicLevel> OakTreeLevelPtr;
  std::shared_ptr<BasicLevel> BallPuzzleLevelPtr;
  std::shared_ptr<BasicLevel> AITestLevelPtr;
  std::shared_ptr<BasicLevel> OakTreeChurchInteriorLevelPtr;
  SPtrShared<BasicLevel> PhysicsDemoLevelPtr;
  tgui::Button::Ptr LevelSelectBack;

  bool m_Paused = false;

  void CreateNewGame();
  void LoadSaveGame();
  void EraseSaveGame();

  void ShowAboutScreen();

  void ShowLevelSelectScreen();
  void LevelSelectGoBack();
};

#endif
