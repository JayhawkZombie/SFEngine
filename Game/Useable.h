#ifndef USEABLE_H
#define USEABLE_H
#include "RPGItem.h"
#include "Damage.h"
class Useable : public RPGItem
{
public:
  Useable();
  ~Useable();
  //getters
  Damage getDamage();
  void setDamage(Damage newDamage);

private:
  Damage m_damage;
};

#endif