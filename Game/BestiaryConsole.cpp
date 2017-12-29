#include "BestiaryConsole.h"
#include <map>
#include "MonsterType.h"
#include "ListReader.h"

BestiaryConsole::BestiaryConsole()
{
}


BestiaryConsole::~BestiaryConsole()
{
}

void BestiaryConsole::run()
{	
	ListReader list;
	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	srand(time(NULL));

	bool exit = false;
	int choice;
	while (!exit)
	{
		std::cout << "Welcome To the Bestiary!\n";
		std::cout << "1) Find Monsters by Element\n";
		std::cout << "2) Look at random Monster\n";
		std::cout << "3) Look up Monster by index\n";
		std::cout << "4) Exit\n";
		try
		{
			std::cin >> choice;
			if (choice == 1)
			{
				BestiaryConsole::PrimaryElementMenu();
			}
			else if (choice == 2)
			{
				MonsterType* myptr = myArray[rand() % 319];
				MonsterView(myptr->getPrimary(), myptr->getSecondary(), myptr->getEvolutionStage(), myptr->getEvolutionType());
			}
			else if (choice == 3)
			{
				std::cout << "What is the index of the monster you want to look at?\n";
				std::cin >> choice;
				if (choice < 0 || choice>319)
				{
					std::cout << "sorry , improper bounds. Must be between  0 and 319\n";
					std::cout << "But well take you to 319 mod your number for stabilities' sake";
					choice = choice % 319;
				}
				MonsterType* myptr = myArray[choice % 319];
				MonsterView(myptr->getPrimary(), myptr->getSecondary(), myptr->getEvolutionStage(), myptr->getEvolutionType());
			}
			else if (choice == 4)
			{
				return;
			}
		}
		catch (int e)
		{
			std::cout << "Exception thrown. Exception number " << e << "\n";
		}
	}
}

void BestiaryConsole::PrimaryElementMenu()
{
	bool exit = false;
	int choice;
	while (!exit)
	{
		std::cout << "1) Fire\n";
		std::cout << "2) Water\n";
		std::cout << "3) Earth\n";
		std::cout << "4) Air\n";
		std::cout << "5) Light\n";
		std::cout << "6) Dark\n";
		std::cout << "7) Back\n";
		try
		{
			std::cin >> choice;
			std::cout << "Choice= " << choice << "\n";
			/*
			if (choice < 1 || choice>7)
			{
				std::cout << "invalid input\n";
				choice = ((choice - 1) % 6) + 1;
			}*/
/*			if (choice != 7)
			{
				SecondaryElementMenu(choice - 1);
			}*/
			if (choice == 1)
			{
				std::cout << "Got here";
				SecondaryElementMenu(0);
			}
			else if (choice == 2)
			{
				SecondaryElementMenu(1);
			}
			else if (choice == 3)
			{
				SecondaryElementMenu(2);
			}
			else if (choice == 4)
			{
				SecondaryElementMenu(3);
			}
			else if (choice == 5)
			{
				SecondaryElementMenu(4);
			}
			else if (choice == 6)
			{
				SecondaryElementMenu(5);
			}
			else
			{
				return;
			}
		}
		catch (int e)
		{
			std::cout << "Error Occured, Error number: " << e << "\n";
		}
	}
}

void BestiaryConsole::SecondaryElementMenu(int primary)
{
	bool exit = false;
	
	std::map<int, std::map<int, std::string>> typeNames = GameMain::SubElementNames();
	/*
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << typeNames[i][j] << "\n";
		}
	}*/
	int choice;
	//std::cout << "Did we get here?";
	while (!exit)
	{
		std::cout << "Primary= " << primary << "\n";
		std::cout << "1) " << typeNames[primary][0] << "\n";
		std::cout << "2) " << typeNames[primary][1] << "\n";
		std::cout << "3) " << typeNames[primary][2] << "\n";
		std::cout << "4) " << typeNames[primary][3] << "\n";
		std::cout << "5) " << typeNames[primary][4] << "\n";
		std::cout << "6) " << typeNames[primary][5] << "\n";
		std::cout << "7) return\n";
		try 
		{
			std::cin >> choice;
			if (choice == 1)
			{
				TreeView(primary, 0);
			}
			else if (choice == 2)
			{
				TreeView(primary, 1);
			}
			else if (choice == 3)
			{
				TreeView(primary, 2);
			}
			else if (choice == 4)
			{
				TreeView(primary, 3);
			}
			else if (choice == 5)
			{
				TreeView(primary, 4);
			}
			else if (choice == 6)
			{
				TreeView(primary, 5);
			}
			/*
			if (choice < 1 || choice>7)
			{
				std::cout << "invalid input\n";
				choice = ((choice - 1) % 6) + 1;
			}
			if (choice != 7)
			{
				TreeView(primary, choice);
			}
			else
			{
				return;
			}
			*/
		}
		catch (int e)
		{
			std::cout << "Error occured. Error number" << e << "\n";
		}
	}

}

