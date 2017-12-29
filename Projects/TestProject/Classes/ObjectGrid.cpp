#include "ObjectGrid.h"

Grid::Grid(int dimX, int dimY)
{
  m_Cells.resize(dimY);
  for (auto & cell : m_Cells)
    cell.resize(dimX);

}

std::vector<std::shared_ptr<Engine::LevelObject>> Grid::GetObjectsInCell(int X, int Y)
{
  static std::vector<std::shared_ptr<Engine::LevelObject>> Objects;

  Objects.clear();

  if (X < m_Cells.size() && Y < m_Cells[X].size()) {
    for (auto & obj : m_Cells[X][Y].m_Objects)
      Objects.push_back(obj);
  }

  return Objects;
}

void Grid::InsertObjectInCell(int X, int Y, std::shared_ptr<Engine::LevelObject> Object)
{
  if (X < m_Cells.size() && Y < m_Cells[X].size()) {
    m_Cells[X][Y].m_Objects.push_back(Object);
  }
}
