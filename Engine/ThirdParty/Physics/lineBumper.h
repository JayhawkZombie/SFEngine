#ifndef LINEBUMPER_H_INCLUDED
#define LINEBUMPER_H_INCLUDED

#include "lineSeg.h"

class lineBumper : public lineSeg
{
public:
  // inherited data members
  vec2d vel;

  //    vec2d pos, L, N;
  //    sf::Vertex vtx[2];

  int state = 0;// -1, 0, +1
  int bumpSteps = 3, bumpIdx = 0;

  lineBumper() : lineSeg() {}// don't use a default constructed lineSeg
  lineBumper(std::istream& fin);
  //    lineSegTranslate( vec2d A, vec2d B, float RotVel, sf::Color clr );

  virtual ~lineBumper() {}
  virtual void init(std::istream& fin);
  virtual void to_file(std::ofstream& fout);

  virtual void update();
  virtual bool hit(mvHit& mh);

  void set_bumpSpeed(float v) {
    vel = N*v;
  }
};

#endif // LINEBUMPER_H_INCLUDED
