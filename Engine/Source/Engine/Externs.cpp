////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "Globals\GlobalHooks.h"
#include "Engine\Engine.h"
#include  "Level\BasicLevel.h"

#include <vector>
#include <TGUI\TGUI.hpp>

//This means war, Microsoft!
#ifdef MessageBox
#pragma push_macro("MessageBox")
#undef MessageBox
#endif

sf::RenderWindow *currentRenderWindow = nullptr;
sf::Vector2f WindowSize;
std::shared_ptr<sf::Texture> DefaultTexture;
//chaiscript::ChaiScript *ScriptEngine;
std::unordered_set<std::uint32_t> UsedIDs;
RenderSettings EngineRenderSettings;
std::shared_ptr<tgui::Gui> GUI;
std::uint32_t MaxIDGenerationAttempts;
volatile bool FlagForClose = false;
DataStream<UserEvent> EngineEventStream;
std::unordered_map<std::string, std::shared_ptr<BasicLevel>> Levels;
BasicLevel *CurrentLevel = nullptr;
std::string EntryLevelName;
InputDeviceState InputState;
SPtrSharedMutex LevelsLock;
volatile double TimeScaleFactor = 1.0;
std::string WindowTitle = "<NO TITLE>";
sf::Uint32 WindowStyle;
volatile unsigned int FramerateLimit;

void SetKeyRepeatEnabled(bool enabled)
{
  if (currentRenderWindow)
    currentRenderWindow->setKeyRepeatEnabled(enabled);
}

void FreeID(const std::uint32_t &ID)
{
  auto it = UsedIDs.find(ID);
  if (it != UsedIDs.end())
    UsedIDs.erase(it);
}

bool IsIDUsed(const std::uint32_t &ID)
{
  return (UsedIDs.find(ID) != UsedIDs.end());
}

std::uint32_t GenerateID()
{
  std::uint32_t ItemID = 0;

  std::uint32_t Tries = 0;
  std::default_random_engine generator;
  generator.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
  std::uniform_int_distribution<std::uint32_t> dist(1, std::numeric_limits<std::uint32_t>::max() - 1);

  //Try one time to generate an ID
  ItemID = dist(generator);

  //If we couldn't do so, we will try a set number of times to generate one
  while (IsIDUsed(ItemID))
  {
    if (Tries >= MaxIDGenerationAttempts) {
      throw IDException({ ExceptionCause::IDGenerationError }, EXCEPTION_MESSAGE("Could not generate an ID for item"));
    }
    Tries++;
    ItemID = dist(generator);
  }

  //We were able to succesfully create an ID
  UsedIDs.insert(ItemID);

  return ItemID;
}

//ENGINE API METHODS
sf::Vector2u GetCurrentWindowSize()
{
  if (CurrentEngine)
    return CurrentEngine->GetCurrentWindowsize();
  else
    return{ 0, 0 };
}

decltype(auto) GetCurrentOpenGLVersionMajor()
{
  sf::ContextSettings settings;

  if (currentRenderWindow) {
    settings = currentRenderWindow->getSettings();

    return settings.majorVersion;
  }

  return decltype(settings.majorVersion)(0);
}

decltype(auto) GetCurrentOpenGLVersionMinor()
{
  sf::ContextSettings settings;

  if (currentRenderWindow) {
    settings = currentRenderWindow->getSettings();

    return settings.minorVersion;
  }

  return decltype(settings.minorVersion)(0);
}

decltype(auto) GetCurrentAASetting()
{
  sf::ContextSettings settings;

  if (currentRenderWindow) {
    settings = currentRenderWindow->getSettings();

    return settings.antialiasingLevel;
  }

  return decltype(settings.antialiasingLevel)(0);
}

decltype(auto) GetCurrentContextSettings()
{
  sf::ContextSettings settings;

  if (currentRenderWindow) {
    settings = currentRenderWindow->getSettings();

    return settings;
  }

  settings.antialiasingLevel = 0;
  settings.attributeFlags = sf::ContextSettings::Attribute::Default;
  settings.depthBits = 0;
  settings.majorVersion = 0;
  settings.minorVersion = 0;

  return settings;
}

decltype(auto) GetCurrentContext()
{
  return sf::Context::getActiveContext();
}

decltype(auto) GetCurrentTexturePoolSize()
{
  return 0;
}

decltype(auto) GetCurrentShaderPoolSize()
{
  return 0;
}

decltype(auto) GetCurrentFramerateSetting()
{
  if (CurrentEngine)
    return CurrentEngine->GetCurrentFrameRate();
  else
    return 0U;
}

