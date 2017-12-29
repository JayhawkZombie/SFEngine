#include "Weapon.h"



Weapon::Weapon()
{
  for (int i = 0; i < Damage::size; i++)
  {
    m_addedDamage.content[i] = 0;
  }
  m_rightHand = true;
  m_leftHand = false;
}


Weapon::~Weapon()
{
}

Damage Weapon::getAddedDamage()
{
  return m_addedDamage;
}

bool Weapon::getRightHand()
{
  return m_rightHand;
}

bool Weapon::getLeftHand()
{
  return m_leftHand;
}

int Weapon::getNumHands()
{
	return m_numHands;
}

int Weapon::getRequiredLevel()
{
	return m_requiredLevel;
}

void Weapon::setNumHands(int hands)
{
	m_numHands = hands;
}

void Weapon::setRequiredLevel(int level)
{
	m_requiredLevel = level;
}

void Weapon::setAddedDamage(Damage addedDamage)
{
  m_addedDamage = addedDamage;
}

void Weapon::setRightHand(bool rightHand)
{
  m_rightHand = rightHand;
}

void Weapon::setLeftHand(bool leftHand)
{
  m_leftHand = leftHand;
}

void Weapon::makeGenericWeaponList()
{
	auto tierNames = RPGItem::TierNames();
	auto typeNames = Weapon::WeaponTypeNames();
	auto textures = Weapon::WeaponTextureLocations();
	auto values = RPGItem::tierValues();
	auto guide = Weapon::WeaponGuideLines();
	auto baseLevel = RPGItem::tierBaseLevel();
	auto description = Weapon::WeaponDescriptions();
	auto damages = Weapon::BaseDamageByTier();

	std::ofstream myfile;
	myfile.open("Game/ContentFiles/Generic/GenericWeapons.txt");
	if (myfile.is_open())
	{
		myfile << "78\n";
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (j >= 0 && j <= 6)//this block types out the teir of the item
				{
					myfile << tierNames[i][0] << " ";//writes the name of the teir, type metal
				}
				else if (j == 8 || j == 11 || j == 12 || j == 10)
				{
					myfile << tierNames[i][1] << " ";//writes the name of the tier type wood
				}
				else if (j == 9)
				{
					myfile << tierNames[i][4] << " ";//writes out the name of the tier type glass
				}
				else
				{
					myfile << tierNames[i][5] << " ";//type tome
				}
				myfile << typeNames[j] << "\n";//writes the type of the item
				myfile << guide[j][2] << "\n";//how many hands
				myfile << textures[j] << "\n";//writes the filePath to the texture
				myfile << ((int)(values[i] * guide[j][4])) << "\n";//prints the value
				if (i == 0)//this else-if blcok types out the level requirement
				{
					myfile << (int)guide[j][3] / 2 << "\n";
				}
				else
				{
					myfile << (int)(baseLevel[i] + guide[j][3]) << "\n";
				}
				myfile << description[i][j] << "\n";//writes the description of the item
				myfile << "6\n";//physical index
				myfile << (int)(damages[i] * guide[j][0]) << "\n";
				myfile << "7\n";//magical index
				myfile << (int)(damages[i] * guide[j][1]) << "\n\n";

			}
		}
	}
	else
	{
		std::cout << "Error opening file\n";
	}

}

std::map<int, std::string> Weapon::WeaponTypeNames()
{
	//The index represents the position in the array of the Item and its name
	std::map<int, std::string> names;
	names[0] = "Dagger";
	names[1] = "Shortsword";
	names[2] = "Hatchet";
	names[3] = "Longsword";
	names[4] = "Maul";
	names[5] = "BattleAxe";
	names[6] = "Claymore";
	names[7] = "Tome";
	names[8] = "Wand";
	names[9] = "Orb";
	names[10] = "Staff";
	names[11] = "Longbow";
	names[12] = "Crossbow";
	return names;
}

