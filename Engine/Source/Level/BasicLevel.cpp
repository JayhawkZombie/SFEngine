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

#include "BasicLevel.h"
#include "Globals/GlobalHooks.h"
#include "Exceptions/Exceptions.h"
#include "Actor/Actor.h"
#include "Physics/Collider.h"
#include "Physics/Occluder.h"

#include <cereal/archives/portable_binary.hpp>

namespace
{
  std::string PROJECT_PATH = "";
}

BasicLevel::BasicLevel(const BaseEngineInterface & Copy)
  : BaseEngineInterface(Copy)
{
}

BasicLevel::BasicLevel(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines, const sf::Vector2f &GridSpacing)
  : //LightTexture(std::make_shared<sf::RenderTexture>()),
  //SceneBlendTexture(std::make_shared<sf::RenderTexture>()),
  ShowGridLines(showlines), Size(LevelSize), GridBlockSize(GridSpacing), CurrentView(DefaultView),
  Gravity(new ::vec2d), TileMap(std::make_shared<sw::TileMap>())
{
    
}

BasicLevel::BasicLevel()
  : Gravity(new ::vec2d), TileMap(std::make_shared<sw::TileMap>())
{

}

BasicLevel::~BasicLevel()
{
  if (Gravity)
    delete Gravity;
}

std::shared_ptr<BaseEngineInterface> BasicLevel::Clone() const
{
  auto LevelCopy = std::make_shared<BasicLevel>(Size, CurrentView, ShowGridLines, GridBlockSize);

  return LevelCopy;
}

void BasicLevel::TickUpdate(const double & delta)
{
  static double cumulative = 0.f;
  cumulative += delta;

  static hres_time_point FrameStart = hres_clock::now();

  for (auto & obj : LevelObjects) {
    if (!obj.second->IsFrozen())
      obj.second->TickUpdate(delta);
  }

  if (cumulative > updateInterval) {

    if (DoUpdatePhysics && (LevelObjects.size() > 0 || Segments.size() > 0)) {
      UpdateObjectPhysics();

      for (auto & obj : LevelObjects) {
        obj.second->PhysicsUpdate();
      }
    }

    cumulative = 0.f;
  }

}

std::string BasicLevel::GetClass() const
{
  return std::string("BasicLevel");
}

void BasicLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  //This function shouldn't ever be called
}

void BasicLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  //SceneBlendTexture->clear(sf::Color::Transparent);

  if (ShowGridLines) {
    for (auto & arr : GridLines)
      Texture->draw(arr);
  }

  for (auto & obj : LevelObjects)
    obj.second->Render(Texture);
      
  //Texture->draw(obj.second->Sprite);

  //If we are using the editor, draw the meshes too
  //Make this configurable later
#ifdef WITH_EDITOR

  for (auto & obj : LevelObjects) {
    for (auto & collider : obj.second->GetColliders())
      if (collider->GetMesh().lock())
        collider->GetMesh().lock()->draw(*Texture);

    for (auto & occluder : obj.second->GetOccluders())
      if (occluder->GetMesh().lock())
        occluder->GetMesh().lock()->draw(*Texture);
  }

  for (auto & seg : Segments)
    seg->draw(*Texture);
#endif
}

void BasicLevel::OnShutDown()
{
  TileMap.reset();

  for (auto & obj : LevelObjects)
    obj.second->OnShutDown();

  LevelObjects.clear();

  Textures.clear();
}

void BasicLevel::SerializeOut(std::ofstream & out)
{
}

void BasicLevel::SerializeIn(std::ifstream & in)
{
}

void BasicLevel::HandleInputEvent(const UserEvent & evnt)
{
}

void BasicLevel::HandleKeyPress(const sf::Keyboard::Key & key)
{
}

void BasicLevel::HandleKeyRelease(const sf::Keyboard::Key & key)
{
}

void BasicLevel::HandleWindowResized()
{
}

void BasicLevel::LoadLevel(const std::string & lvlfile)
{
}

void BasicLevel::OnBegin()
{
}

void BasicLevel::OnEnd()
{
  for (auto & obj : LevelObjects)
    obj.second->OnGameEnd();
}

void BasicLevel::HideUI()
{
}

void BasicLevel::ShowUI()
{
}

void BasicLevel::Reset()
{
}

