#ifndef LINESEGCONVEYOR_H_INCLUDED
#define LINESEGCONVEYOR_H_INCLUDED

#include "lineSeg.h"

class lineSegConveyor : public lineSeg
{
public:
  // inherited data members
  //    vec2d pos, L, N;
  //    sf::Vertex vtx[2];

  //    float drag;

  // added dms
  vec2d uVel;
  float vel;

  // funcs
  lineSegConveyor() : lineSeg() {}// don't use a default constructed lineSeg
  virtual void init(std::istream& fin);
  lineSegConveyor(std::istream& fin) {
    init(fin);
  }
  virtual state_ab* newState() {
    return new state_f(&vel, nullptr);
  }// caching vel in a state_f

  virtual ~lineSegConveyor() {}

  virtual void to_file(std::ofstream& fout);
  virtual bool hit(mvHit& mh);
};

#endif // LINESEGCONVEYOR_H_INCLUDED
