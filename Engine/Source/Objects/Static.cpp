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

#include "Objects\Static.h"
#include "Physics\Collider.h"

#include <cassert>

namespace Engine
{
  RepeatedStaticObject::RepeatedStaticObject(std::shared_ptr<LevelObject> ToRepeat, unsigned int NumRepetitions,
                                             const std::vector<sf::Vector2f> &Positions)
    : 
    m_RepeatedObject(ToRepeat),
    m_RepeatedTexture(ToRepeat->GetTexture()),
    LevelObject()
  {
    assert(Positions.size() == NumRepetitions);

    sf::Vector2f __Size = ToRepeat->GetSize();
    sf::IntRect __Rect = ToRepeat->GetTextureRect();

    std::vector<std::shared_ptr<Collider2D>> __Colliders = ToRepeat->GetColliders();

    m_RepeatedVertices.resize(4 * NumRepetitions);

    for (std::size_t i = 0; i < Positions.size(); ++i) {
      m_RepeatedVertices[4 * i + 0].position =   Positions[i];
      m_RepeatedVertices[4 * i + 1].position = { Positions[i].x + __Size.x, Positions[i].y };
      m_RepeatedVertices[4 * i + 2].position = { Positions[i].x + __Size.x, Positions[i].y + __Size.y };
      m_RepeatedVertices[4 * i + 3].position = { Positions[i].x,            Positions[i].y + __Size.y };

      m_RepeatedVertices[4 * i + 0].texCoords = { __TO_FLOAT__(__Rect.left),                __TO_FLOAT__(__Rect.top) };
      m_RepeatedVertices[4 * i + 1].texCoords = { __TO_FLOAT__(__Rect.left + __Rect.width), __TO_FLOAT__(__Rect.top) };
      m_RepeatedVertices[4 * i + 2].texCoords = { __TO_FLOAT__(__Rect.left + __Rect.width), __TO_FLOAT__(__Rect.top + __Rect.height) };
      m_RepeatedVertices[4 * i + 3].texCoords = { __TO_FLOAT__(__Rect.left),                __TO_FLOAT__(__Rect.top + __Rect.height) };
    }

    //Repeat the colliders for every repeated object (will optimize later)
    m_Colliders.resize(NumRepetitions * __Colliders.size());
    int CollidersPerRepeat = __Colliders.size();

    sf::Vector2f _delta = { 0, 0 };
    for (int i = 0; i < NumRepetitions; ++i) {
      for (int j = 0; j < CollidersPerRepeat; ++j) {
        //Get the position of the collider to be copied, copy it, and move the copy
        _delta = Positions[i] - __Colliders[j]->GetPosition();
        m_Colliders[i * CollidersPerRepeat + j] = __Colliders[j]->Clone();
        m_Colliders[i * CollidersPerRepeat + j]->Move(_delta);
      } //for j = 0 -> CollidersPerRepeat

    } //for i = 0 -> NumRepetitions
  }

  RepeatedStaticObject::~RepeatedStaticObject()
  {
  }

  void RepeatedStaticObject::TickUpdate(const double & delta)
  {
  }

  void RepeatedStaticObject::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
  }

  void RepeatedStaticObject::ScriptInit()
  {
  }

  void RepeatedStaticObject::PhysicsUpdate()
  {
  }

  void RepeatedStaticObject::OnShutDown()
  {
  }

  void RepeatedStaticObject::SerializeOut(std::ofstream & out)
  {
  }

  void RepeatedStaticObject::SerializeIn(std::ifstream & in)
  {
  }

  void RepeatedStaticObject::SetPosition(const sf::Vector2f & pos)
  {
  }

  void RepeatedStaticObject::SetSize(const sf::Vector2f & size)
  {
  }

  void RepeatedStaticObject::SetTexture(std::shared_ptr<sf::Texture> mytexture)
  {
  }

  void RepeatedStaticObject::SetTextureRect(sf::IntRect myRect)
  {
  }

}
