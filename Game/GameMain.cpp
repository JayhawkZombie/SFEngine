#include "GameMain.h"
#include "RPGTest.h"
#include <iostream>
#include <map>
#include "ListReader.h"
#include "MainCharacter.h"
#include "Reliquary.h"
#include "BestiaryConsole.h"
GameMain::GameMain()
{}

GameMain::~GameMain()
{}

std::map<int, std::map<int, std::string>> GameMain::SubElementNames()
{
	std::map<int,
		std::map<int, std::string>> SubElementNames;
	SubElementNames[0][0] = "Pyro";
	SubElementNames[0][1] = "Lava";
	SubElementNames[0][2] = "Dinosaur";
	SubElementNames[0][3] = "Phoenix";
	SubElementNames[0][4] = "Justice";
	SubElementNames[0][5] = "Vengence";
	SubElementNames[1][0] = "Steam";
	SubElementNames[1][1] = "Aqua";
	SubElementNames[1][2] = "Amphibious";
	SubElementNames[1][3] = "Weather";
	SubElementNames[1][4] = "Ice";
	SubElementNames[1][5] = "Deep";
	SubElementNames[2][0] = "Fairy";
	SubElementNames[2][1] = "Swamp";
	SubElementNames[2][2] = "Tera";
	SubElementNames[2][3] = "Pegasus";
	SubElementNames[2][4] = "Compassion";
	SubElementNames[2][5] = "Rotten";
	SubElementNames[3][0] = "Sands";
	SubElementNames[3][1] = "SeaBreeze";
	SubElementNames[3][2] = "Birds";
	SubElementNames[3][3] = "Aero";
	SubElementNames[3][4] = "Cocka";
	SubElementNames[3][5] = "NightWing";
	SubElementNames[4][0] = "Solar";
	SubElementNames[4][1] = "Lunar";
	SubElementNames[4][2] = "Guardian";
	SubElementNames[4][3] = "Holy";
	SubElementNames[4][4] = "Light";
	SubElementNames[4][5] = "Redemption";
	SubElementNames[5][0] = "Demonic";
	SubElementNames[5][1] = "Poison";
	SubElementNames[5][2] = "Undead";
	SubElementNames[5][3] = "Storm";
	SubElementNames[5][4] = "Betrayer";
	SubElementNames[5][5] = "Umbral";
	return SubElementNames;
}

