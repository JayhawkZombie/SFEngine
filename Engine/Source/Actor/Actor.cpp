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

#include "Actor\Actor.h"
#include "Physics\Collider.h"

#include <memory>

GenericActor::GenericActor(const std::string &texfile, const std::string &texID)
{

}

void GenericActor::BuildAnimations(const std::string & filename, const std::string & texturefile, GenericActor * Actor)
{
  
}

GenericActor::GenericActor()
{
  try
  {
    ItemID = std::to_string(GenerateID());
    ItemID = "Player" + ItemID;
  }
  catch (std::exception &err)
  {
    std::cerr << "Exception in GenericActor constructor" << std::endl;

    throw err;
  }
}

GenericActor::GenericActor(const GenericActor & Copy)
  : GameObject()
{
}

void GenericActor::AddAnimation(const std::string &ID, std::shared_ptr<Animation> info)
{

}

void GenericActor::SetAnimation(const std::string & ID)
{

}


void GenericActor::Kill()
{

}

void GenericActor::__HandleKeyPress(const sf::Keyboard::Key &key)
{

}

void GenericActor::ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex)
{

}

GenericActor::~GenericActor()
{

}

void GenericActor::SerializeOut(std::ofstream &out)
{

}

void GenericActor::SerializeIn(std::ifstream &in)
{

}

void GenericActor::OnShutDown()
{
	  
}

void GenericActor::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  
}

std::shared_ptr<BaseEngineInterface> GenericActor::Clone() const
{
  auto Actor = std::make_shared<GenericActor>(*this);

  return Actor;
}

void GenericActor::TickUpdate(const double &delta)
{
  
}
