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
#include "DependencyInterface.h"
#include "Exceptions\Exceptions.hpp"
#include "Physics\Collider.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <sstream>
#include <ostream>

/************************************************************************/
/*                        DependencyInterface                           */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/29                                  */
/************************************************************************/

namespace SFEngine
{

  /************************************************************************/
  /* Anon Namespace for global physics data                               */
  /************************************************************************/
  namespace
  {
    ::vec2d CurrentGravity;
  }

  /************************************************************************/
  /* Construct a physics 2D ball                                          */
  /* Centered at InitialPosition with radius = Radius                     */
  /************************************************************************/
  BallMeshPtr BuildBallMesh2D
  (
    char BallType, 
    const sf::Vector2f & InitialPosition, 
    const sf::Vector2f & InitialVelocity, 
    unsigned int Radius, 
    float Mass, 
    float CoeffecientOfRest, 
    const sf::Color & Color
  )
  {
    try
    {
      std::stringstream Data{ "" };
      FormatConstructionData(
        Data, 
        BallType, 
        InitialPosition.x, 
        InitialPosition.y, 
        Radius, 
        Mass, 
        CoeffecientOfRest, 
        Color.r, 
        Color.g, 
        Color.b
      );

      BallMeshPtr Mesh = std::make_shared<BallMesh>(Data);
      Mesh->siz = 2 * Radius;
      return Mesh;
    }
    catch (EngineRuntimeError& e)
    {
      SString Message = "Failed to construct BallMesh: " + SString(e.what());
      throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitError }, EXCEPTION_MESSAGE(Message));
    }
  } // BuildBallMesh2D

  PolyMeshPtr BuildPolygonMesh2D
  (
    unsigned int num_sides,
    float radius,
    float init_rotation,
    const sf::Vector2f &InitialPosition,
    const sf::Vector2f &InitialVelocity,
    float mass, float CoeffOfRest,
    const sf::Color &Color
  )
  {
    try
    {
      SStream Data{ "" };
      FormatConstructionData(
        Data, 
        num_sides, 
        radius, 
        init_rotation, 
        InitialPosition.x, 
        InitialPosition.y, 
        InitialVelocity.x,
        InitialVelocity.y, 
        mass, 
        CoeffOfRest, 
        (unsigned char)Color.r, 
        (unsigned char)Color.g, 
        (unsigned char)Color.b
      );
      PolyMeshPtr Mesh = std::make_shared<PolyMesh>(Data);
      Mesh->siz = 2 * radius;
      return Mesh;
    }
    catch (EngineRuntimeError& e)
    {
      SString Message = "Failed to construct PolygonMesh2D: " + SString(e.what());
      throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitError }, EXCEPTION_MESSAGE(Message));
    }
  } // BuildPolygonMesh2D

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
  )
  {
    try
    {
      SStream Data{ "" };
      FormatConstructionData(
        Data,
        numSides,
        radiusWhenFull,
        InitialPosition.x,
        InitialPosition.y,
        InitialVelocity.x,
        InitialVelocity.y,
        Mass,
        CoeffOfRest,
        GrowSpeed,
        Color.r,
        Color.g,
        Color.b
      );
      ExpandMeshPtr Mesh = std::make_shared<ExpandMesh>(Data);
      return Mesh;
    }
    catch (EngineRuntimeError& e)
    {
      SString Message = "Failed to construct ExpandPolygon2D: " + SString(e.what());
      throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitError }, EXCEPTION_MESSAGE(Message));
    }
  } // BuildExpandPolygonMesh2D


  SegmentMeshPtr BuildSegmentMesh2D
  (
    char type,
    const sf::Vector2i &TopLeftCorner,
    const sf::Vector2i &BottomRightCorner,
    float radius
  )
  {
    try
    {
      SStream Data{ "" };
      FormatConstructionData(
        Data,
        TopLeftCorner.x,
        TopLeftCorner.y,
        BottomRightCorner.x,
        BottomRightCorner.y,
        radius
      );
      LineSegmentMeshPtr Mesh = std::make_shared<LineSegmentMesh>(Data);
      return Mesh;
     }
     catch (EngineRuntimeError& e)
     {
       SString Message = "Failed to construct SegmentMesh2D: " + SString(e.what());
       throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitError }, EXCEPTION_MESSAGE(Message));
     }
  } // BuildSegmentMesh2D

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
  )
  {
    try
    {
      SStream Data{ "" };
      FormatConstructionData(
        Data,
        TopLeftCorner.x,
        TopLeftCorner.y,
        BottomRightCorner.x,
        BottomRightCorner.y,
        radius,
        IsHard,
        NumWavePts,
        ampRight,
        waveLenRight,
        rFreqRight,
        ampLeft,
        waveLenLeft,
        rFreqLeft,
        elev,
        airDen,
        depth,
        fluidDen
      );
      WaveMeshPtr Mesh = std::make_shared<WaveMesh>(Data);
      return Mesh;
    }
    catch (EngineRuntimeError& e)
    {
      SString Message = "Failed to construct WaveSegmentMesh2D: " + SString(e.what());
      throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitError }, EXCEPTION_MESSAGE(Message));
    }
  } // BuildWaveSegmentMesh2D

  void UpdatePhysicsMeshes(CollideVector & Colliders, STDVector<SegmentMeshPtr> Segments, UINT32 Steps)
  {
    for (auto & Collider : Colliders)
      Collider->RememberPrevPosition();
      /************************************************************************/
      /* Segment update                                                       */
      /************************************************************************/
      for (auto & Segment : Segments)
        Segment->update();

      /************************************************************************/
      /* Detect segment & collider collisions                                 */
      /************************************************************************/
      for (auto & Collider : Colliders) {
        for (auto & Segment : Segments) {
          auto Mesh = Collider->GetMesh();
          if (Mesh.lock() && Segment->hit(*Mesh.lock()))
            Collider->HandleCollisionWithSegment(Segment);
        }
      }

      /************************************************************************/
      /* Detect collider & collider collisions                                */
      /************************************************************************/
      for (SSIZE_T _i = 0; _i < Colliders.size(); ++_i) {
        for (SSIZE_T j = _i; j < Colliders.size(); ++j) {
          if (_i == j)
            continue;

          auto Mesh1 = Colliders[_i]->GetMesh().lock();
          auto Mesh2 = Colliders[j]->GetMesh().lock();

          if (!Mesh1 || !Mesh2)
            continue;

          if (Mesh1->hit(*Mesh2)) {
            Colliders[_i]->HandleCollision(Colliders[j]);
            Colliders[j]->HandleCollision(Colliders[_i]);
          }

        }
      } // Detect collider & Collider collisions

  /************************************************************************/
  /* Collider gravity update                                              */
  /************************************************************************/
  for (auto & Collider : Colliders) {
    if (!Collider->IsStatic())
      Collider->Update(CurrentGravity);
  }
} // UpdatePhysics

  void SetGravity(::vec2d & gravityPtr)
  {
    CurrentGravity = gravityPtr;
  }

  void AssignBoundaries(float WindowWidth, float WindowHeight)
  {
    MeshBase::wdwH = WindowHeight;
    MeshBase::wdwW = WindowWidth;
  }

}
