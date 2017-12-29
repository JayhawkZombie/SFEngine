#ifndef _SHOP_H
#define _SHOP_H

#include "Inventory.h"
#include <array>
#include <iostream>

class Shop
{
public:
  Shop(Inventory* playerInventory, Inventory* shopInventory);
  ~Shop();
  //display all the useables, weapons, and armor of the player
  void displayPlayerInventory();
  //display all the useables, weapons, and armor of the shop
  void displayShopInventory();
  //buying items
  void Buy();
  //selling items
  void Sell();
  //the main shop menu
  void menu();
  //returns true if there's enough gold for the transaction, false if not
  bool sellItem(int itemIndex, int itemType, int amount);
  bool buyItem(int itemIndex, int itemType, int amount);

private:
  Inventory *m_playerInventory;
  Inventory *m_shopInventory;

  bool exitShop;
};
#endif /* _SHOP_H */
