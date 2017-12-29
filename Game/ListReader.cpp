#include "ListReader.h"
ListReader::ListReader() : num_monsters(0), num_armor(0), num_weapons(0), num_useables(0), num_convos(0),
monsters(NULL), armor(NULL), weapons(NULL), useables(NULL), conversations(NULL)
{}
ListReader::~ListReader()
{
	if (monsters != NULL)
  {
    for (int i = 0; i < num_monsters; i++)
    {
      delete monsters[i];
    }
    delete monsters;
    monsters = NULL;
  }
  //repeat for rest, not done
    
}
/***
Testing, ignore
//shared_ptr<MonsterType> ListReader::readMonsters(std::string &fileName)
//shared_ptr<MonsterType*> monsters(new MonsterType*)[num_monsters];
****/

//Reads in monsters from text file
//Passes all of the monsters to new instantiated classes and use pointers to point to them
//Passes all of the newly created monster objects to an array of pointers
//(Same logic for all classes)
MonsterType** ListReader::readMonsters(std::string fileName)
{
  //Declares the ifstream to read in the file from the string file name.
  std::ifstream file;
  file.open(fileName);
  //If the file isn't there, then print no file, and return NULL
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }

  //Reads in total number of monsters
  //Assumes the file size is on top of the text file's data
  file >> num_monsters;
  
  //Creation of monster array that will contain all of the monsters
  monsters = new MonsterType*[num_monsters];

  //Monster pointer for creation of new monster instances
  MonsterType* newMonster;

  //Curent index in monster array
  int index = 0;

  //Temporary types that will pass in data
  std::string line;
  int intVal;
  std::getline(file, line);

  //Main loop for passing in monster data
  //Assumes completed monster descriptions. (might break if they aren't?)
  //While the index is smaller (or equal to, since its index starts at 0) to the total number of monsters that's read in from the top of the file data
  while (index < num_monsters)
  {
    //Create new monster instance
    newMonster = new MonsterType;

    //Reading in data given how it looks like you're formatting the text files
 //   std::getline(file,line);
    std::getline(file,line);
    std::getline(file,line); //Gets the monster name here
    newMonster->setName(line); //Sets the monster name
    
    std::getline(file,line); //Gets the monster description
    newMonster->setDescription(line); //Sets the monster description
    
    file >> intVal; //Gets the primary element in integer form
    newMonster->setPrimary(intVal); //Sets the primary element

    file >> intVal; //Gets the secondary element
    newMonster->setSecondary(intVal); //Sets the secondary element

    file >> intVal; //Gets the evolution stage
    newMonster->setEvolutionStage(intVal); //Sets the evolution stage

    file >> intVal; //Gets the evolution type
    newMonster->setEvolutionType(intVal); //Sets the evolution type

    std::getline(file,line);
    std::getline(file,line); //Gets the texture
    newMonster->setTexture(line); //Sets the texture

    //Evolutions are not currently set because you mentioned it's not finished yet?
    std::getline(file,line); //Gets the Physical Evolution
    //newMonster->setPhysicalEvolution(line);

    std::getline(file,line); //Gets the Balanced Evolution
    //newMonster->setBalancedEvolution(line);

    std::getline(file,line); //Gets the Magical Evolution
    //newMonster->setMagicalEvolution(line);
    
    monsters[index] = newMonster; //Places the monster in the array
    index++; //Increment the index
  }
  file.close(); //Close the data text file
  return monsters; //Return the monster array
}
Armor** ListReader::readArmor(std::string fileName)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  //assumes the file size is on top of the data
  file >> num_armor;
  
  armor = new Armor*[num_armor];
  Armor* newArmor;
  
  Damage* damage;
  int index = 0;
  std::string line;
  int intIndex;
  int intVal;
  
  //accounting for whitespace on the end of the line
  std::regex integers("[[:digit:]]+");
  std::regex truespace("(true)");

  std::getline(file,line);
  while (index < num_armor)
  {
    newArmor = new Armor;

    std::getline(file,line);
    newArmor->setName(line);

    file >> intVal;
    newArmor->setType(intVal);

    std::getline(file,line);
    std::getline(file,line);
    newArmor->setTexture(line);

    file >> intVal;
    newArmor->setValue(intVal);

	//austins' mess up attempt to add a levelRequirement starts here
	file >> intVal;
	newArmor->setRequiredLevel(intVal);

	//and ends here

    std::getline(file,line);
    std::getline(file,line);
    newArmor->setDescription(line);
    
    std::getline(file,line);
    damage = new Damage;
    while ( std::regex_search (line,integers) )
    {  
      intIndex = stoi (line);
      std::getline(file,line);
      intVal = stoi (line);
      damage->setValue(intIndex,intVal);

      std::getline(file,line);
    }
    newArmor->setDefense(*damage);
    
    armor[index] = newArmor;
    index++;
  }

  file.close();
  return armor;  
}
Weapon** ListReader::readWeapons(std::string fileName)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  //assumes the file size is on top of the data
  file >> num_weapons;
  
