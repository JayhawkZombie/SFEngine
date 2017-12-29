#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "Damage.h"
class Skill
{
public:
  //constructors
  Skill();
  ~Skill();

  //getters
  std::string getName();
  std::string getFilePath();
  std::string getDescription();
  bool getIsPhysical();
  bool getIsMagical();
  bool getCastOnSelf();
  bool getCastOnSingle();
  bool getCastOnEnemy();
  int getMpCost();
  Damage getDamage();
  ///static const int m_size;
  //setters
  void setName(std::string name);
  void setFilePath(std::string filePath);
  void setDescription(std::string description);
  void setIsPhysical(bool isPhysical);
  void setIsMagical(bool isMagical);
  void setCastOnSelf(bool castOnSelf);
  void setCastOnSingle(bool castOnSingle);
  void setCastOnEnemy(bool castOnEnemy);
  void setMpCost(int mpCost);
  void setDamage(Damage damage);

private:
  std::string m_name;
  std::string m_filePath;
  std::string m_description;
  bool m_isPhysical;
  bool m_isMagical;
  bool m_castOnSelf;
  bool m_castOnSingle;
  bool m_castOnEnemy;
  int m_mpCost;
  Damage m_effect;
};

#endif