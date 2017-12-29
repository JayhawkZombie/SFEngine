#include "RPGItem.h"

//int RPGItem::num=0;
//constructors
RPGItem::RPGItem()
{
	m_name = "";
	m_description = "";
	m_value = 0;
	m_id = 0;
//	num++;
}


RPGItem::~RPGItem()
{
}

//Getters- Setters
std::string RPGItem::getName() const
{
	return m_name;
}

std::string RPGItem::getDescription() const
{
	return m_description;
}

std::string RPGItem::getTexture() const
{
  return m_texture;
}

int RPGItem::getValue() const
{
	return m_value;
}

int RPGItem::getId() const
{
	return m_id;
}


void RPGItem::setName(std::string name)
{
	m_name = name;
}

void RPGItem::setDescription(std::string description)
{
	m_description = description;
}

void RPGItem::setTexture(std::string texture)
{
  m_texture = texture;
}
void RPGItem::setValue(int value)
{
	m_value = value;
}

void RPGItem::setId(int id)
{
	m_id = id;
}

//Other functions

std::map<int, std::map<int, std::string>> RPGItem::TierNames()
{
	//the first index is the level of the tier
	//teir index 0 is for actors level<5
	//teir index 1 is for actors level<10
	//teir index 2 is for actors level<20
	//teir index 3 is for actors level<30
	//teir index 4 is for actors level<40
	//teir index 5 is for actors level>40
	//the second index is the material type
	//0:Metal 1:Wood 2:Leather 3:Cloth 4:Glass 5:Tome
	std::map<int, std::map<int, std::string>> tiers;
	tiers[0][0] = "Rusted";
	tiers[0][1] = "ScrapWood";
	tiers[0][2] = "Fur";
	tiers[0][3] = "Dirty";
	tiers[0][4] = "Cracked";
	tiers[0][5] = "Decaying";
	tiers[1][0] = "Bronze";
	tiers[1][1] = "Pine";
	tiers[1][2] = "Rawhide";
	tiers[1][3] = "Flax";
	tiers[1][4] = "Opaque";
	tiers[1][5] = "Dusty";
	tiers[2][0] = "Iron";
	tiers[2][1] = "Oak";
	tiers[2][2] = "Buckskin";
	tiers[2][3] = "Wool";
	tiers[2][4] = "Cloudy";
	tiers[2][5] = "Magic";
	tiers[3][0] = "Steel";
	tiers[3][1] = "Elm";
	tiers[3][2] = "Tanned";
	tiers[3][3] = "Cotton";
	tiers[3][4] = "Translucent";
	tiers[3][5] = "Sage";
	tiers[4][0] = "Mithril";
	tiers[4][1] = "Yew";
	tiers[4][2] = "DrakeSkin";
	tiers[4][3] = "Silk";
	tiers[4][4] = "Crystal";
	tiers[4][5] = "Aware";
	tiers[5][0] = "DragonBone";
	tiers[5][1] = "DragonHorn";
	tiers[5][2] = "DragonScale";
	tiers[5][3] = "DragonWebbing";
	tiers[5][4] = "DragonEye";
	tiers[5][5] = "DragonMind";
	return tiers;
}

std::map<int, int> RPGItem::tierValues()
{
	//the first index is the level of the tier
	//teir index 0 is for actors level<5
	//teir index 1 is for actors level<10
	//teir index 2 is for actors level<20
	//teir index 3 is for actors level<30
	//teir index 4 is for actors level<40
	//teir index 5 is for actors level>40
	//the value is the default value for an item at that tier
	std::map<int, int> values;
	values[0] = 30;//Rusted,Scrapwood,Fur,Cracked items have base value 30
	values[1] = 80;
	values[2] = 200;
	values[3] = 500;
	values[4] = 5000;
	values[5] = 40000;
	return values;
}

std::map<int, int> RPGItem::tierBaseLevel()
{
	std::map<int, int> base;
	base[0] = 0;
	base[1] = 5;
	base[2] = 10;
	base[3] = 20;
	base[4] = 30;
	base[5] = 40;
	return base;
}

//void RPGItem::InitializeRPGItem()
//{
//	num = 0;
//}

//int RPGItem::HowMany()
//{
//	return num;
//}