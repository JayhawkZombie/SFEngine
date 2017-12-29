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

#include "Exceptions\Exceptions.h"
#include "Physics\Collider.h"
#include "Physics\Occluder.h"
#include "PhysicsEngine.h"

namespace
{
  vec2d gravity;
}

template<typename T>
inline void InsertIntoStream(const T &Data, std::stringstream &data_stream, bool newline = false)
{
  if (data_stream.fail())
    throw StreamException({ ExceptionCause::StreamFailure }, EXCEPTION_MESSAGE("StringStream is in a fail state"));

  static std::string str_data = " ";

  str_data = std::to_string(Data);

  data_stream << str_data;

  if (newline)
    data_stream << "\n";
  else
    data_stream << " ";
}


BaseMeshPtr BuildBallMesh
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
  BaseMeshPtr Ball;

  std::stringstream data_stream;
  if (BallType != 'G' && BallType != 'B')
    throw PhysicsInterfaceException({ ExceptionCause::PhysicsInitInvalidData }, EXCEPTION_MESSAGE("BallType is invald"));

  try
  {
    //Get the formatted data and try to use it to create a ball
    data_stream = 
      GetFormattedBallConstructionData(BallType, InitialPosition, InitialVelocity, Radius, Mass, CoeffecientOfRest, Color);

    if (BallType == 'G')
      return (std::make_shared<ball_go>(data_stream));
    else
      return (std::make_shared<ball>(data_stream));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause({ ExceptionCause::PhysicsInitError });
    err.AddMessage(EXCEPTION_MESSAGE("Physics Error : Cannot construct ball"));

    throw;
  }
}

