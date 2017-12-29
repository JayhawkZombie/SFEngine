#include "OakTree.h"
#include "Level/LevelObject.h"
#include "../../../../Game/RPGActor.h"
#include <map>
#include <cmath>

OakTreeLevel::OakTreeLevel()
  : BasicLevel({ 800,800 }, { 0,0,800,800 })//: BasicLevel({ 50 * 16, 50 * 16 }, { 28 * 16, 18 * 16, 9 * 16, 9 * 16 }) //:BasicLevel({ 144,144 }, { 0,0,144,144 })//
{
  OakTreeChurchInteriorLevelPtr = std::make_shared<OakTreeChurchInterior>();
  OakTreeChurchInteriorLevelPtr->SetID("oaktree_church");
  Engine::Levels["oaktree_church"] = OakTreeChurchInteriorLevelPtr;
  LoadFromFile("./Projects/TestProject/testproject.json");
  lastPos = { 0,0 };
  std::vector<unsigned char> levelData(100000);
  levelData = {

    // row	  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 
    /*-1*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /* 0*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /* 1*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /* 2*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /* 3*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /* 4*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,16,16,16,16,16,17,17,17,17,17,17,17,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,
    /* 5*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,24,24,24,24,24,24,17,17,17,17,17,17,17,17,
    /* 6*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,17,17,17,17,17,24,17,17,17,17,17,17,17,17,
    /* 7*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,24,17,17,17,17,17,24,17,17,17,17,17,17,17,17,
    /* 8*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,17,24,17,17,17,17,17,24,17,17,17,17,17,17,17,17,
    /* 9*/ 17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,17,17,16,20,17,17,17,17,17,17,17,17,17,17,17,17,16,24,24,24,24,24,24,24,17,17,17,17,17,17,17,17,
    /*10*/ 17,17,17,17,17,17,16,17,16,17,17,16,18,16,17,17,17,17,17,16,19,20,17,17,17,17,17,17,17,17,17,17,17,16, 0,14,14,11,15,15,15,15,17,17,17,17,17,17,17,17,
    /*11*/ 17,17,17,17,17,16,18,16,18,16,16,18,18,18,16,17,17,17,17,18,19,20,17,17,17,17,17,17,17,17,17,17,17, 0, 8,15,15,15,17,17,17,17,17,17,17,17,17,17,17,17,
    /*12*/ 17,17,17,17,16,19,19,19,19,19,19,19,19,19,19,17,17,17,16,18,19,20,17,17,17,17,17,17,17,17,17,17,16,13,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*13*/ 17,17,17,17,18,20,20,20,20,20,20,20,20,20,20,16,17,17,19,18,19,20,17,17,17,17,17,17,16,17,17,16, 0, 8,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*14*/ 17,17,17,17,19,20,17,17,17,17,17,17,17,20,20,19,16,16,20,18,19,20,20,20, 0, 2,20,20,20,17,16, 0, 8,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*15*/ 17,17,17,17,15,20,17,17,17,17,17,17,17,20,20,18,18,20,20,20,20,20,20,20, 3, 5,20,20,20,16, 0, 8,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*16*/ 17,17,17,17,17,20,17,17,17,17,17,17,17,20,15,18,18,20, 0, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 5,18,16,16,16,16,16,17,17,16,16,16,16,16,17,17,17,17,17,17,
    /*17*/ 17,17,17,17,16,20,17,17,17,17,17,17,17,20,16,19,15,20, 3, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 5,19,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*18*/ 17,17,17,17,18,20,17,17,17,17,17,17,17,20,20,19,16,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*19*/ 17,17,17,17,18,20,20,20,20, 9,20,20,20,20,20,18,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*20*/ 17,17,17,17,15,15,15,15,15, 6,14,14,14,14, 2,15,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,
    /*21*/ 17,17,17,17,17,16,16,16,16,20,20,20,20,20,13,16,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,17,18,17,17,17,17,17,17,17,17,17,17,17,17,
    /*22*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20, 6,14,14,14, 4, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,18,13,18,18,18,18,16,20, 9,15,15,15,17,17,17,17,17,17,
    /*23*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,19,19,19, 3, 5,26,17,17,17,17,17,17,17,26, 3, 4,14,14, 7,14,14,14,14,14,14, 8,17,17,17,17,17,17,17,17,17,
    /*24*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,19,19,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,20,20,20,20,20,20,20,20,20,17,16,16,16,16,17,17,17,17,
    /*25*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,15,18,20, 3, 5,26,17,17,17,17,17,17,17,26, 3, 5,20,17,17,17,17,20,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*26*/ 17,17,17,17,17,20,17,17,17,17,17,17,24,20,19,16,19,20, 3, 5,26,26,26,26,26,26,26,26,26, 3, 5,20,17,17,17,17,15,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*27*/ 17,17,17,17,17,15,20,20,20,13,20,20,20,20,19,19,19,20, 3, 5,15,18,15,18,15,18,15,18,15, 3, 5,20,17,17,17,17,16,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*28*/ 17,17,17,17,17,17,15,15,15, 6,14,14,14,14,14,14,14,14, 4, 5,16,19,16,19,16,19,16,19,16, 3, 5,20,17,17,17,17,20,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*29*/ 17,17,17,17,17,17,17,17,17,15,15,15,15,15,15,15,15,15, 3, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5,20,20,20, 9,20,20,20,20, 9,20,16,20,20, 9,20,17,17,17,17,
    /*30*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 6, 7, 7, 7, 7, 4, 4, 4, 4, 7, 7, 7, 7,14,14,14, 7,14,14,14,14, 7,14,14,14,14, 8,15,17,17,17,17,
    /*31*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,15,19,15,19,15, 3, 4, 4, 5,20,20,20,20,20,15,20,20,20,20,20,20,20,20,19,20,18,20,17,17,17,17,17,
    /*32*/ 17,17,17,17,17,17,17,17,17,16,16,16,16,16,17,16,16,16,16,18,16,15,16, 3, 4, 4, 5,15,19,20,20,20,16,20,20,20,20,20,20,20,20,20,20,20,20,17,17,17,17,17,
    /*33*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,15,19,17,19, 3, 4, 4, 5,16,18,15,17,17,17,17,17,17,17,15,15,17,17,17,17,17,15,17,17,17,17,17,
    /*34*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,16,17,17,17,17,17,19,16,19, 3, 4, 4, 5,20,18,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*35*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,20,17,17,17,17,16,15,19,19, 3, 4, 4, 5,20,19,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*36*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,20,17,17,17,17,15,16,15,19, 3, 4, 4, 5,20,15,20,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*37*/ 17,17,17,17,17,17,17,16,16,17,17,17,17,17,20,17,17,17,17,16,19,16,19, 3, 4, 4, 5,20,16,20,17,17,17,17,17,17,17,16,16,16,17,17,17,17,17,17,17,17,17,17,
    /*38*/ 17,17,17,17,17,17,17,18,19,19, 9,20,20,20,20,20, 9,19,19,19,19,19,19, 3, 4, 4, 5,20,20,20,20,13,20,20,20,20,20,20,20,20,13,15,15,15,17,17,17,17,17,17,
    /*39*/ 17,17,17,17,17,17,17,15,18,19, 6,14,14,14,14,14, 7,14,14,14,14,14,14, 4, 4, 4, 4,14,14,14,14, 7,14,14,14,14,14,14,14,14, 8,17,17,17,17,17,17,17,17,17,
    /*40*/ 17,17,17,17,17,17,17,17,15,15,15,18,15,19,19,15,18,15,19,19,15,20,20, 3, 4, 4, 5,20,20,20,20,20,20,19,19,15,15,15,15,15,15,17,17,17,17,17,17,17,17,17,
    /*41*/ 17,17,17,17,17,17,17,17,17,17,17,15,17,18,18,17,15,17,19,19,17,15,20, 3, 4, 4, 5,20,15,20,15,20,20,15,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*42*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,15,15,17,17,17,15,15,16,16,15, 3, 4, 4, 5,15,17,15,17,15,15,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*43*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,15,15,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*44*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*45*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*46*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*47*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*48*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*49*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
    /*50*/ 17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17, 3, 4, 4, 5,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17 };

  std::vector<unsigned char> levelData2(100000);
  for (int i = 0; i < 2500; i++)
  {
	  if (levelData.at(i) == 15)
	  {
		  //std::cout << "i = " << i;
		  levelData2.push_back(1);
	  }
	  else
	  {
		  levelData2.push_back(0);
	  }
  }

  TileMap->setSize({ 800,800 });
  TileMap->setGridSize({ 50,50 });
  TileMap->setTexture(*Textures["ForestSpriteSheet"]);
  TileMap->setNumberOfTextureTilesPerRow(3);
  TileMap->setTextureTileSize({ 16,16 });
  TileMap->update(levelData, 50);
  
  top.setSize({ 800,800 });
  top.setGridSize({ 50,50 });
  top.setTexture(*Textures["TreeOverLap"]);
  top.setNumberOfTextureTilesPerRow(2);
  top.setTextureTileSize({ 16,16 });
  top.update(levelData2, 50);

  //Declaration of the Buildings
  std::shared_ptr <Engine::LevelObject> Barracks = std::make_shared<Engine::LevelObject>(); //Barracks Declaration
  std::shared_ptr <Engine::LevelObject> TownHall = std::make_shared<Engine::LevelObject>(); //TownHall Declaration
  std::shared_ptr <Engine::LevelObject> Church = std::make_shared<Engine::LevelObject>();  //Church Declaration
  std::shared_ptr <Engine::LevelObject> Church_Door = std::make_shared<Engine::LevelObject>(); // Church Door collider
  Church_Door->SetID("oaktree_churchdoor");
  std::shared_ptr <Engine::LevelObject> ItemShop = std::make_shared<Engine::LevelObject>(); //ItemShop Declaration
  std::shared_ptr <Engine::LevelObject> ArmorShop = std::make_shared<Engine::LevelObject>();//ArmorShop Declaration
  std::shared_ptr <Engine::LevelObject> WeaponShop = std::make_shared<Engine::LevelObject>();//WeaponShop Declaration
  std::shared_ptr <Engine::LevelObject> BrahmHouse = std::make_shared<Engine::LevelObject>();//BrahmHouse Declaration - looks like an inn for now
  std::shared_ptr <Engine::LevelObject> Inn = std::make_shared<Engine::LevelObject>();//Inn declaration
  std::shared_ptr <Engine::LevelObject> BigHouse1 = std::make_shared<Engine::LevelObject>(); //Main Characters house
  std::shared_ptr <Engine::LevelObject> BigHouse2 = std::make_shared<Engine::LevelObject>(); //Another big house
  std::shared_ptr <Engine::LevelObject> SmallHouse1 = std::make_shared<Engine::LevelObject>();//A small house
  std::shared_ptr <Engine::LevelObject> SmallHouse2 = std::make_shared<Engine::LevelObject>();//another small house
  std::shared_ptr <Engine::LevelObject> SmallHouse3 = std::make_shared<Engine::LevelObject>();//yet another small house

  //Declaration of The Trees-Texture Set of the Trees
  std::map<int, std::shared_ptr <Engine::LevelObject>> Trees;//Declares an array of trees -these will be the 5x5 tree blocks for filler
  std::shared_ptr <Engine::LevelObject> BigOakTreeTree = std::make_shared<Engine::LevelObject>(); //Declares The big tree in the middle of town

  BigOakTreeTree->SetTexture(Textures["Bigoaktree"]);//sets the texture for the big oak tree in the middle of town
  BigOakTreeTree->SetTextureRect({ 0,0,144,144 });
  BigOakTreeTree->SetPosition({ 20 * 16,19 * 16 });

  //Sets the Textures and the positions of the buildings
  Barracks->SetTexture(Textures["BigBuildings"]);
  Barracks->SetTextureRect({ 112,80,112,80 });
  Barracks->SetPosition({ 6 * 16,15 * 16 });

  TownHall->SetTexture(Textures["BigBuildings"]);
  TownHall->SetTextureRect({ 0,80,112,80 });
  TownHall->SetPosition({ 6 * 16,23 * 16 });

  Church->SetTexture(Textures["Church"]);//may be a bad idea to double use 'church'
  Church->SetPosition({ 22 * 16,6 * 16 });

  Church_Door->SetPosition({ 368.f, 224.f });
  Church_Door->SetSize({ 32, 32 });
  Church_Door->AddCollider(Engine::Collider2D::CreatePolygonMesh(4, 22.6274f, (3.14159 / 4), { 400.f, 224.f }, { 0, 0 }, 1000000000.f, 0.f, sf::Color::Red));

  ItemShop->SetTexture(Textures["5by5Shops"]);
  ItemShop->SetTextureRect({ 0 , 80, 80 ,80 });
  ItemShop->SetPosition({ 9 * 16 , 34 * 16 });

  ArmorShop->SetTexture(Textures["5by5Shops"]);
  ArmorShop->SetTextureRect({ 80,80,80,80 });
  ArmorShop->SetPosition({ 15 * 16,34 * 16 });

  WeaponShop->SetTexture(Textures["5by5Shops"]);
  WeaponShop->SetTextureRect({ 0,0,80,80 });
  WeaponShop->SetPosition({ 39 * 16,34 * 16 });

  BrahmHouse->SetTexture(Textures["BigBuildings"]);
  BrahmHouse->SetTextureRect({ 112,0,112,80 });
  BrahmHouse->SetPosition({ 35 * 16,6 * 16 });

  Inn->SetTexture(Textures["BigBuildings"]);
  Inn->SetTextureRect({ 0,0,112,80 });
  Inn->SetPosition({ 16 * 30,16 * 34 });

  BigHouse1->SetTexture(Textures["5House"]);
  BigHouse1->SetTextureRect({ 0,0,80,80 });
  BigHouse1->SetPosition({ 16 * 32,16 * 18 });

  BigHouse2->SetTexture(Textures["5House"]);
  BigHouse2->SetTextureRect({ 80,80,80,80 });
  BigHouse2->SetPosition({ 16 * 39,16 * 18 });

  SmallHouse1->SetTexture(Textures["4House"]);
  SmallHouse1->SetTextureRect({ 0,0,64,64 });
  SmallHouse1->SetPosition({ 32 * 16,26 * 16 });

  SmallHouse2->SetTexture(Textures["4House"]);
  SmallHouse2->SetTextureRect({ 0,64,64,64 });
  SmallHouse2->SetPosition({ 37 * 16,26 * 16 });

  SmallHouse3->SetTexture(Textures["4House"]);
  SmallHouse3->SetTextureRect({ 64,0,64,64 });
  SmallHouse3->SetPosition({ 42 * 16,26 * 16 });

  LevelObjects["BarracksObj"] = Barracks;
  LevelObjects["TownHallObj"] = TownHall;
  LevelObjects["ChurchObj"] = Church;
  LevelObjects["ItemShopObj"] = ItemShop;
  LevelObjects["ArmorShopObj"] = ArmorShop;
  LevelObjects["WeaponShopObj"] = WeaponShop;
  LevelObjects["BrahmsHouseObj"] = BrahmHouse;
  LevelObjects["InnObj"] = Inn;
  LevelObjects["BigHouse1Obj"] = BigHouse1;
  LevelObjects["BigHouse2Obj"] = BigHouse2;
  LevelObjects["SmallHouse1Obj"] = SmallHouse1;
  LevelObjects["SmallHouse2Obj"] = SmallHouse2;
  LevelObjects["SmallHouse3Obj"] = SmallHouse3;
  LevelObjects["BigOakTree"] = BigOakTreeTree;
  LevelObjects["Church_Door"] = Church_Door;
  

  sf::FloatRect myActor_spawnLocation(176.f, 176.f, 256.f, 256.f);
  sf::FloatRect full_map_view(0.f, 0.f, 800.f, 800.f);
  std::shared_ptr<RPGActor> myActor = std::make_shared<RPGActor>();

  myActor->SetTexture(Textures["MyActor_sheet"]);
  SpawnActor(myActor, { 24 * 16,33 * 16 });
  myActor->SetPosition({ 24 * 16,33 * 16 });
  myActor->SetActorSize({ 16,16 });
  LevelObjects["MainGuy"] = myActor;
  MainCharacter = myActor;
  myActor_camera.AttachToActor(myActor);
  myActor_camera.SetView({325.f,176.f,325.f,176.f});//this is the good one
  //myActor_camera.SetView(full_map_view);

  if (line_segment_builder_tool == true) {
    myActor_camera.DetachFromActor();
    myActor_camera.SetView(full_map_view);
  }

  
  for (auto & obj : LevelObjects)
  {
    if (!(obj.second == myActor))
    {
      Segments.push_back(Engine::BuildSegmentMesh('b', obj.second->getTopLeft(), obj.second->getTopRight()));
      Segments.push_back(Engine::BuildSegmentMesh('b', obj.second->getTopRight(), obj.second->getBottomRight()));
      Segments.push_back(Engine::BuildSegmentMesh('b', obj.second->getBottomLeft(), obj.second->getBottomRight()));
      Segments.push_back(Engine::BuildSegmentMesh('b', obj.second->getTopLeft(), obj.second->getBottomLeft()));
    }
  }


  //Four Corners of level
  Segments.push_back(Engine::BuildSegmentMesh('b', { 0,0 }, { 0,800 }));
  Segments.push_back(Engine::BuildSegmentMesh('b', { 0,800 }, { 800,800 }));
  Segments.push_back(Engine::BuildSegmentMesh('b', { 800,800 }, { 800,0 }));
  Segments.push_back(Engine::BuildSegmentMesh('b', { 800,0 }, { 0,0 }));


  Segments.push_back(Engine::BuildSegmentMesh('b', { (4 * 16) - 1,14 * 16 }, { (4 * 16) - 1,17*16 }));
  Segments.push_back(Engine::BuildSegmentMesh('b', { (4 * 16) - 1, 14 * 16 - 1 }, { (5 * 16) - 1,14 * 16 - 1 }));
  Segments.push_back(Engine::BuildSegmentMesh('b', { (5 * 16), 14 * 16 }, { 5 * 16,13 * 16 }));
  makeSegment({ 5,13 }, { 6,13 });
  makeSegment({ 6,13 }, { 6,12 });
  makeSegment(6, 12, 7, 12);
  makeSegment(7, 12, 7, 13);
  makeSegment(7, 13, 8, 13);
  makeSegment(8, 13, 8, 12);
  setLastSegmentPos({ 8,12 });
  nextSeg(9, 12);
  nextSeg(9, 13);
  nextSeg(11, 13);
  nextSeg(11, 12);
  nextSeg(12, 12);
  nextSeg(12, 11);
  nextSeg(13, 11);
  nextSeg(13, 12);
  nextSeg(14, 12);
  nextSeg(14, 13);
  nextSeg(15, 13);
  nextSeg(15, 15);
  nextSeg(16, 15);
  nextSeg(16, 16);
  nextSeg(18, 16);
  nextSeg(18, 14);
  nextSeg(19, 14);
  nextSeg(19, 12);
  nextSeg(20, 12);
  nextSeg(20, 11);
  nextSeg(21, 11);
  nextSeg(21, 10);
  nextSeg(22, 10);
  setLastSegmentPos({ 28,15 });
  nextSeg(29, 15);
  nextSeg(29, 17);
  nextSeg(30, 17);
  nextSeg(30, 16);
  nextSeg(31, 16);
  nextSeg(31, 15);
  nextSeg(32, 15);
  nextSeg(32, 14);
  nextSeg(33, 14);
  nextSeg(33, 12);
  nextSeg(34, 12);
  nextSeg(34, 11);
  nextSeg(35, 11);
  setLastSegmentPos({ 42,11 });
  nextSeg(42, 12);
  nextSeg(38, 12);
  nextSeg(38, 13);
  nextSeg(35, 13);
  nextSeg(35, 14);
  nextSeg(34, 14);
  nextSeg(34, 16);
  nextSeg(33, 16);
  nextSeg(33, 17);
  nextSeg(32, 17);
  nextSeg(32, 18);
  setLastSegmentPos({ 37,22 });
  nextSeg(38, 22);
  nextSeg(38, 24);
  nextSeg(39, 24);
  nextSeg(39, 23);
  setLastSegmentPos({ 44,23 });
  nextSeg(44, 24);
  nextSeg(41, 24);
  nextSeg(41, 27);
  setLastSegmentPos({ 41,30 });
  nextSeg(41, 31);
  nextSeg(42, 31);
  nextSeg(42, 30);
  setLastSegmentPos({ 36,28 });
  nextSeg(37, 28);
  setLastSegmentPos({ 36,29 });
  nextSeg(37, 29);
  setLastSegmentPos({ 46,30 });
  nextSeg(46, 32);
  nextSeg(45, 32);
  nextSeg(45, 35);
  nextSeg(44, 35);
  setLastSegmentPos({ 37,35 });
  nextSeg(39, 35);
  setLastSegmentPos({ 37,39 });
  nextSeg(39, 39);
  setLastSegmentPos({ 32,34 });
  nextSeg(32, 33);
  nextSeg(33, 33);
  nextSeg(33, 34);
  setLastSegmentPos({ 30,35 });
  nextSeg(29, 35);
  nextSeg(29, 36);
  nextSeg(30, 36);
  setLastSegmentPos({ 44,39 });
  nextSeg(44, 40);
  nextSeg(41, 40);
  nextSeg(41, 42);
  nextSeg(35, 42);
  nextSeg(35, 43);
  nextSeg(33, 43);
  nextSeg(33, 44);
  nextSeg(31, 44);
  nextSeg(31, 43);
  nextSeg(30, 43);
  nextSeg(30, 44);
  nextSeg(29, 44);
  nextSeg(29, 43);
  nextSeg(28, 43);
  nextSeg(28, 44);
  nextSeg(27, 44);
  nextSeg(27, 50);
  setLastSegmentPos({ 4,17 });
  nextSeg(5, 17);
  nextSeg(5, 19);
  nextSeg(4, 19);
  nextSeg(4, 22);
  nextSeg(9, 22);
  nextSeg(9, 23);
  setLastSegmentPos({ 6,23 });
  nextSeg(5, 23);
  nextSeg(5, 29);
  nextSeg(6, 29);
  nextSeg(6, 30);
  nextSeg(9, 30);
  nextSeg(9, 31);
  nextSeg(18, 31);
  nextSeg(18, 33);
  nextSeg(19, 33);
  nextSeg(19, 34);
  setLastSegmentPos({ 20,34 });
  nextSeg(20, 33);
  nextSeg(21, 33);
  nextSeg(21, 34);
  nextSeg(20, 34);
  setLastSegmentPos({ 21,36 });
  nextSeg(21, 34);
  nextSeg(22, 34);
  nextSeg(22, 36);
  nextSeg(21, 36);
  setLastSegmentPos({ 22,34 });
  nextSeg(22, 33);
  nextSeg(23, 33);
  nextSeg(23, 34);
  nextSeg(22, 34);
  setLastSegmentPos({ 20,38 });
  nextSeg(22, 38);
  nextSeg(22, 39);
  nextSeg(21, 39);
  nextSeg(21, 37);
  nextSeg(20, 37);
  nextSeg(20, 38);
  treeBaseSeg(14, 19);
  treeBaseSeg(16, 20);
  treeBaseSeg(15, 23);
  treeBaseSeg(15, 28);
  treeBaseSeg(20, 30);
  treeBaseSeg(22, 30);
  treeBaseSeg(24, 30);
  treeBaseSeg(26, 30);
  treeBaseSeg(28, 30);
  treeBaseSeg(27, 35);
  treeBaseSeg(28, 39);
  setLastSegmentPos({ 9,39 });
  nextSeg(7, 39);
  nextSeg(7, 41);
  nextSeg(8, 41);
  nextSeg(8, 42);
  nextSeg(11, 42);
  nextSeg(11, 43);
  nextSeg(12, 43);
  nextSeg(12, 42);
  nextSeg(13, 42);
  nextSeg(13, 44);
  nextSeg(15, 44);
  nextSeg(15, 42);
  nextSeg(16, 42);
  nextSeg(16, 43);
  nextSeg(17, 43);
  nextSeg(17, 42);
  nextSeg(18, 42);
  nextSeg(18, 44);
  nextSeg(20, 44);
  nextSeg(20, 42);
  nextSeg(21, 42);
  nextSeg(21, 43);
  nextSeg(22, 43);
  nextSeg(22, 44);
  nextSeg(23, 44);
  nextSeg(23, 50);
  setLastSegmentPos({ 14,36 });
  nextSeg(15, 36);

  Gravity->x = 0;
  Gravity->y = 0;
  Engine::SetGravity(Gravity);

  m_LightSystem.AddLight({ 24 * 16,33 * 16 }, 50.f, sf::Color::Red, "RedLight");
}