void SetFramerateLimit(unsigned int Limit)
{
  currentRenderWindow->setFramerateLimit(Limit);
}

void SetVSyncEnabled(bool Enabled)
{
  currentRenderWindow->setVerticalSyncEnabled(Enabled);
}

void SetAALevel(unsigned int Level)
{
  auto settings = currentRenderWindow->getSettings();
  settings.antialiasingLevel = Level;
  auto Winsize = currentRenderWindow->getSize();
  currentRenderWindow->create(sf::VideoMode(Winsize.x, Winsize.y), WindowTitle, WindowStyle, settings);
}

decltype(auto) GetIsGlobalShadingEnabled()
{
  return true;
}

decltype(auto) GetIsStaticShadingEnabled()
{
  return true;
}

decltype(auto) GetIsDynamicShadingEnabled()
{
  return true;
}

decltype(auto) GetIsStaticShadowingEnabled()
{
  return true;
}

decltype(auto) GetIsDynamicShadowingEnabled()
{
  return true;
}

decltype(auto) GetIsMultiThreadedLightingEnabled()
{
  return false;
}

decltype(auto) GetIsUsingPreComputedLightMaps()
{
  return true;
}

decltype(auto) GetCanPhysicsApproxCollision()
{
  return true;
}

void AddScriptGlobal()
{
}

bool GetKeyDown(const sf::Keyboard::Key & key)
{
  std::cerr << "GetKJeyDownCalled" << std::endl;
  return sf::Keyboard::isKeyPressed(key);
}

bool GetKeyLeftDown(const sf::Keyboard::Key & key)
{
  return (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
}

bool GetKeyUp(const sf::Keyboard::Key & key)
{
  return !sf::Keyboard::isKeyPressed(key);
}

bool GetMouseButtonDown(const sf::Mouse::Button & button)
{
  return sf::Mouse::isButtonPressed(button);
}

bool GetMouseButtonUp(const sf::Mouse::Button & button)
{
  return !sf::Mouse::isButtonPressed(button);
}

sf::Vector2f GetMousePosition()
{
  return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*currentRenderWindow));
}

void SerializeString(const std::string & string, std::ofstream & out)
{
  std::size_t len = string.length();
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));

  out.write((char *)(&len), sizeof(std::size_t));
  out.write(string.c_str(), len);
}

void SerializeInt32(const std::int32_t & value, std::ofstream & out)
{
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));
  out.write((char *)(&value), sizeof(std::int32_t));
}

void SerializeFloat(const float & value, std::ofstream & out)
{
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));
  out.write((char *)(&value), sizeof(float));
}

void SerializeUint32(const std::uint32_t &value, std::ofstream & out)
{
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));
  out.write((char *)(&value), sizeof(float));
}

void SerializeSizet(const std::size_t & value, std::ofstream & out)
{
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));
  out.write((char *)(&value), sizeof(std::size_t));
}

void SerializeInt64(const std::int64_t & value, std::ofstream & out)
{
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));
  out.write((char *)(&value), sizeof(std::int64_t));
}

void SerializeUint64(const std::uint64_t & value, std::ofstream & out)
{
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));
  out.write((char *)(&value), sizeof(std::uint64_t));
}

void SerializeChar(const char & c, std::ofstream & out)
{
  if (!out)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ofstream in fail state"));
  out.write((char *)(&c), sizeof(char));
}

void DeserializeString(std::string & string, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  std::size_t len = 0;
  in.read((char *)(&len), sizeof(std::size_t));
  //For somewhat obvious reasons, we'll do a check to make sure the lenght is less than ~500k
  if (len > 500'000)
    throw FormattingError({ ExceptionCause::DataFormatError }, EXCEPTION_MESSAGE("Value too large - data assumed to be corrupt"));

  string.clear();
  string.resize(len);
  in.read(&(string[0]), len);
}

void DeserializeInt32(std::int32_t & value, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  std::int32_t val = 0;
  in.read((char *)(&val), sizeof(std::int32_t));

  value = val;
}

void DeserializeFloat(float & value, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  float val = 0.f;
  in.read((char *)(&val), sizeof(float));

  value = val;
}

void DeserializeUint32(std::uint32_t & value, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  std::uint32_t val = 0;
  in.read((char *)(&val), sizeof(std::uint32_t));
  value = val;
}

void DeserializeSizet(std::size_t & value, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  std::size_t val = 0;
  in.read((char *)(&val), sizeof(std::size_t));
  value = val;
}

void DeserializeInt64(std::int64_t & value, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  std::int64_t val = 0;
  in.read((char *)(&val), sizeof(std::int64_t));
  value = val;
}

void DeserializeUint64(std::uint64_t & value, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  std::uint64_t val = 0;
  in.read((char *)(&val), sizeof(std::uint64_t));
  value = val;
}

void DeserializeChar(char & c, std::ifstream & in)
{
  if (!in)
    throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("ifstream in fail state"));

  char _c = '\0';
  in.read((char *)(&_c), sizeof(char));
  c = _c;
}

