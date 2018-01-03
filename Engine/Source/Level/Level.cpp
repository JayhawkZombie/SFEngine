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

#include "Engine/stdafx.h"

#include "Level.h"
#include "Exceptions/Exceptions.h"
#include "Globals/GlobalHooks.h"
#include "Objects/GameObject.h"
#include "Physics/vec2d.h"
#include "Physics/Collider.h"
#include "Actor/Actor.h"

#include "json/json.h"

namespace
{
  std::string PROJECT_PATH = "";
}


std::shared_ptr<Level> Level::DefaultEmptyLevel()
{
  std::shared_ptr<Level> lvl = std::make_shared<Level>();
  
  return lvl;
}

Level::Level(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines, const sf::Vector2f &GridSpacing)
  : 
  BasicLevel(LevelSize, DefaultView, showlines, GridSpacing)
{
  auto seg = BuildSegmentMesh('L', { 100, 300 }, { 550, 500 });
  Segments.push_back(seg);

  if (ShowGridLines) {
    GenerateGrid();
  }
  CurrentLevel = this;
  Handler.BindCallback(Events::KeyPressed, [this](const sf::Keyboard::Key &k) -> void { this->HandleKeyPress(k); });
  Handler.BindCallback(Events::KeyReleased, [this](const sf::Keyboard::Key &k) ->void { this->HandleKeyRelease(k); });
}


Level::Level()
{
  /*
   *  Default
   **/
}

Level::~Level()
{
  for (auto & tex : Textures)
    tex.second.reset();

  Textures.clear();
  for (auto & anim : Animations)
    anim.second.reset();
  Animations.clear();
  for (auto & buff : SoundBuffers)
    buff.second.reset();
  SoundBuffers.clear();
}

void Level::BindMethods(chaiscript::ModulePtr mptr)
{
  
}

void Level::HandleInputEvent(const UserEvent & evnt)
{
}

void Level::HandleKeyPress(const sf::Keyboard::Key &key)
{

}

void Level::HandleKeyRelease(const sf::Keyboard::Key &key)
{

}

void Level::GenerateGrid()
{
  float xpos = 0, ypos = 0;
  sf::VertexArray hline = sf::VertexArray(sf::Lines, 2);
  sf::VertexArray vline = sf::VertexArray(sf::Lines, 2);

  while (ypos < Size.y) {
    hline[0].position = { 0, ypos }; hline[0].color = sf::Color(0, 123, 137);
    hline[1].position = { static_cast<float>(Size.x), ypos }; hline[1].color = sf::Color(0, 123, 137);

    GridLines.push_back(hline);
    ypos += GridBlockSize.y;
  }

  while (xpos < Size.x) {
    vline[0].position = { xpos, 0 }; vline[0].color = sf::Color(0, 123, 137);
    vline[1].position = { xpos, static_cast<float>(Size.y) }; vline[1].color = sf::Color(0, 123, 137);

    GridLines.push_back(vline);
    xpos += GridBlockSize.y;
  }
}

void Level::LoadLevel(const std::string &lvlfile)
{
  LoadFromFile(lvlfile);
    
}

void Level::OnBegin()
{
}

void Level::OnEnd()
{
}

void Level::OnShutDown()
{

}

void Level::HandleWindowResized()
{

}

std::shared_ptr<GameObject> Level::GetObjectByName(const std::string & ID)
{
  if (!CurrentLevel) {
    std::cerr << "CurrentLevel is NULL" << std::endl;
    return nullptr;
  }

  for (auto & obj : CurrentLevel->m_GameObjects) {
    if (obj.second->GetID() == ID)
      return obj.second;
  }

  return nullptr;
}

void Level::LoadFromFile(const std::string &file)
{
  Json::Value ProjectFile;

  std::ifstream in(file);
  if (!in) {
    std::cerr << "Unable to open project file" << std::endl;
    return;
  }

  in >> ProjectFile;

  try
  {
    PROJECT_PATH = ProjectFile["Project"]["Info"]["PROJECT_PATH"].asString();
    LoadAssets(ProjectFile["Project"]["Data"]);
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::ConstructionError);
    err.AddMessage(EXCEPTION_MESSAGE("Failed to load assets"));
    throw;
  }

}

