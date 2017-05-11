////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "Level\BasicLevel.h"
#include "Exceptions\Exceptions.hpp"
#include "Resources\Resources.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <fstream>

/************************************************************************/
/*                         BasicLevel                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/02                                  */
/************************************************************************/

namespace SFEngine
{
  /************************************************************************/
  /* Required method overrides                                            */
  /************************************************************************/

  BasicLevel::BasicLevel()
    : m_ColliderTree(SVector2F(0.f, 0.f), 0u, SVector2U(0, 0)), m_Gravity(0.f, 0.f)
  {

  }

  BasicLevel::BasicLevel(const sf::Vector2u & LevelSize, const sf::FloatRect & DefaultView, bool showlines, const sf::Vector2f & GridSpacing)
    : m_ColliderTree((SVector2F)LevelSize, 10u, SVector2U(10u, 10u)), m_Gravity(0.f, 0.f), m_CurrentView(0.f, 0.f, (float)LevelSize.x, (float)LevelSize.y)
  {
  }

  BasicLevel::~BasicLevel()
  {
  }

  void BasicLevel::TickUpdate(const SFLOAT & delta)
  {
    for (auto & Object : m_GameObjects) {
      Object->TickUpdate(delta);
    }

    UpdatePhysics();
  }

  void BasicLevel::Render(SFLOAT Alpha, SharedRTexture Target)
  {

  }

  void BasicLevel::OnShutDown()
  {
    m_Textures.clear();
    m_SoundBuffers.clear();
    
    for (auto & object : m_GameObjects)
      object->OnShutDown();
    m_GameObjects.clear();
  }

  void BasicLevel::SerializeOut(SOFStream & out)
  {
  }

  void BasicLevel::SerializeIn(SIFStream & in)
  {
  }

  void BasicLevel::HandleInputEvent(const UserEvent & evnt)
  {
  }

  void BasicLevel::StepSimulation(SFLOAT Dt)
  {
    m_TimeStepAccumulated += Dt;
    UpdatePhysics();
  }

  void BasicLevel::InterpolatePhysics(SFLOAT Alpha)
  {
    for (auto & collider : m_Colliders)
      collider->InterpolateState(Alpha);
  }

  void BasicLevel::InterpolateState(SFLOAT Alpha)
  {
    InterpolatePhysics(Alpha);
  }

  void BasicLevel::EventUpdate(sf::Event Event)
  {
  }

  /************************************************************************/
  /* Basic functionality methods                                          */
  /************************************************************************/

  void BasicLevel::LoadLevel(const std::string & lvlfile)
  {

  }
  void BasicLevel::OnBegin()
  {
  }
  void BasicLevel::OnEnd()
  {
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
  void BasicLevel::CleanUp()
  {
  }

  void BasicLevel::SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f & Position)
  {
    Actor->SetPosition(Position);
    m_GameObjects.push_back(Actor);
  }

  void BasicLevel::SpawnObject(std::shared_ptr<GameObject> Object, const sf::Vector2f & Position)
  {
  }

  void BasicLevel::RenderOnTexture(SFLOAT Alpha, SharedRTexture Texture)
  {
    for (auto & Object : m_GameObjects) {
      Object->Render(Alpha, Texture);
    }
    
    for (auto & Collider : m_Colliders)
      Collider->Render(Alpha, Texture);
  }

  void BasicLevel::Load()
  {
    
  }

  void BasicLevel::Unload()
  {
  }

  /************************************************************************/
  /* Asset loading methods                                                */
  /************************************************************************/
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
      m_ProjectPath = ProjectFile["Project"]["Info"]["PROJECT_PATH"].asString();
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
      path = m_ProjectPath + file["Path"].asString();

      m_SoundBuffers[name] = LoadSoundBuffer(path, name);// std::make_shared<sf::SoundBuffer>();
      if (!m_SoundBuffers[name]) {
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
      path = m_ProjectPath + tex["Path"].asString();
      m_Textures[texname] = LoadTexture(path, texname);// std::make_shared<sf::Texture>();
      if (!m_Textures[texname]) {
        std::cerr << "Unable to load texture: " << path << std::endl;
      }
    }
  }

  void BasicLevel::LoadTileSheets(const Json::Value & value)
  {
  }
  void BasicLevel::LoadSheet(const Json::Value & value)
  {
  }
  void BasicLevel::LoadAnimations(const Json::Value & value)
  {
  }

  void BasicLevel::UpdatePhysics(UINT32 Steps)
  {
    //static STDVector<SPtrShared<Collider2D>> MeshVector;
    //static STDVector<SegmentMeshPtr> SegmentVector;

    //MeshVector.clear();
    //SegmentVector.clear();

    //for (auto & object : m_GameObjects) {
    //  auto vec = object->GetColliders();
    //  for (auto & mesh : vec)
    //    MeshVector.push_back(mesh);
    //}
    //for (auto & collider : m_Colliders)
    //  MeshVector.emplace_back(collider);

    //for (auto & seg : m_Segments) {
    //  SegmentVector.push_back(seg);
    //}

    UpdatePhysicsMeshes(m_Colliders, m_Segments, Steps);
  }

} // namespace SFEngine
