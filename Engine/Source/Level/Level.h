#pragma once

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

#include "BasicLevel.h"
#include "Physics\Physics.h"
#include "Lights\LightingSystem.h"

#include "SelbaWard\TileMap.hpp"

class GameMain;

#ifdef WITH_EDITOR
class Editor;
#endif

class Level : public BasicLevel
{

public:
  friend class GameMain;
  TYPEDEF_PARENT_CLASS(BasicLevel);

  static std::shared_ptr<Level> DefaultEmptyLevel();

  Level();
  Level(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
  Level(const Level &) = delete;
  Level(const BaseEngineInterface &Copy) = delete;
  ~Level();
    
  static void BindMethods(chaiscript::ModulePtr mptr);

  void TickUpdate(const double &delta) override;
  void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override;
  void OnShutDown() override;
  void SerializeOut(std::ofstream &out) override;
  void SerializeIn(std::ifstream &in) override;

  //void SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position) override;
  //void SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f &Position) override;
  //void SpawnLight(std::shared_ptr<LightObject> Light, const sf::Vector2f &Position);

  void HandleInputEvent(const UserEvent &evnt);
  void HandleKeyPress(const sf::Keyboard::Key &key) override;
  void HandleKeyRelease(const sf::Keyboard::Key &key) override;
  void HandleWindowResized() override;

  static std::shared_ptr<LevelObject> GetObjectByName(const std::string &ID);
  void LoadLevel(const std::string &lvlfile) override;
  void OnBegin() override;
  void OnEnd() override;

  virtual std::string GetClass() const override;

private:
  void RenderRegular();
  void RenderLoadingScreen();
  void GenerateGrid();
  sf::View Camera;
  std::shared_ptr<sf::RenderTexture> SceneTexture;
  //Methods for spawning in new object
  void SpawnBall
  (
    char BallType, 
    const sf::Vector2f & InitialPosition, 
    const sf::Vector2f & InitialVelocity,
    unsigned int Radius, 
    float Mass, 
    float CoeffecientOfRest, 
    const sf::Color & Color
  ) override;

  void SpawnSquare
  (
    float radius, 
    float init_rotation, 
    const sf::Vector2f & InitialPosition, 
    const sf::Vector2f & InitialVelocity, 
    float mass, 
    float CoeffOfRest, 
    const sf::Color & Color
  ) override;

  void SpawnRect
  (
    float radius, 
    float init_rotation, 
    const sf::Vector2f & InitialPosition, 
    const sf::Vector2f & InitialVelocity, 
    float mass, 
    float CoeffOfRest, 
    const sf::Color & Color
  ) override;

  void SpawnTriangle
  (
    float radius, 
    float init_rotation, 
    const sf::Vector2f & InitialPosition, 
    const sf::Vector2f & InitialVelocity, 
    float mass, 
    float CoeffOfRest, 
    const sf::Color & Color
  ) override;

  void SpawnNPoly
  (
    unsigned int num_sides, 
    float radius, 
    float init_rotation, 
    const sf::Vector2f & InitialPosition, 
    const sf::Vector2f & InitialVelocity, 
    float mass, 
    float CoeffOfRest, 
    const sf::Color & Color
  ) override;

  void SpawnWave
  (
    char type, 
    const sf::Vector2i &TopLeftCorner, 
    const sf::Vector2i &BottomRightCorner, 
    float radius, 
    bool IsHard,
    unsigned int NumWavePts, 
    float ampRight, 
    float waveLenRight, 
    float rFreqRight,
    float ampLeft, 
    float waveLenLeft, 
    float rFreqLeft,
    float elev, 
    float airDen, 
    float depth, 
    float fluidDen
  ) override;

  bool SpawnAutoGeneratedObject(std::shared_ptr<LevelObject> Object, std::string IDPrePend = "");
    
  void UpdateObjectPhysics() override;
  std::vector<unsigned char> lvlData;

  //functions for loading from file
  void LoadFromFile(const std::string &file) override;
  void LoadAssets(const Json::Value &value) override;
  void LoadAudio(const Json::Value &value) override;
  void LoadTextures(const Json::Value &value) override;
  void LoadTileSheets(const Json::Value &value) override;
  void LoadSheet(const Json::Value &value) override;
  void LoadAnimations(const Json::Value &value) override;
};
