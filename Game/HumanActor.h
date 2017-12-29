#ifndef HUMANACTOR_H
#define HUMANACTOR_H

#include "BattleActor.h"
#include "Damage.h"
#include "Weapon.h"
#include "Armor.h"
#include <Math.h>


class HumanActor: public BattleActor
{
public:
	//constructor/descructor
	HumanActor();
	~HumanActor();

	//virtual methods
	virtual bool takeDamage(const Damage recieved);
	virtual Damage baseDamage();
	virtual void levelUp();
	virtual void gainExp(int gain);

	//getters
	Damage getDefense();
	Weapon getWeaponLeft();
	Weapon getWeaponRight();
	Armor getLegs();
	Armor getTorso();
	Armor getArms();
	Armor getHead();
	Armor getRing();
	int getNumPhysical();
	int getNumMagical();

	//setters
	void setDefense(Damage defense);
	void setWeaponLeft(Weapon* weaponLeft);
	void setWeaponRight(Weapon* weaponRight);
	void setLegs(Armor* legs);
	void setTorso(Armor* torso);
	void setArms(Armor* arms);
	void setHead(Armor* head);
	void setRing(Armor* ring);
	void incrementPhysical();
	void incrementMagical();
	
private:
	
	Damage m_defense;
	Weapon* m_weaponLeft;
	Weapon* m_weaponRight;
	Armor* m_legs;
	Armor* m_torso;
	Armor* m_arms;
	Armor* m_head;
	Armor* m_ring;
	int m_numPhysical;
	int m_numMagical;
};

#endif