std::map<int, std::map<int, std::string>> GameMain::Symbols()
{
	std::map<int, std::map<int, std::string>> SymbolLocations;
	SymbolLocations[0][0] = "Game/ContentFiles/UIStuff/Symbols/PyroSymbol.png";
	SymbolLocations[0][1] = "Game/ContentFiles/UIStuff/Symbols/LavaSymbol.png";
	SymbolLocations[0][2] = "Game/ContentFiles/UIStuff/Symbols/DinoSymbol.png";
	SymbolLocations[0][3] = "Game/ContentFiles/UIStuff/Symbols/PhoenixSymbol.png";
	SymbolLocations[0][4] = "Game/ContentFiles/UIStuff/Symbols/JusticeSymbol.png";
	SymbolLocations[0][5] = "Game/ContentFiles/UIStuff/Symbols/VengenceSymbol.png";
	SymbolLocations[1][0] = "Game/ContentFiles/UIStuff/Symbols/SteamSymbol.png";
	SymbolLocations[1][1] = "Game/ContentFiles/UIStuff/Symbols/AquaSymbol.png";
	SymbolLocations[1][2] = "Game/ContentFiles/UIStuff/Symbols/AmphibiousSymbol.png";
	SymbolLocations[1][3] = "Game/ContentFiles/UIStuff/Symbols/WeatherSymbol.png";
	SymbolLocations[1][4] = "Game/ContentFiles/UIStuff/Symbols/IceSymbol.png";
	SymbolLocations[1][5] = "Game/ContentFiles/UIStuff/Symbols/DeepSymbol.png";
	SymbolLocations[2][0] = "Game/ContentFiles/UIStuff/Symbols/FeySymbol.png";
	SymbolLocations[2][1] = "Game/ContentFiles/UIStuff/Symbols/SwampSymbol.png";
	SymbolLocations[2][2] = "Game/ContentFiles/UIStuff/Symbols/TeraSymbol.png";
	SymbolLocations[2][3] = "Game/ContentFiles/UIStuff/Symbols/PegasusSymbol.png";
	SymbolLocations[2][4] = "Game/ContentFiles/UIStuff/Symbols/CompassionSymbol.png";
	SymbolLocations[2][5] = "Game/ContentFiles/UIStuff/Symbols/RottenSymbol.png";
	SymbolLocations[3][0] = "Game/ContentFiles/UIStuff/Symbols/SandSymbol.png";
	SymbolLocations[3][1] = "Game/ContentFiles/UIStuff/Symbols/SeaBreeze.png";
	SymbolLocations[3][2] = "Game/ContentFiles/UIStuff/Symbols/BirdSymbol.png";
	SymbolLocations[3][3] = "Game/ContentFiles/UIStuff/Symbols/AeroSymbol.png";
	SymbolLocations[3][4] = "Game/ContentFiles/UIStuff/Symbols/CockaSymbol.png";
	SymbolLocations[3][5] = "Game/ContentFiles/UIStuff/Symbols/NightWingSymbol.png";
	SymbolLocations[4][0] = "Game/ContentFiles/UIStuff/Symbols/SolarSymbol.png";
	SymbolLocations[4][1] = "Game/ContentFiles/UIStuff/Symbols/LunarSymbol.png";
	SymbolLocations[4][2] = "Game/ContentFiles/UIStuff/Symbols/GuardianSymbol.png";
	SymbolLocations[4][3] = "Game/ContentFiles/UIStuff/Symbols/AngelSymbol.png";
	SymbolLocations[4][4] = "Game/ContentFiles/UIStuff/Symbols/LightSymbol.png";
	SymbolLocations[4][5] = "Game/ContentFiles/UIStuff/Symbols/RedemptionSymbol.png";
	SymbolLocations[5][0] = "Game/ContentFiles/UIStuff/Symbols/DemonSymbol.png";
	SymbolLocations[5][1] = "Game/ContentFiles/UIStuff/Symbols/PoisonSymbol.png";
	SymbolLocations[5][2] = "Game/ContentFiles/UIStuff/Symbols/UndeadSymbol.png";
	SymbolLocations[5][3] = "Game/ContentFiles/UIStuff/Symbols/StormSymbol.png";
	SymbolLocations[5][4] = "Game/ContentFiles/UIStuff/Symbols/BetrayerSymbol.png";
	SymbolLocations[5][5] = "Game/ContentFiles/UIStuff/Symbols/UmbralSymbol.png";
	return SymbolLocations;
}

