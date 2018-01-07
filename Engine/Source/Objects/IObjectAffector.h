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
 *  Base class for affecting game objects (animations, movement, etc)
 **/

#include "Minimal.h"

class GameObject;

class IGameObjectAffector
{
public:

  IGameObjectAffector();
  virtual ~IGameObjectAffector();

  /* Whether the affector has a valid target to change */
  bool HasValidTarget() const;

  /* Change the object that is being affected */
  void SetTarget(GameObject *Target);

  /* Retrieve the object that is being affected */
  GameObject* GetTarget() const;

  float GetScale() const;

  void SetScale(float Scale);

  /* Called whenever the target changes */
  virtual void OnTargetChanged() = 0;

  /* Called whenevr the affector speed scale changes */
  virtual void OnSpeedChanged() = 0;

  /* Serialization */
  template<class Archive>
  void load(Archive & ar)
  {
    ar(m_AffectorScale);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(m_AffectorScale);
  }

protected:

  GameObject * m_TargetObject = nullptr;

  /* The scale to apply to the rate of application (higher = "faster") */
  float m_AffectorScale = 1.f;

};
