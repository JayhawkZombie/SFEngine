#include "Reliquary.h"



Reliquary::Reliquary()
{
}


Reliquary::~Reliquary()
{
}

void Reliquary::run()
{
	int choice;
	while (true)
	{
		std::cout << "Reliquary Main Menu\n";
		std::cout << "1) Look at Armors\n";
		std::cout << "2) Look at Weapons\n";
		std::cout << "3) Exit\n";
		std::cin >> choice;
		if (choice == 1)
		{
			Reliquary::armorMainMenu();
		}
		else if (choice == 2)
		{
			Reliquary::weaponMainMenu();
		}
		else
		{
			return;
		}
	}
}

void Reliquary::armorMainMenu()
{
	ListReader list;
	Armor** myArray = list.ListReader::readArmor("Game/ContentFiles/Generic/GenericArmor.txt");
	int choice;
	int numArmor;
	std::ifstream file;
	file.open("Game/ContentFiles/Generic/GenericArmor.txt");
	file >> numArmor;
	file.close();
	while (true)
	{
		std::cout << "1) Select Armor by Teir\n";
		std::cout << "2) Select Armor by Type\n";
		std::cout << "3) Look at random Armor\n";
		std::cout << "4) return\n";
		std::cin >> choice;
		if (choice == 1)
		{
			Reliquary::selectArmorTier();
		}
		else if (choice == 2)
		{
			Reliquary::selectArmorType();
		}
		else if (choice == 3)
		{
			//Armor* myptr = myArray[rand() % numArmor];
			srand(time(NULL));
			int tier = rand() % 6;
			int type = rand() % 12;
			Reliquary::displayArmor(tier, type);
		}
		else if (choice == 4)
		{
			return;
		}
		else
		{
			std::cout << "Didn't understand your input\n";
		}
	}
}

void Reliquary::weaponMainMenu()
{
	ListReader list;
	Weapon** myArray = list.readWeapons("Game/ContentFiles/Generic/GenericWeapons.txt");
	int choice;
	int numWeapon;
	std::ifstream file;
	file.open("Game/ContentFiles/Generic/GenericWeapons.txt");
	file >> numWeapon;
	file.close();
	while (true)
	{
		std::cout << "1) Select Weapon by Teir\n";
		std::cout << "2) Select Weapon by Type\n";
		std::cout << "3) Look at random Weapon\n";
		std::cout << "4) Return\n";
		std::cin >> choice;
		if (choice == 1)
		{
			Reliquary::selectWeaponTier();
		}
		else if (choice == 2)
		{
			Reliquary::selectWeaponType();
		}
		else if (choice == 3)
		{
			srand(time(NULL));
			int teir = rand() % 6;
			int type = rand() % 13;
			//Weapon* myptr = myArray[rand() % numWeapon];
			Reliquary::displayWeapon(teir, type);
		}
		else if (choice == 4)
		{
			return;
		}
		else
		{
			std::cout << "Sorry, we couldn't understand your input\n\n";
		}
	}
}

void Reliquary::selectArmorTier()
{
	auto tiers = RPGItem::TierNames();
	int choice;
	while (true)
	{
		std::cout << "Please select the Tier you would like to view\n";
		std::cout << "1) " << tiers[0][0] << " / " << tiers[0][2] << " / " << tiers[0][3] << "\n";
		std::cout << "2) " << tiers[1][0] << " / " << tiers[1][2] << " / " << tiers[1][3] << "\n";
		std::cout << "3) " << tiers[2][0] << " / " << tiers[2][2] << " / " << tiers[2][3] << "\n";
		std::cout << "4) " << tiers[3][0] << " / " << tiers[3][2] << " / " << tiers[3][3] << "\n";
		std::cout << "5) " << tiers[4][0] << " / " << tiers[4][2] << " / " << tiers[4][3] << "\n";
		std::cout << "6) " << tiers[5][0] << " / " << tiers[5][2] << " / " << tiers[5][3] << "\n";
		std::cout << "7) return\n";
		std::cin >> choice;
		if (choice == 1)
		{
			viewArmorTier(0);
		}
		else if (choice == 2)
		{
			viewArmorTier(1);
		}
		else if (choice == 3)
		{
			viewArmorTier(2);
		}
		else if (choice == 4)
		{
			viewArmorTier(3);
		}
		else if (choice == 5)
		{
			viewArmorTier(4);
		}
		else if (choice == 6)
		{
			viewArmorTier(5);
		}
		else if (choice == 7)
		{
			return;
		}
		else
		{
			std::cout << "Sorry we didn't understand your input";
		}
	}
}