//  std::cout << "NumWeapons: " << num_weapons << "\n";

  weapons = new Weapon*[num_weapons];
  Weapon* newWeapon;
  Damage* damage;

  int index = 0;
  std::string line;
  int intVal;
  int intIndex;

  //accounting for whitespace on the end of the line
  std::regex integers("[[:digit:]]+");
  std::regex truespace("(true)");

  std::getline(file,line);
  while (index < num_weapons)
  {
    newWeapon = new Weapon;

    std::getline(file,line);
    newWeapon->setName(line);
//	std::cout << "Name: " << line << "\n";
	std::getline(file, line);
	
//	try
//	{
		newWeapon->setNumHands(std::stoi(line));
//		std::cout << "NumHands: " << std::stoi(line) << "\n";
//	}
//	catch(int e)
//	{
//		std::cout << "error with stoi" << "\n";
//	}
	std::getline(file, line);
	newWeapon->setTexture(line);
//	std::cout << "Texture: " << line << "\n";

//	try
//	{
		std::getline(file, line);
		newWeapon->setValue(std::stoi(line));
//		std::cout << "Value: " << line << "\n";

		std::getline(file, line);
		newWeapon->setRequiredLevel(std::stoi(line));
//		std::cout << "RequiredLevel: " << line << "\n";
//	}
//	catch (int e)
//	{
		std::cout << "Error with stoi in ListReader readWeapons";
//	}

	std::getline(file, line);
	newWeapon->setDescription(line);
//	std::cout << "Description: " << line << "\n";



	/*
    file >> intVal;
    newWeapon->setValue(intVal);

    std::getline(file,line);  
    std::getline(file,line);
    newWeapon->setDescription(line);  

    std::getline(file,line);
    newWeapon->setTexture(line);
    */
    std::getline(file,line);
    damage = new Damage;
	
    while ( std::regex_search (line,integers) )
    {  
		//std::getline(file, line);
      intIndex = stoi (line);
      std::getline(file,line);
//	  try
//	  {
		  intVal = stoi(line);
		  damage->setValue(intIndex, intVal);
	//	  std::cout << "Damage set Index:" << intIndex << " Value " << intVal << "\n";
//	  }
//	  catch (int e)
//	  {
//		  std::cout << "Exeption thrown number " << e << "\n";

//	  }
      std::getline(file,line);
    }
    newWeapon->setAddedDamage(*damage);

    if ( std::regex_search (line,truespace) )
    {
      newWeapon->setRightHand(true);
    }
   // std::getline(file,line);
    if ( std::regex_search (line,truespace) )
    {
      newWeapon->setLeftHand(true);
    }
	//std::getline(file, line);
    
    
    weapons[index] = newWeapon;
    index++;
  }
  file.close();
  return weapons;  
}
Useable** ListReader::readUseables(std::string fileName)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  //assumes the file size is on top of the data
  file >> num_useables;
  
  useables = new Useable*[num_useables];
  Useable* newUseable;
  Damage* damage;

  int index = 0;
  std::string line;
  int intVal;
  int intIndex;
	
  std::getline(file,line);
  std::getline(file,line);
  //accounting for whitespace on the end of the line
  std::regex integers("[[:digit:]]+");
  std::regex truespace("(true)");

  while (index < num_useables)
  {
    newUseable = new Useable;

    newUseable->setName(line);
	  
    std::getline(file,line);
    newUseable->setTexture(line);
	  
    file >> intVal;
    newUseable->setValue(intVal);

    std::getline(file,line);
    std::getline(file,line);
    newUseable->setDescription(line);

    std::getline(file,line);

    damage = new Damage;
    while ( std::regex_search (line,integers) )
    {  
      intIndex = stoi (line);
      std::getline(file,line);
      intVal = stoi (line);
      damage->setValue(intIndex,intVal);

      std::getline(file,line);
    }
    newUseable->setDamage(*damage);

    useables[index] = newUseable;
    index++;
  }
  file.close();
  return useables;  
}
Conversation** ListReader::readConversation(std::string fileName, MainCharacter mchar)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  int index = 0;
  std::string line;
  int intVal;
  int intIndex;
  int intChoices;
  std::string name;
  std::getline(file, name);
  file >> num_convos;
  conversations = new Conversation*[num_convos];
  Conversation* newConversation;
  std::regex integers("[[:digit:]]+");
  //  MainCharacter* newCharacter = new MainCharacter;
  std::getline(file, line);
  while (index < num_convos)
  {
    newConversation = new Conversation;

    newConversation->setUserID(name);
    std::getline(file, line);
    std::getline(file, line);
    //if conversationID doesn't match any previous conversation ID
    newConversation->setConvoID(line);
    std::getline(file, line);
	newConversation->setContent(line);
	file >> intChoices;
	if (intChoices == 0)
	{
		file >> intChoices;
		newConversation->setExitStatus(intChoices);
		std::getline(file, line);
	}
	else
	{
		newConversation->setNumChoices(intChoices);
		std::getline(file, line);
		for (int i = 0; i < intChoices; i++)
		{
			std::getline(file, line);
			newConversation->setConvoNodesContent(line);
			std::getline(file, line);
			while (std::regex_search(line, integers))
			{
				intIndex = stoi(line);
				std::getline(file, line);
				intVal = stoi(line);
				//MC->setValue(intIndex, intVal);
				std::getline(file, line);
			}
			newConversation->setConvoNodes(line);
		}
	}

    conversations[index] = newConversation;
    index++;
  }

  file.close();
  return conversations;
}
//MENU 
int ListReader::menu()
{
  //if readConversations("") hasn't been declared with a working text file, exit
  if (conversations == NULL)
  {
    std::cout << "NO CONVERSATIONS PASSED IN. EXITING. RETURNING -1\n";
    return -1;
  }
  //variables
  int menuChoice = 0; //user input
  int current = 0; //current conversation node
  int previous = 0; //previous conversation node
  bool Out = true; //exit condition, if menuChoice = 999 then exit
  //main loop
  while (Out)
  {
    //prints out the current conversation node
    std::cout << "\nEnter 999 to Exit";
    std::cout << "\nConversation with: " << conversations[current]->getUserID();
    std::cout << "\nConversation Node ID: " << conversations[current]->getConvoID();
    std::cout << "\nNumber of responses: " << conversations[current]->getNumChoices();

    if (conversations[current]->getNumChoices() == 0)
    {
      std::cout << "\nReturning exit status: " << conversations[current]->getExitStatus();
      return conversations[current]->getExitStatus();
    }
    //checks/prints the conversation node's choices
    for (int k = 0; k < conversations[current]->getNumChoices(); k++)
    {
      std::cout << "\nChoice " << k << ": " << conversations[current]->getConvoNodes(k);
      std::cout << "\n\t" << conversations[current]->getConvoNodesContent(k);
    }
    //allowing user input to go to the next node
    std::cout << "\nChoose a number: (start at 0, 999 is exit, -1 is previous): ";
    std::cin >> menuChoice;
    //repeating the steps above but with the previous conversation node
    if (menuChoice == -1)
    {
      current = previous;
      std::cout << "\nConversation with: " << conversations[current]->getUserID();
      std::cout << "\nConversation Node ID: " << conversations[current]->getConvoID();
      std::cout << "\nNumber of responses: " << conversations[current]->getNumChoices();
      
      for (int k = 0; k < conversations[current]->getNumChoices(); k++)
      {
        std::cout << "\nChoice " << k << ": " << conversations[current]->getConvoNodes(k);
        std::cout << "\n\t" << conversations[current]->getConvoNodesContent(k);
      }
      std::cout << "\nChoose a number: (start at 0, 999 is exit, previous is unreachable): ";
      std::cin >> menuChoice;
    }
    //break loop
    if (menuChoice == 999)
    {
      Out = false;
      break;
    }

    /***
    Testing, ignore
    //  std::cout << conversations[1]->getConvoID(); //sleepingReponse
    //   std::cout << conversations[0]->getConvoNodes(0); //no, tell him i'm sleeping
    ****/

    //switches to the new conversation node to be read in
    for (int k = 0; k < num_convos; k++)
    {
      //basically say you chose sleepingResponse in the previous section
      //then sleepingResponse (its own ID, with its own possible responses) == sleepingResponse (its ID in the current conversation's possible choices)
      //and switches the conversation node/tree
      if (conversations[k]->getConvoID() == conversations[current]->getConvoNodes(menuChoice))
      {
        //sets the previous to the current before switching to the new conversation node
        previous = current;
        current = k;
        std::cout << "\nYou chose: " << conversations[current]->getConvoID();
        std::cout << "\n\t" << conversations[current]->getContent();
        break;
      }
    } //end for
  } //end while
  return 0;
}

