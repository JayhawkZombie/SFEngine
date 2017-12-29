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

#include "Utils\AssetConverters.h"

//--DEFINE IN_GAME WHEN COOKING FOR RELEASE!!!
#ifndef IN_GAME //if we aren't actually launching a game (ie we are in the compiler)

namespace Engine
{

  namespace Convert
  {

    namespace
    {

      struct __Tile {
        __Tile() = default;
        __Tile(const __Tile &other)
          : Configs(other.Configs), ID(other.ID), Frames(other.Frames)
        {}

        std::size_t Configs = 0b00;
        std::string ID = "";
        std::vector<unsigned int> Frames;
      };

      std::map<std::string, __Tile> MapToTiles;
      std::vector<std::string> TileOptionStrings;
    }

    std::size_t get_tile_configs(const std::string &tag, const std::string &sourcefile, std::ifstream &in)
    {
      std::size_t conf{ 0 };
      for (std::size_t i = 0; i < TileOptionStrings.size(); ++i) {
        bool val = Util::GetBooleanConfig(tag, TileOptionStrings[i], false, sourcefile, in);
        conf |= (val ? (1 << i) : 0);
      }

      return conf;
    }

    void encode_tile(const std::string &tag, std::ofstream &out)
    {
      //encode the TileID string
      __Tile tile = MapToTiles[tag];
      Encode::String(tile.ID, out);

      //encode the configs for it
      out.write((char *)(&tile.Configs), sizeof(tile.Configs));

      //encode the frames for the tile
      for (auto & frame : tile.Frames)
        out.write((char *)(&frame), sizeof(frame));
    }

    void encode_layer(std::size_t layernumber, std::vector<std::string> &layout, std::ofstream &out)
    {
      //write out the layer number
      out.write((char *)(&layernumber), sizeof(layernumber));
    }

    std::vector<sf::IntRect> get_frames(const std::string &sourcefile, std::ifstream &in)
    {
      std::string _framestr = Util::GetBracedConfig("Config", "Frames", "{}", sourcefile, in);
      _framestr.erase(_framestr.begin() + 0); _framestr.erase(_framestr.end() - 1);

      std::vector<sf::IntRect> Frames;
      std::stringstream SS(_framestr);
      std::string discard;

      sf::IntRect rect;
      while (SS 
             >> rect.left 
             >> rect.top 
             >> rect.width 
             >> rect.height) 
      {
        Frames.push_back(rect);
      }

      return Frames;
    }

    std::vector<sf::IntRect> divide_image(const sf::Vector2u ImageSize, unsigned int TileHeight, unsigned int TileWidth)
    {
      std::vector<sf::IntRect> Frames;
      //get num tiles across the image
      std::size_t numacross = ImageSize.x / TileWidth;
      std::size_t numhigh = ImageSize.y / TileHeight;

      sf::IntRect Frame{ 0,0,0,0 };

      for (std::size_t y = 0; y < numhigh; ++y) {
        for (std::size_t x = 0; x < numacross; ++x) {
          Frame.left = x * TileWidth;
          Frame.top = y * TileWidth;
          Frame.width = TileWidth;
          Frame.height = TileHeight;

          Frames.push_back(Frame);
        }
      }

      return Frames;
    }

