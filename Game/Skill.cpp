#include "Skill.h"



Skill::Skill()
{
  m_name = "";
  m_filePath = "";
  m_description = "";
  m_isPhysical = false;
  m_isMagical = false;
  m_castOnSelf = false;
  m_castOnSingle = false;
  m_castOnEnemy = false;
  m_mpCost = 0;
  m_effect = Damage();
}


Skill::~Skill()
{
}

std::string Skill::getName()
{
  return m_name;
}
std::string Skill::getFilePath()
{
  return m_filePath;
}
std::string Skill::getDescription()
{
  return m_description;
}

bool Skill::getIsPhysical()
{
  return m_isPhysical;
}
bool Skill::getIsMagical()
{
  return m_isMagical;
}
bool Skill::getCastOnSelf()
{
  return m_castOnSelf;
}
bool Skill::getCastOnSingle()
{
  return m_castOnSingle;
}
bool Skill::getCastOnEnemy()
{
  return m_castOnEnemy;
}
int Skill::getMpCost()
{
  return m_mpCost;
}
Damage Skill::getDamage()
{
  return m_effect;
}
//int Skill::getSize()//returns how many skills there are for use as the parameter of SkillSet(s)
//{
 // return m_size;
//}


//setters
void Skill::setName(std::string name)
{
  m_name = name;
}
void Skill::setFilePath(std::string filePath)
{
  m_filePath = filePath;
}
void Skill::setDescription(std::string description)
{
  m_description = description;
}
void Skill::setIsPhysical(bool isPhysical)
{
  m_isPhysical = isPhysical;
}
void Skill::setIsMagical(bool isMagical)
{
  m_isMagical = isMagical;
}
void Skill::setCastOnSelf(bool castOnSelf)
{
  m_castOnSelf = castOnSelf;
}
void Skill::setCastOnSingle(bool castOnSingle)
{
  m_castOnSingle = castOnSingle;
}
void Skill::setCastOnEnemy(bool castOnEnemy)
{
  m_castOnEnemy = castOnEnemy;
}
void Skill::setMpCost(int mpCost)
{
  m_mpCost = mpCost;
}
void Skill::setDamage(Damage newDamage)
{
  m_effect =  newDamage;
}