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

#include "Objects/GameObject.h"

class GenericActor : public GameObject
{
public:
  friend class Level;
  TYPEDEF_PARENT_CLASS(GameObject);

  static void BuildAnimations(const std::string &filename, const std::string &texturefile, GenericActor *Actor);

  GenericActor();
  GenericActor(const GenericActor &Copy);
  GenericActor(const std::string &texfile, const std::string &texID);
  virtual ~GenericActor();

  //Forbid implicit copy assignment definitions
  //We [MUST] use a clone method
  GenericActor& operator=(const GenericActor &) = delete;
  virtual std::shared_ptr<BaseEngineInterface> Clone() const override;

  virtual void TickUpdate(const double &delta) override;
  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
  virtual void OnShutDown() override;
  virtual void SerializeOut(std::ofstream &out) override;
  virtual void SerializeIn(std::ifstream &in) override;

//  virtual void SetTexture(const std::string &texfile, const std::string &texID);
  virtual void AddAnimation(const std::string &ID, std::shared_ptr<Animation> info);
  virtual void SetAnimation(const std::string &ID);

  //Internal methods, each has a corresponding script that will be called
  void Spawn(const sf::Vector2f &Position);
  void Respawn(const sf::Vector2f &Position);
  void Kill() override;

  virtual std::string GetClass() const override {
    return "GenericActor";
  }

protected:
  void __HandleKeyPress(const sf::Keyboard::Key &key);
  bool DrawCollisionMesh = true;

  Animation *CurrentAnimation = nullptr;
  float WindowWidth;
  float WindowHeight;

  sf::RectangleShape ActorRectangle;
    
  void ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex);
};
