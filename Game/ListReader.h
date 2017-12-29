#ifndef ListReader_H
#define ListReader_H

//all of the things for list reader to read in
#include "MonsterType.h"
#include "Armor.h"
#include "Weapon.h"
#include "Useable.h"
#include "Conversation.h"
#include "MainCharacter.h"

//extra libraries for reading in the text files or seperating functions
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <regex>
#include <memory> //wanted to use smart pointers but doesn't seem like it's a good idea for this class

/*
  Creates objects as new instantiated classes and
  Passes all of the objects as pointers to an array
  Returns the array
*/
class ListReader{
  public:
    //instantiates all of the arrays to NULL and number of objects to 0
    ListReader();

    //delete in progress
    ~ListReader();

    /****
    In testing, ignore
    //reads in the file and fills in an array
    //returns the array
    //shared_ptr<MonsterType> readMonsters(std::string &fileName);
    ****/

    //reads in all of the file names from a string, reads the file, and passes back an array
    MonsterType** readMonsters(std::string fileName);
    Armor** readArmor(std::string fileName);
    Weapon** readWeapons(std::string fileName);    
    Useable** readUseables(std::string fileName);
    Conversation** readConversation(std::string fileName, MainCharacter mchar);
    //pass back an integer once a conversation is read
    int menu();
  
    //returns the number given on top of the file
    //assumes it's the proper number of objects given
    const int getNumMonsters();
    int getNumArmor() const;
    const int getNumWeapons();
    const int getNumUseables();
    const int getNumConversations();

  private:
    //number of objects
    int num_monsters;
    int num_armor;
    int num_weapons;
    int num_useables;
    int num_convos;

    //arrays of objects
    //double pointer because it's a new array instance that contains a list of pointers
    MonsterType** monsters;
    Armor** armor;
    Weapon** weapons;
    Useable** useables;
    Conversation** conversations;
};
#endif
