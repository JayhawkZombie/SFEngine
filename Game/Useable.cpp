#include "Useable.h"



Useable::Useable()
{
  for (int i = 0; i < Damage::size; i++)
  {
    m_damage.content[i] = 0;
  }
}


Useable::~Useable()
{
}

Damage Useable::getDamage()
{
  return m_damage;
}

void Useable::setDamage(Damage newDamage)
{
  m_damage = newDamage;
}