OakTreeLevel::OakTreeLevel(const sf::Vector2u & LevelSize, const sf::FloatRect & DefaultView, bool showlines, const sf::Vector2f & GridSpacing)
  : BasicLevel(LevelSize, DefaultView, showlines, GridSpacing)
{

}

void OakTreeLevel::TickUpdate(const double & delta)
{
  BasicLevel::TickUpdate(delta);
  LevelObjects["MainGuy"]->TickUpdate(delta);
  myActor_camera.Update();
  m_LightSystem.Update(LevelObjects);
}

void OakTreeLevel::makeSegment(sf::Vector2i endPoint1, sf::Vector2i endPoint2)
{
	Segments.push_back(Engine::BuildSegmentMesh('b', { endPoint1.x * 16,endPoint1.y * 16}, { endPoint2.x * 16,endPoint2.y * 16}));
}

void OakTreeLevel::makeSegment(int pt1x, int pt1y, int pt2x, int pt2y)
{
	Segments.push_back(Engine::BuildSegmentMesh('b', {pt1x*16,pt1y*16}, { pt2x*16,pt2y*16 }));
}

std::string OakTreeLevel::GetClass() const
{
  return std::string("OakTreeLevel");
}

void OakTreeLevel::setLastSegmentPos(sf::Vector2i last)
{
	lastPos = last;
}