BaseMeshPtr BuildPolygonMesh
(
  unsigned int num_sides, 
  float radius, 
  float init_rotation, 
  const sf::Vector2f & InitialPosition, 
  const sf::Vector2f & InitialVelocity, 
  float mass, 
  float CoeffOfRest, 
  const sf::Color & Color
)
{
  try
  {
    std::stringstream data = GetFormattedPolyConstructionData(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, Color);
    return (std::make_shared<regPolygon>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct poly"));
    throw;
  }
}

ExpandMeshPtr BuildExpandPolygonMesh
(
  unsigned int numSides, 
  float radiusWhenFull, 
  float IAngle, 
  const sf::Vector2f & InitialPosition, 
  const sf::Vector2f & InitialVelocity, 
  float Mass, 
  float CoeffOfRest, 
  float GrowSpeed, 
  sf::Color Color
)
{
  try
  {
    std::stringstream data = GetFormattedExpandPolyConstructionData(numSides, radiusWhenFull, IAngle, InitialPosition, InitialVelocity, Mass, CoeffOfRest, GrowSpeed, Color);
    return (std::make_shared<expandPolygon>(data));
  }
  catch (EngineRuntimeError& e)
  {
    e.AddCause(ExceptionCause::PhysicsInitError);
    e.AddMessage(EXCEPTION_MESSAGE("Physics error : cannot construct expand poly"));
    throw;
  }
}

SegmentPtr BuildSegmentMesh
(
  char type, 
  const sf::Vector2i & TopLeftCorner, 
  const sf::Vector2i & BottomRightCorner, 
  float radius
)
{
  try
  {
    std::stringstream data = GetFormattedSegmentConstructionData(type, TopLeftCorner, BottomRightCorner, radius);
    return (std::make_shared<lineSeg>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct segment"));
    throw;
  }
}

WaveSegmentPtr BuildWaveSegment
(
  char type, 
  const sf::Vector2i & TopLeftCorner, 
  const sf::Vector2i & BottomRightCorner, 
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
    std::stringstream data = GetFormattedWaveSegmentConstructionData(type, TopLeftCorner, BottomRightCorner, radius, IsHard, NumWavePts, ampRight, waveLenRight, rFreqRight, ampLeft, waveLenLeft, rFreqLeft, elev, airDen, depth, fluidDen);
    return (std::make_shared<waveSeg>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct wave"));
    throw;
  }
}

/*
  *
  *     Build an arcSeg data type from provided data
  *
  **/
ArcSegmentPtr BuildArcSegmentMesh
(
  const sf::Vector2f CenterOfArcPoint, 
  sf::Vector2f StartPoint, 
  sf::Vector2f EndPoint, 
  float Radius
)
{
  try
  {
    std::stringstream data = GetFormattedArcSegmentData(CenterOfArcPoint, StartPoint, EndPoint, Radius);
    return (std::make_shared<arcSeg>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct argSegment"));
    throw;
  }
}

/*
  *
  *    Build a block mesh (rectangle - sides do not have to have same length)
  *
  **/
BlockMeshPtr BuildBlockMesh
(
  float Width, 
  float Height, 
  float IAngle, 
  const sf::Vector2f & Position, 
  const sf::Vector2f & Velocity, 
  float Mass, 
  float CoeffOfRest, 
  sf::Color Color
)
{
  try
  {
    std::stringstream data = GetFormattedBlockMeshData(Width, Height, IAngle, Position, Velocity, Mass, CoeffOfRest, Color);
    return (std::make_shared<block>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct block"));
    throw;
  }
}

ElevatorSegmentPtr BuildElevator
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length, 
  const sf::Vector2f & Velocity, 
  float SMin, 
  float SMax
)
{
  try
  {
    std::stringstream data = GetFormattedElevatorSegmentData(Position, Length, Velocity, SMin, SMax);
    return (std::make_shared<lineSegElevator>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct elevator segment"));
    throw;
  }
}

SegFlipPtr BuildSegFlip
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length, 
  float RotateVelocity, 
  float RotateAngle
)
{
  try
  {
    std::stringstream data = GetFormattedSegFipData(Position, Length, RotateVelocity, RotateAngle);
    return (std::make_shared<lineSegFlip>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct flip segment"));
    throw;
  }
}

SegRotatePtr BuildSegRotate
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length,
  float RotateVelocity
)
{
  try
  {
    std::stringstream data = GetFormattedSegRotateData(Position, Length, RotateVelocity);
    return (std::make_shared<lineSegRotate>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct segRotate"));
    throw;
  }
}

SegSwingPtr BuildSegSwing
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length, 
  float RotateVelocity, 
  float Mass
)
{
  try
  {
    std::stringstream data = GetFormattedSegSwingData(Position, Length, RotateVelocity, Mass);
    return (std::make_shared<lineSegSwing>(data));
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause(ExceptionCause::PhysicsInitError);
    err.AddMessage(EXCEPTION_MESSAGE("Physics error : Cannot construct swing segment"));
    throw;
  }
}

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
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream<int>(TopLeftCorner.x, data);
    InsertIntoStream<int>(TopLeftCorner.y, data);
    InsertIntoStream<int>(BottomRightCorner.x, data);
    InsertIntoStream<int>(BottomRightCorner.y, data);
    InsertIntoStream<unsigned int>(NumWavePts, data);
    InsertIntoStream<float>(ampRight, data);
    InsertIntoStream<float>(waveLenRight, data);
    InsertIntoStream<float>(rFreqRight, data);
    InsertIntoStream<float>(ampLeft, data);
    InsertIntoStream<float>(waveLenLeft, data);
    InsertIntoStream<float>(rFreqLeft, data, true);
    InsertIntoStream<float>(elev, data);
    InsertIntoStream<float>(airDen, data);
    InsertIntoStream<float>(depth, data);
    InsertIntoStream<float>(fluidDen, data);
  }
  catch (StreamException &err)
  {
    std::cerr << "StreamExcetion: " << err.what() << std::endl;
  }
  catch (FormattingError &ferr)
  {
    std::cerr << "Formatting Error: " << ferr.what() << std::endl;
  }

  return data;
}

std::stringstream GetFormattedArcSegmentData
(
  const sf::Vector2f CenterOfArcPoint, 
  sf::Vector2f StartPoint, 
  sf::Vector2f EndPoint, 
  float Radius
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream<float>(CenterOfArcPoint.x, data);
    InsertIntoStream<float>(CenterOfArcPoint.y, data);
    InsertIntoStream<float>(StartPoint.x, data);
    InsertIntoStream<float>(StartPoint.y, data);
    InsertIntoStream<float>(EndPoint.x, data);
    InsertIntoStream<float>(EndPoint.y, data);
    InsertIntoStream<float>(Radius, data);
  }
  catch (EngineRuntimeError& e)
  {
    std::cerr << "Stream error in GetFormattedArcSegmentData" << std::endl;
  }

  return data;
}

