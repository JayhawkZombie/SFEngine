#ifndef LINESEGSWING_H_INCLUDED
#define LINESEGSWING_H_INCLUDED

#include "lineSegRotate.h"

class lineSegSwing : public lineSegRotate
{
public:
  // inherited data members
  //    vec2d pos, L, N;
  //    sf::Vertex vtx[2];
  static bool gravity_on;
  float m;// mass
  static vec2d grav;// gravity

  lineSegSwing() : lineSegRotate() {}// don't use a default constructed lineSeg
  lineSegSwing(std::istream& fin);

  virtual ~lineSegSwing() {}
  virtual void init(std::istream& fin);
  virtual void to_file(std::ofstream& fout);

  virtual void update();
  virtual bool hit(mvHit& mh);

  //    virtual bool hit( ball& rB );
};

#endif // LINESEGSWING_H_INCLUDED
