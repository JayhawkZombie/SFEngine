#ifndef RELIQUARY_H
#define RELIQUARY_H

#include "Weapon.h"
#include "Armor.h"
#include "ListReader.h"
#include "RPGItem.h"
#include "Damage.h"

#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <map>

class Reliquary
{
public:
	Reliquary();
	~Reliquary();
	static void run();
	static void armorMainMenu();
	static void weaponMainMenu();
	static void selectArmorTier();
	static void selectWeaponTier();
	static void selectArmorType();
	static void selectWeaponType();
	static void viewArmorTier(int tier);
	static void viewWeaponTier(int tier);
	static void viewArmorType(int type);
	static void viewWeaponType(int type);
	static void displayArmor(int teir, int type);
	static void displayWeapon(int teir, int type);
};

#endif