std::stringstream GetFormattedBlockMeshData
(
  float Width, 
  float Height, 
  float IAngle, 
  const sf::Vector2f & Position, 
  const sf::Vector2f & Velocity, 
  float Mass, 
  float CoeffOfRest, 
  sf::Color Color
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream(Width, data);
    InsertIntoStream(Height, data);
    InsertIntoStream(IAngle, data);
    InsertIntoStream(Position.x, data);
    InsertIntoStream(Position.y, data);
    InsertIntoStream(Mass, data);
    InsertIntoStream(CoeffOfRest, data);
    InsertIntoStream(Color.r, data);
    InsertIntoStream(Color.g, data);
    InsertIntoStream(Color.b, data);
  }
  catch (EngineRuntimeError& e)
  {
    std::cerr << "Stream error in GetFormattedBlockMeshData" << std::endl;
  }

  return data;
}

std::stringstream GetFormattedElevatorSegmentData
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length, 
  const sf::Vector2f & Velocity, 
  float SMin, 
  float SMax
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream(Position.x, data);
    InsertIntoStream(Position.y, data);
    InsertIntoStream(Length.x, data);
    InsertIntoStream(Length.y, data);
    InsertIntoStream(Velocity.x, data);
    InsertIntoStream(Velocity.y, data);
    InsertIntoStream(SMin, data);
    InsertIntoStream(SMax, data);
  }
  catch (EngineRuntimeError& e)
  {
    std::cerr << "Stream error in GetFormattedElevatorSegmentData" << std::endl;
  }

  return data;
}

std::stringstream GetFormattedSegFipData
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length, 
  float RotateVelocity, 
  float RotateAngle
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream(Position.x, data);
    InsertIntoStream(Position.y, data);
    InsertIntoStream(Length.x, data);
    InsertIntoStream(Length.y, data);
    InsertIntoStream(RotateVelocity, data);
    InsertIntoStream(RotateAngle, data);
  }
  catch (EngineRuntimeError& e)
  {
    std::cerr << "Stream error in GetFormattedSegFipData" << std::endl;
  }

  return data;
}

std::stringstream GetFormattedSegRotateData
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length, 
  float RotateVelocity
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream(Position.x, data);
    InsertIntoStream(Position.y, data);
    InsertIntoStream(Length.x, data);
    InsertIntoStream(Length.y, data);
    InsertIntoStream(RotateVelocity, data);
  }
  catch (EngineRuntimeError& e)
  {
    std::cerr << "Stream error in GetFormattedSegRotateData" << std::endl;
  }

  return data;
}

std::stringstream GetFormattedSegSwingData
(
  const sf::Vector2f & Position, 
  const sf::Vector2f & Length, 
  float RotateVelocity, 
  float Mass
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream(Position.x, data);
    InsertIntoStream(Position.y, data);
    InsertIntoStream(Length.x, data);
    InsertIntoStream(Length.y, data);
    InsertIntoStream(RotateVelocity, data);
    InsertIntoStream(Mass, data);
  }
  catch (EngineRuntimeError& e)
  {
    std::cerr << "Stream error in GetFormattedSegSwingData" << std::endl;
  }

  return data;
}


std::stringstream GetFormattedBallConstructionData
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
  std::stringstream data;

  try
  {
    InsertIntoStream<int>((int)(std::floor(InitialPosition.x)), data);
    InsertIntoStream<int>((int)(std::floor(InitialPosition.y)), data);
    InsertIntoStream<int>((int)(std::floor(InitialVelocity.x)), data);
    InsertIntoStream<int>((int)(std::floor(InitialVelocity.y)), data, true);
    InsertIntoStream<unsigned int>(Radius, data, true);
    InsertIntoStream<float>(Mass, data);
    InsertIntoStream<float>(CoeffecientOfRest, data, true);
    InsertIntoStream<unsigned char>(Color.r, data);
    InsertIntoStream<unsigned char>(Color.g, data);
    InsertIntoStream<unsigned char>(Color.b, data, true);
  }
  catch (StreamException &err)
  {
    std::cerr << "StreamExcetion: " << err.what() << std::endl;
  }
  catch (FormattingError &ferr)
  {
    std::cerr << "Formatting Error: " << ferr.what() << std::endl;
  }

  return data;
}

