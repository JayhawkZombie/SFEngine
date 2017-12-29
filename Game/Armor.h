#ifndef ARMOR_H
#define ARMOR_H

#include "Damage.h"
#include "RPGItem.h"
#include <iostream>
#include <fstream>

class Armor : public RPGItem
{
public:
  Armor();
  ~Armor();
  //getters
  Damage getDefense();
  int getType();
  static void makeGenericList();
  //setters
  void setDefense(Damage defense);
  void setType(int type);
  void setRequiredLevel(int requredLevel);
  static std::map<int, std::map< int, float>> guideLines();
  static std::map<int, int> baseDamageReductionByTeir();
  static std::map<int, std::string> ArmorTypeNames();
  static std::map<int, std::map<int, std::string>> ArmorDescriptions();
  static std::map<int, std::string> genericTextureLocations();
  int getRequiredLevel();

private:
  Damage m_defense;
  int m_type;
  int m_requiredLevel;
};

#endif