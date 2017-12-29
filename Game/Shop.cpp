#include "Shop.h"
Shop::Shop(Inventory* playerInventory, Inventory* shopInventory)
{
  m_playerInventory = playerInventory;
  m_shopInventory = shopInventory;
  exitShop = false;
}
Shop::~Shop()
{
/*
  if (useable != NULL)
    delete useable;
  if (armor != NULL)
    delete armor;
  if (weapon != NULL)
    delete weapon;
*/
}
void Shop::Buy()
{
  //player option
  int option = 0;
  //amount they plan on buying
  int amount;
  //index of the item
  int item;
  //while they don't choose to leave, keep looping the buy menu
  while (-1 != option)
  {
    //display inventories
    displayPlayerInventory();
    displayShopInventory();

    //buying and item display
    std::cout << "\n-Buying- \n[1] for Useables, \n[2] for Weapons, \n[3] for Armor, \n[-1] to go back to menu: ";
    std::cin >> option;

    switch (option)
    {
    case 1:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if ( !(m_shopInventory->incrementUseables(item, (-amount))) )
      {
        std::cout << "\nInvalid. Not enough items.";
      }
      /*else if (! buyItem(option,item,amount) ) {}*/
      else
      {
        std::cout << "\nItems bought.";
        m_playerInventory->incrementUseables(item, amount);
      }
      break;
    case 2:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if ( !(m_shopInventory->incrementWeapons(item, (-amount))) )
      {
        std::cout << "\nInvalid. Not enough items.";
      }
      /*else if (! buyItem(option,item,amount) ) {}*/
      else
      {
        std::cout << "\nItems bought.";
        m_playerInventory->incrementWeapons(item, amount);
      }
      break;
    case 3:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if ( !(m_shopInventory->incrementArmor(item, (-amount))) )
      {
        std::cout << "\nInvalid. Not enough items.";
      }
      /*else if (! buyItem(option,item,amount) ) {}*/
      else
      {
        std::cout << "\nItems bought.";
        m_playerInventory->incrementArmor(item, amount);
      }
      break;
    case -1:
      menu();
      break;
    default:
      break;
    }
  }
}
void Shop::Sell()
{
  //player option
  int option = 0;
  //amount they plan on selling
  int amount;
  //index number of the item they're selling
  int item;
  //while they don't choose to leave, keep looping the selling menu
  while (-1 != option)
  {
    displayPlayerInventory();
    displayShopInventory();
    std::cout << "\n-Selling- \n[1] for Useables, \n[2] for Weapons, \n[3] for Armor, \n[-1] to go back to menu: ";
    std::cin >> option;
    switch (option)
    {
    case 1:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (! (m_playerInventory->incrementUseables(item, (-amount))) )
      {
        std::cout << "\nInvalid. Not enough items.";
      }
      /*else if (! sellItem(option,item,amount) ) {}*/
      else
      {
        std::cout << "\nItems sold.";
        m_shopInventory->incrementUseables(item, amount);
      }
      break;
    case 2:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (! (m_playerInventory->incrementWeapons(item, (-amount))) )
      {
        std::cout << "\nInvalid. Not enough items.";
      }
      /*else if (! sellItem(option,item,amount) ) {}*/
      else
      {
        std::cout << "\nItems sold.";
        m_shopInventory->incrementWeapons(item, amount);
      }
      break;
    case 3:
      std::cout << "\nItem #: ";
      std::cin >> item;
      std::cout << "\nInsert amount: ";
      std::cin >> amount;

      if (! (m_playerInventory->incrementArmor(item, (-amount))) )
      {
        std::cout << "\nInvalid. Not enough items.";
      }
      /*else if (! sellItem(option,item,amount) ) {}*/
      else
      {
        std::cout << "\nItems sold.";
        m_shopInventory->incrementArmor(item, amount);
      }
      break;
    case -1:
      menu();
      break;
    default:
      break;
    }
  }
}
void Shop::displayPlayerInventory()
{

  ListReader reader;
  Useable** useable = NULL;
  Armor** armor = NULL;
  Weapon** weapon = NULL;


  /*
  useable = reader.readUseables("Game/ContentFiles/useable.txt");
  armor = reader.readArmor("Game/ContentFiles/armor.txt");
  weapon = reader.readWeapons("Game/ContentFiles/weapons.txt");
  */
  bool noItems = true;

  std::cout << "\nYour inventory\n";
  //display useables
  //may not display if the number of the items is less than or equal to 0
  for (int i = 0; i < sizeof(m_playerInventory->getUseables()); i++)
  {
    //if there isn't any item for this index, go to the next loop iteration
    if (0 >= m_playerInventory->getUseables()[i])
    {
       continue;
    }
    else
    {
       //set noItems to false if there are items
       //if the name file exists, print the names of the item.
       noItems = false;
       std::cout << "Useable index#" << i;
       if (useable != NULL)
       { std::cout << "; Name: " << useable[i]->getName(); }
       std::cout << "; Amount: " << m_playerInventory->getUseables()[i] << "\n";
    }
  }
  if (noItems)
  {
     std::cout << "No Useables.\n";
  }
  noItems = true;
  //display weapons
  //may not display if the number of the items is less than or equal to 0
  for (int i = 0; i < sizeof(m_playerInventory->getWeapons()); i++)
  {
    if (0 >= m_playerInventory->getWeapons()[i])
    {
       continue;
    }
    else
    {
       //set noItems to false if there are items
       //if the name file exists, print the names of the item.
       noItems = false;
       std::cout << "Weapon index#" << i;
       if (weapon != NULL)
       { std::cout << "; Name: " << weapon[i]->getName(); }
       std::cout << "; Amount: " << m_playerInventory->getWeapons()[i] << "\n";
    }
  }
  if (noItems)
  {
     std::cout << "No Weapons.\n";
  }
  noItems = true;
  //display armor
  //may not display if the number of the items is less than or equal to 0
  for (int i = 0; i < sizeof(m_playerInventory->getArmor()); i++)
  {
    //if there isn't any item for this index, go to the next loop iteration
    if (0 >= m_playerInventory->getArmor()[i])
    {
       continue;
    }
    else
    {
       //set noItems to false if there are items
       //if the name file exists, print the names of the item.
       noItems = false;
       std::cout << "Armor index#" << i;
       if (armor != NULL)
       { std::cout << "; Name: " << armor[i]->getName(); }
       std::cout << "; Amount: " << m_playerInventory->getArmor()[i] << "\n";
    }
  }
  if (noItems)
  {
     std::cout << "No Armor.\n";
  }
  //display gold
  std::cout << "Gold: " << m_playerInventory->getGold() << "\n";

}
void Shop::displayShopInventory()
{
  ListReader reader;
  Useable** useable = NULL;
  Armor** armor = NULL;
  Weapon** weapon = NULL;


  /*
  useable = reader.readUseables("Game/ContentFiles/useable.txt");
  armor = reader.readArmor("Game/ContentFiles/armor.txt");
  weapon = reader.readWeapons("Game/ContentFiles/weapons.txt");
  */

  bool noItems = true;
  std::cout << "\nShop's inventory\n";
  //display useables
  //may not display if the number of the items is less than or equal to 0
  for (int i = 0; i < sizeof(m_shopInventory->getUseables()); i++)
  {
    //if there isn't any item for this index, go to the next loop iteration
    if (0 >= m_shopInventory->getUseables()[i])
    {
       continue;
    }
    else
    {
       //set noItems to false if there are items
       //if the name file exists, print the names of the item.
       noItems = false;
       std::cout << "Useable index#" << i;
       if (useable != NULL)
       { std::cout << "; Name: " << useable[i]->getName(); }
       std::cout << "; Amount: " << m_shopInventory->getUseables()[i] << "\n";
    }
  }
  if (noItems)
  {
     std::cout << "No Useables.\n";
  }
  noItems = true;
  //display weapons
  //may not display if the number of the items is less than or equal to 0
  for (int i = 0; i < sizeof(m_shopInventory->getWeapons()); i++)
  {
    //if there isn't any item for this index, go to the next loop iteration
    if (0 >= m_shopInventory->getWeapons()[i])
    {
       continue;
    }
    else
    {
       //set noItems to false if there are items
       //if the name file exists, print the names of the item.
       noItems = false;
       std::cout << "Weapon index#" << i;
       if (weapon != NULL)
       { std::cout << "; Name: " << weapon[i]->getName(); }
       std::cout << "; Amount: " << m_shopInventory->getWeapons()[i] << "\n";
    }
  }
  if (noItems)
  {
     std::cout << "No Weapons.\n";
  }
  noItems = true;
  //display armor
  //may not display if the number of the items is less than or equal to 0
  for (int i = 0; i < sizeof(m_shopInventory->getArmor()); i++)
  {
    if (0 >= m_shopInventory->getArmor()[i])
    {
       continue;
    }
    else
    {
       //set noItems to false if there are items
       //if the name file exists, print the names of the item.
       noItems = false;
       std::cout << "Armor index#" << i;
       if (armor != NULL)
       { std::cout << "; \tName: " << armor[i]->getName(); }
       std::cout << ";\tAmount: " << m_shopInventory->getArmor()[i] << "\n";
    }
  }
  if (noItems)
  {
     std::cout << "No Armor.\n";
  }
  //display gold
  std::cout << "Gold: " << m_shopInventory->getGold() << "\n";
}

