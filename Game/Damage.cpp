#include "Damage.h"


int Damage::size = 31;
Damage::Damage()
{
  for (int i = 0; i < Damage::size; i++)
  {
    content[i] = 0;
  }
}
Damage::Damage(Damage inflicted, Damage defense)
{
	for (int i = 0; i < Damage::size; i++)
	{
		if (i == 8)
		{
			this->content[8] = inflicted.content[8];
		}
		if (inflicted.content[i] - defense.content[i] > 0)
		{
			this->content[i] = inflicted.content[i] - defense.content[i];
		}
		else
		{
			this->content[i] = 0;
		}
	}
}

Damage::~Damage()
{
}

void Damage::setValue(int index, int value)
{
  if (index > Damage::size)
  {
    std::cout << "Went outside the bounds of the array!";
    return;
  }
  content[index] = value;
  return;
}

std::map<int, std::string> Damage::DamageTypesByIndex()
{
	std::map<int, std::string> typeNames;
	typeNames[0] = "Fire";
	typeNames[1] = "Water";
	typeNames[2] = "Earth";
	typeNames[3] = "Air";
	typeNames[4] = "Light";
	typeNames[5] = "Dark";
	typeNames[6] = "Physical";
	typeNames[7] = "Magical";
	typeNames[8] = "True";
	typeNames[9] = "Burn";
	typeNames[10] = "Headache";
	typeNames[11] = "Wet";
	typeNames[12] = "Poison";
	typeNames[13] = "Toxic";
	typeNames[14] = "Stun";
	typeNames[15] = "Inspired";
	typeNames[16] = "Furious";
	typeNames[17] = "Chilled";
	typeNames[18] = "Frozen";
	typeNames[19] = "Dispelled";
	typeNames[20] = "Haste";
	typeNames[21] = "Numb";
	typeNames[22] = "Silence";
	typeNames[23] = "Regen";
	typeNames[24] = "Physical Shield";
	typeNames[25] = "Magical Shield";
	typeNames[26] = "Fire Shield";
	typeNames[27] = "Water Shield";
	typeNames[28] = "Earth Shield";
	typeNames[29] = "Air Shield";
	typeNames[30] = "Light Shield";
	typeNames[31] = "Dark Shield";
	return typeNames;
}