void Reliquary::selectWeaponTier()
{
	auto tiers = RPGItem::TierNames();
	int choice;
	while (true)
	{
		std::cout << "Please Select the Tier you would like to view\n";
		std::cout << "1) " << tiers[0][0] << " / " << tiers[0][1] << " / " << tiers[0][4] << " / " << tiers[0][5] << "\n";
		std::cout << "2) " << tiers[1][0] << " / " << tiers[1][1] << " / " << tiers[1][4] << " / " << tiers[1][5] << "\n";
		std::cout << "3) " << tiers[2][0] << " / " << tiers[2][1] << " / " << tiers[2][4] << " / " << tiers[2][5] << "\n";
		std::cout << "4) " << tiers[3][0] << " / " << tiers[3][1] << " / " << tiers[3][4] << " / " << tiers[3][5] << "\n";
		std::cout << "5) " << tiers[4][0] << " / " << tiers[4][1] << " / " << tiers[4][4] << " / " << tiers[4][5] << "\n";
		std::cout << "6) " << tiers[5][0] << " / " << tiers[5][1] << " / " << tiers[5][4] << " / " << tiers[5][5] << "\n";
		std::cout << "7) return\n";
		std::cin >> choice;
		if (choice == 1)
		{
			viewWeaponTier(0);
		}
		else if (choice == 2)
		{
			viewWeaponTier(1);
		}
		else if (choice == 3)
		{
			viewWeaponTier(2);
		}
		else if (choice == 4)
		{
			viewWeaponTier(3);
		}
		else if (choice == 5)
		{
			viewWeaponTier(4);
		}
		else if (choice == 6)
		{
			viewWeaponTier(5);
		}
		else if (choice == 7)
		{
			return;
		}
		else
		{
			std::cout << "Sorry, we couldn't read your input\n";
		}
	}
}

void Reliquary::selectArmorType()
{
	auto types = Armor::ArmorTypeNames();
	//int count;
	int choice;
	for (int i = 1; i <= 12; i++)
	{
		std::cout << i << ") " << types[i - 1] << "\n";
	}
	std::cout << "13) Return\n";
	std::cin >> choice;
	if (choice == 13)
	{
		return;
	}
	else if (choice > 0 && choice < 13)
	{
		viewArmorType(choice - 1);
	}
	else
	{
		std::cout << "Sorry we didn't understand your input\n";
	}
}

void Reliquary::selectWeaponType()
{
	auto types = Weapon::WeaponTypeNames();
	int choice;
	for (int i = 1; i <= 13; i++)
	{
		std::cout << i << ") " << types[i - 1] << "\n";
	}
	std::cout << "14) Return\n";
	std::cin >> choice;
	if (choice == 14)
	{
		return;
	}
	else if (choice > 0 && choice < 14)
	{
		viewWeaponType(choice - 1);
	}
	else
	{
		std::cout << "Sorry we didn't understand your input\n";
	}
}

void Reliquary::viewArmorTier(int tier)
{
	auto tiernames = RPGItem::TierNames();
	auto typeNames = Armor::ArmorTypeNames();
	int choice;
	while (true)
	{
		for (int i = 1; i <= 12; i++)
		{
			std::cout << i << ") ";
			if (i == 1 || i == 2 || i == 4 || i == 7 || i == 10)
			{
				std::cout << tiernames[tier][0] << " ";
			}
			else if (i == 5 || i == 8 || i == 11)
			{
				std::cout << tiernames[tier][2] << " ";
			}
			else
			{
				std::cout << tiernames[tier][3] << " ";
			}
			std::cout << typeNames[i - 1] << "\n";
		}
		std::cout << "13) return;";
		std::cin >> choice;
		if (choice == 13)
		{
			return;
		}
		else if (choice > 0 && choice < 13)
		{
			displayArmor(tier, choice - 1);
		}
		else
		{
			std::cout << "Sorry, we couldn't understand your input\n";
		}
	}
}

void Reliquary::viewWeaponTier(int tier)
{
	auto tiernames = RPGItem::TierNames();
	auto typeNames = Weapon::WeaponTypeNames();
	int choice;
	while (true)
	{
		for (int i = 1; i <= 13; i++)
		{
			std::cout << i << ") ";
			if (i-1 == 9)//Glass
			{
				std::cout << tiernames[tier][4] << " ";
			}
			else if (i-1 == 7)//Tome
			{
				std::cout << tiernames[tier][5] << " ";
			}
			else if (i-1 > 7)//Wood
			{
				std::cout << tiernames[tier][1] << " ";
			}
			else//everything else is metal
			{
				std::cout << tiernames[tier][0] << " ";
			}
			std::cout << typeNames[i - 1] << "\n";
		}
		std::cout << "14) return";
		std::cin >> choice;
		if (choice == 14)
		{
			return;
		}
		else if (choice > 0 && choice < 14)
		{
			displayWeapon(tier, choice - 1);
		}
		else
		{
			std::cout << "Sorry, we couldn't understand your input\n";
		}
	}
}

