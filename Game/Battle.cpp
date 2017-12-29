

#include "Battle.h"



Battle::Battle(Party allies, Party enemies, bool canEscape)
{
	m_allies = allies;
	m_enemies = enemies;
	m_canEscape = canEscape;
	lastAllyAttackIndex = 3;
	lastEnemyAttackIndex = 3;
}


Battle::~Battle()
{
}

/*This function is in charge of determining who goes first, whose turn it is, and returning values and
directing the flow towards the different ending conditions (victory, defeat, run)*/

int Battle::run()
{
	int leaveCondition;//-1 means keep going, 0 means failure, 1 success, 2 ran away
	srand(time(NULL));
	int r = rand();
	if (r % 2 == 0)
	{
		leaveCondition = alliesTurn();
		if (leaveCondition == 0)
		{
			return 0;
		}
		else if (leaveCondition == 1)
		{
			victory();
			return 1;
		}
		else if (leaveCondition == 2)
		{
			//runAway();
			return 2;
		}
	}
	while (!isBattleOver())
	{
		leaveCondition = enemiesTurn();
		if (leaveCondition == 0)
		{
			return 0;
		}
		else if (leaveCondition == 1)
		{
			victory();
			return 1;
		}
		else if (leaveCondition == 2)
		{
			//runAway();
			return 2;
		}

		leaveCondition = alliesTurn();
		if (leaveCondition == 0)
		{
			return 0;
		}
		else if (leaveCondition == 1)
		{
			victory();
			return 1;
		}
		else if (leaveCondition == 2)
		{
			//runAway();
			return 2;
		}
	}
}


/*
* Return Values Breakdown for alliesTurn()
* -1 no result, do nothing
* 0 failure, go to loading screen
* 1 success, go back to map, victory screen?
* 2 ran away, go back to map, no victory screen
*/

int Battle::alliesTurn()
{
	int check = isBattleOver();//checks to see if the battle is over
	if (check != -1)//if the check doesnt say continue, return the battleOver value
	{//makes sure that there is at least one ally left alive
		return check;
	}
	BattleActor* Current= selectCurrent(true);//this is the current battleActor
	if (!Current)
	{
		std::cout << "Allies wait for a turn after all of them attack\n";
		return -1;
	}
	else
	{
		std::cout << "Its " << Current->getName() << "'s turn to attack\n";
	}

	int choice=-1;//holds the choice the user makes
	bool decided = false;//makes sure the user has made a decision, controls the loop
	while (!decided)
	{
		//print options
		std::cout << "1) Attack\n";
		std::cout << "2) Use Skill\n";
		std::cout << "3) Use Item\n";
		std::cout << "4) Wait\n";
		if (m_canEscape)
		{
			std::cout << "5) Run\n";
		}
		try
		{
			std::cin >> choice;
			if (m_canEscape)
			{
				if (choice < 1 || choice>5)
				{
					std::cout << "Please input a number between 1 and 5";
					choice = -1;
				}
			}
			else
			{
				if (choice < 1 || choice > 4)
				{
					std::cout << "Please input a number between 1 and 4";
					choice = -1;
				}
			}
		}
		catch (int e)
		{
			if (m_canEscape)
			{
				std::cout << "Please input a number between 1 and 4";
			}
			else
			{
				std::cout << "Please input a number between 1 and 3";
			}
		}
		if (choice == 1)
		{
			BattleActor* victim =	selectTarget(true,true);
			if (victim->takeDamage(Current->baseDamage()))
			{
				return isBattleOver();
			}
			else
			{
				return -1;
			}
		}
		else if (choice == 2)//Logic for use skill here
		{
			return -1;
		}
		else if (choice == 3)//logic for use item here
		{
			return -1;
		}
		else if (choice == 4)//logic for wait here
		{
			return -1;
		}
		else if (choice == 5)//logic for run here
		{
			return runAway();
		}
	}
}

int Battle::enemiesTurn()
{
	BattleActor* current = selectCurrent(false);

	srand(time(NULL));
	int r = rand() % 100;
	if (r < 50)//bogo
	{

	}
	else//leastHp
	{

	}

	return isBattleOver();
}

BattleActor* Battle::selectTarget(bool whichSide, bool targetsEnemy)
{
	return nullptr;
}