std::map<int, std::map<int, float>> Weapon::WeaponGuideLines()
{
	//The first index is the weapontype, 0:dagger, 1:shortsword, 2:Hatchet etc
	//The second index is the kind of information about that weapon type
	//[][0] = Physical Damage Multiplier
	//[][1] = Magic Damage Multiplier
	//[][2] = How many hands (1 or 2)
	//[][3] = Minimum level offset
	//[][4] = Base Value multiplier
	std::map<int, std::map<int, float>> guide;
	guide[0][0] = (float).7;//daggers have a physical damage multipler of .7, they do 70% of normal damage
	guide[0][1] = 0; // daggers do not do magical damage
	guide[0][2] = 1; //daggers are one-handed
	guide[0][3] = 0; //daggers level is not offset
	guide[0][4] = (float).8;//Daggers are worth .8 the base amount for their tier
	guide[1][0] = (float).85;//ShortSwords
	guide[1][1] = 0;
	guide[1][2] = 1;
	guide[1][3] = 3;
	guide[1][4] = (float).9;
	guide[2][0] = 1;//hatchets
	guide[2][1] = 0;
	guide[2][2] = 1;
	guide[2][3] = 5;
	guide[2][4] = 1;
	guide[3][0] = (float)1.05;//longswords
	guide[3][1] = 0;
	guide[3][2] = 1;
	guide[3][3] = 7;
	guide[3][4] = (float)1.2;
	guide[4][0] = (float)1.1;
	guide[4][1] = 0;
	guide[4][2] = 2;
	guide[4][3] = 2;
	guide[4][4] = 1;
	guide[5][0] = (float)1.15;//BattleAxe
	guide[5][1] = 0;
	guide[5][2] = 2;
	guide[5][3] = 4;
	guide[5][4] = (float)1.15;
	guide[6][0] = (float)1.2;//Claymore
	guide[6][1] = 0;
	guide[6][2] = 2;
	guide[6][3] = 6;
	guide[6][4] = (float)1.25;
	guide[7][0] = 0;//Tome
	guide[7][1] = 1;
	guide[7][2] = 1;
	guide[7][3] = 0;
	guide[7][4] = (float).95;
	guide[8][0] = (float).1;//wands
	guide[8][1] = (float).95;
	guide[8][2] = 1;
	guide[8][3] = 3;
	guide[8][4] = (float)1.07;
	guide[9][0] = (float).1;
	guide[9][1] = (float)1.05;
	guide[9][2] = 1;
	guide[9][3] = 6;
	guide[9][4] = (float)1.27;
	guide[10][0] = (float).25;
	guide[10][1] = (float)1.2;
	guide[10][2] = 2;
	guide[10][3] = 8;
	guide[10][4] = (float)1.34;
	guide[11][0] = 1;
	guide[11][1] = (float).1;
	guide[11][2] = 2;
	guide[11][3] = 2;
	guide[11][4] = (float)1.13;
	guide[12][0] = (float)1.2;
	guide[12][1] = (float).05;
	guide[12][2] = 2;
	guide[12][3] = 5;
	guide[12][4] = (float)1.23;
	return guide;
}

std::map<int, int> Weapon::BaseDamageByTier()
{
	std::map<int, int> damage;
	damage[0] = 8;
	damage[1] = 16;
	damage[2] = 34;
	damage[3] = 55;
	damage[4] = 75;
	damage[5] = 105;
	return damage;
}

std::map<int, std::map<int, std::string>> Weapon::WeaponDescriptions()
{
	//the first index is the teir, the second is the item type
	std::map<int, std::map<int, std::string>> descriptions;
	for (int i = 0; i < 6; i++)//inserts a message in all indeces
	{
		for (int j = 0; j < 13; j++)
		{
			descriptions[i][j] = "Due to Developer Laziness, this content hasn't been added yet";
		}
	}
	descriptions[0][0] = "This rusty blunted dagger couldn't slice an orange if it was sharpened first";
	descriptions[0][1] = "The edge of this shortsword is so dull that you can drag it across your bare hand without cutting it";
	descriptions[0][2] = "This hatchet has felled many trees, and it shows. Its blade is chipped and now it is nearly useless";
	descriptions[0][3] = "This longsword has not aged well. It has enough rust spots that one can't help but wonder if it was stored in water or something";
	descriptions[0][4] = "The Head of this maul has fallen off many times, and it may again soon. The iron work is cracked, and it seems that the metal may shatter";
	descriptions[0][5] = "This Battleaxe has seen better days. The crusty blade hangs loosely on the shaft as if it may fall off at any time";
	descriptions[0][6] = "This Claymore is rusted and pitted. Its cumbersome and heavy frame is brittle and will break soon";
	descriptions[0][7] = "A worm has eaten through this tome, and some pages are missing. It also seems to have been vomited on, by the look of page 63";
	descriptions[0][8] = "This wand has no head, and as such is not a great channel for magic. But it sure is cheap though. Probably because you could just go outside and pick up a twig that would serve just as well.";
	descriptions[0][9] = "How anyone could see the future with cracked orb i have no idea.";
	descriptions[0][10] = "This feeble staff has no head, which makes me wonder how anyone could channel magic though it";
	descriptions[0][11] = "The wood used to make this longbow is weak and may crack at any moment";
	descriptions[0][12] = "The clinch to this crossbow is missing. It seems so broken, it may be better just to throw the bolts at your opponent";
	return descriptions;
}

std::map<int, std::string> Weapon::WeaponTextureLocations()
{
	std::map<int, std::string> loc;
	loc[0] = "Game/ContentFiles/ItemTextures/Daggers.png";
	loc[1] = "Game/ContentFiles/ItemTextures/ShortSwords.png";
	loc[2] = "Game/ContentFiles/ItemTextures/Hatchets.png";
	loc[3] = "Game/ContentFiles/ItemTextures/LongSwords.png";
	loc[4] = "Game/ContentFiles/ItemTextures/Maul.png";
	loc[5] = "Game/ContentFiles/ItemTextures/BattleAxes.png";
	loc[6] = "Game/ContentFiles/ItemTextures/Claymores.png";
	loc[7] = "Game/ContentFiles/ItemTextures/Tomes.png";
	loc[8] = "Game/ContentFiles/ItemTextures/Wands.png";
	loc[9] = "Game/ContentFiles/ItemTextures/Orbs.png";
	loc[10] = "Game/ContentFiles/ItemTextures/Staffs.png";
	loc[11] = "Game/ContentFiles/ItemTextures/Bow.png";
	loc[12] = "Game/ContentFiles/ItemTextures/Crossbow.png";
	return loc;
}
