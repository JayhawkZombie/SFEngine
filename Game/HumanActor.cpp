#include "HumanActor.h"


//constructor/Destructor
HumanActor::HumanActor()
{
	m_defense = Damage();
	m_weaponLeft = nullptr;
	m_weaponRight = nullptr;
	m_legs = nullptr;
	m_torso = nullptr;
	m_arms = nullptr;
	m_head = nullptr;
	m_ring = nullptr;
	m_numPhysical = 0;
	m_numMagical = 0;
}


HumanActor::~HumanActor()
{
}


//virtual methods

bool HumanActor::takeDamage(const Damage recieved)
{
	Damage* incurred = new Damage(recieved, m_defense);
	for (int i = 0; i < 9; i++)
	{
		//handle advantage case
		if (i == getPrimary())
		{
			this->setHpCur((int)(getHpCur() - incurred->content[i] * .8));
		}//handle disadvantage cases
		else if (getPrimary() == 0 && i == 1)
		{
			this->setHpCur((int)(getHpCur() - incurred->content[1] * 1.2));
		}
		else if (getPrimary() == 1 && i == 2)
		{
			this->setHpCur((int)(getHpCur() - incurred->content[2] * 1.2));
		}
		else if (getPrimary() == 2 && i == 3)
		{
			this->setHpCur((int)(getHpCur() - incurred->content[3] * 1.2));
		}
		else if (getPrimary() == 3 && i == 0)
		{
			this->setHpCur((int)(getHpCur() - incurred->content[i] * 1.2));
		}
		else if (getPrimary() == 4 && i == 5)
		{
			this->setHpCur((int)(getHpCur() - incurred->content[i] * 1.2));
		}
		else if (getPrimary() == 5 && i == 4)
		{
			this->setHpCur((int)(getHpCur() - incurred->content[i] * 1.2));
		}
		else
		{
			this->setHpCur((int)(getHpCur() - incurred->content[i]* 1.2));
		}
	}
	delete incurred;
	return(isAlive());
}

Damage HumanActor::baseDamage()
{
	Damage* base= new Damage();
	base->content[getPrimary()] = getLevel() * 1;
	double balance;
	double magMultiplier;
	double phyMultiplier;
	if (m_numPhysical < 0)
	{
		m_numPhysical = 0;
	}
	if (m_numMagical < 0)
	{
		m_numMagical = 0;
	}
	if (m_numPhysical == m_numMagical&&m_numPhysical == 0)
	{
		balance = .5;
	}
	else
	{
		balance = ((m_numMagical) / (m_numMagical + m_numPhysical));
	}
	int size = m_numMagical + m_numPhysical;

	if (balance > 1)
	{
		balance = 1;
	}
	else if (balance < 0)
	{
		balance = 0;
	}
	if (balance <= .2)
	{
		phyMultiplier = 1;
		magMultiplier = 0;
	}
	else if (balance <= .4)
	{
		phyMultiplier = .65;
		magMultiplier = .25;
	}
	else if (balance <= .6)
	{
		phyMultiplier = .4;
		magMultiplier = .4;
	}
	else if (balance <= .8)
	{
		phyMultiplier = .25;
		magMultiplier = .65;
	}
	else
	{
		phyMultiplier = 0;
		magMultiplier = 1;
	}
	if (size < 10)
	{
		base->content[6] = (int)(getLevel()*phyMultiplier);
		base->content[7] = (int)(getLevel()*magMultiplier);
	}
	else if (size < 50)
	{
		base->content[6] = (int)((getLevel()+1)*1.2*phyMultiplier);
		base->content[7] = (int)((getLevel() + 1)*1.2*magMultiplier);
	}
	else if (size < 100)
	{
		base->content[6] = (int)((getLevel() + 2)*1.4*phyMultiplier);
		base->content[7] = (int)((getLevel() + 2)*1.4*magMultiplier);
	}
	else if (size < 250)
	{
		base->content[6] = (int)((getLevel() + 4)*1.6*phyMultiplier);
		base->content[7] = (int)((getLevel() + 4)*1.6*magMultiplier);
	}
	else if (size < 500)
	{
		base->content[6] = (int)((getLevel() + 6)*1.8*phyMultiplier);
		base->content[7] = (int)((getLevel() + 6)*1.8*magMultiplier);
	}
	else if (size < 1000)
	{
		base->content[6] = (int)((getLevel()+10)*2*phyMultiplier);
		base->content[7] = (int)((getLevel() + 10) * 2 * magMultiplier);
	}
	else if (size < 5000)
	{
		base->content[6] = (int)((getLevel()+13)*2.2*phyMultiplier);
		base->content[7] = (int)((getLevel() + 13)*2.2*magMultiplier);
	}
	else if (size < 10000)
	{
		base->content[6] = (int)((getLevel()+17)*2.4*phyMultiplier);
		base->content[7] = (int)((getLevel() + 17)*2.4*magMultiplier);
	}
	else if (size < 50000)
	{
		base->content[6] = (int)((getLevel()+20)*2.6*phyMultiplier);
		base->content[7] = (int)((getLevel() + 20)*2.6*magMultiplier);
	}
	else if (size < 100000)
	{
		base->content[6] = (int)((getLevel()+25)*2.8*phyMultiplier);
		base->content[7] = (int)((getLevel() + 25)*2.8*magMultiplier);
	}
	else if (size < 500000)
	{
		base->content[6] = (int)((getLevel()+35)*3*phyMultiplier);
		base->content[7] = (int)((getLevel() + 35) * 3 * magMultiplier);
	}
	else
	{
		base->content[6] = (int)((getLevel()+50) * 4 * phyMultiplier);
		base->content[7] = (int)((getLevel() + 50) * 4 * magMultiplier);
	}
	return *(base);
}