void BestiaryConsole::TreeView(int primary, int secondary)
{
	std::map<int, std::map<int, std::string>> typeNames = GameMain::SubElementNames();
	std::map<int, std::map<int, std::map<int,int>>> TreeLookup = GameMain::numStagesLookup();
	int choice;
	ListReader list;
	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");

	std::map<int, std::map<int, std::map<int, std::map< int, MonsterType*>>>> Monsters = GameMain::Monsters(myArray);
	
	std::cout << "SubElement: " << typeNames[primary][secondary] << "\n";
	if (TreeLookup[primary][secondary][4] == 1)
	{
		std::cout << "Tree is Type 1, standard Line";
	}
	else if (TreeLookup[primary][secondary][4] == 2)
	{
		std::cout << "Tree is type 2, a two-pronged fork";
	}
	else if (TreeLookup[primary][secondary][4] == 3)
	{
		std::cout << "Tree is Type 3, a three-pronged fork";
	}
	else if (TreeLookup[primary][secondary][4] == 4)
	{
		std::cout << "Tree is Type 4";
	}
	else if (TreeLookup[primary][secondary][4] == 6)
	{
		std::cout << "Tree is Type 5";
	}
	int index = 1;
	std::map<int, int> stage;
	std::map<int, int> type;

	std::cout << "Infants:\n";
	for (int i = 0; i < TreeLookup[primary][secondary][1]; i++)
	{
		std::cout << index << ") " << Monsters[primary][secondary][1][i]->getName() << "\n";
		stage[index] = 1;
		type[index] = i;
		index++;
	}

	std::cout << "Adolescents:\n";
	for (int i = 0; i < TreeLookup[primary][secondary][2]; i++)
	{
		std::cout << index << ") " << Monsters[primary][secondary][2][i]->getName() << "\n";
		stage[index] = 2;
		type[index] = i;
		index++;
	}

	std::cout << "Adults:\n";
	for (int i = 0; i < TreeLookup[primary][secondary][3]; i++)
	{
		std::cout << index << ") " << Monsters[primary][secondary][3][i]->getName() << "\n";
		stage[index] = 3;
		type[index] = i;
		index++;
	}

	std::cout << "Elders:\n";
	for (int i = 0; i < TreeLookup[primary][secondary][4]; i++)
	{
		std::cout << index << ") " << Monsters[primary][secondary][4][i]->getName() << "\n";
		stage[index] = 4;
		type[index] = i;
		index++;
	}

	std::cout << index << ") Return";
	try
	{
		std::cin >> choice;
		if (choice <0 || choice>index)
		{
			choice = choice%index;
		}
		if (choice != index)
		{
			MonsterView(primary, secondary, stage[choice], type[choice]);//[primary][secondary][stage[choice]][type[choice]]
		}
		else
		{
			return;
		}
	}
	catch (int e)
	{
		std::cout << "Exception Thrown, number: " << e << "\n";
	}
}

void BestiaryConsole::MonsterView(int primary, int secondary, int stage, int type)
{
	std::map<int, std::string> ages;
	ages[0] = "Egg";
	ages[1] = "Infant";
	ages[2] = "Adolescent";
	ages[3] = "Adult";
	ages[4] = "Elder";
	int choice;
	ListReader list;
	MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	std::map<int, std::map<int, std::map<int, std::map<int, MonsterType*>>>> myMonsters = GameMain::Monsters(myArray);

	std::map<int, std::string> element = GameMain::ElementNames();
	std::map<int, std::map<int, std::string>> subElement = GameMain::SubElementNames();

	std::cout << "Type Name:         " << myMonsters[primary][secondary][stage][type]->getName() << "\n";
	std::cout << "Primary Element:   " << element[primary] << "\n";
	std::cout << "Secondary Element: " << element[secondary] << "\n";
	std::cout << "Derived Element:   " << subElement[primary][secondary] << "\n";
	std::cout << "Stage:             " << ages[stage] << "\n";
	std::cout << "Description:       " << myMonsters[primary][secondary][stage][type]->getDescription() << "\n";

	std::cout << "Ready to leave?";
	try
	{
		std::cin >> choice;
		return;

	}
	catch (int e)
	{
		std::cout << "Exception thrown, Exception number: " << e << "\n";
	}
}