std::stringstream GetFormattedPolyConstructionData
(
  unsigned int num_sides, 
  float radius, 
  float init_rotation, 
  const sf::Vector2f & InitialPosition, 
  const sf::Vector2f & InitialVelocity, 
  float mass, 
  float CoeffOfRest, 
  const sf::Color & Color
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream<unsigned int>(num_sides, data);
    InsertIntoStream<float>(radius, data);
    InsertIntoStream<float>(init_rotation, data, true);
    InsertIntoStream<int>((int)(std::floor(InitialPosition.x)), data);
    InsertIntoStream<int>((int)(std::floor(InitialPosition.y)), data);
    InsertIntoStream<int>((int)(std::floor(InitialVelocity.x)), data);
    InsertIntoStream<int>((int)(std::floor(InitialVelocity.y)), data, true);
    InsertIntoStream<float>(mass, data);
    InsertIntoStream<float>(CoeffOfRest, data, true);
    InsertIntoStream<unsigned char>(Color.r, data);
    InsertIntoStream<unsigned char>(Color.g, data);
    InsertIntoStream<unsigned char>(Color.b, data, true);
  }
  catch (StreamException &serr)
  {
    std::cerr << "StreamExcetion: " << serr.what() << std::endl;
  }
  catch (FormattingError &ferr)
  {
    std::cerr << "Formatting Error: " << ferr.what() << std::endl;
  }

  return data;
}

std::stringstream GetFormattedExpandPolyConstructionData
(
  unsigned int numSides, 
  float radiusWhenFull, 
  float IAngle,
  const sf::Vector2f & InitialPosition,
  const sf::Vector2f & InitialVelocity,
  float Mass, 
  float CoeffOfRest, 
  float GrowSpeed, 
  sf::Color Color
)
{
  std::stringstream data;
  try
  {
    InsertIntoStream((std::size_t)numSides, data);
    InsertIntoStream(radiusWhenFull, data);
    InsertIntoStream(IAngle, data);
    InsertIntoStream(InitialPosition.x, data); InsertIntoStream(InitialPosition.y, data);
    InsertIntoStream(InitialVelocity.x, data); InsertIntoStream(InitialVelocity.y, data);
    InsertIntoStream(Mass, data);
    InsertIntoStream(CoeffOfRest, data);
    InsertIntoStream(GrowSpeed, data);
    InsertIntoStream(Color.r, data); InsertIntoStream(Color.g, data); InsertIntoStream(Color.b, data);

    return data;

      
  }
  catch (EngineRuntimeError& e)
  {
    throw InitializationException({ ExceptionCause::PhysicsInitError }, EXCEPTION_MESSAGE("Failed to construct expand poly data"));
  }
}

std::stringstream GetFormattedSegmentConstructionData
(
  char type, 
  const sf::Vector2i & TopLeftCorner, 
  const sf::Vector2i & BottomRightCorner, 
  float radius
)
{
  std::stringstream data;

  try
  {
    InsertIntoStream<int>(TopLeftCorner.x, data);
    InsertIntoStream<int>(TopLeftCorner.y, data);
    InsertIntoStream<int>(BottomRightCorner.x, data);
    InsertIntoStream<int>(BottomRightCorner.y, data);
    if (type == 'A')
      InsertIntoStream<float>(radius, data, true);
    else
      InsertIntoStream<char>('\n', data);
  }
  catch (StreamException &serr)
  {
    std::cerr << "StreamExcetion: " << serr.what() << std::endl;
  }
  catch (FormattingError &ferr)
  {
    std::cerr << "Formatting Error: " << ferr.what() << std::endl;
  }

  return data;
}


void UpdatePhysics(std::vector<PhysicsEngineBaseMeshType *> &Meshes, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t Steps)
{

  for (std::size_t _step = 0; _step < Steps; ++_step) {

    for (std::size_t i = 0; i < Meshes.size(); ++i) {
      Meshes[i]->update(gravity);
    }

    //Update segments
    for (auto & segPtr : Segments) {
      segPtr->update();
    }

    //Do collision testing and response
    for (auto & segPtr : Segments) {
      for (auto & meshPtr : Meshes) {
        segPtr->hit(*meshPtr);
      }
    }

    for (std::size_t i = 0; i + 1 < Meshes.size(); ++i) {
      for (std::size_t j = i + 1; j < Meshes.size(); ++j) {
        Meshes[i]->hit(*Meshes[j]);
      }
    }


  } //for _step = 0; _step < Steps;...
}

