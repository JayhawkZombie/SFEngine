#include "RPGTest.h"



RPGTest::RPGTest()
{
}


RPGTest::~RPGTest()
{
}

void RPGTest::runTests(bool quiet)
{
	int numPassed = 0;
	int numTotal = 0;
	if (testRPGActor1(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGActor2(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGItem1(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGItem2(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}	
	if (testRPGItem3(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}	
	if (testRPGItem4(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testRPGItem5(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile1(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile2(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile3(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile4(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile5(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
	if (testTile6(quiet))
	{
		numPassed++;
		numTotal++;
	}
	else
	{
		numTotal++;
	}
  if (testDamage1(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testDamage2(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon1(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon2(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon3(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testWeapon4(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }


  if (testUseable1(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testUseable2(quiet))
  {
    numPassed++;
    numTotal++;
  }
  else
  {
    numTotal++;
  }
  if (testInventory1(quiet))
  {
	  numPassed++;
	  numTotal++;
  }
  else
  {
	  numTotal++;
  }
  if (testMainCharacter1(quiet))
  {
	  numPassed++;
	  numTotal++;
  }
  else
  {
	  numTotal++;
  }
  if (testGameMain1(quiet))
  {
	  numPassed++;
  }
  numTotal++;
  /*
  if (testGameMain2(quiet))
  {
	  numPassed++;
  }
  numTotal++;
  if (testGameMain3(quiet))
  {
	  numPassed++;
  }
  numTotal++;
  if (testGameMain4(quiet))
  {
	  numPassed++;
  }
  */
  numTotal++;
	std::cout << numPassed << "/" << numTotal << "Passed, " << ((double)numPassed / (double)numTotal) * 100 << "%\n";

}

bool RPGTest::testRPGActor1(bool quiet)
{//This function tests the constructor for the RPGActor
	RPGActor* myActor = new RPGActor();
	if (myActor->getName() == "")
	{
		if (!quiet)
		{
			std::cout << "RPGActor Test 1:  PASSED\n";
		}
		delete myActor;
		return true;
	}
	else
	{
		std::cout << "RPGActor Test 1: FAILED\n";
		std::cout << "myActor->getName() ==" << myActor->getName() << "\n";
		delete myActor;
		return false;
	}
}

bool RPGTest::testRPGActor2(bool quiet)
{//This function tests the getName and setName functions in the RPGActor Class
	RPGActor* myActor = new RPGActor();
	myActor->setName("test");
	if (myActor->getName() == "test")
	{
		if (!quiet)
		{
			std::cout << "RPGActor Test 2: PASSED\n";
		}
		delete myActor;
		return true;
	}
	else
	{
		std::cout << "RPGActor Test 2: FAILED\n";
		delete myActor;
		return false;
	}
}

bool RPGTest::testRPGItem1(bool quiet)
{//tests constructor and implicitly test getters and setters
	RPGItem* myItem = new RPGItem();
	if (  (myItem->getName().compare("")==0) && (myItem->getDescription().compare("")==0 ) && (myItem->getValue() == 0) && (myItem->getId() == 0)  )
	{
		if (!quiet)
		{
			std::cout << "RPGItem Test 1: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem Test 1: FAILED\n";
		std::cout << "myItem->getName() = " << myItem->getName() << "\n";
		std::cout << "myItem->getDescription() = " << myItem->getDescription() << "\n";
		std::cout << "myItem->getValue() = " << myItem->getValue() << "\n";
		std::cout << "myItem->getId() = " << myItem->getId() << "\n";
		std::cout << "myItem->getName().compare(\"\") = " << myItem->getName().compare("") << "\n";
//		std::cout << "myItem->getName()==\"\" " << myItem->getName() == "";
		delete myItem;
		return false;
	}
}

bool RPGTest::testRPGItem2(bool quiet)
{//Tests getters and setters for m_name variable
	RPGItem* myItem = new RPGItem();
	myItem->setName("TestName");
	if (myItem->getName() == "TestName")
	{
		if (!quiet)
		{
			std::cout << "RPGItem Test 2: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem Test 2: FAILED\n";
		delete myItem;
		return false;
	}
}

bool RPGTest::testRPGItem3(bool quiet)
{//Tests getters and setters for m_description variable
	RPGItem* myItem = new RPGItem();
	myItem->setDescription("TestDescription");
	if (myItem->getDescription() == "TestDescription")
	{
		if (!quiet)
		{
			std::cout << "RPGItem test 3: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem test 3: FAILED\n";
		delete myItem;
		return false;
	}
}

bool RPGTest::testRPGItem4(bool quiet)
{
	RPGItem* myItem = new RPGItem();
	myItem->setValue(1337);
	if (myItem->getValue() == 1337)
	{
		if (!quiet)
		{
			std::cout << "RPGItem test 4: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem test 4: FAILED\n";
		return false;
	}
}

bool RPGTest::testRPGItem5(bool quiet)
{
	RPGItem* myItem = new RPGItem();
	myItem->setId(1337);
	if (myItem->getId() == 1337)
	{
		if (!quiet)
		{
			std::cout << "RPGItem test 5: PASSED\n";
		}
		delete myItem;
		return true;
	}
	else
	{
		std::cout << "RPGItem test 5: FAILED\n";
		return false;
	}
}

bool RPGTest::testTile1(bool quiet)
{
	Tile* myTile = new Tile();
	if (  (myTile->getCanTravel()) && (myTile->getShow() == 'W') && (myTile->getSpriteBackground().compare("") == 0) && (myTile->getSpriteForeground().compare("") == 0))
	{
		if (!quiet)
		{
			std::cout << "Tile test 1: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 1: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile2(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setCanTravel(true);
	if (myTile->getCanTravel())
	{
		if (!quiet)
		{
			std::cout << "Tile test2: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 2: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile3(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setCanTravel(false);
	if (!(myTile->getCanTravel()))
	{
		if (!quiet)
		{
			std::cout << "Tile test 3: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 3: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile4(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setShow('X');
	if (myTile->getShow() == 'X')
	{
		if (!quiet)
		{
			std::cout << "Tile test 4: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 4: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile5(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setSpriteBackground("/pixels/Bgtile/Grass1.png");
	if (myTile->getSpriteBackground().compare("/pixels/Bgtile/Grass1.png") == 0)
	{
		if (!quiet)
		{
			std::cout << "Tile test 5: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 5: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testTile6(bool quiet)
{
	Tile* myTile = new Tile();
	myTile->setSpriteForeground("/pixels/Bgtile/Grass1.png");
	if (myTile->getSpriteForeground().compare("/pixels/Bgtile/Grass1.png") == 0)
	{
		if (!quiet)
		{
			std::cout << "Tile test 6: PASSED\n";
		}
		delete myTile;
		return true;
	}
	else
	{
		std::cout << "Tile test 6: FAILED\n";
		delete myTile;
		return false;
	}
}

bool RPGTest::testDamage1(bool quiet)
{
  Damage* myDamage = new Damage();
  {
    for (int i = 0; i < 30; i++)
    {
      if (myDamage->content[i] != 0)
      {
        std::cout << "Damage Test 1: FAILED\n";
        delete myDamage;
        return false;
      }
    }
    if(!quiet)
    {
      std::cout << "Damage Test 1: PASSED\n";
    }
    delete myDamage;
    return true;
  }
}

bool RPGTest::testDamage2(bool quiet)
{
  Damage* myDamage = new Damage();
  for (int i = 0; i < 30; i++)//loads damage into the array
  {
    myDamage->content[i] = ((i * 2) + (i%5));
  }
  for (int i = 0; i < 30; i++)//Testing that the array was loaded properly
  {
    if (myDamage->content[i] != ((i * 2) + (i % 5)))
    {
      std::cout << "Damage Test 2: FAILED\n";
      delete myDamage;
      return false;
    }
  }
  if (!quiet)
  {
    std::cout << "Damage Test 2: PASSED\n";
  }
  delete myDamage;
  return true;

}

bool RPGTest::testWeapon1(bool quiet)
{
  Weapon* myWeapon = new Weapon();
  for (int i = 0; i < Damage::size; i++)
  {
    if (myWeapon->getAddedDamage().content[i] != 0)
    {
      std::cout << "Weapon Test 1: FAILED\n";
      delete myWeapon;
      return false;
    }
  }
  if (!myWeapon->getRightHand() || myWeapon->getLeftHand())
  {
    std::cout << "Weapon Test 1: FAILED\n";
    delete myWeapon;
    return false;
  }
  else
  {
    if (!quiet)
    {
      std::cout << "Weapon Test 1: PASSED\n";
    }
    delete myWeapon;
    return true;
  }
}

bool RPGTest::testWeapon2(bool quiet)
{
  Weapon* myWeapon = new Weapon();
  Damage* myDamage = new Damage();
  for (int i = 0; i < Damage::size; i++)
  {
    myDamage->content[i] = ((i * 3) + (i % 5));
  }
  myWeapon->setAddedDamage(*myDamage);
  delete myDamage;
  for (int i = 0; i < Damage::size; i++)
  {
    if (myWeapon->getAddedDamage().content[i] != ((i * 3) + (i % 5)))
    {
      std::cout << "Weapon Test 2: FAILED\n";
      delete myWeapon;
      return false;
    }
  }
  if (!quiet)
  {
    std::cout << "Weapon Test 2: PASSED\n";
  }
  delete myWeapon;
  return true;
}

bool RPGTest::testWeapon3(bool quiet)
{
  Weapon* myWeapon = new Weapon();
  myWeapon->setRightHand(true);
  if (!myWeapon->getRightHand())
  {
    std::cout << "Weapon Test 3: FAILED\n";
    delete myWeapon;
    return false;
  }
  myWeapon->setRightHand(false);
  if (myWeapon->getRightHand())
  {
    std::cout << "Weapon Test 3: FAILED\n";
    delete myWeapon;
    return false;
  }
  if (!quiet)
  {
    std::cout << "Weapon Test 3: PASSED\n";
  }
  delete myWeapon;
  return true;
}

bool RPGTest::testWeapon4(bool quiet)

{
  Weapon* myWeapon = new Weapon();
  myWeapon->setLeftHand(true);
  if (!myWeapon->getLeftHand())
  {
    std::cout << "Weapon Test 4: FAILED\n";
    delete myWeapon;
    return false;
  }
  myWeapon->setLeftHand(false);
  if (myWeapon->getLeftHand())
  {
    std::cout << "Weapon Test 4: FAILED\n";
    delete myWeapon;
    return false;
  }
  if (!quiet)
  {
    std::cout << "WeaponTest 4: PASSED\n";
  }
  delete myWeapon;
  return true;
}

bool RPGTest::testMonsterType1(bool quiet)
{
  MonsterType* myMonster = new MonsterType();
  if ((myMonster->getDescription().compare("") != 0) || (myMonster->getPrimary() != -1) || (myMonster->getSecondary() != -1) || (myMonster->getEvolutionStage() != -1) || (myMonster->getEvolutionType() != -1) || (myMonster->getName().compare("") != 0))
  {
    std::cout << "Monster Test 1: FAILED\n";
    delete myMonster;
    return false;
  }
  if (!quiet)
  {
    std::cout << "Monster Test 1: PASSED\n";
  }
  delete myMonster;
  return true;
}

bool RPGTest::testUseable1(bool quiet)
{
  Useable* myUseable = new Useable();
  for (int i = 0; i < Damage::size; i++)
  {
    if (myUseable->getDamage().content[i] != 0)
    {
      std::cout << "Useable Test 1: FAILED\n";
      delete myUseable;
      return false;
    }
  }
  if (!quiet)
  {
    std::cout << "Useable Test 1: PASSED\n";
  }
  delete myUseable;
  return true;
}

bool RPGTest::testUseable2(bool quiet)
{
  Useable* myUseable = new Useable();
  Damage* myDamage = new Damage();
  for (int i = 0; i < Damage::size; i++)
  {
    myDamage->content[i] = ((i * 4) + (i % 3));
  }
  myUseable->setDamage(*myDamage);
  delete myDamage;
  for (int i = 0; i < Damage::size; i++)
  {
    if (myUseable->getDamage().content[i] != ((i * 4) + (i % 3)))
    {
      std::cout << "Useable Test 2: FAILED\n";
      delete myUseable;
      return false;
    }
  }
  if (!quiet)
  {
    std::cout << "Useable Test 2: PASSED\n";
  }
  delete myUseable;
  return true;
}

bool RPGTest::testSkill1(bool quiet)
{
  Skill* mySkill = new Skill();
  {
    mySkill->setIsMagical(true);
    if (!mySkill->getIsMagical())
    {
      std::cout << "Skill Test 1: FAILED\n";
      delete mySkill;
      return false;
    }
    if (!quiet)
    {
      std::cout << "Skill Test 1: PASSED\n";
    }
    delete mySkill;
    return true;
  }
}

bool RPGTest::testInventory1(bool quiet)
{
	try
	{
		Inventory* myInventory = new Inventory();
		if (!quiet)
		{
			std::cout << "Inventory Test 1: PASSED\n";
		}
		return true;
	}
	catch (int e)
	{
		std::cout << "Error number " << e << "\n";
		std::cout << "There is an error in the constructor of Inventory";
		std::cout << "Inventory Test 1: FAILED\n";
		return false;
	}
}

bool RPGTest::testMainCharacter1(bool quiet)
{
	try
	{
		MainCharacter* myMainCharacter = new MainCharacter();
		if (!quiet)
		{
			std::cout << "Main Character Test1: PASSED\n";
		}
		return true;
	}
	catch (int e)
	{
		std::cout << "Error number " << e << "\n";
		std::cout << "There is an error in the constructor of Main Character\n";
		std::cout << "Main Character Test1: FAILED\n";
		return false;
	}
}

bool RPGTest::testGameMain1(bool quiet)
{
	//std::cout << "GOT HERE\n";
	std::map<int, std::map<int, std::map< int, int>>> SizeLookup;

	std::map<int, int> TreeType1;
	TreeType1[1] = 1;
	TreeType1[2] = 1;
	TreeType1[3] = 1;
	TreeType1[4] = 1;

	std::map<int, int> TreeType2;
	TreeType2[1] = 1;
	TreeType2[2] = 2;
	TreeType2[3] = 2;
	TreeType2[4] = 2;

	std::map<int, int> TreeType3;
	TreeType3[1] = 1;
	TreeType3[2] = 3;
	TreeType3[3] = 3;
	TreeType3[4] = 3;

	std::map<int, int> TreeType4;
	TreeType4[1] = 1;
	TreeType4[2] = 3;
	TreeType4[3] = 4;
	TreeType4[4] = 4;

	std::map<int, int> TreeType5;
	TreeType5[1] = 3;
	TreeType5[2] = 4;
	TreeType5[3] = 5;
	TreeType5[4] = 6;

	SizeLookup[0][0] = TreeType4;
	SizeLookup[0][1] = TreeType2;
	SizeLookup[0][2] = TreeType3;
	SizeLookup[0][3] = TreeType2;
	SizeLookup[0][4] = TreeType2;
	SizeLookup[0][5] = TreeType2;

	SizeLookup[1][0] = TreeType1;
	SizeLookup[1][1] = TreeType4;
	SizeLookup[1][2] = TreeType3;
	SizeLookup[1][3] = TreeType3;
	SizeLookup[1][4] = TreeType4;
	SizeLookup[1][5] = TreeType4;

	SizeLookup[2][0] = TreeType3;
	SizeLookup[2][1] = TreeType2;
	SizeLookup[2][2] = TreeType5;
	SizeLookup[2][3] = TreeType2;
	SizeLookup[2][4] = TreeType2;
	SizeLookup[2][5] = TreeType1;

	SizeLookup[3][0] = TreeType3;
	SizeLookup[3][1] = TreeType2;
	SizeLookup[3][2] = TreeType2;
	SizeLookup[3][3] = TreeType4;
	SizeLookup[3][4] = TreeType3;
	SizeLookup[3][5] = TreeType3;

	SizeLookup[4][0] = TreeType3;
	SizeLookup[4][1] = TreeType2;
	SizeLookup[4][2] = TreeType2;
	SizeLookup[4][3] = TreeType2;
	SizeLookup[4][4] = TreeType4;
	SizeLookup[4][5] = TreeType3;

	SizeLookup[5][0] = TreeType3;
	SizeLookup[5][1] = TreeType3;
	SizeLookup[5][2] = TreeType2;
	SizeLookup[5][3] = TreeType1;
	SizeLookup[5][4] = TreeType1;
	SizeLookup[5][5] = TreeType4;

	ListReader list;
	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	//GameMain* myGameMain = new GameMain();
	std::map<int, std::map< int, std::map<int, std::map<int, MonsterType*>>>> MonsterArray = GameMain::Monsters(myArray);
	if (MonsterArray[0][0][1][0] == nullptr)
	{
		std::cout << "NULLPTR? HOW?" << "\n";
	}

/*
	if (MonsterArray[0][0][1][0] = myArray[0])
	{
		std::cout << "Why is there a problem?";
	}*/
	//std::cout << myArray[0]->getPrimary() << "\n";
	//std::cout << MonsterArray[0][0][1][0]->getPrimary();
	bool result = true;
	int input;
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 1;  k < 5; k++)
			{
				for (int el = 0; el < SizeLookup[i][j][k]; el++)
				{
					//std::cout << "i:" << i << " j:" << j << " k: " << k << " el:" << el << "\n";

					if (count%5 == 4)
					{
						//std::cin >> input;
					}
					if (MonsterArray[i][j][k][el] != myArray[count])
					{
						std::cout << "count: " << count << "does not match\n";
						result = false;
					}
					count++;
					if (MonsterArray[i][j][k][el]->getPrimary() != i)
					{
						std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] primary Element mismatch. Actual: ";
						std::cout << MonsterArray[i][j][k][el]->getPrimary() << " Expected: " << i << "\n";
						result = false;
					}
					if (MonsterArray[i][j][k][el]->getSecondary() != j)
					{
						std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] Secondary Element mismatch. Actual: ";
						std::cout << MonsterArray[i][j][k][el]->getSecondary() << " Expected: " << j << "\n";
						result = false;
					}
					if (MonsterArray[i][j][k][el]->getEvolutionStage() != k)
					{
						std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] Evolution Stage mismatch. Actual: ";
						std::cout << MonsterArray[i][j][k][el]->getEvolutionStage() << " Expected: " << k << "\n";
						result = false;
					}
					if (MonsterArray[i][j][k][el]->getEvolutionType() != el)
					{
						std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] Evolution Type mismatch. Actual: ";
						std::cout << MonsterArray[i][j][k][el]->getEvolutionType() << " Expected: " << el << "\n";
						result = false;
					}
				}
			}
		}
	}
	if (result && !quiet)
	{
		std::cout << "Test Game Main 1: PASSED\n";
	}
	if (!result)
	{
		std::cout << "Test Game Main 1: FAILED\n";
	}
	return result;
}



/*
bool RPGTest::testGameMain1(bool quiet)
{
	try
	{
		GameMain* myGameMain = new GameMain();
		if (sizeof(myGameMain->MonsterArray) != 6)
		{
			//delete myGameMain;
			std::cout << "Bounds of first dimension of Monster array was: " << sizeof(myGameMain->MonsterArray) << " expected: 6\nGame Main Test 1: FAILED";
			delete myGameMain;
			return false;
		}
	}
	catch (int e)
	{
		std::cout << "Error number " << e << "\n";
		std::cout << "There is an error in the constructor of GameMain\n";
		std::cout << "Game Main test 1: FAILED\n";
		return false;
	}
	if (!quiet)
	{
		std::cout << "Game Main test 1: PASSED\n";
	}
	return true;
}

bool RPGTest::testGameMain2(bool quiet)
{
	try
	{
		bool result = true;
		GameMain* myGameMain = new GameMain();
		if (sizeof(myGameMain->MonsterArray) != 6)
		{
			//delete myGameMain;
			//std::cout << "Bounds of first dimension of Monster array was: " << sizeof(myGameMain->MonsterArray) << " expected: 6\nGame Main Test 1: FAILED";
			delete myGameMain;
			return false;
		}
		for (int i = 0; i < 6; i++)
		{
			if (sizeof(myGameMain->MonsterArray[i]) != 6)
			{
				std::cout << "Bounds of second dimension of Monster array dimension " << i << " was " << sizeof(myGameMain->MonsterArray[i]) << " expected: 6\n";
				result = false;
			}
		}
		if (result && !quiet)
		{
			std::cout << "Game Main test 2: PASSED\n";
		}
		delete myGameMain;
		return result;
	}
	catch (int e)
	{
		std::cout << "Error number " << e << "\n";
		std::cout << "There is an error in the constructor of GameMain\n";
		std::cout << "Game Main test 2: FAILED\n";
		return false;
	}
}

bool RPGTest::testGameMain3(bool quiet)
{
	try
	{
		if ((!testGameMain1(true)) || (!testGameMain2(true)))//if one or two fails we shouldn't even try 3
		{
			std::cout << "Game Main test 3: FAILED\n";
			return false;
		}
		GameMain* myGameMain = new GameMain();
		bool result = true;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (sizeof(myGameMain->MonsterArray[i][j]) != 5)
				{
					std::cout << "Bounds of third dimension of Monster Array for first index " << i << " second index " << j << " was " << sizeof(myGameMain->MonsterArray[i][j]) << " expected: 5\n";
					result = false;
				}
			}
		}
		if (result && !quiet)
		{
			std::cout << "Game Main test 3: PASSED\n";
		}

		if (!result)
		{
			std::cout << "Game Main test 4: FAILED\n";
		}
		return result;
	}
	catch (int e)
	{
		std::cout << "Error number " << e << "\n";
		std::cout << "There is an error in the constructor of GameMain\n";
		std::cout << "Game Main test 3: FAILED\n";
		return false;
	}
}

bool RPGTest::testGameMain4(bool quiet)
{
	try
	{
//		if (!(testGameMain1(true) && testGameMain2(true) && testGameMain3(true)))
//		{
//			std::cout << "Game Main test 4 failed\n";
//			return false;
//		}
		GameMain* myGameMain = new GameMain();
		int arrayLookup;
		bool result = true;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 1; k < 5; k++)
				{
					if (k == 1 && (i != 2) && (j != 2))
					{
						arrayLookup = 1;
					}
					else if (k == 1 && i == 2 && j == 2)
					{
						arrayLookup = 3;
					}
					else if ((i == 1 && j == 1) || (i == 2 && j == 5) || (i == 5 && j == 3) || (i == 5 && j == 4)
					{
						arrayLookup = 1;
					}
					for (int el = 0; el < arrayLookup; el++)
					{
						if (myGameMain->MonsterArray[i][j][k][el]->getPrimary() != i)
						{
							std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] primary Element mismatch. Actual: ";
							std::cout << myGameMain->MonsterArray[i][j][k][el]->getPrimary() << " Expected: " << i << "\n";
							result = false;
						}
						if (myGameMain->MonsterArray[i][j][k][el]->getSecondary() != j)
						{
							std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] Secondary Element mismatch. Actual: ";
							std::cout << myGameMain->MonsterArray[i][j][k][el]->getSecondary() << " Expected: " << j << "\n";
							result = false;
						}
						if (myGameMain->MonsterArray[i][j][k][el]->getEvolutionStage() != k)
						{
							std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] Evolution Stage mismatch. Actual: ";
							std::cout << myGameMain->MonsterArray[i][j][k][el]->getEvolutionStage() << " Expected: " << k << "\n";
							result = false;
						}
						if (myGameMain->MonsterArray[i][j][k][el]->getEvolutionType() != el)
						{
							std::cout << "MonsterArray[" << i << "][" << j << "][" << k << "][" << el << "] Evolution Type mismatch. Actual: ";
							std::cout << myGameMain->MonsterArray[i][j][k][el]->getEvolutionType() << " Expected: " << el << "\n";
						}
					}
				}
			}
		}

	}
	catch (int e)
	{
		std::cout << "Error number " << e << "\n";
		std::cout << "There is an error in the constructor of GameMain\n";
		std::cout << "Game Main test 3: FAILED\n";
		return false;
	}
}
*/