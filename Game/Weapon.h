#ifndef WEAPON_H
#define WEAPON_H
#include "RPGItem.h"
#include "Damage.h"
#include <iostream>
#include <fstream>
#include <map>
class Weapon : public RPGItem
{
public:
  Weapon();
  ~Weapon();
  
  //getters and setters
  Damage getAddedDamage();
  bool getRightHand();
  bool getLeftHand();
  void setAddedDamage(Damage addedDamage);
  void setRightHand(bool rightHand);
  void setLeftHand(bool leftHand);
  void setNumHands(int hands);
  void setRequiredLevel(int level);
  int getNumHands();
  int getRequiredLevel();
  static void makeGenericWeaponList();
  static std::map<int, std::string> WeaponTypeNames();
  static std::map<int, std::map<int, float>> WeaponGuideLines();
  static std::map<int, int> BaseDamageByTier();
  static std::map<int, std::map<int, std::string>> WeaponDescriptions();
  static std::map<int, std::string> WeaponTextureLocations();


private:
  Damage m_addedDamage;
  bool m_rightHand;
  bool m_leftHand;
  int m_numHands;
  int m_requiredLevel;
};

#endif;