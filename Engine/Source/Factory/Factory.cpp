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

#include "Factory\Factory.h"
#include "Actor\Actor.h"
#include "Actor\Player.h"
#include "Animation\Animation.h"
#include "Level\Level.h"
#include "Tiles\LevelTile.h"
#include "Tiles\TileSheet.h"

#include "json\json.h"

std::shared_ptr<GenericActor> MakeActor(std::string Name)
{
  try
  {
    auto ptr = std::make_shared<GenericActor>();
    ptr->SetID(Name);

    return ptr;
  }
  catch (EngineRuntimeError &err)
  {
    err.AddCause({ ExceptionCause::ConstructionError });
    err.AddMessage(EXCEPTION_MESSAGE("Factory failed to construct GenericActor object"));

    throw;
  }
}

std::shared_ptr<thor::ParticleSystem> MakeParticleSystem(std::string Name)
{
  try
  {
    auto ptr = std::make_shared<thor::ParticleSystem>();
      
    return ptr;
  }
  catch (std::exception &err)
  {
    throw;
  }
}

std::shared_ptr<thor::FrameAnimation> CreateAnimation(std::shared_ptr<LevelObject> Object, std::string Name)
{
  try
  {
    auto Anim = std::make_shared<thor::FrameAnimation>();

    return Anim;
  }
  catch (std::exception &err)
  {
    throw;
  }
}

void AddAnimationFrame(std::shared_ptr<thor::FrameAnimation> Anim, float Duration, int left, int top, int height, int width)
{

}

void AddStaticAnimationFrame(std::shared_ptr<thor::FrameAnimation>, int left, int top, int width, int height)
{

}
