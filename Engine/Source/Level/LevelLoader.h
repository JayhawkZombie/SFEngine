#pragma once

#include "Globals\GlobalHooks.h"
#include "Level\LevelObject.h"
#include "Actor\Player.h"
#include "Tiles\LevelTile.h"
#include "Lights\GlobalLightSource.h"
#include "Physics\QuadTree.h"
#include "Factory\Factory.h"

namespace Engine
{

  struct LoaderLayer {
    QuadTree ObjectTree;

  };

  struct TestLayer {
    std::vector<std::vector<std::shared_ptr<LevelTile>>> Tiles;
  };

  struct LayerInfo
  {
    std::string RawLayout;
    std::vector<std::vector<std::string>> FormalLayout;
  };

  class Level;

  class LevelLoader
  {
  public:
    LevelLoader();
    ~LevelLoader();

    void Load(const std::string &lvlfile);
    void JoinThread();
    void TestRender();
    bool DoneLoading() const;

    void SetLevel(Level *lvl);

  private:
    std::thread LOADER_THREAD;
    std::mutex *Lock;
    bool FailedToLoad;
    bool IsDoneSettingData = false;
    bool ReadyToTest = false;

    Level *lvl;
    std::string LevelFile;
    std::string TileSheetPath;

    std::size_t LevelHeight, LevelWidth;
    std::size_t NumTiles, TileHeight, TileWidth;
    std::size_t NumTilesWide, NumTilesHigh;

    std::shared_ptr<Engine::LevelTile> *Tiles;
    std::vector<DoubleStringPair> TilePairs;
    std::vector<std::string> PairTexts;

    std::vector<std::shared_ptr<Engine::LevelTile>> BaseTiles;
    SharedTexture TileSheet;
    std::shared_ptr<SpriteSheet> TileSpriteSheet;

    void DebugPrintData();

    void LoadLevelInformation(const std::string &filename);
    void LoadFailure(std::ifstream &IN);
    void LoadConfigInfo(std::ifstream &IN);
    void LoadLayerInfo(std::ifstream &IN);
    void LoadTileInfo(std::ifstream &IN);
    void LoadLayoutInfo(std::ifstream &IN);
    void RequestLevelData();
    void FormalizeLayerLayouts();
    void ReceiveLevelTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID);
    void SetLevelData();
    void LoadLayerData(std::ifstream &IN);
    void LoadTilesData(std::ifstream &IN);
    void LoadObjectData(std::ifstream &IN);

    void LoadLights(std::ifstream &IN);
    void LoadVolumes(std::ifstream &IN);
    void LoadActors(std::ifstream &IN);
  };


}