void Reliquary::viewArmorType(int type)
{
	auto tiernames = RPGItem::TierNames();
	auto typenames = Armor::ArmorTypeNames();
	int choice;
	while (true)
	{
		for (int i = 1; i <= 6; i++)
		{
			//this else if block prints the tier component of the item name
			if (type == 0 || type == 1 || type == 6 || type == 3 || type == 9)
			{
				std::cout << tiernames[i - 1][0];
			}
			else if(type == 2 || type == 5 || type == 8 || type == 11)
			{
				std::cout << tiernames[i - 1][3];
			}
			else
			{
				std::cout << tiernames[i - 1][2];
			}
			std::cout << typenames[type] << "\n";
		}
		std::cout << "7) return";
		std::cin >> choice;
		if (choice == 7)
		{
			return;
		}
		else if (choice > 0 && choice < 7)
		{
			displayArmor(choice-1,type);
		}
		else
		{
			std::cout << "Sorry, we didn't understand your input\n";
		}
	}
}

void Reliquary::viewWeaponType(int type)
{
	auto tiernames = RPGItem::TierNames();
	auto typenames = Weapon::WeaponTypeNames();
	int choice;
	while (true)
	{
		for (int i = 1; i <= 6; i++)
		{
			if (type == 7)
			{
				std::cout << tiernames[i - 1][5];
			}
			else if (type == 9)
			{
				std::cout << tiernames[i - 1][4];
			}
			else if (type > 7)
			{
				std::cout << tiernames[i - 1][1];
			}
			else
			{
				std::cout << tiernames[i - 1][0];
			}
			std::cout << typenames[type] << "\n";
		}
		std::cout << "7) return";
		std::cin >> choice;
		if (choice == 7)
		{
			return;
		}
		else if (choice > 0 && choice < 7)
		{
			displayWeapon(choice - 1, type);
		}
		else
		{
			std::cout << "Sorry, we didn't understand your input\n\n";
		}
	}
}

void Reliquary::displayArmor(int tier, int type)
{
	ListReader list;
	int choice;
	auto DamageNames = Damage::DamageTypesByIndex();
	Armor** myArray = list.ListReader::readArmor("Game/ContentFiles/Generic/GenericArmor.txt");
	std::cout << "Name:          " << myArray[tier * 12 + type]->getName() << "\n";
	std::cout << "Equip Type:    ";
	if (myArray[tier * 12 + type]->getType() == 0)
	{
		std::cout << "Chest\n";
	}
	else if (myArray[tier * 12 + type]->getType() == 1)
	{
		std::cout << "Legs\n";
	}
	else if (myArray[tier * 12 + type]->getType() == 2)
	{
		std::cout << "Head\n";
	}
	else if (myArray[tier * 12 + type]->getType() == 3)
	{
		std::cout << "Hands\n";
	}
	std::cout << "Texture:       " << myArray[tier * 12 + type]->getTexture() << "\n";
	std::cout << "Value:         " << myArray[tier * 12 + type]->getValue() << "\n";
	std::cout << "Required Level:" << myArray[tier * 12 + type]->getRequiredLevel() << "\n";
	for (int i = 0; i < 32; i++)
	{
		if (myArray[tier * 12 + type]->getDefense().content[i] != 0)
		{
			std::cout << DamageNames[i] << ":   " << myArray[tier * 12 + type]->getDefense().content[i] << "\n";
		}
	}
	std::cout << "Enter a number to return\n";
	std::cin >> choice;
	return;
}

void Reliquary::displayWeapon(int tier, int type)
{
	ListReader list;
	int choice;
	auto DamageNames = Damage::DamageTypesByIndex();
	Weapon** myArray = list.readWeapons("Game/ContentFiles/Generic/GenericWeapons.txt");
	std::cout << "Name:                   " << myArray[tier * 13 + type]->getName() << "\n";
	std::cout << "Equip type:             ";
	if (myArray[tier * 13 + type]->getNumHands() == 1)
	{
		std::cout << "One Handed\n";
	}
	else if (myArray[tier * 13 + type]->getNumHands() == 2)
	{
		std::cout << "Two Handed\n";
	}
	else
	{
		std::cout << "Error, invalid numHands\n";
	}
	std::cout << "Texture:                " << myArray[tier * 13 + type]->getTexture() << "\n";
	std::cout << "Value:                  " << myArray[tier * 13 + type]->getValue() << "\n";
	std::cout << "Required Level:         " << myArray[tier * 13 + type]->getRequiredLevel() << "\n";
	for (int i = 0; i < 32; i++)
	{
		if (myArray[tier * 13 + type]->getAddedDamage().content[i] != 0)
		{
			std::cout << DamageNames[i] << ":   " << myArray[tier * 12 + type]->getAddedDamage().content[i] << "\n";
		}
	}
	std::cout << "Enter a number to return\n";
	std::cin >> choice;
	return;
 }