    /**
     *  Format
     *  [String]  LevelID String
     *  [String]  TileSheetPath
     *  [size_t]  NumFramesInSheet
     *  [IntRect] FramesFromSheet
     *  [size_t]  NumTiles
     *  [Tile]    Encoded Base Tile Data
     *  [size_t]  NumLayers
     *    [size_t]  LayerNumber
     *    [size_t]  NumTilesInLayer
     *       [Tile]   Encoded Tiles
     *
     */
    void Level(const std::string &SourceIni)
    {
      std::cerr << ">>> Level conversion beginning" << std::endl;
      std::string DISCARD;

      std::ofstream out;
      std::ifstream in(SourceIni);
      if (!in) {
        std::cerr << "Error opening source level ini file" << std::endl;
        return;
      }
      else {
      //get the name of the level (ItemID for the level)
      //and then try to create the ouptut file (opened in binary mode, of course)
        std::string LevelName = Util::GetStringConfig("Config", "LevelName", "Untitled", SourceIni, in);
        std::cerr << ">>> LevelID: " << LevelName << std::endl;

        std::string SFASSETFILE = LevelName + ".sflevel";
        std::cerr << ">>> DestinationFile: " << SFASSETFILE << std::endl;

        out.open(SFASSETFILE, std::ios::out | std::ios::binary);
        if (!out)
          throw std::runtime_error("Unable to open output file for SFASSET file");

        Encode::String(LevelName, out);

        //get the path for the tile sheet
        std::string TileSheetPath = Util::GetStringConfig("Config", "TileSheet", "", SourceIni, in);
        std::cerr << ">>> TileSheetPath: " << TileSheetPath << std::endl;
        Encode::String(TileSheetPath, out);

        //OK, so we have to get the actual tiles out of it now
        bool divide = Util::GetBooleanConfig("Config", "EvenlyDivideTiles", true, SourceIni, in);
        //get the height/width of the tiles
        std::size_t TileHeight{ 1 }, TileWidth{ 1 };
        TileHeight = Util::GetUnsignedIntConfig("Config", "TileHeight", 1, SourceIni, in);
        TileWidth = Util::GetUnsignedIntConfig("Config", "TileWidth", 1, SourceIni, in);

        //get the frames that are in the tile sheet
        std::vector<sf::IntRect> Frames;
        Frames = get_frames(SourceIni, in);

        //encode the number of frames
        std::size_t framecnt = Frames.size();
        out.write((char *)(&framecnt), sizeof(framecnt));

        //encode the frames
        for (auto & frame : Frames)
          Encode::Rect(frame, out);

        for (auto & frame : Frames)
          std::cerr << ">>> \tFrame: (" << frame.left << ", " << frame.top << ", " << frame.width << ", " << frame.height << ")" << std::endl;

        std::size_t NumLayers = Util::GetUnsignedIntConfig("Config", "NumLayers", 1, SourceIni, in);
        std::size_t NumTiles = Util::GetUnsignedIntConfig("Config", "NumTiles", 0, SourceIni, in);
        std::cerr << ">>> NumLayers: " << NumLayers << std::endl;
        std::cerr << ">>> NumTiles: " << NumTiles << std::endl;

        //get the config options for the tiles
        std::string _tileoptstr = Util::GetBracedConfig("Config", "TileConfigs", "{}", SourceIni, in);
        //remove excess '{' and '}'
        _tileoptstr.erase(_tileoptstr.begin() + 0); _tileoptstr.erase(_tileoptstr.end() - 1);

        std::stringstream TileOptionsStream(_tileoptstr);
        //push into vector to store strings
        while (TileOptionsStream >> DISCARD)
          TileOptionStrings.push_back(DISCARD);

        for (auto & str : TileOptionStrings)
          std::cerr << ">>> TileOpt: " << str << std::endl;

        //get the tile mapping
        std::string TileMappingString = Util::GetBracedConfig("Config", "Tiles", "{}", SourceIni, in);
        //remove the {} around the string
        TileMappingString.erase(TileMappingString.begin() + 0);
        TileMappingString.erase(TileMappingString.end() - 1);

        std::stringstream TileMappingStream(TileMappingString);
        std::pair<std::string, std::string> pair;
        while (TileMappingStream >> pair.first && TileMappingStream >> pair.second) {
          __Tile t;
          t.ID = pair.second;
          t.Configs = get_tile_configs(t.ID, SourceIni, in);
          std::cerr << ">>> " << t.ID << " configs: " << t.Configs << std::endl;

          MapToTiles.emplace(
            std::piecewise_construct,
            std::make_tuple(pair.first),
            std::make_tuple(t)
          );
        }

        //write out the number of different kinds of tiles
        std::size_t tilecnt = MapToTiles.size();
        out.write((char *)(&tilecnt), sizeof(tilecnt));

        for (auto & mapping : MapToTiles) {
          std::cerr << ">>> " << mapping.first << " --> " << mapping.second.ID << std::endl;
          //write out tile info for each type of tile
          encode_tile(mapping.first, out);
        }


        //get the layouts
        std::string piece;
        std::string LayoutTag{ "" };

        std::map<std::string, std::vector<sf::Vector2f>> TilePositions;
        
        std::size_t LayerHeight{ 0 }, LayerWidth{ 0 };
        std::cerr << "--------- Layouts ----------" << std::endl;
        for (std::size_t i = 0; i < NumLayers; ++i) {
          LayoutTag = "Layer" + std::to_string(i);
          std::cerr << ">>> " << LayoutTag << std::endl;
          std::string layoutstr = Util::GetBracedConfig(LayoutTag, "TileLayout", "{}", SourceIni, in);
          LayerHeight = Util::GetUnsignedIntConfig(LayoutTag, "Height", 0, SourceIni, in);
          LayerWidth = Util::GetUnsignedIntConfig(LayoutTag, "Width", 0, SourceIni, in);

          std::cerr << ">>> Layer Height : " << LayerHeight << std::endl;
          std::cerr << ">>> Layer Width  : " << LayerWidth << std::endl;

          layoutstr.erase(layoutstr.begin() + 0); layoutstr.erase(layoutstr.end() - 1);
          std::cerr << ">>> Layoutstr    : " << layoutstr << std::endl;


          std::stringstream SS(layoutstr);
          std::string _tilestr;

          std::size_t x{ 0 }, y{ 0 };
          sf::Vector2f pos;

          std::vector<std::string> Layout;
          std::string RealTileID;

          while (SS >> _tilestr) {
            
            if (_tilestr != "_") {
              //non-empty tile
              RealTileID = MapToTiles[_tilestr].ID;
              
              pos = sf::Vector2f(x * TileWidth, y * TileHeight);

              std::cerr << ">>> " << RealTileID << " : (" << pos.x << ", " << pos.y << ") " << std::endl;
              if (TilePositions.find(RealTileID) == TilePositions.end())
                TilePositions[RealTileID] = {};

              TilePositions[RealTileID].push_back(pos);
            } //if (_tilestr != "_")

            ++x;
            if (x >= LayerWidth) {
              x = 0;
              ++y;
            }
          } //while SS >> _tilestr
          //test print out positions of each kind of tile
          std::cerr << std::endl;
          
        } //for i = 0 -> NumLayers

      }

      in.close();
      out.close();
    }

    void Animation(const std::string &SourceIni)
    {

    }

    void Tile(const std::string &SourceIni)
    {

    }

  }
}

#endif