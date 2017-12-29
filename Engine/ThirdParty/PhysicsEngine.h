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

#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "Physics/arcSeg.h"
#include "Physics/ball.h"
#include "Physics/ball_go.h"
#include "Physics/block.h"
#include "Physics/decayPolygon.h"
#include "Physics/expandPolygon.h"
#include "Physics/lineBumper.h"
#include "Physics/lineSeg.h"
#include "Physics/lineSegElevator.h"
#include "Physics/lineSegFlip.h"
#include "Physics/lineSegRotate.h"
#include "Physics/lineSegSwing.h"
#include "Physics/mvHit.h"
#include "Physics/pipeSeg.h"
#include "Physics/regPolygon.h"
#include "Physics/segHit.h"
#include "Physics/vec2d.h"
#include "Physics/waveSeg.h"

namespace Engine
{
  using PhysicsEngineBaseMeshType = mvHit;
  using PhysicsEngineBlockType = block;
  using PhysicsEngineSegmentType = lineSeg;
  using PhysicsEngineWaveSegment = waveSeg;
  using PhysicsEngineArgSegmentType = arcSeg;
  using PhysicsEnginePipeSegmentType = pipeSeg;
  using PhysicsEngineElevatorType = lineSegElevator;
  using PhysicsEngineSegFlipType = lineSegFlip;
  using PhysicsEngineSegRotateType = lineSegRotate;
  using PhysicsEngineSegSwingType = lineSegSwing;
  using PhysicsEngineExpandingPolygon = expandPolygon;

  class Collider2D;
  class Occluder2D;

  using BaseMeshPtr = std::shared_ptr<PhysicsEngineBaseMeshType>;
  using BlockMeshPtr = std::shared_ptr<PhysicsEngineBlockType>;
  using SegmentPtr = std::shared_ptr<PhysicsEngineSegmentType>;
  using ArcSegmentPtr = std::shared_ptr<PhysicsEngineArgSegmentType>;
  using WaveSegmentPtr = std::shared_ptr<PhysicsEngineWaveSegment>;
  using PipeSegmentPtr = std::shared_ptr<PhysicsEnginePipeSegmentType>;
  using ElevatorSegmentPtr = std::shared_ptr<PhysicsEngineElevatorType>;
  using SegFlipPtr = std::shared_ptr<PhysicsEngineSegFlipType>;
  using SegRotatePtr = std::shared_ptr<PhysicsEngineSegRotateType>;
  using SegSwingPtr = std::shared_ptr<PhysicsEngineSegSwingType>;
  using ExpandMeshPtr = std::shared_ptr<PhysicsEngineExpandingPolygon>;

  BaseMeshPtr BuildBallMesh
  (
    char BallType, 
    const sf::Vector2f &InitialPosition, 
    const sf::Vector2f &InitialVelocity, 
    unsigned int Radius, 
    float Mass, 
    float CoeffecientOfRest, 
    const sf::Color &Color
  );

  BaseMeshPtr BuildPolygonMesh
  (
    unsigned int num_sides, 
    float radius, 
    float init_rotation, 
    const sf::Vector2f &InitialPosition, 
    const sf::Vector2f &InitialVelocity, 
    float mass, float CoeffOfRest, 
    const sf::Color &Color
  );

  ExpandMeshPtr BuildExpandPolygonMesh
  (
    unsigned int numSides,
    float radiusWhenFull,
    float IAngle,
    const sf::Vector2f &InitialPosition,
    const sf::Vector2f &InitialVelocity,
    float Mass,
    float CoeffOfRest,
    float GrowSpeed,
    sf::Color Color
  );

  SegmentPtr BuildSegmentMesh
  (
    char type, 
    const sf::Vector2i &TopLeftCorner, 
    const sf::Vector2i &BottomRightCorner, 
    float radius = -1
  );

  WaveSegmentPtr BuildWaveSegment
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
  );

  ArcSegmentPtr BuildArcSegmentMesh
  (
    const sf::Vector2f CenterOfArcPoint,
    sf::Vector2f StartPoint,
    sf::Vector2f EndPoint,
    float Radius
  );

  BlockMeshPtr BuildBlockMesh
  (
    float Width,
    float Height,
    float IAngle,
    const sf::Vector2f &Position,
    const sf::Vector2f &Velocity,
    float Mass,
    float CoeffOfRest,
    sf::Color Color = sf::Color::Transparent
  );

  ElevatorSegmentPtr BuildElevator
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    const sf::Vector2f &Velocity,
    float SMin,
    float SMax
  );

  SegFlipPtr BuildSegFlip
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    float RotateVelocity,
    float RotateAngle
  );

  SegRotatePtr BuildSegRotate
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    float RotateVelocity
  );

  SegSwingPtr BuildSegSwing
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    float RotateVelocity,
    float Mass
  );

  std::stringstream GetFormattedBallConstructionData
  (
    char BallType, 
    const sf::Vector2f &InitialPosition, 
    const sf::Vector2f &InitialVelocity, 
    unsigned int Radius, 
    float Mass, 
    float CoeffecientOfRest, 
    const sf::Color &Color
  );

  std::stringstream GetFormattedPolyConstructionData
  (
    unsigned int num_sides, 
    float radius, 
    float init_rotation, 
    const sf::Vector2f &InitialPosition, 
    const sf::Vector2f &InitialVelocity, 
    float mass, 
    float CoeffOfRest, 
    const sf::Color &Color
  );

  std::stringstream GetFormattedExpandPolyConstructionData
  (
    unsigned int numSides,
    float radiusWhenFull,
    float IAngle,
    const sf::Vector2f &InitialPosition,
    const sf::Vector2f &InitialVelocity,
    float Mass,
    float CoeffOfRest,
    float GrowSpeed,
    sf::Color Color
  );

  std::stringstream GetFormattedSegmentConstructionData
  (
    char type, 
    const sf::Vector2i &TopLeftCorner, 
    const sf::Vector2i &BottomRightCorner, 
    float radius
  );

  std::stringstream GetFormattedWaveSegmentConstructionData
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
  );

  std::stringstream GetFormattedArcSegmentData
  (
    const sf::Vector2f CenterOfArcPoint,
    sf::Vector2f StartPoint,
    sf::Vector2f EndPoint,
    float Radius
  );

  std::stringstream GetFormattedBlockMeshData
  (
    float Width,
    float Height,
    float IAngle,
    const sf::Vector2f &Position,
    const sf::Vector2f &Velocity,
    float Mass,
    float CoeffOfRest,
    sf::Color Color = sf::Color::Transparent
  );

  std::stringstream GetFormattedElevatorSegmentData
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    const sf::Vector2f &Velocity,
    float SMin,
    float SMax
  );

  std::stringstream GetFormattedSegFipData
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    float RotateVelocity,
    float RotateAngle
  );

  std::stringstream GetFormattedSegRotateData
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    float RotateVelocity
  );

  std::stringstream GetFormattedSegSwingData
  (
    const sf::Vector2f &Position,
    const sf::Vector2f &Length,
    float RotateVelocity,
    float Mass
  );

  void UpdatePhysics(std::vector<PhysicsEngineBaseMeshType *> &Meshes, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t Steps = 1);
  void UpdatePhysics(std::vector<std::shared_ptr<Engine::Collider2D>> Colliders, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t steps = 1);
  void UpdatePhysics(std::vector<std::shared_ptr<Engine::Occluder2D>> Occluders, std::vector<std::shared_ptr<Engine::Collider2D>> Colliders, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t steps = 1);
  void AssignBoundaries(float WindowHeight, float WindowWidth);
  void SetGravity(::vec2d *Gravity);
}