//returns false if there isn't enough gold or the transaction can't occur
//itemTypes = 1 for useable, 2 for weapons, 3 for armor
bool Shop::sellItem(int itemIndex, int itemType, int amount)
{
  ListReader reader;
  Useable** useable = NULL;
  Armor** armor = NULL;
  Weapon** weapon = NULL;

  /*
  useable = reader.readUseables("Game/ContentFiles/useable.txt");
  armor = reader.readArmor("Game/ContentFiles/armor.txt");
  weapon = reader.readWeapons("Game/ContentFiles/weapons.txt");
  */

  float cost = 0;
  float multiplier = .75;

  switch (itemType)
  {
     case 1:
       /*cost = useable[itemIndex]->getValue()*amount*multiplier;*/
       break;
     case 2:
       /*cost = armor[itemIndex]->getValue()*amount*multiplier;*/
       break;
     case 3:
       /*cost = weapon[itemIndex]->getValue()*amount*multiplier;*/
       break;
     default:
       return false;
  }
  if (m_shopInventory->getGold() < cost)
  {
    std::cout << "The shop does not have enough gold.\n";
    return false;
  }
  else
  {
    // --still need to decrement the shop's gold --
    switch (itemType)
    {
       case 1:
         /*std::cout << amount << " " << useable[itemIndex]->getName() << " sold\n";*/
         break;
       case 2:
         /*std::cout << amount << " " << armor[itemIndex]->getName() << " sold\n";*/
         break;
       case 3:
         /*std::cout << amount << " " << weapon[itemIndex]->getName() << " sold\n";*/
         break;
       default:
         return false;
    }
  }
  return true;
}
//returns false if there isn't enough gold or the transaction can't occur
//itemTypes = 1 for useable, 2 for weapons, 3 for armor
bool Shop::buyItem(int itemIndex, int itemType, int amount)
{
  ListReader reader;
  Useable** useable = NULL;
  Armor** armor = NULL;
  Weapon** weapon = NULL;


  /*
  useable = reader.readUseables("Game/ContentFiles/useable.txt");
  armor = reader.readArmor("Game/ContentFiles/armor.txt");
  weapon = reader.readWeapons("Game/ContentFiles/weapons.txt");
  */

  float cost = 0;
  float multiplier = 1.25;

  switch (itemType)
  {
     case 1:
       /*cost = useable[itemIndex]->getValue()*amount*multiplier;*/
       break;
     case 2:
       /*cost = armor[itemIndex]->getValue()*amount*multiplier;*/
       break;
     case 3:
       /*cost = weapon[itemIndex]->getValue()*amount*multiplier;*/
       break;
     default:
       return false;
  }
  if (m_playerInventory->getGold() < cost)
  {
    std::cout << "You do not have enough gold.\n";
    return false;
  }
  else
  {
    // --still need to decrement the player's gold --
    switch (itemType)
    {
       case 1:
         /*std::cout << amount << " " << useable[itemIndex]->getName() << " bought\n";*/
         break;
       case 2:
         /*std::cout << amount << " " << armor[itemIndex]->getName() << " bought\n";*/
         break;
       case 3:
         /*std::cout << amount << " " << weapon[itemIndex]->getName() << " bought\n";*/
         break;
       default:
         return false;
    }
  }
  return true;
}

void Shop::menu()
{
  int playerSelection;

  std::cout << "\nBuy [1], Sell [2], or Exit [3]\n";
  std::cin >> playerSelection;
  while (!exitShop)
  {
    switch (playerSelection)
    {
    case 1:
      Buy();
      break;
    case 2:
      Sell();
      break;
    case 3:
      exitShop = true;
      break;
    default:
      break;
    }
  }
}
