#include "Party.h"

Party::Party()
{
	fighters = new BattleActor*[4];
	fighters[0] = NULL;
	fighters[1] = NULL;
	fighters[2] = NULL;
	fighters[3] = NULL;
	myInventory = new Inventory();
}

Party::~Party()
{
	delete fighters;
	delete myInventory;
}

bool Party::assignFighter(int index, BattleActor* fighter)
{
	if (index < 0 || index>3)//reject the assignment if the index is invalid
	{
		return false;
	}
	if (fighters[index] != NULL)//reject the assignment if there is already a fighter there
	{
		return false;
	}
	fighters[index] = fighter; //assign
	return true;
}

BattleActor* Party::removeFighter(int index)
{
	if (index < 0 || index > 3)//reject the removal if index is invalid
	{
		return NULL;
	}
	return fighters[index];
}

BattleActor* Party::getActor(int index)
{
	if (index < 0||index > 3)
	{
		return nullptr;
	}
	else
	{
		return fighters[index];
	}

}

float Party::levelAverage()
{
	int size = 0;
	int total = 0;
	//if(!(fighters[0] && fighters[1] && fighters[2] && fighters[3]))
	if (fighters[0])
	{
		total += fighters[0]->getLevel();
		size++;
	}
	if (fighters[1])
	{
		total += fighters[1]->getLevel();
		size++;
	}
	if (fighters[2])
	{
		total += fighters[2]->getLevel();
	}
	if (fighters[3])
	{
		total += fighters[3]->getLevel();
	}
	if (total == 0 ||size ==0)
	{
		return 0;
	}
	else
	{
		return(total / size);
	}
}

bool Party::hasLost()
{
	for(int i = 0; i < 4; i++)
	{
		if (fighters[i] != NULL)//if there is a fighter in i
		{
			if (fighters[i]->isAlive())//if he is alive, we haven't lost
			{
				return false;
			}
		}
	}//if none of them are alive, we've lost
	return true;
}