void HumanActor::levelUp()
{
	double balance;//this is the balance between numPhysical and numMagical - used later on
	setLevel(getLevel()+1);//increments the level
	if (m_numPhysical < 0)//sets negative values to zero
	{
		m_numPhysical = 0;
	}
	if (m_numMagical < 0)
	{
		m_numMagical = 0;
	}
	if (m_numMagical == 0 && m_numPhysical == 0)//if both are zero sets balance to .5 to avoid
	{//divide by zero errors
		balance = .5;
	}
	else//sets balance to be a double between zero and one
	{
		balance = m_numMagical / (m_numMagical + m_numPhysical);
	}


	//sets mp regen based on the number of magical techniques used
	if (m_numMagical <= 10)
	{
		setMpRegen(1);
	}
	else if (m_numMagical <= 50)
	{
		setMpRegen(2);
	}
	else if (m_numMagical <= 100)
	{
		setMpRegen(3);
	}
	else if (m_numMagical <= 250)
	{
		setMpRegen(4);
	}
	else if (m_numMagical <= 500)
	{
		setMpRegen(5);
	}
	else if (m_numMagical <= 1000)
	{
		setMpRegen(7);
	}
	else if (m_numMagical <= 5000)
	{
		setMpRegen(9);
	}
	else if (m_numMagical <= 10000)
	{
		setMpRegen(12);
	}
	else if (m_numMagical <= 50000)
	{
		setMpRegen(15);
	}
	else if (m_numMagical <= 100000)
	{
		setMpRegen(20);
	}
	else if (m_numMagical <= 500000)
	{
		setMpRegen(25);
	}
	else
	{
		setMpRegen(30);
	}

	//these mulitpliers are used later to determine how much health/magic the player recieves
	//upon leveling up- they are based on the balance variable
	double hpMultiplier;
	double mpMultiplier;


	if (balance <= .2)
	{
		hpMultiplier = 1.3;
		mpMultiplier = .65;
	}
	else if (balance <= .4)
	{
		hpMultiplier = 1.15;
		mpMultiplier = .8;
	}
	else if (balance <= .6)
	{
		hpMultiplier = 1;
		mpMultiplier = 1;
	}
	else if (balance <= .8)
	{
		hpMultiplier = .85;
		mpMultiplier = 1.2;
	}
	else
	{
		hpMultiplier = .7;
		mpMultiplier = 1.35;
	}

	//this block actually distributes the added mp and hp based on the multiplier above
	if (getLevel() <=5)
	{
		setHpCur((int)(getHpCur() + 5 * hpMultiplier));
		setHpMax((int)(getHpMax() + 5 * hpMultiplier));
		setMpCur((int)(getMpCur() + 4 * mpMultiplier));
		setMpMax((int)(getMpMax() + 4 * mpMultiplier));
	}
	else if (getLevel() <= 10)
	{
		setHpCur((int)(getHpCur() + 20 * hpMultiplier));
		setHpMax((int)(getHpMax() + 20 * hpMultiplier));
		setMpCur((int)(getMpCur() + 4 * mpMultiplier));
		setMpMax((int)(getMpMax() + 4 * mpMultiplier));
	}
	else if (getLevel() <= 20)
	{
		setHpCur((int)(getHpCur() + 30 * hpMultiplier));
		setHpMax((int)(getHpMax() + 30 * hpMultiplier));
		setMpCur((int)(getMpCur() + 2 * mpMultiplier));
		setMpMax((int)(getMpMax() + 2 * mpMultiplier));
	}
	else if (getLevel() <= 30)
	{
		setHpCur((int)(getHpCur() + 40 * hpMultiplier));
		setHpMax((int)(getHpMax() + 40 * hpMultiplier));
		setMpCur((int)(getMpCur() + 2 * mpMultiplier));
		setMpMax((int)(getMpMax() + 2 * mpMultiplier));
	}
	else if (getLevel() <= 40)
	{
		setHpCur((int)(getHpCur() + 50 * hpMultiplier));
		setHpMax((int)(getHpMax() + 50 * hpMultiplier));
		setMpCur((int)(getMpCur() + 3 * mpMultiplier));
		setMpMax((int)(getMpMax() + 3 * mpMultiplier));
	}
	else if (getLevel() <= 50)
	{
		setHpCur((int)(getHpCur() + 60 * hpMultiplier));
		setHpMax((int)(getHpMax() + 60 * hpMultiplier));
		setMpCur((int)(getMpCur() + 3 * mpMultiplier));
		setMpMax((int)(getMpCur() + 3 * mpMultiplier));
	}
	else
	{
		setHpCur((int)(getHpCur() + 70 * hpMultiplier));
		setHpMax((int)(getHpCur() + 70 * hpMultiplier));
		setMpCur((int)(getMpCur() + 4 * mpMultiplier));
		setMpCur((int)(getMpMax() + 4 * mpMultiplier));
	}
}

