#ifndef SFEngine_DependencyInterface_H
#define SFEngine_DependencyInterface_H

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


/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "BasicIncludes.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <PhysicsEngine\mvHit.h>
#include <PhysicsEngine\segHit.h>
#include <PhysicsEngine\arcSeg.h>
#include <PhysicsEngine\ball.h>
#include <PhysicsEngine\ball_go.h>
#include <PhysicsEngine\block.h>
#include <PhysicsEngine\decayPolygon.h>
#include <PhysicsEngine\expandPolygon.h>
#include <PhysicsEngine\lineBumper.h>
#include <PhysicsEngine\lineSeg.h>
#include <PhysicsEngine\lineSegConveyor.h>
#include <PhysicsEngine\lineSegElevator.h>
#include <PhysicsEngine\lineSegFlip.h>
#include <PhysicsEngine\lineSegRotate.h>
#include <PhysicsEngine\lineSegSwing.h>
#include <PhysicsEngine\pipeSeg.h>
#include <PhysicsEngine\polyHitFuncs.h>
#include <PhysicsEngine\rec.h>
#include <PhysicsEngine\regPolygon.h>
#include <PhysicsEngine\waveSeg.h>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <sstream>
#include <string>
#include <vector>

/************************************************************************/
/*                        DependencyInterface                           */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

namespace SFEngine
{

  using MeshBase = ::mvHit;
  using PolyMesh = ::regPolygon;
  using BlockMesh = ::block;
  using SegmentMesh = ::segHit;
  using LineSegmentMesh = ::lineSeg;
  using ExpandMesh = ::expandPolygon;
  using BallMesh = ::ball;
  using WaveMesh = ::waveSeg;

  using MeshBasePtr = SPtrShared<mvHit>;
  using PolyMeshPtr = SPtrShared<PolyMesh>;
  using BlockMeshPtr = SPtrShared<BlockMesh>;
  using SegmentMeshPtr = SPtrShared<SegmentMesh>;
  using LineSegmentMeshPtr = SPtrShared<LineSegmentMesh>;
  using BallMeshPtr = SPtrShared<BallMesh>;
  using ExpandMeshPtr = SPtrShared<ExpandMesh>;
  using WaveMeshPtr = SPtrShared<WaveMesh>;

  class Collider2D;
  using CollideVector = STDVector<SPtrShared<Collider2D>>;

  /************************************************************************/
  /* Methods for mesh construction                                        */
  /************************************************************************/
  BallMeshPtr BuildBallMesh2D
  (
    char BallType,
    const sf::Vector2f &InitialPosition,
    const sf::Vector2f &InitialVelocity,
    unsigned int Radius,
    float Mass,
    float CoeffecientOfRest,
    const sf::Color &Color
  );

  PolyMeshPtr BuildPolygonMesh2D
  (
    unsigned int num_sides,
    float radius,
    float init_rotation,
    const sf::Vector2f &InitialPosition,
    const sf::Vector2f &InitialVelocity,
    float mass, float CoeffOfRest,
    const sf::Color &Color
  );

  ExpandMeshPtr BuildExpandPolygonMesh2D
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

  SegmentMeshPtr BuildSegmentMesh2D
  (
    char type,
    const sf::Vector2i &TopLeftCorner,
    const sf::Vector2i &BottomRightCorner,
    float radius = -1
  );

  WaveMeshPtr BuildWaveSegmentMesh2D
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

  /************************************************************************/
  /* Methods for construcing properly formatted init data for meshes      */
  /************************************************************************/
  template<typename T>
  void InsertIntoStream(std::stringstream &Stream, T Data);

  template<typename T>
  void FormatConstructionData(std::stringstream &Stream, T Data);

  template<typename T, typename... Others>
  void FormatConstructionData(std::stringstream &Stream, T Data, Others... Rest);

  template<typename T, typename... Others>
  void FormatConstructionData(std::stringstream & Stream, T Data, Others... Rest);

  /************************************************************************/
  /* Physics update methods                                               */
  /* Wraps physics engine update code & interfaces with collider classes  */
  /************************************************************************/
  void UpdatePhysics(CollideVector &Colliders, STDVector<SegmentMeshPtr> Segments, UINT32 Steps = 1);
}

#include "DependencyInterface.inl"
#endif // SFEngine_DependencyInterface_H
