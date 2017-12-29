#include "Tile.h"

int Tile::num = 0;
//Constructor
Tile::Tile()
{
	m_spriteBackground = "";
	m_spriteForeground = "";
	m_canTravel = true;
	m_show = 'W';
	num++;
}

//Destructor
Tile::~Tile()
{
}

//Getters
std::string Tile::getSpriteBackground() const
{
	return m_spriteBackground;
}

std::string Tile::getSpriteForeground() const
{
	return m_spriteForeground;
}

bool Tile::getCanTravel() const
{
	return m_canTravel;
}

char Tile::getShow() const
{
	return m_show;
}

//Setters
void Tile::setSpriteBackground(std::string spriteBackground)
{
	m_spriteBackground = spriteBackground;
}

void Tile::setSpriteForeground(std::string spriteForeground)
{
	m_spriteForeground = spriteForeground;
}

void Tile::setShow(char show)
{
	m_show = show;
}

void Tile::setCanTravel(bool canTravel)
{
	m_canTravel = canTravel;
}