std::map<int, std::map<int, std::map<int, std::map<int, MonsterType*>>>> GameMain::Monsters(MonsterType** myArray)
{
	std::map<int, std::map<int, std::map<int, std::map< int, MonsterType*>>>> Monsters;
	Monsters[0][0][1][0] = myArray[0];
	Monsters[0][0][2][0] = myArray[1];
	Monsters[0][0][2][1] = myArray[2];
	Monsters[0][0][2][2] = myArray[3];
	Monsters[0][0][3][0] = myArray[4];
	Monsters[0][0][3][1] = myArray[5];
	Monsters[0][0][3][2] = myArray[6];
	Monsters[0][0][3][3] = myArray[7];
	Monsters[0][0][4][0] = myArray[8];
	Monsters[0][0][4][1] = myArray[9];
	Monsters[0][0][4][2] = myArray[10];
	Monsters[0][0][4][3] = myArray[11];
	Monsters[0][1][1][0] = myArray[12];
	Monsters[0][1][2][0] = myArray[13];
	Monsters[0][1][2][1] = myArray[14];
	Monsters[0][1][3][0] = myArray[15];
	Monsters[0][1][3][1] = myArray[16];
	Monsters[0][1][4][0] = myArray[17];
	Monsters[0][1][4][1] = myArray[18];
	Monsters[0][2][1][0] = myArray[19];
	Monsters[0][2][2][0] = myArray[20];
	Monsters[0][2][2][1] = myArray[21];
	Monsters[0][2][2][2] = myArray[22];
	Monsters[0][2][3][0] = myArray[23];
	Monsters[0][2][3][1] = myArray[24];
	Monsters[0][2][3][2] = myArray[25];
	Monsters[0][2][4][0] = myArray[26];
	Monsters[0][2][4][1] = myArray[27];
	Monsters[0][2][4][2] = myArray[28];
	Monsters[0][3][1][0] = myArray[29];
	Monsters[0][3][2][0] = myArray[30];
	Monsters[0][3][2][1] = myArray[31];
	Monsters[0][3][3][0] = myArray[32];
	Monsters[0][3][3][1] = myArray[33];
	Monsters[0][3][4][0] = myArray[34];
	Monsters[0][3][4][1] = myArray[35];
	Monsters[0][4][1][0] = myArray[36];
	Monsters[0][4][2][0] = myArray[37];
	Monsters[0][4][2][1] = myArray[38];
	Monsters[0][4][3][0] = myArray[39];
	Monsters[0][4][3][1] = myArray[40];
	Monsters[0][4][4][0] = myArray[41];
	Monsters[0][4][4][1] = myArray[42];
	Monsters[0][5][1][0] = myArray[43];
	Monsters[0][5][2][0] = myArray[44];
	Monsters[0][5][2][1] = myArray[45];
	Monsters[0][5][3][0] = myArray[46];
	Monsters[0][5][3][1] = myArray[47];
	Monsters[0][5][4][0] = myArray[48];
	Monsters[0][5][4][1] = myArray[49];
	Monsters[1][0][1][0] = myArray[50];
	Monsters[1][0][2][0] = myArray[51];
	Monsters[1][0][3][0] = myArray[52];
	Monsters[1][0][4][0] = myArray[53];
	Monsters[1][1][1][0] = myArray[54];
	Monsters[1][1][2][0] = myArray[55];
	Monsters[1][1][2][1] = myArray[56];
	Monsters[1][1][2][2] = myArray[57];
	Monsters[1][1][3][0] = myArray[58];
	Monsters[1][1][3][1] = myArray[59];
	Monsters[1][1][3][2] = myArray[60];
	Monsters[1][1][3][3] = myArray[61];
	Monsters[1][1][4][0] = myArray[62];
	Monsters[1][1][4][1] = myArray[63];
	Monsters[1][1][4][2] = myArray[64];
	Monsters[1][1][4][3] = myArray[65];
	Monsters[1][2][1][0] = myArray[66];
	Monsters[1][2][2][0] = myArray[67];
	Monsters[1][2][2][1] = myArray[68];
	Monsters[1][2][2][2] = myArray[69];
	Monsters[1][2][3][0] = myArray[70];
	Monsters[1][2][3][1] = myArray[71];
	Monsters[1][2][3][2] = myArray[72];
	Monsters[1][2][4][0] = myArray[73];
	Monsters[1][2][4][1] = myArray[74];
	Monsters[1][2][4][2] = myArray[75];
	Monsters[1][3][1][0] = myArray[76];
	Monsters[1][3][2][0] = myArray[77];
	Monsters[1][3][2][1] = myArray[78];
	Monsters[1][3][2][2] = myArray[79];
	Monsters[1][3][3][0] = myArray[80];
	Monsters[1][3][3][1] = myArray[81];
	Monsters[1][3][3][2] = myArray[82];
	Monsters[1][3][4][0] = myArray[83];
	Monsters[1][3][4][1] = myArray[84];
	Monsters[1][3][4][2] = myArray[85];
	Monsters[1][4][1][0] = myArray[86];
	Monsters[1][4][2][0] = myArray[87];
	Monsters[1][4][2][1] = myArray[88];
	Monsters[1][4][2][2] = myArray[89];
	Monsters[1][4][3][0] = myArray[90];
	Monsters[1][4][3][1] = myArray[91];
	Monsters[1][4][3][2] = myArray[92];
	Monsters[1][4][3][3] = myArray[93];
	Monsters[1][4][4][0] = myArray[94];
	Monsters[1][4][4][1] = myArray[95];
	Monsters[1][4][4][2] = myArray[96];
	Monsters[1][4][4][3] = myArray[97];
	Monsters[1][5][1][0] = myArray[98];
	Monsters[1][5][2][0] = myArray[99];
	Monsters[1][5][2][1] = myArray[100];
	Monsters[1][5][2][2] = myArray[101];
	Monsters[1][5][3][0] = myArray[102];
	Monsters[1][5][3][1] = myArray[103];
	Monsters[1][5][3][2] = myArray[104];
	Monsters[1][5][3][3] = myArray[105];
	Monsters[1][5][4][0] = myArray[106];
	Monsters[1][5][4][1] = myArray[107];
	Monsters[1][5][4][2] = myArray[108];
	Monsters[1][5][4][3] = myArray[109];
	Monsters[2][0][1][0] = myArray[110];
	Monsters[2][0][2][0] = myArray[111];
	Monsters[2][0][2][1] = myArray[112];
	Monsters[2][0][2][2] = myArray[113];
	Monsters[2][0][3][0] = myArray[114];
	Monsters[2][0][3][1] = myArray[115];
	Monsters[2][0][3][2] = myArray[116];
	Monsters[2][0][4][0] = myArray[117];
	Monsters[2][0][4][1] = myArray[118];
	Monsters[2][0][4][2] = myArray[119];
	Monsters[2][1][1][0] = myArray[120];
	Monsters[2][1][2][0] = myArray[121];
	Monsters[2][1][2][1] = myArray[122];
	Monsters[2][1][3][0] = myArray[123];
	Monsters[2][1][3][1] = myArray[124];
	Monsters[2][1][4][0] = myArray[125];
	Monsters[2][1][4][1] = myArray[126];
	Monsters[2][2][1][0] = myArray[127];
	Monsters[2][2][1][1] = myArray[128];
	Monsters[2][2][1][2] = myArray[129];
	Monsters[2][2][2][0] = myArray[130];
	Monsters[2][2][2][1] = myArray[131];
	Monsters[2][2][2][2] = myArray[132];
	Monsters[2][2][2][3] = myArray[133];
	Monsters[2][2][3][0] = myArray[134];
	Monsters[2][2][3][1] = myArray[135];
	Monsters[2][2][3][2] = myArray[136];
	Monsters[2][2][3][3] = myArray[137];
	Monsters[2][2][3][4] = myArray[138];
	Monsters[2][2][4][0] = myArray[139];
	Monsters[2][2][4][1] = myArray[140];
	Monsters[2][2][4][2] = myArray[141];
	Monsters[2][2][4][3] = myArray[142];
	Monsters[2][2][4][4] = myArray[143];
	Monsters[2][2][4][5] = myArray[144];
	Monsters[2][3][1][0] = myArray[145];
	Monsters[2][3][2][0] = myArray[146];
	Monsters[2][3][2][1] = myArray[147];
	Monsters[2][3][3][0] = myArray[148];
	Monsters[2][3][3][1] = myArray[149];
	Monsters[2][3][4][0] = myArray[150];
	Monsters[2][3][4][1] = myArray[151];
	Monsters[2][4][1][0] = myArray[152];
	Monsters[2][4][2][0] = myArray[153];
	Monsters[2][4][2][1] = myArray[154];
	Monsters[2][4][3][0] = myArray[155];
	Monsters[2][4][3][1] = myArray[156];
	Monsters[2][4][4][0] = myArray[157];
	Monsters[2][4][4][1] = myArray[158];
	Monsters[2][5][1][0] = myArray[159];
	Monsters[2][5][2][0] = myArray[160];
	Monsters[2][5][3][0] = myArray[161];
	Monsters[2][5][4][0] = myArray[162];
	Monsters[3][0][1][0] = myArray[163];
	Monsters[3][0][2][0] = myArray[164];
	Monsters[3][0][2][1] = myArray[165];
	Monsters[3][0][2][2] = myArray[166];
	Monsters[3][0][3][0] = myArray[167];
	Monsters[3][0][3][1] = myArray[168];
	Monsters[3][0][3][2] = myArray[169];
	Monsters[3][0][4][0] = myArray[170];
	Monsters[3][0][4][1] = myArray[171];
	Monsters[3][0][4][2] = myArray[172];
	Monsters[3][1][1][0] = myArray[173];
	Monsters[3][1][2][0] = myArray[174];
	Monsters[3][1][2][1] = myArray[175];
	Monsters[3][1][3][0] = myArray[176];
	Monsters[3][1][3][1] = myArray[177];
	Monsters[3][1][4][0] = myArray[178];
	Monsters[3][1][4][1] = myArray[179];
	Monsters[3][2][1][0] = myArray[180];
	Monsters[3][2][2][0] = myArray[181];
	Monsters[3][2][2][1] = myArray[182];
	Monsters[3][2][3][0] = myArray[183];
	Monsters[3][2][3][1] = myArray[184];
	Monsters[3][2][4][0] = myArray[185];
	Monsters[3][2][4][1] = myArray[186];
	Monsters[3][3][1][0] = myArray[187];
	Monsters[3][3][2][0] = myArray[188];
	Monsters[3][3][2][1] = myArray[189];
	Monsters[3][3][2][2] = myArray[190];
	Monsters[3][3][3][0] = myArray[191];
	Monsters[3][3][3][1] = myArray[192];
	Monsters[3][3][3][2] = myArray[193];
	Monsters[3][3][3][3] = myArray[194];
	Monsters[3][3][4][0] = myArray[195];
	Monsters[3][3][4][1] = myArray[196];
	Monsters[3][3][4][2] = myArray[197];
	Monsters[3][3][4][3] = myArray[198];
	Monsters[3][4][1][0] = myArray[199];
	Monsters[3][4][2][0] = myArray[200];
	Monsters[3][4][2][1] = myArray[201];
	Monsters[3][4][2][2] = myArray[202];
	Monsters[3][4][3][0] = myArray[203];
	Monsters[3][4][3][1] = myArray[204];
	Monsters[3][4][3][2] = myArray[205];
	Monsters[3][4][4][0] = myArray[206];
	Monsters[3][4][4][1] = myArray[207];
	Monsters[3][4][4][2] = myArray[208];
	Monsters[3][5][1][0] = myArray[209];
	Monsters[3][5][2][0] = myArray[210];
	Monsters[3][5][2][1] = myArray[211];
	Monsters[3][5][2][2] = myArray[212];
	Monsters[3][5][3][0] = myArray[213];
	Monsters[3][5][3][1] = myArray[214];
	Monsters[3][5][3][2] = myArray[215];
	Monsters[3][5][4][0] = myArray[216];
	Monsters[3][5][4][1] = myArray[217];
	Monsters[3][5][4][2] = myArray[218];
	Monsters[4][0][1][0] = myArray[219];
	Monsters[4][0][2][0] = myArray[220];
	Monsters[4][0][2][1] = myArray[221];
	Monsters[4][0][2][2] = myArray[222];
	Monsters[4][0][3][0] = myArray[223];
	Monsters[4][0][3][1] = myArray[224];
	Monsters[4][0][3][2] = myArray[225];
	Monsters[4][0][4][0] = myArray[226];
	Monsters[4][0][4][1] = myArray[227];
	Monsters[4][0][4][2] = myArray[228];
	Monsters[4][1][1][0] = myArray[229];
	Monsters[4][1][2][0] = myArray[230];
	Monsters[4][1][2][1] = myArray[231];
	Monsters[4][1][3][0] = myArray[232];
	Monsters[4][1][3][1] = myArray[233];
	Monsters[4][1][4][0] = myArray[234];
	Monsters[4][1][4][1] = myArray[235];
	Monsters[4][2][1][0] = myArray[236];
	Monsters[4][2][2][0] = myArray[237];
	Monsters[4][2][2][1] = myArray[238];
	Monsters[4][2][3][0] = myArray[239];
	Monsters[4][2][3][1] = myArray[240];
	Monsters[4][2][4][0] = myArray[241];
	Monsters[4][2][4][1] = myArray[242];
	Monsters[4][3][1][0] = myArray[243];
	Monsters[4][3][2][0] = myArray[244];
	Monsters[4][3][2][1] = myArray[245];
	Monsters[4][3][3][0] = myArray[246];
	Monsters[4][3][3][1] = myArray[247];
	Monsters[4][3][4][0] = myArray[248];
	Monsters[4][3][4][1] = myArray[249];
	Monsters[4][4][1][0] = myArray[250];
	Monsters[4][4][2][0] = myArray[251];
	Monsters[4][4][2][1] = myArray[252];
	Monsters[4][4][2][2] = myArray[253];
	Monsters[4][4][3][0] = myArray[254];
	Monsters[4][4][3][1] = myArray[255];
	Monsters[4][4][3][2] = myArray[256];
	Monsters[4][4][3][3] = myArray[257];
	Monsters[4][4][4][0] = myArray[258];
	Monsters[4][4][4][1] = myArray[259];
	Monsters[4][4][4][2] = myArray[260];
	Monsters[4][4][4][3] = myArray[261];
	Monsters[4][5][1][0] = myArray[262];
	Monsters[4][5][2][0] = myArray[263];
	Monsters[4][5][2][1] = myArray[264];
	Monsters[4][5][2][2] = myArray[265];
	Monsters[4][5][3][0] = myArray[266];
	Monsters[4][5][3][1] = myArray[267];
	Monsters[4][5][3][2] = myArray[268];
	Monsters[4][5][4][0] = myArray[269];
	Monsters[4][5][4][1] = myArray[270];
	Monsters[4][5][4][2] = myArray[271];
	Monsters[5][0][1][0] = myArray[272];
	Monsters[5][0][2][0] = myArray[273];
	Monsters[5][0][2][1] = myArray[274];
	Monsters[5][0][2][2] = myArray[275];
	Monsters[5][0][3][0] = myArray[276];
	Monsters[5][0][3][1] = myArray[277];
	Monsters[5][0][3][2] = myArray[278];
	Monsters[5][0][4][0] = myArray[279];
	Monsters[5][0][4][1] = myArray[280];
	Monsters[5][0][4][2] = myArray[281];
	Monsters[5][1][1][0] = myArray[282];
	Monsters[5][1][2][0] = myArray[283];
	Monsters[5][1][2][1] = myArray[284];
	Monsters[5][1][2][2] = myArray[285];
	Monsters[5][1][3][0] = myArray[286];
	Monsters[5][1][3][1] = myArray[287];
	Monsters[5][1][3][2] = myArray[288];
	Monsters[5][1][4][0] = myArray[289];
	Monsters[5][1][4][1] = myArray[290];
	Monsters[5][1][4][2] = myArray[291];
	Monsters[5][2][1][0] = myArray[292];
	Monsters[5][2][2][0] = myArray[293];
	Monsters[5][2][2][1] = myArray[294];
	Monsters[5][2][3][0] = myArray[295];
	Monsters[5][2][3][1] = myArray[296];
	Monsters[5][2][4][0] = myArray[297];
	Monsters[5][2][4][1] = myArray[298];
	Monsters[5][3][1][0] = myArray[299];
	Monsters[5][3][2][0] = myArray[300];
	Monsters[5][3][3][0] = myArray[301];
	Monsters[5][3][4][0] = myArray[302];
	Monsters[5][4][1][0] = myArray[303];
	Monsters[5][4][2][0] = myArray[304];
	Monsters[5][4][3][0] = myArray[305];
	Monsters[5][4][4][0] = myArray[306];
	Monsters[5][5][1][0] = myArray[307];
	Monsters[5][5][2][0] = myArray[308];
	Monsters[5][5][2][1] = myArray[309];
	Monsters[5][5][2][2] = myArray[310];
	Monsters[5][5][3][0] = myArray[311];
	Monsters[5][5][3][1] = myArray[312];
	Monsters[5][5][3][2] = myArray[313];
	Monsters[5][5][3][3] = myArray[314];
	Monsters[5][5][4][0] = myArray[315];
	Monsters[5][5][4][1] = myArray[316];
	Monsters[5][5][4][2] = myArray[317];
	Monsters[5][5][4][3] = myArray[318];

	return Monsters;//std::map<int, std::map<int, std::map<int, std::map<int, MonsterType>>>>();
}

