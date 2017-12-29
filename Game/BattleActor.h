#ifndef BATTLEACTOR_H
#define BATTLEACTOR_H

#include "ElementsEnum.h"
#include "RPGActor.h"
#include "Damage.h"
#include "Skill.h"
#include "SkillSet.h"
#include <map>


class BattleActor: public RPGActor
{
public:
  BattleActor();
  ~BattleActor();
  //functions
  virtual bool takeDamage(const Damage recieved) = 0;
  virtual Damage baseDamage() = 0;
  virtual void levelUp() = 0;
  virtual void gainExp(int gain) = 0;
  virtual bool isAlive() const;
  std::map<int, int> ElementDominator();//returns the element dominated by the index
  std::map<int, int> ElementDominated();//returns the element that dominates the index

  

  //getters
  Element getPrimary()const;
  Damage getThorns()const;
  int getHpCur()const;
  int getHpMax()const;
  int getMpCur()const;
  int getMpMax()const;
  int getMpRegen()const;
  SkillSet getSkillSet()const;
  int getLevel()const;
  int getExp()const;

  //setters
  void setPrimary(Element primary);
  void setThorns(Damage thorns);
  void setHpCur(int hpCur);
  void setHpMax(int hpMax);
  void setMpCur(int mpCur);
  void setMpMax(int mpMax);
  void setMpRegen(int mpRegen);
  void setLevel(int level);
  void setExp(int exp);



private:
  Element m_primary;
  Damage m_thorns;
  int m_hpCur;
  int m_hpMax;
  int m_mpCur;
  int m_mpMax;
  int m_mpRegen;
  SkillSet m_skillSet;
  int m_level;
  int m_exp;
};

#endif