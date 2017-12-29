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

#include "Tiles\TileGrid.h"

TileGrid::TileGrid()
  : BaseEngineInterface()
{
}

TileGrid::~TileGrid()
{
}

void TileGrid::AddTile(std::shared_ptr<LevelTile> Tile)
{
  Tiles.push_back(Tile);
}

void TileGrid::RemoveTile(std::shared_ptr<LevelTile> Tile)
{
}

void TileGrid::SerializeIn(std::ifstream & in)
{
}

void TileGrid::SerializeOut(std::ofstream & out)
{
}

void TileGrid::TickUpdate(const double & delta)
{
}

void TileGrid::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  for (auto & tile : Tiles)
    tile->Render(Target);
}

void TileGrid::GetTile(const sf::Vector2f & Position) const
{
}

void TileGrid::SetBGTileTexture(std::shared_ptr<sf::Texture> Tex)
{
  BGTileTexture = Tex;
  TileRenderState.texture = BGTileTexture.get();
}

void TileGrid::DrawGridLines(bool draw)
{
  DrawGrid = draw;
}
