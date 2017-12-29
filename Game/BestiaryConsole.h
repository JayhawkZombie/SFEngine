#ifndef BESTIARYCONSOLE
#define BESTIARYCONSOLE

#include "GameMain.h"
#include "MonsterType.h"
#include "ListReader.h"


#include <stdlib.h>  
#include <time.h>

#include <map>
class BestiaryConsole
{
public:
	BestiaryConsole();
	~BestiaryConsole();
	static void run();
	static void PrimaryElementMenu();
	static void SecondaryElementMenu(int primary);
	static void TreeView(int primary, int secondary);
	static void MonsterView(int primary, int secondary, int stage, int type);

};

#endif