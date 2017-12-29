#ifndef OBJECT_GRID_H_
#define OBJECT_GRID_H_

#include "../../../Engine/Source/Level/LevelObject.h"
#include "../../../Game/RPGActor.h"

struct GridCell {
  std::vector<std::shared_ptr<LevelObject>> m_Objects;
  std::shared_ptr<RPGActor> m_Actor;
};

class Grid
{
public:
  Grid() = delete;
  Grid(int dimX, int dimY);

  std::vector<std::shared_ptr<LevelObject>> GetObjectsInCell(int X, int Y);
  void InsertObjectInCell(int X, int Y, std::shared_ptr<LevelObject> Object);

protected:
  std::vector<std::vector<GridCell>> m_Cells;
};

#endif
