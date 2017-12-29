#ifndef RPG_TEST_H
#define RPG_TEST_H

#include "Armor.h"
#include "RPGActor.h"
#include "RPGItem.h"
#include "Damage.h"
#include "Tile.h"
#include "Weapon.h"
#include "MonsterType.h"
#include "Useable.h"
#include "Skill.h"
#include "Inventory.h"
#include "MainCharacter.h"
#include "GameMain.h"
#include "ListReader.h"
#include <map>
#include <iostream>
class RPGTest
{
public:
	RPGTest();
	~RPGTest();
	//method that runs the tests
	static void runTests(bool quiet);

	//RPGActor Tests
	static bool testRPGActor1(bool quiet);
	static bool testRPGActor2(bool quiet);

	//RPGItem Tests
	static bool testRPGItem1(bool quiet);
	static bool testRPGItem2(bool quiet);
	static bool testRPGItem3(bool quiet);
	static bool testRPGItem4(bool quiet);
	static bool testRPGItem5(bool quiet);

	//Tile Tests
	static bool testTile1(bool quiet);
	static bool testTile2(bool quiet);
	static bool testTile3(bool quiet);
	static bool testTile4(bool quiet);
	static bool testTile5(bool quiet);
	static bool testTile6(bool quiet);
	
	//Damage Tests
	static bool testDamage1(bool quiet);
	static bool testDamage2(bool quiet);
    
	//Armor Tests
    
	//Weapon Tests
	static bool testWeapon1(bool quiet);
    static bool testWeapon2(bool quiet);
    static bool testWeapon3(bool quiet);
    static bool testWeapon4(bool quiet);

	//MonsterType Tests (unfinished)
    static bool testMonsterType1(bool quiet);

	//UseableTests
	static bool testUseable1(bool quiet);
    static bool testUseable2(bool quiet);

	//Skill tests
    static bool testSkill1(bool quiet);

	//Inventory tests
	static bool testInventory1(bool quiet);

	//MainCharactertests
	static bool testMainCharacter1(bool quiet);

	//GameMainTests
	static bool testGameMain1(bool quiet);
	//static bool testGameMain2(bool quiet);
	//static bool testGameMain3(bool quiet);
	//static bool testGameMain4(bool quiet);

};
#endif
