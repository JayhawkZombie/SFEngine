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
#include "Objects/GameObject.h"
#include "Globals/GlobalHooks.h"
#include "Actor/Actor.h"
#include "Physics/Collider.h"
#include "Physics/Occluder.h"
#include "Exceptions/Exceptions.h"
#include "Time/TimerManager.h"

#include <cereal/archives/portable_binary.hpp>

namespace
{
  std::string PROJECT_PATH = "";
}

BasicLevel::BasicLevel(const BaseEngineInterface & Copy)
  : BaseEngineInterface(Copy)
{
  
}

BasicLevel::BasicLevel(const sf::FloatRect &DefaultView)
  : CurrentView(DefaultView), Gravity(new ::vec2d)
{
    
}

BasicLevel::BasicLevel()
  : Gravity(new ::vec2d)
{

}

BasicLevel::~BasicLevel()
{
  if (Gravity)
    delete Gravity;
}


std::shared_ptr<BasicLevel> BasicLevel::DefaultEmptyLevel()
{
  return std::make_shared<BasicLevel>();
}

std::shared_ptr<BaseEngineInterface> BasicLevel::Clone() const
{
  auto LevelCopy = std::make_shared<BasicLevel>(CurrentView);

  return LevelCopy;
}

void BasicLevel::TickUpdate(const double & delta)
{
  static double cumulative = 0.f;
  cumulative += delta;

  static hres_time_point FrameStart = hres_clock::now();

  for (auto & obj : m_GameObjects)
    obj.second->TickUpdate(delta);

  UpdateObjectPhysics();
}

std::string BasicLevel::GetClass() const
{
  return std::string("BasicLevel");
}

void BasicLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  //This function shouldn't ever be called
  // ^ lies

  for (auto & seg : SegHits)
    seg->draw(*Target);

  for (auto & hit : MVHits)
    hit->draw(*Target);
}

void BasicLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  Render(Texture);
}

void BasicLevel::OnShutDown()
{
  for (auto & obj : m_GameObjects)
    obj.second->OnShutDown();

  m_GameObjects.clear();

  Textures.clear();

  MVHits.clear();
  SegHits.clear();
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


void BasicLevel::Init()
{

}

void BasicLevel::OnBegin()
{
  for (auto & obj : m_GameObjects)
    obj.second->BeginPlay();


  auto timers = GetGlobalTimerManager();

  timers->AddTimer(1.0, true, 0.0, 1.0, [] () { std::cout << "1 sec repeat timer\n"; });
  timers->AddTimer(5.0, true, 0.0, 1.0, [] () { std::cout << "5 sec delay timer\n"; });
}

void BasicLevel::OnEnd()
{
  for (auto & obj : m_GameObjects)
    obj.second->EndPlay();
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
  
}

void BasicLevel::SpawnObject(std::shared_ptr<GameObject> Object, const sf::Vector2f & Position)
{
}

bool BasicLevel::SpawnAutoGeneratedObject(std::shared_ptr<GameObject> Object, std::string IDPrePend)
{
  try
  {
    auto _id = GenerateID();
    std::string objid = IDPrePend + std::to_string(_id);
    Object->SetInternalD(_id);
    if (Object->GetID() == "") {
      Object->SetID(objid);
    }
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


void BasicLevel::Save(const std::string &Filename)
{
  std::ofstream ofile(Filename);

  std::cout << "Saving to: " << Filename << "\n";

  {
    cereal::PortableBinaryOutputArchive archive(ofile);

    archive(MVHits);
    archive(SegHits);
  }

  ofile.close();
  std::cout << "Done saving\n";

}


void BasicLevel::Load(const std::string &Filename)
{
  std::ifstream ifile(Filename, std::ios_base::binary);


  if (ifile)
  {

    std::cout << "Loading from: " << Filename << "\n";

    {
      cereal::PortableBinaryInputArchive archive(ifile);

      archive(MVHits);
      archive(SegHits);
    }

    ifile.close();
    std::cout << "Done loading\n";
  }
  else
  {
    std::cout << "Failed to load\n";
  }
}

void BasicLevel::SpawnBall(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color)
{
  //auto ball = BuildBallMesh(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(__TO_FLOAT__(Radius), __TO_FLOAT__(Radius)));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  MeshType type = ( BallType == 'G' ? MeshType::BallGo : MeshType::Ball );

  if (!SpawnAutoGeneratedObject(Object, "BallMesh"))
  {
    //Awh, sad
    //for now, print the error, but don't throw an exception
    ERR_STREAM << "Failed to spawn Ball" << std::endl;
  }
}

void BasicLevel::SpawnSquare(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto sq = BuildPolygonMesh(4, radius, 0, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  MeshType type = MeshType::Polygon;

  if (!SpawnAutoGeneratedObject(Object, "Square"))
  {
    ERR_STREAM << "Failed to spawn Square" << std::endl;
  }
}

void BasicLevel::SpawnRect(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  auto Object = std::make_shared<GameObject>();

  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  if (!SpawnAutoGeneratedObject(Object, "RectMesh"))
  {
    ERR_STREAM << "Failed to spawn Rect" << std::endl;
  }
}

void BasicLevel::SpawnTriangle(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  if (!SpawnAutoGeneratedObject(Object, "TriMesh"))
  {
    ERR_STREAM << "Failed to spawn TriMesh" << std::endl;
  }
}

void BasicLevel::SpawnNPoly(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color)
{
  //auto poly = BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
  auto Object = std::make_shared<GameObject>();
  Object->SetSize(sf::Vector2f(radius, radius));
  Object->SetPosition(InitialPosition);
  Object->SetVelocity(InitialVelocity);
  if (!SpawnAutoGeneratedObject(Object, "NPolyMesh"))
  {
    ERR_STREAM << "Failed to spawn NPolyMesh" << std::endl;
  }
}

void BasicLevel::SpawnWave(char type, const sf::Vector2i & TopLeftCorner, const sf::Vector2i & BottomRightCorner, float radius, bool IsHard, unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight, float ampLeft, float waveLenLeft, float rFreqLeft, float elev, float airDen, float depth, float fluidDen)
{

  auto ptr = BuildWaveSegment(type, TopLeftCorner, BottomRightCorner, radius, IsHard, NumWavePts, ampRight, waveLenRight, rFreqRight, ampLeft, waveLenLeft, rFreqLeft, elev, airDen, depth, fluidDen);
  Segments.push_back(ptr);
}

void BasicLevel::SpawnTrigger(const std::string &Name, const sf::Vector2f & Where, const sf::Vector2f & _Size, std::function<void(void)> TriggerCB, std::function<void(std::shared_ptr<GameObject>)> CheckCB, bool NotifyEveryFrame, bool DoPhysicalResponse, bool RestrictTriggers, std::vector<std::string> RestrictedTriggers)
{
  
}

void BasicLevel::CleanUp()
{
}

void BasicLevel::UpdateObjectPhysics()
{
  UpdateAllPhysics(MVHits, SegHits);
}

CEREAL_REGISTER_TYPE(BasicLevel);
