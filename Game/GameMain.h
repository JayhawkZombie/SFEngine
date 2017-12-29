#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include "Engine/Source/BasicIncludes.h"
#include "Engine/Source/Level/Level.h"

#include "ListReader.h"
#include <vector>
#include <map>
#include "MonsterType.h"

enum class Type : std::uint32_t
{
	Fire = 0,
	Water = 1,
	Earth = 2,
	Air   = 3,
	Light = 4,
	Dark  = 5,
	Count
};

struct MonsterTree
{
	int TreeType;
	std::vector<MonsterType> myvec;
	MonsterTree() = default;
	MonsterTree(const MonsterTree &copy) : myvec(copy.myvec), TreeType(copy.TreeType) {};
};




class GameMain
{
public:
	GameMain();
	~GameMain();
	static int run();
	static std::map<int, std::string> ElementNames();
	static std::map<int, std::map<int, std::string>> SubElementNames();
    void TickUpdate(const double &Delta);
    void Render(std::shared_ptr<sf::RenderTexture> Target);
	static std::map<int, std::map<int, std::string>> Symbols();
	static std::map<int, std::map<int, std::map<int, std::map<int, MonsterType*>>>> Monsters(MonsterType** myArray);
	static std::map<int, std::map<int, std::map<int, std::map<int, int>>>> indexLookup(MonsterType** myArray);
	static std::map<int, std::map<int, std::map<int, int>>> numStagesLookup();

    std::map<Type, std::map<Type, MonsterTree>> m_MonsterMap;

private:

};

#endif
