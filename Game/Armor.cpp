#include "Armor.h"



Armor::Armor()
{
  for (int i = 0; i < Damage::size; i++)
  {
    m_defense.content[i] = 0;
  }
  m_type = -1;
}


Armor::~Armor()
{
}

void Armor::makeGenericList()
{
	auto tierNames = RPGItem::TierNames();
	auto typeNames = Armor::ArmorTypeNames();
	auto textures = Armor::genericTextureLocations();
	auto values = RPGItem::tierValues();
	auto guide = Armor::guideLines();
	auto baseLevel = RPGItem::tierBaseLevel();
	auto description = Armor::ArmorDescriptions();
	auto damages = Armor::baseDamageReductionByTeir();
	std::cout << "Got here";
	std::ofstream myfile;
	myfile.open("Game/ContentFiles/Generic/GenericArmor.txt");
	if (myfile.is_open())
	{
		//myfile << "Writing this to a file\n";
		myfile << "72\n";//number of items in the file
		for (int i = 0; i < 6; i++)//writes each tier
		{
			for (int j = 0; j < 12; j++)//writes each type
			{
				if (j == 0 || j == 1 || j == 3 || j == 6 || j == 9)
				{
					myfile << tierNames[i][0] << " ";//writes the name of the teir, type metal
				}
				else if (j == 4 || j == 7 || j == 10)
				{
					myfile << tierNames[i][2] << " ";//writes the name of the tier, type leather
				}
				else
				{
					myfile << tierNames[i][3] << " ";//writes the name of the tier, type cloth
				}
				myfile << typeNames[j] << "\n";//writes the type of item
				myfile << (int)guide[j][0] << "\n";//writes the equiptype
				myfile << textures[j] << "\n";//writes the filepath to the texture
				myfile << ((int)(values[i] * guide[j][4])) << "\n";//writes the value of the item
				if (i == 0)
				{
					myfile << (int)guide[j][3] / 2 << "\n";
				}
				else
				{
					myfile << (int)(baseLevel[i] + guide[j][3]) << "\n";
				}
				myfile << description[i][j] << "\n";//writes the description of the item
				myfile << "6\n";//physical index
				myfile << (int)(damages[i] * guide[j][1]) << "\n";//writes the damage reduction
				myfile << "7\n";//magical index
				myfile << (int)(damages[i] * guide[j][2]) << "\n\n";
			}
		}
	}
	else
	{
		std::cout << "Myfile is not open";
	}
	myfile.close();
	return;
}

Damage Armor::getDefense()
{
  return m_defense;
}
int Armor::getType()
{
	return m_type;
}
int Armor::getRequiredLevel()
{
	return m_requiredLevel;
}

//setters
void Armor::setDefense(Damage defense)
{
  m_defense = defense;
}
void Armor::setType(int type)
{
	m_type = type;
}
void Armor::setRequiredLevel(int requiredLevel)
{
	m_requiredLevel = requiredLevel;
}

std::map<int, std::map<int, float>> Armor::guideLines()
{
	//The first index is the armor type
	//0:Plate 1:ChainMail 2:Robes 3:Greaves 4:Boots 5:Shoes
	//6:Helmet 7:Hood 8:Hat 9:Gauntlets 10:Bracers 11:Gloves

	//The second index  value=0 is the EquipType
	//0:Torso 1:Legs 2:Head 3:Hands
	//The second index value = 1 is the PMultiplier, which multiplies the base Physical defense 
	//of the tier by the value
	//The second index value = 2 is the MMultiplier,
	//The second index value = 3 is the levelOffset, how many levels after the teir is enabled the item is enabled
	//The second index value = 4 is the ValueMultiplier, how expensive the item is times the base

	std::map<int, std::map<int, float>> guide;
	guide[0][0] = 0;//Plates EquipType is chest
	guide[0][1] = (float)1.2;//Plates PMultiplier is 1.2
	guide[0][2] = 0;//Plates MMultiplier is 0
	guide[0][3] = 6;//Plates levelOffset is 6
	guide[0][4] = (float)1.5;//Plates Value is 1.5 times base
	guide[1][0] = 0;//chest
	guide[1][1] = (float).6;//pMultiplier
	guide[1][2] = (float).6;
	guide[1][3] = 4;
	guide[1][4] = (float)1.2;
	guide[2][0] = 0;//robes
	guide[2][1] = (float).3;
	guide[2][2] = (float)1.2;
	guide[2][3] = 4;
	guide[2][4] = (float)1.15;
	guide[3][0] = 1;//Greaves
	guide[3][1] = (float).95;
	guide[3][2] = (float).15;
	guide[3][3] = 3;
	guide[3][4] = (float).98;
	guide[4][0] = 1;//boots
	guide[4][1] = (float).55;
	guide[4][2] = (float).55;
	guide[4][3] = 2;
	guide[4][4] = (float).95;
	guide[5][0] = 1;//Shoes
	guide[5][1] = (float).2;
	guide[5][2] = 1;
	guide[5][3] = 1;
	guide[5][4] = (float).88;
	guide[6][0] = 2;//Helmet
	guide[6][1] = 1;
	guide[6][2] = 0;
	guide[6][3] = 3;
	guide[6][4] = (float)1.17;
	guide[7][0] = 2;//Hood
	guide[7][1] = (float).5;
	guide[7][2] = (float).5;
	guide[7][3] = 3;
	guide[7][4] = (float)1.07;
	guide[8][0] = 2;//Hat
	guide[8][1] = (float).1;
	guide[8][2] = (float).9;
	guide[8][3] = 3;
	guide[8][4] = (float)1.05;
	guide[9][0] = 3;//Gauntlets
	guide[9][1] = 1;
	guide[9][2] = 0;
	guide[9][3] = 4;
	guide[9][4] = (float).6;
	guide[10][0] = 3;//Bracers
	guide[10][1] = (float).5;
	guide[10][2] = (float).5;
	guide[10][3] = 3;
	guide[10][4] = (float).55;
	guide[11][0] = 3;//Gloves
	guide[11][1] = 0;
	guide[11][2] = 1;
	guide[11][3] = 2;
	guide[11][4] = (float).52;

	return guide;
}

