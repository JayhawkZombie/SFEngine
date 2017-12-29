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

#include "Level\Level.h"
#include "Level\LevelLoader.h"

#include <regex>

namespace Engine
{

  LevelLoader::LevelLoader()
  {
    //LayoutIDToTileID = new std::map<std::string, std::string>;
    //TileIDs = new std::vector<std::string>;
    //TileIDToTexture = new std::map<std::string, std::shared_ptr<sf::Texture>>;
    Lock = new std::mutex;
    FailedToLoad = false;
  }

  LevelLoader::~LevelLoader()
  {
    JoinThread();

    //delete LayoutIDToTileID;
    //delete TileIDs;
    //delete TileIDToTexture;
    delete Lock;
  }

  void LevelLoader::SetLevel(Level *l)
  {
    lvl = l;
  }

  void LevelLoader::Load(const std::string &lvlfile)
  {
    LoadLevelInformation(lvlfile);
  }

  void LevelLoader::JoinThread()
  {
    if (LOADER_THREAD.joinable())
      LOADER_THREAD.join();
  }

  bool LevelLoader::DoneLoading() const
  {
    return IsDoneSettingData;
  }

  void LevelLoader::LoadLevelInformation(const std::string &filename)
  {
    LevelFile = filename;

    LOADER_THREAD = std::thread(
      [this, filename]() {
      std::ifstream in(filename);
      this->LoadConfigInfo(in);
    }
    );
  }

  void LevelLoader::LoadFailure(std::ifstream &infile)
  {
    std::cerr << "Failure loading level. Able to read up to: " << infile.tellg() << std::endl;

    Lock->lock();
    //TileIDs->clear();
    //LayoutIDToTileID->clear();

    //for (auto & tex : *TileIDToTexture)
    //  tex.second.reset();

    //TileIDToTexture->clear();
    delete[] Tiles;
    TilePairs.clear();
    PairTexts.clear();
    Lock->unlock();

    infile.clear();
    infile.close();
  }

  void LevelLoader::LoadConfigInfo(std::ifstream &infile)
  {
    if (infile.fail()) {
      LoadFailure(infile);
      return;
    }

    //Get the width and height of the level
    LevelWidth = Util::GetUnsignedIntConfig("Config", "LevelWidth", 0, LevelFile, infile);
    LevelHeight = Util::GetUnsignedIntConfig("Config", "LevelHeight", 0, LevelFile, infile);

    //Get the height and width of the tiles
    TileWidth = Util::GetUnsignedIntConfig("Config", "TileWidth", 0, LevelFile, infile);
    TileHeight = Util::GetUnsignedIntConfig("Config", "TileHeight", 0, LevelFile, infile);

    //Divide the level into tiles
    NumTilesWide = LevelWidth;
    NumTilesHigh = LevelHeight;

    //Load the tile sheet
    TileSheetPath = Util::GetStringConfig("Config", "TileSheet", "", LevelFile, infile);
    TileSheet = std::shared_ptr<sf::Texture>(new sf::Texture);
    if (!TileSheet->loadFromFile(TileSheetPath)) {
      std::cerr << "Unable to load tile sheet" << std::endl;
      throw std::runtime_error("Unable to load tile sheet");
    }

    TileSpriteSheet = std::shared_ptr<SpriteSheet>(new SpriteSheet);
    TileSpriteSheet->SetTexture(TileSheet);
    TileSpriteSheet->EvenlyDivideFrames(TileWidth, TileHeight);

    //Create a temporary storage for the tiles
    //Allocate in 1D array for speed
    Tiles = new std::shared_ptr<Engine::LevelTile>[NumTilesWide * NumTilesHigh];

    ////Create the blank tiles
    //for (std::size_t y = 0; y < NumTilesHigh; ++y) {

    //  for (std::size_t x = 0; x < NumTilesWide; ++x) {

    //    Tiles[y * NumTilesWide + x] = Factory::Tile();

    //  }

    //}
    
    //Load the rest of the information
    LoadTileInfo(infile);
    LoadLayerInfo(infile);
    LoadLayoutInfo(infile);
    FormalizeLayerLayouts();
    RequestLevelData();
    SetLevelData();
    DebugPrintData();
  }

