#ifndef SKILLSET_H
#define SKILLSET_H

#include "Skill.h"
class SkillSet
{
public:
  SkillSet();
  ~SkillSet();
  void learnSkill(int index);
  bool knowSkill(int index);
private:
  bool skillArray[12];//TODO - need to update when new skills are introduced

};


#endif