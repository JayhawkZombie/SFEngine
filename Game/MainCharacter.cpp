#include "MainCharacter.h"



MainCharacter::MainCharacter()
{
	for (int i = 0; i < 6; i++)
	{
		m_affinity[i] = 0;
	}
}

MainCharacter::MainCharacter(const MainCharacter &copy)
  : HumanActor()
{
  m_affinity[0] = copy.m_affinity[0];
  m_affinity[1] = copy.m_affinity[1];
  m_affinity[2] = copy.m_affinity[2];
  m_affinity[3] = copy.m_affinity[3];
  m_affinity[4] = copy.m_affinity[4];
  m_affinity[5] = copy.m_affinity[5];
}

MainCharacter::~MainCharacter()
{
}
/*
bool MainCharacter::takeDamage(const Damage recieved)
{
	HumanActor::takeDamage(recieved);
}

Damage MainCharacter::baseDamage()
{
	return HumanActor::baseDamage();
}

void MainCharacter::levelUp()
{
	HumanActor::levelUp();
}

void MainCharacter::gainExp(int gain)
{
	HumanActor::gainExp(gain);
}
*/
std::shared_ptr<BaseEngineInterface> MainCharacter::Clone() const
{
  auto Character = std::make_shared<MainCharacter>(*this);

  return Character;
}

void MainCharacter::IncrementAffinity(int index, int value)
{
	if (index < 1 || index>6)//no work done on bad values
	{
		return;
	}
	if (value > 20)
	{
		value = 20;
	}
	else if (value < -20)
	{
		value = -20;
	}
	m_affinity[index] = m_affinity[index] + value;
}

int MainCharacter::getAffinity(int index)
{
	if (index < 1 || index>6)
	{
		return -1;
	}
	else
	{
		return m_affinity[index];
	}
}
void MainCharacter::printAffinities()
{
	std::cout << "fire:    " << m_affinity[0] << "\n";
	std::cout << "water:   " << m_affinity[1] << "\n";
	std::cout << "earth:   " << m_affinity[2] << "\n";
	std::cout << "air:     " << m_affinity[3] << "\n";
	std::cout << "light:   " << m_affinity[4] << "\n";
	std::cout << "dark:    " << m_affinity[5] << "\n";
}