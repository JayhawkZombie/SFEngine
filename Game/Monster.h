#ifndef MONSTER_H
#define MONSTER_H

#include "BattleActor.h"
#include "ElementsEnum.h"
#include "MonsterType.h"
#include <math.h>


class Monster: public BattleActor
{
public:
	Monster();
	~Monster();

	virtual bool takeDamage(const Damage recieved);
	virtual Damage baseDamage();
	virtual void levelUp();
	virtual void gainExp(int gain);
	
	//getters
	Element getSecondary()const;


	//setters
	void setSecondary(Element Secondary);

private:
	MonsterType m_monsterType;
	Element m_secondary;
	int m_numPhysical;
	int m_numMagical;
};

#endif