void ConfirmAlert(const std::string &message, std::string OKText, std::string CancelText, std::function<void(void)> OKcb, std::function<void(void)> Cancelcb)
{
  tgui::MessageBox::Ptr mbox = std::make_shared<tgui::MessageBox>();

  mbox->setText(message);
  mbox->setSize({ 400, 400 });

  float xDiff = WindowSize.x - 400.f;
  float yDiff = WindowSize.x - 400.f;

  float buttonDiffX = 0;

  tgui::Button::Ptr OKButton = std::make_shared<tgui::Button>();
  tgui::Button::Ptr CancelButton = std::make_shared<tgui::Button>();

  OKButton->setText(OKText);
  CancelButton->setText(CancelText);

  OKButton->connect("Clicked", [mbox, OKcb]() { 
    if (OKcb) 
      OKcb(); 
    mbox->hide();
    GUI->remove(mbox);
  });
  CancelButton->connect("Clicked", [mbox, Cancelcb]() {
    if (Cancelcb)
      Cancelcb();
    mbox->hide();
    GUI->remove(mbox);
  });
  mbox->connect("Closed", [message, OKText, CancelText, OKcb, Cancelcb] { ConfirmAlert(message, OKText, CancelText, OKcb, Cancelcb); });

  auto OKxSize = OKButton->getSize().x;
  auto CancelxSize = CancelButton->getSize().x;

  //center the OK button in the left 200px of the message box
  float OKSizeDiff = 200.f - OKxSize;
  OKButton->setPosition({ OKSizeDiff / 2.f, 350 });

  float CancelSizeDiff = 200.f - CancelxSize;
  CancelButton->setPosition({ 200.f + CancelSizeDiff / 2.f, 350 });

  mbox->add(OKButton);
  mbox->add(CancelButton);

}

void Confirm(const std::string & message)
{
  ConfirmAlert(message);
}

void Shutdown()
{
  FlagForClose = true;
}

void LoadLevel(const std::string & jsonPath)
{

}

void SwitchLevel(std::shared_ptr<BasicLevel> Level)
{
  if (CurrentLevel) {
    CurrentLevel->HideUI();
    CurrentLevel->CleanUp();
    CurrentLevel->OnEnd();
  }
  CurrentLevel = Level.get();
  CurrentLevel->OnBegin();
  CurrentLevel->ShowUI();
}

void SwitchLevel_RawPtr(BasicLevel * Level)
{
  Level->CleanUp();
}

void LoadMainLevel()
{
  auto it = Levels.find("Main");

  if (it != Levels.end()) {
    SwitchLevel((*it).second);
  }
}

void LoadLevelByName(const std::string & Name)
{
  auto it = Levels.find(Name);

  if (it != Levels.end()) {
    SwitchLevel((*it).second);
  }
}

void ScaleTimeUpdate(const double & factor)
{
  TimeScaleFactor = factor;
}

void MessageAlert(const std::string & message)
{
#ifdef MessageBox
#undef MessageBox
#endif
  tgui::MessageBox::Ptr mbox = std::make_shared<tgui::MessageBox>();
  mbox->setText(message);
  mbox->setSize({ 400, 400 });
    
  float xDiff = WindowSize.x - 400.f;
  float yDiff = WindowSize.y - 400.f;

  mbox->setPosition({ xDiff / 2.f, yDiff / 2.f });

  tgui::Button::Ptr btn = std::make_shared<tgui::Button>();
  btn->setText("OK");
  btn->setPosition({ 180, 350 });
  mbox->add(btn);

  GUI->add(mbox, "errorAlert");
  GUI->focusWidget(mbox);
  mbox->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));

  mbox->connect("closed", [mbox]() { mbox->hide(); GUI->remove(mbox); });
  btn->connect("clicked", [mbox]() { mbox->hide(); GUI->remove(mbox); });
}

//if the editor is being used, link to the current engine and allow access to the global UI handler
#ifdef WITH_EDITOR
SFEngine *CurrentEngine = nullptr;
#endif
