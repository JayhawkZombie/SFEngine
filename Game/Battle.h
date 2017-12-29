
#ifndef BATTLE_H
#define BATTLE_H

#include <time.h>
#include <stdlib.h>
#include "BattleActor.h"
#include "Party.h"
#include <ctime>
#include <cmath>//abs

class Battle
{
public:
	Battle(Party allies, Party enemies, bool canEscape);
	~Battle();

	int run();
	int alliesTurn();//untested
	int enemiesTurn();//unfinished
	BattleActor* selectTarget(bool whichSide, bool targetsEnemy);//allies is if the user is from the allies, bool is i, unfinished
	BattleActor* selectCurrent(bool isAlly);
	void physicalAttack();//unfinished
	void magicalAttack();//unfinished
	void itemAttack();//unfinished
	void printActorInfo(BattleActor* ba);
	void printPartyInfo(Party p);
	int isBattleOver();
	void victory();//unfinished
	int runAway();
	
private:
	Party m_allies;
	Party m_enemies;
	bool m_canEscape;
	int lastEnemyAttackIndex;
	int lastAllyAttackIndex;

};

#endif
