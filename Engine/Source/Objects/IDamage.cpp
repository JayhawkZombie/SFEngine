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

#include "Engine/stdafx.h"

#include "IDamage.h"

#include <cereal/archives/portable_binary.hpp>

/*
 *  Base damage interface
 **/

IDamage::IDamage(float DamageMagnitude, float DamageFalloff) 
  : Magnitude(DamageMagnitude), Falloff(DamageFalloff)
{

}

std::string IDamage::GetDescription() const
{
  return "UnknownDamageType";
}

void IDamage::Apply(GameObject *AppyingFrom, GameObject *ApplyingTo)
{
  /* By default, damage does nothing */
}

/*
 *  Piercing damage
 **/

IPiercingDamage::IPiercingDamage(float DamageMagnitude, float DamageFalloff, float Penetration) 
  : IDamage(DamageMagnitude, DamageFalloff), DamagePenetration(Penetration)
{
  m_DamageDescriptionValues.push_back(EDamageTypeDescriptions::Piercing);
}

std::string IPiercingDamage::GetDescription() const
{
  return "Piercing";
}

/*
 *  Area of effect damage
 **/

IAreaOfEffectDamage::IAreaOfEffectDamage(float DamageMagnitude, float DamageFalloff, const AreaOfEffectDamageAreaDescription &AreaDescription) 
  : IDamage(DamageMagnitude, DamageFalloff), DamageAreaDescription(AreaDescription)
{

}

std::string IAreaOfEffectDamage::GetDescription() const
{
  return "AreaOfEffect";
}

IContactDamage::IContactDamage(float DamageMagnitude, float DamageFalloff, float TotalAreaHit)
  : IDamage(DamageMagnitude, DamageFalloff), AreaHit(TotalAreaHit)
{

}

std::string IContactDamage::GetDescription() const
{
  return "Contact";
}

CEREAL_REGISTER_TYPE(IContactDamage);