void BasicLevel::RequestLevelSwitch(const std::string & LevelName)
{
}

void BasicLevel::SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f & Position)
{
  Actor->SetActorPosition(Position);

  if (!SpawnAutoGeneratedObject(Actor, "Actor")) {
    ERR_STREAM << "Failed to spawn ACTOR" << std::endl;
  }
  else
    Actor->ScriptInit();
}

void BasicLevel::SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f & Position)
{
}

bool BasicLevel::SpawnAutoGeneratedObject(std::shared_ptr<LevelObject> Object, std::string IDPrePend)
{
  try
  {
    auto _id = GenerateID();
    std::string objid = IDPrePend + std::to_string(_id);
    Object->InternalID = _id;
    if (Object->ItemID == "") {
      Object->ItemID = objid;
    }
    LevelObjects[objid] = Object;

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

void BasicLevel::SpawnBall(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
{
  //auto ball = BuildBallMesh(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);
  auto Object = std::make_shared<LevelObject>();
  Object->Size = { __TO_FLOAT__(Radius), __TO_FLOAT__(Radius) };
  Object->Position = InitialPosition;
  MeshType type = (BallType == 'G' ? MeshType::BallGo : MeshType::Ball);
  Object->AddCollider(Collider2D::CreateCircularMesh(type, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color));
  //Object->ObjectMesh = BuildBallMesh(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);
  if (!SpawnAutoGeneratedObject(Object, "BallMesh")) {
    //Awh, sad
    //for now, print the error, but don't throw an exception
    ERR_STREAM << "Failed to spawn Ball" << std::endl;
  }
}

void BasicLevel::SpawnSquare(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto sq = BuildPolygonMesh(4, radius, 0, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  auto Object = std::make_shared<LevelObject>();
  Object->Size = { radius, radius };
  Object->Position = InitialPosition;
  MeshType type = MeshType::Polygon;
  Object->AddCollider(Collider2D::CreatePolygonMesh(4, radius, 0, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color));
  //Object->ObjectMesh = BuildPolygonMesh(4, radius, 0, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);

  if (!SpawnAutoGeneratedObject(Object, "Square")) {
    ERR_STREAM << "Failed to spawn Square" << std::endl;
  }
}

void BasicLevel::SpawnRect(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto sq = BuildPolygonMesh(4, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  std::shared_ptr<LevelObject> Object = std::make_shared<LevelObject>();
  Object->Size = { radius, radius };
  Object->Position = InitialPosition;
  Object->AddCollider(Collider2D::CreatePolygonMesh(4, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color));
  //Object->ObjectMesh = BuildPolygonMesh(4, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  if (!SpawnAutoGeneratedObject(Object, "RectMesh")) {
    ERR_STREAM << "Failed to spawn Rect" << std::endl;
  }
}

void BasicLevel::SpawnTriangle(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  std::shared_ptr<LevelObject> Object = std::make_shared<LevelObject>();
  Object->Size = { radius, radius };
  Object->Position = InitialPosition;
  Object->AddCollider(Collider2D::CreatePolygonMesh(3, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color));
  //Object->ObjectMesh = BuildPolygonMesh(3, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  if (!SpawnAutoGeneratedObject(Object, "TriMesh")) {
    ERR_STREAM << "Failed to spawn TriMesh" << std::endl;
  }
}

void BasicLevel::SpawnNPoly(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto poly = BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  std::shared_ptr<LevelObject> Object = std::make_shared<LevelObject>();
  Object->Size = { radius, radius };
  Object->Position = InitialPosition;
  Object->AddCollider(Collider2D::CreatePolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color));
  //Object->ObjectMesh = BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  if (!SpawnAutoGeneratedObject(Object, "NPolyMesh")) {
    ERR_STREAM << "Failed to spawn NPolyMesh" << std::endl;
  }
}

void BasicLevel::SpawnWave(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius, bool IsHard, unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight, float ampLeft, float waveLenLeft, float rFreqLeft, float elev, float airDen, float depth, float fluidDen)
{

  auto ptr = BuildWaveSegment(type, TopLeftCorner, BottomRightCorner, radius, IsHard, NumWavePts, ampRight, waveLenRight, rFreqRight, ampLeft, waveLenLeft, rFreqLeft, elev, airDen, depth, fluidDen);
  Segments.push_back(ptr);
}

void BasicLevel::SpawnTrigger(const std::string &Name, const sf::Vector2f & Where, const sf::Vector2f & _Size, std::function<void(void)> TriggerCB, std::function<void(std::shared_ptr<LevelObject>)> CheckCB, bool NotifyEveryFrame, bool DoPhysicalResponse, bool RestrictTriggers, std::vector<std::string> RestrictedTriggers)
{
  try
  {
    auto Trigger = std::make_shared<TriggerObject>(TriggerMethod::Touch_NoPhysicalResponse);
    Trigger->SetTriggerMethod(TriggerMethod::Touch_NoPhysicalResponse);
    Trigger->SetNotifyEveryFrame(NotifyEveryFrame);
      
    auto collider = Collider2D::CreatePolygonMesh(
      4, 
      _Size.x / 2.f, 
      0.f, 
      Where, 
      sf::Vector2f(0.f, 0.f), 
      5.f, 
      0.f, 
      sf::Color::Red
    );
      
    if (RestrictTriggers) {
      Trigger->SetRestrictedTriggerIDs(RestrictedTriggers);
    }

    m_TriggerObjects.emplace(
      std::piecewise_construct,
      std::make_tuple(Name),
      std::make_tuple(Trigger)
    );
  }
  catch (EngineRuntimeError& e)
  {
    e.AddCause(ExceptionCause::SpawnFailure);
    e.AddMessage(EXCEPTION_MESSAGE("Failed to spawn TriggerObject"));

    throw;
  }
}

void BasicLevel::LoadFromFile(const std::string & file)
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

void BasicLevel::LoadAssets(const Json::Value & value)
{
  LoadTextures(value["Textures"]);
  LoadAudio(value["Audio"]);
  LoadTileSheets(value["Sheets"]);
  LoadAnimations(value["Animations"]);
}

void BasicLevel::LoadAudio(const Json::Value & value)
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

void BasicLevel::LoadTextures(const Json::Value & value)
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

void BasicLevel::LoadTileSheets(const Json::Value & value)
{
  for (auto & sheet : value)
    LoadSheet(sheet);
}

void BasicLevel::LoadSheet(const Json::Value & value)
{
  try
  {
    
  }
  catch (Json::Exception &err)
  {
    throw EngineRuntimeError({ ExceptionCause::DataParseError }, EXCEPTION_MESSAGE("JSON error"));
  }
}

void BasicLevel::LoadAnimations(const Json::Value & value)
{
  for (auto & anim : value) {

    std::string name = anim["Name"].asString();
    std::string texture = anim["Texture"].asString();
    float time = anim["FrameTime"].asFloat();
    bool bPingPong = anim["PingPong"].asBool();
    bool looping = anim["Looping"].asBool();

    auto it = Textures.find(texture);
    if (it == Textures.end())
      return;

    auto tex = it->second;
    Animations[name] = std::make_shared<Animation>();

    Animations[name]->SetSpriteSheet(tex, "Anim" + name + "sheet");
    Animations[name]->SetFrameTime(time);

    std::vector<sf::IntRect> Frames = {};
    auto frames = anim["Frames"];
    sf::IntRect framerect = {};

    for (auto & frame : frames) {
      framerect.left = frame[0].asInt();
      framerect.top = frame[1].asInt();
      framerect.width = frame[2].asInt();
      framerect.height = frame[3].asInt();

      Animations[name]->AddFrame(framerect);
    }

    Animations[name]->MakePingPong(bPingPong);
    Animations[name]->MakeLooped(looping);
  }
}

void BasicLevel::CleanUp()
{
}

void BasicLevel::UpdateObjectPhysics()
{
  static std::vector<PhysicsEngineBaseMeshType *> MeshVector;
  static std::vector<PhysicsEngineSegmentType *> SegVector;

  static std::vector<std::shared_ptr<Collider2D>> Colliders;


  MeshVector.clear();
  SegVector.clear();
  Colliders.clear();

  for (auto & obj : LevelObjects) {
    auto vec = obj.second->GetColliders();
    auto _vec = obj.second->GetOccluders();
    for (auto & mesh : vec) {
      Colliders.push_back(mesh);
    }
  }

  for (auto & seg : Segments)
    SegVector.push_back(seg.get());

  UpdatePhysics(Colliders, SegVector);
}

CEREAL_REGISTER_TYPE(BasicLevel);