  void LevelLoader::LoadLayerInfo(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadTileInfo(std::ifstream &infile)
  {
    try
    {
    //Regexs to use for parsing
      static std::regex_iterator<std::string::iterator> reg_end;
      static std::string Pair("(<[^>]*>)");
      static std::regex PairRegex(Pair);
      static std::string PairPieces("<(\\w*),( ?\\w*)>");
      static std::regex PairPiecesRegex(PairPieces);

      //Need to get the information about each of the tiles
      std::string TilesPairList = Util::GetBracedConfig("Config", "Tiles", "{}", LevelFile, infile);
      TilesPairList.erase(TilesPairList.begin() + 0);
      TilesPairList.erase(TilesPairList.end() - 1);

      //So first push each of the pairs back as strings "<..., ...>"
      std::regex_iterator<std::string::iterator> reg_iter(TilesPairList.begin(), TilesPairList.end(), PairRegex);
      while (reg_iter != reg_end) {
        PairTexts.push_back(reg_iter->str());
        ++reg_iter;
      }

      //Then parse each string and create a pair for it
      TilePairs.resize(PairTexts.size());

      //Each of those pairs should be unique, so there should be exactly that many tiles
      NumTiles = TilePairs.size();

      std::smatch match;

      for (auto & pair : PairTexts) {

        if (!std::regex_search(pair, match, PairPiecesRegex)) {
          std::string message = "Error parsing tile information. Unable to parse pair <*,*>. Problematic Text: \"" + pair + "\"\n";
          throw std::runtime_error(message);
        }

        /**
         * 3 because match 0 will be the entire string
         * match 1 will be the first item
         * match 2 will be the second item
         *   if there are more than 3 matches, something went wrong
         */
        if (!(match.size() == 3)) {
          std::string message = "Error parsing tile information. Did not find 3 elements in match. Found " + std::to_string(match.size()) + ". Problematic text: \"" + pair + "\"\n";
          throw std::runtime_error(message);
        }

        std::string pair_first = match[1].str();
        std::string pair_second = match[2].str();

        TilePairs.push_back({ pair_first, pair_second });
      }

      LoadTilesData(infile);
    }
    catch (std::runtime_error &e)
    {
      std::cerr << "Level loading failure. Message: " << e.what() << std::endl;
      LoadFailure(infile);
    }
    
  }

  void LevelLoader::LoadTilesData(std::ifstream &infile)
  {

    //std::regex vecreg("([0-9]+)");
    //std::regex_iterator<std::string::iterator> RegEnd;

    //std::string category{ "" };
    //bool trav{ false }, anim{ false };
    //std::vector<std::size_t> frames;

    ////For each of the tiles that we have, we need to load the data for it
    ////Only one for each tile, of course, these are the set of basic tiles and we'll duplicate them
    ////to create the actual layout
    //for (std::size_t i = 0; i < NumTiles; ++i) {
    //  category = TilePairs[i].second;

    //  //First get whether it is traversible/animated
    //  trav = Util::GetBooleanConfig(category, "IsTraversible", trav, LevelFile, infile);
    //  anim = Util::GetBooleanConfig(category, "IsAnimated", anim, LevelFile, infile);

    //  //Now get the frames out of the tile sheet that will be used for the tile
    //  std::string framestring = Util::GetStringConfig(category, "Frames", "", LevelFile, infile);
    //  
    //  //Get the mathces out of the string #,#,#,...
    //  std::regex_iterator<std::string::iterator> reg_iter(framestring.begin(), framestring.end(), vecreg);
    //  std::stringstream SS;
    //  while (reg_iter != RegEnd) {
    //    SS.clear();
    //    SS << reg_iter->str();
    //    std::size_t frame;
    //    SS >> frame;

    //    frames.push_back(frame);
    //  }

    //  BaseTiles.push_back({ Factory::Tile() });
    //  BaseTiles.back()->SetISAnimated(anim);
    //  BaseTiles.back()->SetIsTraversible(trav);
    //  BaseTiles.back()->SetTextureFrameIndices(frames);
    //  BaseTiles.back()->SetTileSheet(TileSpriteSheet);
    //}
    
    ReadyToTest = true;
  }

  void LevelLoader::TestRender()
  {
    //if (!ReadyToTest)
    //  return;

    //for (std::size_t i = 0; i < 10; ++i) {

    //  std::shared_ptr<sf::Sprite> spr = BaseTiles[i]->GetTileSheet()->GetSprite(i);
    //  spr->setPosition(sf::Vector2f(i * 16, i * 16));

    //  Render::RenderSprite(spr.get());

    //}
  }

  void LevelLoader::LoadLayoutInfo(std::ifstream &infile)
  {

  }

  void LevelLoader::RequestLevelData()
  {
    
  }

  void LevelLoader::FormalizeLayerLayouts()
  {

  }

  void LevelLoader::ReceiveLevelTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID)
  {

  }

  void LevelLoader::SetLevelData()
  {

  }

  void LevelLoader::LoadLayerData(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadObjectData(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadLights(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadVolumes(std::ifstream &infile)
  {

  }

  void LevelLoader::LoadActors(std::ifstream &infile)
  {

  }

  void LevelLoader::DebugPrintData()
  {



  }
}
