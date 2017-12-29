#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H
#include <string>
#include <iostream>
#include <map>
class MonsterType{

public:	
	MonsterType();
	~MonsterType();
    int getPrimary();
    int getSecondary();
    int getEvolutionStage();
    int getEvolutionType();
	int getConcatenation();
	
	std::string getTexture();
    std::string getName();
    std::string getDescription();

    MonsterType* getPhysicalEvolution();
    MonsterType* getBalancedEvolution();
    MonsterType* getMagicalEvolution();

	void setPrimary(int primary);
	void setSecondary(int secondary);
	void setEvolutionStage(int evolutionStage);
	void setEvolutionType(int evolutionType);
	void setName(std::string name);
	void setDescription(std::string description);
	void setTexture(std::string texture);
	
	void setPhysicalEvolution(MonsterType* physicalEvolution);
	void setBalancedEvolution(MonsterType* balancedEvolution);
	void setMagicalEvolution(MonsterType* magicalEvolution);
	std::map<int, std::map<int, std::map<int, std::map<int, int>>>> getMBPType();


private:
	int m_primary;
	int m_secondary;
	int m_evolutionStage;
	int m_evolutionType;
	int m_concatenation;
	std::string m_name;
	std::string m_description;
	MonsterType* m_physicalEvolution;
	MonsterType* m_balancedEvolution;
	MonsterType* m_magicalEvolution;
	int m_numEvolutions;
	std::string m_texture;
};
#endif