//Return number of items in arrays
const int ListReader::getNumConversations()
{
  return num_convos;
}
const int ListReader::getNumMonsters()
{
  return num_monsters;
}  
int ListReader::getNumArmor()const
{
  return num_armor;
}
const int ListReader::getNumWeapons()
{
  return num_weapons;
}
const int ListReader::getNumUseables()
{
  return num_useables;
}
/*
=======
#include "ListReader.h"
ListReader::ListReader() : num_monsters(0), num_armor(0), num_weapons(0), num_useables(0), num_convos(0),
monsters(NULL), armor(NULL), weapons(NULL), useables(NULL), conversations(NULL)
{}
ListReader::~ListReader()
{
	if (monsters != NULL)
  {
    for (int i = 0; i < num_monsters; i++)
    {
      delete monsters[i];
    }
    delete monsters;
    monsters = NULL;
  }
  //repeat for rest, not done
    
}
/***
Testing, ignore
//shared_ptr<MonsterType> ListReader::readMonsters(std::string &fileName)
//shared_ptr<MonsterType*> monsters(new MonsterType*)[num_monsters];
****/

//Reads in monsters from text file
//Passes all of the monsters to new instantiated classes and use pointers to point to them
//Passes all of the newly created monster objects to an array of pointers
//(Same logic for all classes)
/*
MonsterType** ListReader::readMonsters(std::string fileName)
{
  //Declares the ifstream to read in the file from the string file name.
  std::ifstream file;
  file.open(fileName);
  //If the file isn't there, then print no file, and return NULL
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }

  //Reads in total number of monsters
  //Assumes the file size is on top of the text file's data
  file >> num_monsters;
  
  //Creation of monster array that will contain all of the monsters
  monsters = new MonsterType*[num_monsters];

  //Monster pointer for creation of new monster instances
  MonsterType* newMonster;

  //Curent index in monster array
  int index = 0;

  //Temporary types that will pass in data
  std::string line;
  int intVal;

  //Main loop for passing in monster data
  //Assumes completed monster descriptions. (might break if they aren't?)
  //While the index is smaller (or equal to, since its index starts at 0) to the total number of monsters that's read in from the top of the file data
  while (index < num_monsters)
  {
    //Create new monster instance
    newMonster = new MonsterType;

    //Reading in data given how it looks like you're formatting the text files
    std::getline(file,line);
    std::getline(file,line);
    std::getline(file,line); //Gets the monster name here
    newMonster->setName(line); //Sets the monster name
    
    std::getline(file,line); //Gets the monster description
    newMonster->setDescription(line); //Sets the monster description
    
    file >> intVal; //Gets the primary element in integer form
    newMonster->setPrimary(intVal); //Sets the primary element

    file >> intVal; //Gets the secondary element
    newMonster->setSecondary(intVal); //Sets the secondary element

    file >> intVal; //Gets the evolution stage
    newMonster->setEvolutionStage(intVal); //Sets the evolution stage

    file >> intVal; //Gets the evolution type
    newMonster->setEvolutionType(intVal); //Sets the evolution type

    std::getline(file,line);
    std::getline(file,line); //Gets the texture
    newMonster->setTexture(line); //Sets the texture

    //Evolutions are not currently set because you mentioned it's not finished yet?
    std::getline(file,line); //Gets the Physical Evolution
    //newMonster->setPhysicalEvolution(line);

    std::getline(file,line); //Gets the Balanced Evolution
    //newMonster->setBalancedEvolution(line);

    std::getline(file,line); //Gets the Magical Evolution
    //newMonster->setMagicalEvolution(line);
    
    monsters[index] = newMonster; //Places the monster in the array
    index++; //Increment the index
  }
  file.close(); //Close the data text file
  return monsters; //Return the monster array
}
Armor** ListReader::readArmor(std::string fileName)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  //assumes the file size is on top of the data
  file >> num_armor;
  
  armor = new Armor*[num_armor];
  Armor* newArmor;
  
  Damage* damage;
  int index = 0;
  std::string line;
  int intIndex;
  int intVal;
  
  //accounting for whitespace on the end of the line
  std::regex integers("[[:digit:]]+");
  std::regex truespace("(true)");

  std::getline(file,line);
  while (index < num_armor)
  {
    newArmor = new Armor;

    std::getline(file,line);
    newArmor->setName(line);

    file >> intVal;
    newArmor->setType(intVal);

    std::getline(file,line);
    std::getline(file,line);
    newArmor->setTexture(line);

    file >> intVal;
    newArmor->setValue(intVal);

    std::getline(file,line);
    std::getline(file,line);
    newArmor->setDescription(line);
    
    std::getline(file,line);
    damage = new Damage;
    while ( std::regex_search (line,integers) )
    {  
      intIndex = stoi (line);
      std::getline(file,line);
      intVal = stoi (line);
      damage->setValue(intIndex,intVal);

      std::getline(file,line);
    }
    newArmor->setDefense(*damage);
    
    armor[index] = newArmor;
    index++;
  }

  file.close();
  return armor;  
}
Weapon** ListReader::readWeapons(std::string fileName)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  //assumes the file size is on top of the data
  file >> num_weapons;
  
  weapons = new Weapon*[num_weapons];
  Weapon* newWeapon;
  Damage* damage;

  int index = 0;
  std::string line;
  int intVal;
  int intIndex;

  //accounting for whitespace on the end of the line
  std::regex integers("[[:digit:]]+");
  std::regex truespace("(true)");

  std::getline(file,line);
  while (index < num_weapons)
  {
    newWeapon = new Weapon;

    std::getline(file,line);
    newWeapon->setName(line);

    file >> intVal;
    newWeapon->setValue(intVal);

    std::getline(file,line);  
    std::getline(file,line);
    newWeapon->setDescription(line);  

    std::getline(file,line);
    newWeapon->setTexture(line);
    
    std::getline(file,line);
    damage = new Damage;
    while ( std::regex_search (line,integers) )
    {  
      intIndex = stoi (line);
      std::getline(file,line);
      intVal = stoi (line);
      damage->setValue(intIndex,intVal);

      std::getline(file,line);
    }
    newWeapon->setAddedDamage(*damage);

    if ( std::regex_search (line,truespace) )
    {
      newWeapon->setRightHand(true);
    }
    std::getline(file,line);
    if ( std::regex_search (line,truespace) )
    {
      newWeapon->setLeftHand(true);
    }
    
    
    weapons[index] = newWeapon;
    index++;
  }
  file.close();
  return weapons;  
}
Useable** ListReader::readUseables(std::string fileName)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  //assumes the file size is on top of the data
  file >> num_useables;
  
  useables = new Useable*[num_useables];
  Useable* newUseable;
  Damage* damage;

  int index = 0;
  std::string line;
  int intVal;
  int intIndex;

  //accounting for whitespace on the end of the line
  std::regex integers("[[:digit:]]+");
  std::regex truespace("(true)");

  while (index < num_useables)
  {
    newUseable = new Useable;

    std::getline(file,line);
    newUseable->setName(line);

    file >> intVal;
    newUseable->setValue(intVal);

    std::getline(file,line);
    std::getline(file,line);
    newUseable->setDescription(line);

    std::getline(file,line);
    newUseable->setTexture(line);
    
    std::getline(file,line);

    damage = new Damage;
    while ( std::regex_search (line,integers) )
    {  
      intIndex = stoi (line);
      std::getline(file,line);
      intVal = stoi (line);
      damage->setValue(intIndex,intVal);

      std::getline(file,line);
    }
    newUseable->setDamage(*damage);

    useables[index] = newUseable;
    index++;
  }
  file.close();
  return useables;  
}
Conversation** ListReader::readConversation(std::string fileName, MainCharacter mchar)
{
  std::ifstream file;
  file.open(fileName);
  if (!file.is_open())
  {
    std::cout << "No file\n";
    return NULL;
  }
  int index = 0;
  std::string line;
  int intVal;
  int intIndex;
  int intChoices;
  std::string name;
  std::getline(file, name);
  file >> num_convos;
  conversations = new Conversation*[num_convos];
  Conversation* newConversation;
  std::regex integers("[[:digit:]]+");
  //  MainCharacter* newCharacter = new MainCharacter;
  std::getline(file, line);
  while (index < num_convos)
  {
    newConversation = new Conversation;

    newConversation->setUserID(name);
    std::getline(file, line);
    std::getline(file, line);
    //if conversationID doesn't match any previous conversation ID
    newConversation->setConvoID(line);
    std::getline(file, line);
	newConversation->setContent(line);
	file >> intChoices;
	if (intChoices == 0)
	{
		file >> intChoices;
		newConversation->setExitStatus(intChoices);
		std::getline(file, line);
	}
	else
	{
		newConversation->setNumChoices(intChoices);
		std::getline(file, line);
		for (int i = 0; i < intChoices; i++)
		{
			std::getline(file, line);
			newConversation->setConvoNodesContent(line);
			std::getline(file, line);
			while (std::regex_search(line, integers))
			{
				intIndex = stoi(line);
				std::getline(file, line);
				intVal = stoi(line);
				//MC->setValue(intIndex, intVal);
				std::getline(file, line);
			}
			newConversation->setConvoNodes(line);
		}
	}

    conversations[index] = newConversation;
    index++;
  }

  file.close();
  return conversations;
}
//MENU 
int ListReader::menu()
{
  //if readConversations("") hasn't been declared with a working text file, exit
  if (conversations == NULL)
  {
    std::cout << "NO CONVERSATIONS PASSED IN. EXITING. RETURNING -1\n";
    return -1;
  }
  //variables
  int menuChoice = 0; //user input
  int current = 0; //current conversation node
  int previous = 0; //previous conversation node
  bool Out = true; //exit condition, if menuChoice = 999 then exit
  //main loop
  while (Out)
  {
    //prints out the current conversation node
    std::cout << "\nEnter 999 to Exit";
    std::cout << "\nConversation with: " << conversations[current]->getUserID();
    std::cout << "\nConversation Node ID: " << conversations[current]->getConvoID();
    std::cout << "\nNumber of responses: " << conversations[current]->getNumChoices();

    if (conversations[current]->getNumChoices() == 0)
    {
      std::cout << "\nReturning exit status: " << conversations[current]->getExitStatus();
      return conversations[current]->getExitStatus();
    }
    //checks/prints the conversation node's choices
    for (int k = 0; k < conversations[current]->getNumChoices(); k++)
    {
      std::cout << "\nChoice " << k << ": " << conversations[current]->getConvoNodes(k);
      std::cout << "\n\t" << conversations[current]->getConvoNodesContent(k);
    }
    //allowing user input to go to the next node
    std::cout << "\nChoose a number: (start at 0, 999 is exit, -1 is previous): ";
    std::cin >> menuChoice;
    //repeating the steps above but with the previous conversation node
    if (menuChoice == -1)
    {
      current = previous;
      std::cout << "\nConversation with: " << conversations[current]->getUserID();
      std::cout << "\nConversation Node ID: " << conversations[current]->getConvoID();
      std::cout << "\nNumber of responses: " << conversations[current]->getNumChoices();
      
      for (int k = 0; k < conversations[current]->getNumChoices(); k++)
      {
        std::cout << "\nChoice " << k << ": " << conversations[current]->getConvoNodes(k);
        std::cout << "\n\t" << conversations[current]->getConvoNodesContent(k);
      }
      std::cout << "\nChoose a number: (start at 0, 999 is exit, previous is unreachable): ";
      std::cin >> menuChoice;
    }
    //break loop
    if (menuChoice == 999)
    {
      Out = false;
      break;
    }

    /***
    Testing, ignore
    //  std::cout << conversations[1]->getConvoID(); //sleepingReponse
    //   std::cout << conversations[0]->getConvoNodes(0); //no, tell him i'm sleeping
    ****/

    //switches to the new conversation node to be read in
    /*
    for (int k = 0; k < num_convos; k++)
    {
      //basically say you chose sleepingResponse in the previous section
      //then sleepingResponse (its own ID, with its own possible responses) == sleepingResponse (its ID in the current conversation's possible choices)
      //and switches the conversation node/tree
      if (conversations[k]->getConvoID() == conversations[current]->getConvoNodes(menuChoice))
      {
        //sets the previous to the current before switching to the new conversation node
        previous = current;
        current = k;
        std::cout << "\nYou chose: " << conversations[current]->getConvoID();
        std::cout << "\n\t" << conversations[current]->getContent();
        break;
      }
    } //end for
  } //end while
  return 0;
}

//Return number of items in arrays
const int ListReader::getNumConversations()
{
  return num_convos;
}
const int ListReader::getNumMonsters()
{
  return num_monsters;
}  
int ListReader::getNumArmor()const
{
  return num_armor;
}
const int ListReader::getNumWeapons()
{
  return num_weapons;
}
const int ListReader::getNumUseables()
{
  return num_useables;
}
>>>>>>> 4ca3795773366637aca7b6630fc6700985923c04
*/
//>>>>>>> game