std::map<int, std::map<int, std::map<int, std::map<int, int>>>> GameMain::indexLookup(MonsterType** myArray)
{
	std::map<int, std::map<int, std::map<int, std::map<int, int>>>> lookUp;
	//ListReader list;
	//MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");

	for (int i = 0; i < 319; i++)
	{
		lookUp[myArray[i]->getPrimary()][myArray[i]->getSecondary()][myArray[i]->getEvolutionStage()][myArray[i]->getEvolutionType()] = i;
	}
	return lookUp;
}

std::map<int, std::map<int, std::map<int, int>>> GameMain::numStagesLookup()
{
	std::map<int, std::map<int, std::map< int, int>>> SizeLookup;

	std::map<int, int> TreeType1;
	TreeType1[1] = 1;
	TreeType1[2] = 1;
	TreeType1[3] = 1;
	TreeType1[4] = 1;

	std::map<int, int> TreeType2;
	TreeType2[1] = 1;
	TreeType2[2] = 2;
	TreeType2[3] = 2;
	TreeType2[4] = 2;

	std::map<int, int> TreeType3;
	TreeType3[1] = 1;
	TreeType3[2] = 3;
	TreeType3[3] = 3;
	TreeType3[4] = 3;

	std::map<int, int> TreeType4;
	TreeType4[1] = 1;
	TreeType4[2] = 3;
	TreeType4[3] = 4;
	TreeType4[4] = 4;

	std::map<int, int> TreeType5;
	TreeType5[1] = 3;
	TreeType5[2] = 4;
	TreeType5[3] = 5;
	TreeType5[4] = 6;

	SizeLookup[0][0] = TreeType4;
	SizeLookup[0][1] = TreeType2;
	SizeLookup[0][2] = TreeType3;
	SizeLookup[0][3] = TreeType2;
	SizeLookup[0][4] = TreeType2;
	SizeLookup[0][5] = TreeType2;

	SizeLookup[1][0] = TreeType1;
	SizeLookup[1][1] = TreeType4;
	SizeLookup[1][2] = TreeType3;
	SizeLookup[1][3] = TreeType3;
	SizeLookup[1][4] = TreeType4;
	SizeLookup[1][5] = TreeType4;

	SizeLookup[2][0] = TreeType3;
	SizeLookup[2][1] = TreeType2;
	SizeLookup[2][2] = TreeType5;
	SizeLookup[2][3] = TreeType2;
	SizeLookup[2][4] = TreeType2;
	SizeLookup[2][5] = TreeType1;

	SizeLookup[3][0] = TreeType3;
	SizeLookup[3][1] = TreeType2;
	SizeLookup[3][2] = TreeType2;
	SizeLookup[3][3] = TreeType4;
	SizeLookup[3][4] = TreeType3;
	SizeLookup[3][5] = TreeType3;

	SizeLookup[4][0] = TreeType3;
	SizeLookup[4][1] = TreeType2;
	SizeLookup[4][2] = TreeType2;
	SizeLookup[4][3] = TreeType2;
	SizeLookup[4][4] = TreeType4;
	SizeLookup[4][5] = TreeType3;

	SizeLookup[5][0] = TreeType3;
	SizeLookup[5][1] = TreeType3;
	SizeLookup[5][2] = TreeType2;
	SizeLookup[5][3] = TreeType1;
	SizeLookup[5][4] = TreeType1;
	SizeLookup[5][5] = TreeType4;
	return SizeLookup;
}

