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

#include "Level\LevelObject.h"

namespace Engine
{

  class StaticLevelObject : public LevelObject
  {
  public:


  protected:

  };

  class RepeatedStaticObject : public LevelObject
  {
  public:
    RepeatedStaticObject(std::shared_ptr<LevelObject> ToRepeat, unsigned int NumRepetitions,
                         const std::vector<sf::Vector2f> &Positions);
    RepeatedStaticObject(const RepeatedStaticObject &) = delete;
    ~RepeatedStaticObject();

    void TickUpdate(const double &delta)                     override final;
    void Render(std::shared_ptr<sf::RenderTarget> Target)    override final;
    void ScriptInit()                                        override final;
    void PhysicsUpdate()                                     override final;
    void OnShutDown()                                        override final;
    void SerializeOut(std::ofstream &out)                    override final;
    void SerializeIn(std::ifstream &in)                      override final;
    void SetPosition(const sf::Vector2f &pos)                override final;
    void SetSize(const sf::Vector2f &size)                   override final;
    void SetTexture(std::shared_ptr<sf::Texture> mytexture)  override final;
    void SetTextureRect(sf::IntRect myRect)                  override final;

    static void BindScriptMethods(chaiscript::ModulePtr module);
  protected:

    std::shared_ptr<LevelObject> m_RepeatedObject;
    sf::VertexArray m_RepeatedVertices;
    std::shared_ptr<sf::Texture> m_RepeatedTexture;
  };

}
