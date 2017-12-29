#include "lineSegConveyor.h"
#include "mvHit.h"

void lineSegConveyor::init(std::istream& fin)
{
  lineSeg::init(fin);// base overload
  fin >> vel;
  uVel = (vel / L.mag())*L;
  if (vel < 0.0f) uVel *= -1.0f;
}

void lineSegConveyor::to_file(std::ofstream& fout)
{
  fout << "C\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu << '\n';
  fout << vel << '\n';
}

bool lineSegConveyor::hit(mvHit& mh)
{
  //    bool Hit = mh.hit(pos);
  //   if( Hit ) return true;
  //   Hit = mh.hit(pos+L);
  //   if( Hit ) return true;

  mh.v -= vel*uVel;
  bool Hit = lineSeg::hit(mh);
  mh.v += vel*uVel;
  return Hit;
}