std::map<int, std::string> Armor::ArmorTypeNames()
{
	//This map holds the name associated with each item type
	std::map<int, std::string> ItemNames;
	ItemNames[0] = "Plate";
	ItemNames[1] = "ChainMail";
	ItemNames[2] = "Robes";
	ItemNames[3] = "Greaves";
	ItemNames[4] = "Boots";
	ItemNames[5] = "Shoes";
	ItemNames[6] = "Helmet";
	ItemNames[7] = "Hood";
	ItemNames[8] = "Hat";
	ItemNames[9] = "Gauntlets";
	ItemNames[10] = "Bracers";
	ItemNames[11] = "Gloves";
	return ItemNames;
}

std::map<int, std::map<int, std::string>> Armor::ArmorDescriptions()
{
	//the first index is the tier eg 0=Rusted, scrapwood, etc
	//the second index is the ItemTypeName  0=Plate, 1=ChainMail etc
	std::map<int, std::map<int, std::string>> desc;
	desc[0][0] = "This worn plate hasn't been used in years, and rust has creeped into the edges, making it weak";
	desc[0][1] = "This old chainmail has rings missing and is showing signs of rust";
	desc[0][2] = "These old robes have holes in them. And stains too. Eww.";
	desc[0][3] = "These broken-down greaves have a clasp missing on the left side. And theyre really rusty.";
	desc[0][4] = "These boots leather has long since cracked away, leaving them weak.";
	desc[0][5] = "These shoes are loud and after wearing them for a while, your feet hurt.";
	desc[0][6] = "This rusted helmet has a hole in it, presumably from when a crossbow bolt went through it. Headshot!";
	desc[0][7] = "This hood is frayed in places. Whatever theif who used to own it must have fallen on really hard times";
	desc[0][8] = "For some reason, Wizards tend to wear very silly hats. The wizard who wore this hat clearly had lots of problems";
	desc[0][9] = "These gauntlets squeak and reduce the wrist mobility of the user, which could be fatal for the guy who wears them";
	desc[0][10] = "Someone must have left these leather bracers in water or something. They are messed UP.";
	desc[0][11] = "Why someone would bother wearing these gloves I have no idea. They are worn and scabby in places, as if someone bled on them";
	for (int i = 1; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			desc[i][j] = "Due to a lazy developer, this content has not been added yet";
		}
	}
	return desc;
}

std::map<int, std::string> Armor::genericTextureLocations()
{
	//The index corresponds to the Item Type
	//Plate=0 etc
	std::map<int, std::string> loc;
	loc[0] = "Game/ContentFiles/ItemTextures/PlateArmors.png";
	loc[1] = "Game/ContentFiles/ItemTextures/ChainMail.png";
	loc[2] = "Game/ContentFiles/ItemTextures/Robes.png";
	loc[3] = "Game/ContentFiles/ItemTextures/Greaves.png";
	loc[4] = "Game/ContentFiles/ItemTextures/Boots.png";
	loc[5] = "Game/ContentFiles/ItemTextures/Shoes.png";
	loc[6] = "Game/ContentFiles/ItemTextures/Helmets.png";
	loc[7] = "Game/ContentFiles/ItemTextures/Hoods.png";
	loc[8] = "Game/ContentFiles/ItemTextures/Hats.png";
	loc[9] = "Game/ContentFiles/ItemTextures/Gauntlets.png";
	loc[10] = "Game/ContentFiles/ItemTextures/Bracers.png";
	loc[11] = "Game/ContentFiles/ItemTextures/Gloves.png";
	return loc;
}

std::map<int, int> Armor::baseDamageReductionByTeir()
{
	std::map<int, int> base;
	base[0] = 3;//tier zero items (rusted, scrapwood, fur etc) save 3 damage
	base[1] = 6;
	base[2] = 14;
	base[3] = 20;
	base[4] = 30;
	base[5] = 50;
	return base;
}