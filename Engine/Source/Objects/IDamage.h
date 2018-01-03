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
 *  Damage interface to inflicting damage to objects
 *  
 *  Some basic types of damage are provided - derive from these to 
 *  further customize it or derive from IDamage to create a custom damage type
 **/

#include "Minimal.h"

enum EDamageTypeDescriptions : uint32_t
{
  Piercing = 1,
  AreaOfEffect = 2,
  DamageOverTime = 3,
};

/* Fwds */
class GameObject;

class IDamage
{
public:
  IDamage() = default;
  IDamage(float DamageMagnitude, float DamageFalloff);
  virtual ~IDamage() = default;

  virtual std::string GetDescription() const = 0;

  /* Application of damage to game object
   * A pointer to the object trying to do the damage as well as a pointer
   * to the object it is trying to do damage to is provided
   * */
  virtual void Apply(GameObject *AppyingFrom, GameObject *ApplyingTo);

  /* Serialization */

  template<class Archive>
  void load(Archive & ar)
  {
    ar(Magnitude);
    ar(Falloff);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(Magnitude);
    ar(Falloff);
  }

  float Magnitude = 0.f;
  float Falloff = 0.f;

  /* A set of values describing the type of damage */
  std::vector<EDamageTypeDescriptions> m_DamageDescriptionValues;
};

/*
 *  Contact damage - ideal for when two object hit with a "thud" and do damage
 **/

class IContactDamage : public IDamage
{
public:
  IContactDamage() = default;
  IContactDamage(float DamageMagnitude, float DamageFalloff, float TotalAreaHit);
  virtual ~IContactDamage() override = default;

  virtual std::string GetDescription() const override;

  template<class Archive>
  void load(Archive & ar)
  {
    ar(cereal::base_class<IDamage>(this));

    ar(AreaHit);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(cereal::base_class<IDamage>(this));

    ar(AreaHit);
  }

  float AreaHit = 0.f;

};

/*
 *  Piercing damage - ideal for high-speed projectiles like bullets
 **/

class IPiercingDamage : public IDamage
{
public:
  IPiercingDamage() = default;
  IPiercingDamage(float DamageMagnitude, float DamageFalloff, float Penetration);


  virtual ~IPiercingDamage() override = default;

  virtual std::string GetDescription() const override;

  template<class Archive>
  void load(Archive & ar)
  {
    ar(cereal::base_class<IDamage>(this));

    ar(DamagePenetration);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(cereal::base_class<IDamage>(this));

    ar(DamagePenetration);
  }

  /* How far this damage will penetrate */
  float DamagePenetration = 1.f;

};

struct AreaOfEffectDamageAreaRectangular
{
  sf::Vector2f AreaTopLeft;
  sf::Vector2f AreaSize;

  template<class Archive>
  void load(Archive & ar)
  {
    ar(AreaTopLeft, AreaSize);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(AreaTopLeft, AreaSize);
  }

};

struct AreaOfEffectDamageAreaCircular
{
  sf::Vector2f AreaCenter;
  float AreaRadius;

  template<class Archive>
  void load(Archive & ar)
  {
    ar(AreaCenter);
    ar(AreaRadius);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(AreaCenter);
    ar(AreaRadius);
  }

};

enum EAreaOfEffectDamageAreaType
{
  Rectangular,
  Circular
};

struct AreaOfEffectDamageAreaDescription
{
  AreaOfEffectDamageAreaDescription() : RegionCirc{ } {}
  EAreaOfEffectDamageAreaType AreaType = EAreaOfEffectDamageAreaType::Circular;

  union
  {
    AreaOfEffectDamageAreaRectangular RegionRect;
    AreaOfEffectDamageAreaCircular    RegionCirc;
  };

  template<class Archive>
  void load(Archive & ar)
  {
    ar(AreaType);

    switch (AreaType)
    {
      case EAreaOfEffectDamageAreaType::Circular:
      {
        ar(RegionCirc);
        break;
      }

      case EAreaOfEffectDamageAreaType::Rectangular:
      {
        ar(RegionRect);
        break;
      }
    }
  } //load

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(AreaType);

    switch (AreaType)
    {
      case EAreaOfEffectDamageAreaType::Circular:
      {
        ar(RegionCirc);
        break;
      }

      case EAreaOfEffectDamageAreaType::Rectangular:
      {
        ar(RegionRect);
        break;
      }
    }
  } // save

};

/*
 *  Area of effect damage - ideal for elemental and magical damage
 **/

class IAreaOfEffectDamage : public IDamage
{
public:
  IAreaOfEffectDamage(float DamageMagnitude, float DamageFalloff, const AreaOfEffectDamageAreaDescription &AreaDescription);
  virtual ~IAreaOfEffectDamage() override = default;

  virtual std::string GetDescription() const override;

  template<class Archive>
  void load(Archive & ar)
  {
    ar(cereal::base_class<IDamage>(this));

    ar(DamageAreaDescription);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(cereal::base_class<IDamage>(this));

    ar(DamageAreaDescription);
  }

  AreaOfEffectDamageAreaDescription DamageAreaDescription;

};