void OakTreeLevel::nextSeg(int x, int y)
{
	if (y == lastPos.y)//x corrdinates are the same, the line is vertical
	{
		if (lastPos.x < x)
		{
			Segments.push_back(Engine::BuildSegmentMesh('b', { lastPos.x * 16 - 1, lastPos.y * 16 }, { x * 16 + 1,y * 16 }));
		}
		else
		{
			Segments.push_back(Engine::BuildSegmentMesh('b', { lastPos.x * 16 + 1, lastPos.y * 16 }, { x * 16 - 1,y*16 }));
		}
	}
	else
	{
		if (lastPos.y < y)
		{
			Segments.push_back(Engine::BuildSegmentMesh('b', { lastPos.x * 16,lastPos.y * 16 - 1 }, { x * 16,y * 16 + 1 }));
		}
		else
		{
			Segments.push_back(Engine::BuildSegmentMesh('b', { lastPos.x * 16, lastPos.y * 16 + 1 }, { x * 16,y * 16 - 1 }));
		}
	}
	//Segments.push_back(Engine::BuildSegmentMesh('b', { lastPos.x*16,lastPos.y * 16 }, {x*16,y*16 }));
	lastPos = { x,y };
}

void OakTreeLevel::treeBaseSeg(int x, int y)
{
	setLastSegmentPos({ x,y });
	nextSeg(x, y - 1);
	nextSeg(x + 1, y - 1);
	nextSeg(x + 1, y);
	nextSeg(x, y);
}

void OakTreeLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{
  sf::View view(myActor_camera.GetView());
  view.setViewport({ 0.f,0.f,1.f,1.f });
  Texture->setView(view);
  Texture->draw(*TileMap);
  BasicLevel::RenderOnTexture(Texture);
  Texture->draw(top);
  m_LightSystem.RenderOnTexture(Texture, view);
}

void OakTreeLevel::HandleInputEvent(const Engine::UserEvent & evnt)
{
  MainCharacter->HandleInputEvent(evnt);

  if (line_segment_builder_tool == true) {
    static sf::Vector2i start_position;
    static sf::Vector2i end_position;
    static int x_d = 0;
    static int y_d = 0;
    static int number_of_clicks = 0;
    static bool end_line_segment = false;

    if (evnt.KeyWasPressed && evnt.Key == sf::Keyboard::Space) {
      end_line_segment = true;
    }
    if (evnt.KeyWasPressed && evnt.Key == sf::Keyboard::Z) {
      //std::cout << "Undo was pressed\n";
    }

    if (evnt.MouseButtonWasPressed) {
      if (number_of_clicks == 0) {
        start_position = evnt.CurrentMousePosition;
        number_of_clicks++;
        //std::cout << "Start click\n";
      }
      else {
        start_position = end_position;
      }
      if (number_of_clicks > 0) {
        end_position = evnt.CurrentMousePosition;

        if (end_line_segment == true) {
          //std::cout << "End line\n";
          number_of_clicks = 0;
          end_line_segment = false;
        }
      }

      //Try to make straight lines
      x_d = std::abs(start_position.x - end_position.x);
      y_d = std::abs(start_position.y - end_position.y);
      if (x_d < 5) {
        end_position.x = start_position.x;
      }
      if (y_d < 5) {
        end_position.y = start_position.y;
      }

      if (snap_to_16x16 == true) {

        if (start_position.x % 16 != 0) {
          start_position.x = (start_position.x / 16) * 16;
        }
        if (start_position.y % 16 != 0) {
          start_position.y = (start_position.y / 16) * 16;
        }
        if (end_position.x % 16 != 0) {
          end_position.x = (end_position.x / 16) * 16;
        }
        if (end_position.y % 16 != 0) {
          end_position.y = (end_position.y / 16) * 16;
        }
      }

      Segments.push_back(Engine::BuildSegmentMesh('b', { start_position.x, start_position.y }, { end_position.x,end_position.y }));
      //std::cout << "Segments.push_back(Engine::BuildSegmentMesh('b', {" << start_position.x << ", " << start_position.y << " }, { " << end_position.x << "," << end_position.y << " }));\n";
    }
  } 
}

void OakTreeLevel::OnBegin()
{
  Engine::SetGravity(Gravity);
  if (MainCharacter->GetActorPosition().x != 384 && MainCharacter->GetActorPosition().y != 528) {
    MainCharacter->SetActorPosition({ 398, 250 });
  }
}

void OakTreeLevel::OnEnd()
{
}
