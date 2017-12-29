#ifndef COMPANION_H
#define COMPANION_H
#include "HumanActor.h"
class Companion : public HumanActor
{
public:
	Companion();
	~Companion();
	int getInfluence();
	void incrimentInfluence(int incriment);
private:
	int m_influence;
};
#endif