void UpdatePhysics(std::vector<std::shared_ptr<Collider2D>> Colliders, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t steps)
{
  for (std::size_t _step = 0; _step < steps; ++_step) {

    for (auto & collider : Colliders) {
      if (!collider->IsStatic())
        collider->Update(gravity);
    }

    for (auto & seg : Segments)
      seg->update();

    for (auto & coll : Colliders) {
      for (auto & seg : Segments) {
        auto mesh = coll->GetMesh();
        if (mesh.lock() && seg->hit(*(mesh.lock())))
          coll->HandleCollisionWithSegment(seg);
      }
    }

    //for (auto & seg : Segments) {
    //  for (auto & coll : Colliders) {
    //    auto mesh = coll->GetMesh();
    //    if (mesh.lock() && seg->hit(*mesh.lock())) {
    //      coll->HandleCollisionWithSegment(seg);
    //    }
    //  }
    //}

    for (std::size_t i = 0; i < Colliders.size(); ++i) {
      for (std::size_t j = 0; j < Colliders.size(); ++j) {
        auto m_1 = Colliders[i]->GetMesh().lock();
        auto m_2 = Colliders[j]->GetMesh().lock();

        if (Colliders[i]->HasPhyicalResponse() && Colliders[j]->HasPhyicalResponse()) {
          if (m_1 && m_2 && m_1->hit(*m_2)) {
            Colliders[j]->HandleCollision(Colliders[i]);
            Colliders[i]->HandleCollision(Colliders[j]);
          }
        }

        else {
          if (Colliders[i]->NotifyOnTouch() || Colliders[j]->NotifyOnTouch()) {
            auto pos1 = m_1->pos;
            auto pos2 = m_2->pos;
            if (m_1->hit(*m_2)) {
              Colliders[i]->HandleTouch(Colliders[j]);
              Colliders[j]->HandleTouch(Colliders[i]);

              m_1->setPosition(pos1); //Move them back because they didn't actually want to be moved
              m_2->setPosition(pos2);
            }
          }
        }

        //if (m_1 && m_2 && m_1->hit(*m_2)) {
        //  if (Colliders[i]->IsAwake() && Colliders[j]->IsAwake()) {

        //    Colliders[i]->HandleCollision(Colliders[j]);
        //    Colliders[j]->HandleCollision(Colliders[i]);
        //  }
        //}

      }
    }

  }
}

void UpdatePhysics
(
  std::vector<std::shared_ptr<Occluder2D>> Occluders, 
  std::vector<std::shared_ptr<Collider2D>> Colliders, 
  std::vector<PhysicsEngineSegmentType*> Segments, std::size_t steps
)
{
  UpdatePhysics(Colliders, Segments, steps);
  for (std::size_t _step = 0; _step < steps; ++_step) {

    for (auto & occluder : Occluders)
      occluder->GetMesh().lock()->update(gravity);

    for (auto & seg : Segments) {
      for (auto & occluder : Occluders) {
        auto mesh = occluder->GetMesh().lock();
        if (mesh && seg->hit(*mesh)) {
          //Do something here
        }
      }
    }

    for (std::size_t i = 0; i < Colliders.size(); ++i) {
      if (!Colliders[i]->IsAwake())
        continue;

      for (std::size_t j = 0; j < Occluders.size(); ++j) {
        auto m_1 = Colliders[i]->GetMesh().lock();
        auto m_2 = Occluders[j]->GetMesh().lock();

        if (m_1 && m_2 && m_1->hit(*m_2)) {
            Colliders[i]->HandleCollision(Occluders[j]);
            Occluders[j]->HandleCollision(Colliders[i]);
        }

      }
    }

  }
}

void AssignBoundaries(float WindowHeight, float WindowWidth)
{
  PhysicsEngineBaseMeshType::wdwH = WindowHeight;
  PhysicsEngineBaseMeshType::wdwW = WindowWidth;
  PhysicsEngineBaseMeshType::wdwCf = 0.f;
}

void SetGravity(::vec2d *Gravity)
{
  gravity = *Gravity;
}