void HumanActor::gainExp(int gain)
{
	setExp(getExp() + gain);
	if (getLevel() < 10)//if the level is less than ten, the required exp to level up is the level*100 + 1000
	{
		while (getExp()> (getLevel() * 100 + 1000))
		{
			levelUp();
			setExp(getExp()-(getLevel()*100 +1000));
		}
	}
	else//if the level is ten or greater, the required exp to level up has a power function as well
	{
		while (getExp() > ((getLevel() * 100 + 1000) + (int)(12 * (pow(getLevel(), 1.65)))))
		{
			levelUp();
			setExp(getExp() - ((getLevel() * 100 + 1000) + (int)(12 * (pow(getLevel(), 1.65)))));
		}
	}
}

//getters

Damage HumanActor::getDefense()
{
	return m_defense;
}

Weapon HumanActor::getWeaponLeft()
{
	return *(m_weaponLeft);
}

Weapon HumanActor::getWeaponRight()
{
	return *(m_weaponRight);
}

Armor HumanActor::getLegs()
{
	return *(m_legs);
}

Armor HumanActor::getTorso()
{
	return *(m_torso);
}

Armor HumanActor::getArms()
{
	return *(m_arms);
}

Armor HumanActor::getHead()
{
	return *(m_head);
}

Armor HumanActor::getRing()
{
	return *(m_ring);
}

int HumanActor::getNumPhysical()
{
	return m_numPhysical;
}

int HumanActor::getNumMagical()
{
	return m_numMagical;
}
//setters

void HumanActor::setDefense(Damage defense)
{
	m_defense = defense;
}

void HumanActor::setWeaponLeft(Weapon* weaponLeft)
{
	m_weaponLeft = weaponLeft;
}

void HumanActor::setWeaponRight(Weapon* weaponRight)
{
	m_weaponRight = weaponRight;
}

void HumanActor::setLegs(Armor* legs)
{
	m_legs = legs;
}

void HumanActor::setTorso(Armor* torso)
{
	m_torso = torso;
}

void HumanActor::setArms(Armor* arms)
{
	m_arms = arms;
}

void HumanActor::setHead(Armor* head)
{
	m_head = head;
}

void HumanActor::setRing(Armor* ring)
{
	m_ring = ring;
}

void HumanActor::incrementPhysical()
{
	m_numPhysical++;
}

void HumanActor::incrementMagical()
{
	m_numMagical++;
}