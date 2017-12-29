#include "Companion.h"

Companion::Companion()
{
	m_influence = 0;
}

Companion::~Companion()
{

}

int Companion::getInfluence()
{
	return m_influence;
}

void Companion::incrimentInfluence(int incriment)
{
	m_influence += incriment;
}