BattleActor* Battle::selectCurrent(bool isAlly)
{
	BattleActor* result;

	if (isAlly)
	{
		if (lastAllyAttackIndex >= 4)//if lastAllyAttackIndex ==4, its the wait turn, also handles case
		{//where index goes beyond bounds.
			lastAllyAttackIndex = 0;
			return nullptr;
		}
		else if (lastAllyAttackIndex <= 0)
		{
			lastAllyAttackIndex = 0;
			for (int i = 0; i < 4; i++)
			{
				result = m_allies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastAllyAttackIndex++;
						return result;
					}
				}
			}
			lastAllyAttackIndex = 0;
			return nullptr;
		}
		else if (lastAllyAttackIndex == 1)
		{
			for (int i = 1; i < 4; i++)
			{
				result = m_allies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastAllyAttackIndex++;
						return result;
					}
				}
			}
			lastAllyAttackIndex = 0;
			return nullptr;
			/*//this code may be useful if I decide to implement battle in a different way
			result = m_allies.getActor(0);
			if (result)
			{
				if (result->isAlive())
				{
					lastAllyAttackIndex++;
					return result;
				}
			}*/
		}
		else if (lastAllyAttackIndex == 2)
		{
			for (int i = 2; i < 4; i++)
			{
				result = m_allies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastAllyAttackIndex++;
						return result;
					}
				}
			}
			lastAllyAttackIndex = 0;
			return nullptr;
			/*//may need this later
			for (int i = 0; i < 2; i++)
			{
				result = m_allies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastAllyAttackIndex++;
						return result;
					}
				}
			}*/
		}
		else if (lastAllyAttackIndex == 3)
		{
			result = m_allies.getActor(3);
			if (result)
			{
				if (result->isAlive())
				{
					lastAllyAttackIndex++;
					return result;
				}
			}
			/*
			for (int i = 0; i < 3; i++)
			{
				result = m_allies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastAllyAttackIndex++;
						return result;
					}
				}
			}*/
			lastAllyAttackIndex = 0;
			return nullptr;
		}
		else//should be redundant
		{
			lastAllyAttackIndex = 0;
			return nullptr;
		}
	}
	else
	{
		if (lastEnemyAttackIndex >= 4)//if lastAllyAttackIndex ==4, its the wait turn, also handles case
		{//where index goes beyond bounds.
			lastEnemyAttackIndex = 0;
			return nullptr;
		}
		else if (lastEnemyAttackIndex <= 0)
		{
			lastEnemyAttackIndex = 0;
			for (int i = 0; i < 4; i++)
			{
				result = m_enemies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastEnemyAttackIndex++;
						return result;
					}
				}
			}
			lastEnemyAttackIndex = 0;
			return nullptr;
		}
		else if (lastEnemyAttackIndex == 1)
		{
			for (int i = 1; i < 4; i++)
			{
				result = m_enemies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastEnemyAttackIndex++;
						return result;
					}
				}
			}
			lastEnemyAttackIndex = 0;
			return nullptr;
			/*//this code may be useful if I decide to implement battle in a different way
			result = m_allies.getActor(0);
			if (result)
			{
			if (result->isAlive())
			{
			lastAllyAttackIndex++;
			return result;
			}
			}*/
		}
		else if (lastEnemyAttackIndex == 2)
		{
			for (int i = 2; i < 4; i++)
			{
				result = m_enemies.getActor(i);
				if (result)
				{
					if (result->isAlive())
					{
						lastEnemyAttackIndex++;
						return result;
					}
				}
			}
			lastEnemyAttackIndex = 0;
			return nullptr;
			/*//may need this later
			for (int i = 0; i < 2; i++)
			{
			result = m_allies.getActor(i);
			if (result)
			{
			if (result->isAlive())
			{
			lastAllyAttackIndex++;
			return result;
			}
			}
			}*/
		}
		else if (lastEnemyAttackIndex == 3)
		{
			result = m_enemies.getActor(3);
			if (result)
			{
				if (result->isAlive())
				{
					lastEnemyAttackIndex++;
					return result;
				}
			}
			/*
			for (int i = 0; i < 3; i++)
			{
			result = m_allies.getActor(i);
			if (result)
			{
			if (result->isAlive())
			{
			lastAllyAttackIndex++;
			return result;
			}
			}
			}*/
			lastEnemyAttackIndex = 0;
			return nullptr;
		}
		else
		{
			lastEnemyAttackIndex = 0;
			return nullptr;
		}
	}
}

void Battle::physicalAttack()
{
	//will hold the animations/engine-specific stuff necessary for physical attacks
}

void Battle::magicalAttack()
{
	//will hold the animations/engine-specific stuff necessary for magical attacks
}

void Battle::itemAttack()
{

}

int Battle::runAway()
{
	float alliesLevelAverage = m_allies.levelAverage();
	float enemiesLevelAverage = m_enemies.levelAverage();
	float difference = abs(alliesLevelAverage - enemiesLevelAverage);
	float probability = 0.0;
	if (difference <= 5)
	{
		probability = .4 + .1*difference;
	}
	else
	{
		probability = .9;
	}
	srand(time(NULL));
	int r = rand() % 100;
	if (r > probability * 100)
	{
		return -1;
	}
	else
	{
		return 2;
	}
}

void Battle::printActorInfo(BattleActor* ba)
{
	std::cout << "Name:        " << ba->getName() << "\n";
	std::cout << "HP:          " << ba->getHpCur() << "/" << ba->getHpMax() << "\n";
	std::cout << "MP:          " << ba->getMpCur() << "/" << ba->getMpMax() << "\n";
	//TODO: add status stuff
}

void Battle::printPartyInfo(Party p)
{
	if (p.getActor(0))
	{
		printActorInfo(p.getActor(0));
	}
	if (p.getActor(1))
	{
		printActorInfo(p.getActor(1));
	}
	if (p.getActor(2))
	{
		printActorInfo(p.getActor(2));
	}
	if (p.getActor(3))
	{
		printActorInfo(p.getActor(3));
	}
}

int Battle::isBattleOver()
{
	bool alliesSurvive = false;
	bool enemiesSurvive = false;

	for (int i = 0; i < 4; i++)
	{
		if (m_allies.getActor(i)->isAlive())
		{
			alliesSurvive = true;
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		if (m_enemies.getActor(i)->isAlive())
		{
			alliesSurvive = true;
		}
	}

	if (alliesSurvive&&enemiesSurvive)
	{
		return -1;//continue
	}
	else if (!alliesSurvive)
	{
		return 0;//defeat 
	}
	else if (!enemiesSurvive)
	{
		return 1;
	}
}

void Battle::victory() 
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; i < 4; j++)
		{
			m_allies.getActor(i)->gainExp(100 * ((m_enemies.getActor(j)->getLevel() + 2) / (m_allies.getActor(i)->getLevel() + 2)));
		}
	}
}

