#pragma once

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "Globals/GlobalHooks.h"
#include "Objects/GameObject.h"
#include "Actor/Player.h"
#include "Lights/GlobalLightSource.h"
#include "Physics/QuadTree.h"
#include "Factory/Factory.h"

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

  std::shared_ptr<LevelTile> *Tiles;
  std::vector<DoubleStringPair> TilePairs;
  std::vector<std::string> PairTexts;

  std::shared_ptr<sf::Texture> TileSheet;

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
