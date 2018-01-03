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

/*
 *  Interface for automatic movement along predefined paths
 **/

#include "IObjectAffector.h"

class GameObject;

class IMovementPath : public IGameObjectAffector
{
public:
  IMovementPath();
  virtual ~IMovementPath() override;

  virtual void OnTargetChanged() override;
  virtual void OnSpeedChanged() override;

  virtual void OnImpeded(GameObject *ImpedingObject);

  template<class Archive>
  void load(Archive & ar)
  {
    ar(cereal::base_class<IGameObjectAffector>(this));
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(cereal::base_class<IGameObjectAffector>(this));
  }

protected:

  sf::Vector2f m_StartPosition = sf::Vector2f(0.f, 0.f);
  sf::Vector2f m_EndPosition = sf::Vector2f(0.f, 0.f);
  
  /* How quickly to traverse over the path segment */
  float m_InitialSpeed  = 1.f;

  /* Whether or not the path can be impeded 
   * 
   * If the path is impeded, the object will simply
   * be unable to move
   * 
   * If the path cannot be impeded, how the object
   * deals with collisions is up to the programmer
   * */
  bool m_CanBeImpeded = true;

  IMovementPath *m_PreviousPathSegment = nullptr;
  IMovementPath *m_NextPathSegment = nullptr;

};
