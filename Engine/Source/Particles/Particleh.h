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

#include "Minimal.h"

struct Particle
{
  sf::Color Color = sf::Color::White;
  sf::Vector2f Position = sf::Vector2f(0.f, 0.f);
  sf::Vector2f Velocity = sf::Vector2f(0.f, 0.f);
  
  float Radius = 0.f;
  double Lifetime = 0.0;
  double TimeSinceSpawned = 0.0;

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(Color);
    ar(Position, Velocity);
    ar(Radius);
    ar(Lifetime);
    ar(TimeSinceSpawned);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(Color);
    ar(Position, Velocity);
    ar(Radius);
    ar(Lifetime);
    ar(TimeSinceSpawned);
  }

};
