//Basically passing arrays is frustrating in C++ so Damage is a wrapper for an int array
//length 30
#ifndef DAMAGE_H
#define DAMAGE_H
#include <iostream>
#include <map>
#include "ElementsEnum.h"
class Damage
{
public:
  Damage();
  Damage(Damage inflicted, Damage defense);
  //Damage(Damage inflicted, Damage defense, Element primary);
  //Damage(Damage inflicted, Damage defense, Element primary, Element secondary);
  ~Damage();
  int content[31];//feeling risky, making public to save time
  static int size;
  void setValue(int index, int value);
  static std::map<int, std::string> DamageTypesByIndex();
};

#endif
