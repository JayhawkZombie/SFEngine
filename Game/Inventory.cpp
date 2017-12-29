#include "Inventory.h"
#include "ListReader.h"
Inventory::Inventory()
{
	//these variables will hold the length of the arrays, which needs to be read  from file
	int armorSize;
	int weaponSize;
	int useableSize;
	
	std::ifstream file;//this ifstream will read the files
	file.open("Game/ContentFiles/armor.txt");
	if (!file.is_open())
	{
		std::cout << "Game/ContentFies/Armor.txt is missing\n";
		armorSize = 0;
	}
	else
	{
		file >> armorSize;
	}
	file.close();
	file.open("Game/ContentFiles/weapons.txt");
	if (!file.is_open())
	{
		std::cout << "Game/ContentFiles/weapons.txt is missing\n";
		weaponSize = 0;
	}
	else
	{
		file >> weaponSize;
	}
	file.close();
	file.open("Game/ContentFiles/useable.txt");
	if (!file.is_open())
	{
		std::cout << "Game/ContentFiles/useable.txt is missing";
		useableSize = 0;
	}
	else
	{
		file >> useableSize;
	}
	m_gold = 0;//sets amount of gold to zero

	//initializes m_armorCount to have all values at zero
	m_armorCount = new int[armorSize];
	for (int i = 0; i < armorSize; i++)
	{
		m_armorCount[i] = 0;
	}

	//intializes m_weaponCount to have all values at zero
	m_weaponCount = new int[weaponSize];
	for (int i = 0; i < weaponSize; i++)
	{
		m_weaponCount[i] = 0;
	}

	//initializes m_useableCount to have all values at zero
	m_useableCount = new int[useableSize];
	for (int i = 0; i < useableSize; i++)
	{
		m_useableCount[i] = 0;
	}
}

Inventory::~Inventory()
{

}

int* Inventory::getArmor()
{
	return m_armorCount;
}

int* Inventory::getWeapons()
{
	return m_weaponCount;
}

int* Inventory::getUseables()
{
	return m_useableCount;
}

int Inventory::getGold()
{
	return m_gold;
}
void Inventory::setGold(int delta)
{
  m_gold += delta;
}

bool Inventory::incrementArmor(int index, int delta)
{
	if (index < 0 || index >= sizeof(m_armorCount))
	{
		return false;//cant increment out of the bounds of the array
	}
	if (m_armorCount[index] + delta < 0)
	{
		return false;//cant have a negative number of an item
	}
	return true;
}

bool Inventory::incrementWeapons(int index, int delta)
{
	if (index < 0 || index >= sizeof(m_weaponCount))
	{
		return false;
	}
	if (m_weaponCount[index] + delta < 0)
	{
		return false;
	}
	return true;
}

bool Inventory::incrementUseables(int index, int delta)
{
	if (index < 0 || index >= sizeof(m_useableCount))
	{
		return false;
	}
	if (m_useableCount[index] + delta < 0)
	{
		return false;
	}
	return true;
}

void Inventory::updateArmor(int index, int delta)
{
  m_armorCount[index] += delta;
}

void Inventory::updateWeapons(int index, int delta)
{
  m_weaponCount[index] += delta;
}

void Inventory::updateUseables(int index, int delta)
{
  m_useableCount[index] += delta;
}
