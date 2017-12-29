#ifndef INVENTORY_H
#define INVENTORY_H

#include <fstream>
#include "ListReader.h"
class Inventory
{
public:
	Inventory();
	~Inventory();

	//these functions return the array containing their inventories
	int* getArmor();
	int* getWeapons();
	int* getUseables();

	bool incrementArmor(int index, int delta);//returns if successful or not
	bool incrementWeapons(int index, int delta);
	bool incrementUseables(int index, int delta);

  void updateArmor(int index, int delta);
  void updateWeapons(int index, int delta);
  void updateUseables(int index, int delta);
  
  void setGold(int delta);
	int getGold();
private:
	int* m_armorCount;//the number of each type of armor the party has
	int* m_weaponCount;//the number of each type of weapon the party has
	int* m_useableCount;//see above
	int m_gold;
};
#endif