bool Level::SpawnAutoGeneratedObject(std::shared_ptr<GameObject> Object, std::string IDPrePend)
{
  try
  {
    auto _id = GenerateID();
    std::string objid = IDPrePend + std::to_string(_id);
    Object->SetInternalD(_id);
    Object->SetID(objid);
    m_GameObjects[objid] = Object;
    return true;
  }
  //When we implement logging, we will log the errors here
  catch (IDException &exc)
  {
    exc.AddCause({ ExceptionCause::SpawnFailure });
    exc.AddMessage(EXCEPTION_MESSAGE("Failed to spawn object"));
      
    return false;
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::Unknown);
    err.AddMessage(EXCEPTION_MESSAGE("Failed to spawn object - unknown reason"));
      
    return false;
  }
  catch (std::exception *)
  {
    throw StdException({ ExceptionCause::StdException, ExceptionCause::Unknown }, EXCEPTION_MESSAGE("Exception occurred in standard library - unknown cause"));
    throw;
  }
}

void Level::SpawnBall(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
{
  //auto ball = BuildBallMesh(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(__TO_FLOAT__(Radius), __TO_FLOAT__(Radius)));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  MeshType type = (BallType == 'G' ? MeshType::BallGo : MeshType::Ball);

  if (!SpawnAutoGeneratedObject(Object, "BallMesh")) {
    //Awh, sad
    //for now, print the error, but don't throw an exception
    ERR_STREAM << "Failed to spawn Ball" << std::endl;
  }
}

void Level::SpawnSquare(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto sq = BuildPolygonMesh(4, radius, 0, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  MeshType type = MeshType::Polygon;

  if (!SpawnAutoGeneratedObject(Object, "Square")) {
    ERR_STREAM << "Failed to spawn Square" << std::endl;
  }
}

void Level::SpawnRect(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto sq = BuildPolygonMesh(4, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  auto Object = std::make_shared<GameObject>();
  
  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  if (!SpawnAutoGeneratedObject(Object, "RectMesh")) {
    ERR_STREAM << "Failed to spawn Rect" << std::endl;
  }
}

void Level::SpawnTriangle(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  if (!SpawnAutoGeneratedObject(Object, "TriMesh")) {
    ERR_STREAM << "Failed to spawn TriMesh" << std::endl;
  }
}

void Level::SpawnNPoly(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto poly = BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  if (!SpawnAutoGeneratedObject(Object, "NPolyMesh")) {
    ERR_STREAM << "Failed to spawn NPolyMesh" << std::endl;
  }
}

void Level::SpawnWave(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius, bool IsHard, unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight, float ampLeft, float waveLenLeft, float rFreqLeft, float elev, float airDen, float depth, float fluidDen)
{

  auto ptr = BuildWaveSegment(type, TopLeftCorner, BottomRightCorner, radius, IsHard, NumWavePts, ampRight, waveLenRight, rFreqRight, ampLeft, waveLenLeft, rFreqLeft, elev, airDen, depth, fluidDen);
  Segments.push_back(ptr);
}

void Level::LoadAssets(const Json::Value & value)
{
  //textures
  LoadTextures(value["Textures"]);
  LoadAudio(value["Audio"]);
  LoadTileSheets(value["Sheets"]);
  LoadAnimations(value["Animations"]);
}
void Level::LoadAudio(const Json::Value & value)
{
  std::string name{ "" };
  std::string path{ "" };

  for (auto & file : value) {
    name = file["Name"].asString();
    path = PROJECT_PATH + file["Path"].asString();

    SoundBuffers[name] = LoadSoundBuffer(path, name);// std::make_shared<sf::SoundBuffer>();
    if (!SoundBuffers[name]) {
      std::cerr << "Failed to load audio file: " << path << std::endl;
    }


  }
}
void Level::LoadTextures(const Json::Value & value)
{
  std::string texname{ "" };
  std::string path{ "" };

  for (auto & tex : value) {
    texname = tex["Name"].asString();
    path = PROJECT_PATH + tex["Path"].asString();
    Textures[texname] = LoadTexture(path, texname);// std::make_shared<sf::Texture>();
    if (!Textures[texname]) {
      std::cerr << "Unable to load texture: " << path << std::endl;
    }
  }

}
void Level::LoadTileSheets(const Json::Value & value)
{
  for (auto & sheet : value)
    LoadSheet(sheet);
}
void Level::LoadSheet(const Json::Value & value)
{
  try
  {

  }
  catch (Json::Exception &err)
  {
    throw EngineRuntimeError({ ExceptionCause::DataParseError }, EXCEPTION_MESSAGE("JSON error"));
  }
}
void Level::LoadAnimations(const Json::Value & value)
{
  
}
