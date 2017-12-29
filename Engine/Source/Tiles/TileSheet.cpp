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

#include "Tiles\TileSheet.h"

/*
std::shared_ptr<sf::Texture> Texture;
std::map<std::string, sf::VertexArray> GenericTiles;
std::map<std::string, std::shared_ptr<LevelTile>> Tiles;
sf::RenderStates SheetState;
*/

TileSheet::TileSheet()
  : BaseEngineInterface()
{

}

TileSheet::TileSheet(const TileSheet & Copy)
  : 
  Texture(Copy.Texture),
  GenericTiles(Copy.GenericTiles),
  Tiles(Copy.Tiles),
  SheetState(Copy.SheetState),
  BaseEngineInterface(Copy)
{
}

TileSheet::~TileSheet()
{
}

std::shared_ptr<BaseEngineInterface> TileSheet::Clone() const
{
  auto Sheet = std::make_shared<TileSheet>(*this);

  return Sheet;
}

void TileSheet::SerializeIn(std::ifstream & in)
{
}

void TileSheet::SerializeOut(std::ofstream & out)
{
}

void TileSheet::TickUpdate(const double & delta)
{
}

void TileSheet::Render(std::shared_ptr<sf::RenderTarget> Target)
{
    
}

void TileSheet::OnShutDown()
{
}

void TileSheet::RenderTiles(const sf::VertexArray & Vertices)
{
}

void TileSheet::ReadFromMap(const std::string & filename)
{
  /*This will read from a text file like:
    some_tile_name = <num - Left> <num - Top> <num - Width> <num - Height>
    eg
      fire_tile = 0 0 168 168
      water_tile = 168 168 168 168
      etc
  */
  std::ifstream mapin(filename);
  if (!mapin)
    throw StreamException({ ExceptionCause::StreamFailure }, EXCEPTION_MESSAGE("Failed to open map file for tile sheet"));

  std::string tile_name{ "" };
  std::string discard{ "" };
  sf::IntRect tile_rect{ 0, 0, 0, 0 };

  sf::VertexArray vArr = sf::VertexArray(sf::Quads, 4);

  while (mapin >> tile_name) {
    std::shared_ptr<LevelTile> Tile = std::make_shared<LevelTile>();

    mapin >> discard;
    mapin >> tile_rect.left >> tile_rect.top >> tile_rect.width >> tile_rect.height;

    //Assign the name and tile texture coordinates
    Tile->SetID(tile_name);
    vArr[0].texCoords = { static_cast<float>(tile_rect.left), static_cast<float>(tile_rect.top) };
    vArr[1].texCoords = { static_cast<float>(tile_rect.left + tile_rect.width), static_cast<float>(tile_rect.top) };
    vArr[2].texCoords = { static_cast<float>(tile_rect.left + tile_rect.width), static_cast<float>(tile_rect.top + tile_rect.height) };
    vArr[3].texCoords = { static_cast<float>(tile_rect.left), static_cast<float>(tile_rect.top + tile_rect.height) };

    //store the generic tile so we can generate new ones when requested
    GenericTiles[tile_name] = vArr;
  }
}

sf::VertexArray TileSheet::GetTileVertices(const std::string & Name) const
{
  auto it = GenericTiles.find(Name);

  if (it != GenericTiles.end()) {
    return it->second;
  }
  else {
    throw InvalidParameter({ ExceptionCause::InvalidParameter }, EXCEPTION_MESSAGE("Failed to locate tile"));
  }
}

void TileSheet::SetTileVertices(const std::string & Name)
{
}

std::map<std::string, sf::VertexArray> TileSheet::GetTiles()
{
  return GenericTiles;
}

std::shared_ptr<LevelTile> TileSheet::GenerateTile(const std::string & Name)
{
  auto it = GenericTiles.find(Name);

  if (it != GenericTiles.end()) {
    std::shared_ptr<LevelTile> Tile = std::make_shared<LevelTile>();
    Tile->SetFrames(it->second, 1);
    Tile->SetID(Name);

    return Tile;
  }
  else {
    throw InvalidParameter({ ExceptionCause::InvalidParameter }, EXCEPTION_MESSAGE("Failed to locate tile"));
  }
}

std::map<std::string, std::shared_ptr<LevelTile>> TileSheet::GetLevelTiles()
{
  return Tiles;
}

std::shared_ptr<sf::Texture> TileSheet::GetTexture() const
{
  return Texture;
}

void TileSheet::SetTexture(std::shared_ptr<sf::Texture> Tex)
{
  Texture = Tex;
  SheetState.texture = Texture.get();
}

void TileSheet::AddTile(const std::string & str, const sf::IntRect & Rect)
{
  GenericTiles[str] = sf::VertexArray(sf::Quads, 4);
  GenericTiles[str][0].texCoords = { static_cast<float>(Rect.left), static_cast<float>(Rect.top) };
  GenericTiles[str][1].texCoords = { static_cast<float>(Rect.left + Rect.width), static_cast<float>(Rect.top) };
  GenericTiles[str][2].texCoords = { static_cast<float>(Rect.left + Rect.width), static_cast<float>(Rect.top + Rect.height) };
  GenericTiles[str][3].texCoords = { static_cast<float>(Rect.left), static_cast<float>(Rect.top + Rect.height) };


  Tiles[str] = std::make_shared<LevelTile>();
  Tiles[str]->Name = str;
  Tiles[str]->Sheet = this;
  Tiles[str]->TextureRect = Rect;
  Tiles[str]->TileRect.setTexture(Texture.get());
  Tiles[str]->Frames.back()[0].texCoords = { static_cast<float>(Rect.left), static_cast<float>(Rect.top) };
  Tiles[str]->Frames.back()[1].texCoords = { static_cast<float>(Rect.left + Rect.width), static_cast<float>(Rect.top) };
  Tiles[str]->Frames.back()[2].texCoords = { static_cast<float>(Rect.left + Rect.width), static_cast<float>(Rect.top + Rect.height) };
  Tiles[str]->Frames.back()[3].texCoords = { static_cast<float>(Rect.left), static_cast<float>(Rect.top + Rect.height) };
}

void TileSheet::RemoveTile(const std::string & str)
{
  auto it = GenericTiles.find(str);
  if (it != GenericTiles.end())
    GenericTiles.erase(it);
}

std::string TileSheet::GetClass() const
{
  return std::string("TileSheet");
}
