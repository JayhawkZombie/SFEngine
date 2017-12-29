#include "SkillSet.h"



SkillSet::SkillSet()
{
  for (int i = 0; i < sizeof(skillArray); i++)
  {
    skillArray[i] = false;
  }
}


SkillSet::~SkillSet()
{
}

void SkillSet::learnSkill(int index)
{
  if (index > sizeof(skillArray)||index<0)
  {
    return;//ignore case-outside bounds
  }
  skillArray[index] = true;
}

bool SkillSet::knowSkill(int index)
{
  if (index > sizeof(skillArray)|| index<0)
  {
	  return false;//ignore case-outside bounds
  }
  return skillArray[index];
}