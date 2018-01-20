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

#include <Box2D/Box2D.h>

namespace cereal
{

  template<class Archive>
  void save(Archive & ar, const b2Vec2 &vec)
  {
    ar(vec.x, vec.y);
  }

  template<class Archive>
  void save(Archive & ar, const b2Vec3 &vec)
  {
    ar(vec.x, vec.y, vec.z);
  }

  template<class Archive>
  void save(Archive & ar, const b2Mat22 &mat)
  {
    ar(mat.ex, mat.ey);
  }

  template<class Archive>
  void save(Archive & ar, const b2Mat33 &mat)
  {
    ar(mat.ex, mat.ey, mat.ez);
  }

  template<class Archive>
  void save(Archive & ar, const b2Rot &rot)
  {
    ar(rot.s, rot.c);
  }

  template<class Archive>
  void save(Archive & ar, const b2Transform &trans)
  {
    ar(trans.p, trans.q);
  }

  template<class Archive>
  void save(Archive & ar, const b2Sweep &sweep)
  {
    ar(sweep.localCenter, sweep.c0, sweep.c, sweep.a0, sweep.a, sweep.alpha0);
  }

  /* struct defs */

  template<class Archive>
  void save(Archive & ar, const b2BodyDef &def)
  {
    ar(def.type, def.position, def.angle, def.linearVelocity, def.angularVelocity, linearDamping,
      def.allowSleep, def.awake, def.fixedRotation, def.bullet, def.active, def.gravityScale);
  }

  template<class Archive>
  void save(Archive & ar, const b2Filter &filt)
  {
    ar(filt.categoryBits, filt.maskBits, filt.groupIndex);
  }

  template<class Archive>
  void save(Archive & ar, const b2FixtureDef &def)
  {
    ar(def.friction, def.restitution, def.density, def.isSensor, def.filter);
  }



}
