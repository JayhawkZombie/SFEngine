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

#include "BasicIncludes.h"

#include "json\json.h"

namespace
{
  std::map<std::string, unsigned int> TexToID;
}

namespace TMX
{

  struct TileAnimationFrame {
    double       m_Duration;
    unsigned int m_Frame;
  };

  class Tile
  {
  public:
    sf::IntRect  m_TexCoords;
    unsigned int m_GlobalID;
    bool         m_IsAnimated = false;
    std::vector<TileAnimationFrame> m_AnimationFrames;
  };

  class TileSet
  {
  public:
    TileSet() = default;

    void Parse(const Json::Value &JsonDoc);
    void InitTileInfo();
    void ParseTileProperties(const Json::Value &JsonDoc);
  protected:
    static void ParseAnimatedTile(const Json::Value &JsonDoc, TileSet *set);


    std::string  m_Name;
    unsigned int m_Columns;
    unsigned int m_FirstGid;
    std::string  m_Image;
    unsigned int m_ImageHeight;
    unsigned int m_ImageWidth;
    unsigned int m_TileCount;
    unsigned int m_TileHeight;
    unsigned int m_TileWidth;
    std::shared_ptr<sf::Texture> m_Texture;
    std::map<unsigned int, TMX::Tile> m_Tiles;
  };

  /*
    Layer - Holds the layout of the tiles

    A Layer will contain static tiles (non-animated) and
      dynamic tiles (animated)
    The static tiles never need to be updated, and only the animated tiles will be updated every frame.

    A mapping will exist from every known texture alias to the tiles on this layer that use tiles from that alias
    Another mapping will hold the grunt of the data about every individual tile
  */
  class Layer
  {
  public:
    Layer() = delete;
    Layer(const Json::Value &JsonDoc, std::vector<TMX::TileSet> &TileSets);
    ~Layer();

  protected:
    /*
      This is what will be rendered, for each texture alias known
      -- Every texture alias loaded is given an ID and this will map from that 
          to a sf::VertexArray containing the position and texcoords for every
          tile to be rendered from that alias on this layer

          If a tile is animated, that tile will be aware of where it is in that array and will be able to update itself
    */
    std::map<unsigned int, sf::VertexArray> m_TexToTiles;

    /*
      We will map from the global id given to each tile to the tile itself
    */
    std::map<unsigned int, TMX::Tile> m_Tiles;

    /*
      We will maintain a set of tiles that are animated
        This way we can iterate over only these tiles and update only those that we absolutely have to update
    */
    std::set<unsigned int> m_AnimatedTiles;
  };

  class Map
  {
  public:
    Map() = delete;
    Map(const std::string &file);
    ~Map();

  protected:
    unsigned int m_Height;
    unsigned int m_Width;
    std::string  m_Orientation = "orthogonal";
    std::string  m_RenderOrder = "left-down";

    std::vector<TMX::TileSet> m_TileSets;
  };

}