int GameMain::run()
{
	int choice;

	while (true)
	{
		std::cout << "What would you like to do?\n";
		std::cout << "1) rewrite Armor Content\n";
		std::cout << "2) Print all the Monsters\n";
		std::cout << "3) Run Bestiary Simulator\n";
		std::cout << "4) Run Tests\n";
		std::cout << "5) rewrite Weapon Content\n";
		std::cout << "6) Peruse Reliquary\n";
		std::cout << "7) Exit\n";
		std::cin >> choice;
		if (choice == 1)
		{
			Armor::makeGenericList();
		}
		else if (choice == 2)
		{
			ListReader list;
			MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
			for (int i = 0; i<319; i++)
			{
				std::cout << "Index:            " << i << "\n";
				std::cout << "Name:             " << myArray[i]->getName() << "\n";
				std::cout << "Description:      " << myArray[i]->getDescription() << "\n";
				std::cout << "PrimaryElement:   " << myArray[i]->getPrimary() << "\n";
				std::cout << "SecondaryElement: " << myArray[i]->getSecondary() << "\n";
				std::cout << "EvolutionStage:   " << myArray[i]->getEvolutionStage() << "\n";
				std::cout << "EvolutionType:    " << myArray[i]->getEvolutionType() << "\n";
				std::cout << "Texture:          " << myArray[i]->getTexture() << "\n";
				//		std::cout << "PhysicalEvolution:" << myArray[i]->getPhysicalEvolution() << "\n";
				//		std::cout << "BalancedEvolution:" << myArray[i]->getBalancedEvolution() << "\n";
				//		std::cout << "MagicalEvolution: " << myArray[i]->getMagicalEvolution() << "\n";

				std::cout << "\n\n";
			}
		}
		else if (choice == 3)
		{
			BestiaryConsole::run();
		}
		else if (choice == 4)
		{
			RPGTest::runTests(true);
		}
		else if (choice == 5)
		{
			Weapon::makeGenericWeaponList();
		}
		else if (choice == 6)
		{
			Reliquary::run();
		}
		else if (choice == 7)
		{
			return 0;
		}
		else
		{
			std::cout << "Sorry we didn't understand your input\n";
		}
	}


	/*
	Armor** myArmors = list.readArmor("Game/ContentFiles/Generic/GenericArmor.txt");
	for (int i = 0; i < 72; i++)
	{
		std::cout << myArmors[i]->getName() << "\n";
		std::cout << myArmors[i]->getDescription() << "\n\n";
	}*/
	//std::map<int, std::map<int, std::map<int, std::map<int,int>>>> lookup = indexLookup(myArray);
	//std::cout << "ITS WORKING!\n";

//	MainCharacter* mchar = new MainCharacter();
//	list.readConversation("Game/ContentFiles/Conversation/ConvoJohnWakeUp.txt",*(mchar));
	//MonsterType** myArray = list.readMonsters("Game/ContentFiles/MonsterTypes/MonsterTypes.txt");
	//std::cout << "Myarray's length " << sizeof(myArray) << "\n";
	
	//std::map<int, std::map<int, std::string>> SymbolHolder = Symbols();

	/*
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			std::cout << Symbols()[i][j] << "\n";
			std::cout << SubElementNames()[i][j] << "\n";
		}
	}
	*/

	//for (int i = 0; i < sizeof(myArray); i++)
	

	


	//std::cout << "\n\n\n Lets try this: " << MonsterArray[0][0][1][0]->getName() << "\n";

	/*
	* int reply;
	* reply = list.readConversation(...);
	*/
//	list.menu();
//	delete mchar;
//	return 0;
}

std::map<int, std::string> GameMain::ElementNames()
{
	std::map<int, std::string> result;
	result[0] = "Fire";
	result[1] = "Water";
	result[2] = "Earth";
	result[3] = "Air";
	result[4] = "Light";
	result[5] = "Darkness";
	return result;
}

void GameMain::TickUpdate(const double &Delta)
{

}

void GameMain::Render(std::shared_ptr<sf::RenderTexture> Target)
{

}