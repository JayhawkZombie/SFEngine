#ifndef OBJECT_GRID_H_
#define OBJECT_GRID_H_

#include "../../../Engine/Source/Level/LevelObject.h"
#include "../../../Game/RPGActor.h"

struct GridCell {
  std::vector<std::shared_ptr<Engine::LevelObject>> m_Objects;
  std::shared_ptr<RPGActor> m_Actor;
};

class Grid
{
public:
  Grid() = delete;
  Grid(int dimX, int dimY);

  std::vector<std::shared_ptr<Engine::LevelObject>> GetObjectsInCell(int X, int Y);
  void InsertObjectInCell(int X, int Y, std::shared_ptr<Engine::LevelObject> Object);

protected:
  std::vector<std::vector<GridCell>> m_Cells;
};

#endif
