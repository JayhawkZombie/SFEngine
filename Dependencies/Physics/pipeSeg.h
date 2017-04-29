#ifndef PIPESEG_H_INCLUDED
#define PIPESEG_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include"segHit.h"
#include"mvHit.h"

#include"lineSeg.h"// for pipeSegLine
#include"arcSeg.h"// for pipeSegArc

class pipeSeg
{
public:
  vec2d pos;
  float W;// width or diameter of pipe
  float vf;// fluid speed

  pipeSeg() {}
  pipeSeg(vec2d Pos, float Width) : pos(Pos), W(Width) {}
  virtual ~pipeSeg() {}

  bool hit(mvHit& mh);// true if mh within? update mh elsewhere
  virtual bool is_inMe(mvHit& mh, float& b, vec2d& T) = 0;
  virtual void draw(sf::RenderTarget&)const = 0;
};


class pipeSegLine : public pipeSeg
{
public:
  float L;// length
  lineSeg wallLt, wallRt;// in direction dir

  pipeSegLine() {}
  pipeSegLine(vec2d& Pos, vec2d& T, float Width, float Length, float Vf);// writes ending pos, dir to args. For chaining
  void init(vec2d& Pos, vec2d& T, float Width, float Length, float Vf);// writes ending pos, dir to args. For chaining
  virtual ~pipeSegLine() {}

  virtual bool is_inMe(mvHit& mh, float& b, vec2d& T);// writes distance off centerline to b (+ toward wallLt)
  virtual void draw(sf::RenderWindow& rRW)const {
    wallLt.draw(rRW); wallRt.draw(rRW);
  }
};

class pipeSegArc : public pipeSeg
{
public:
  float R;
  arcSeg wallOut, wallIn;

  pipeSegArc() {}
  pipeSegArc(vec2d& Pos, vec2d& T, float Width, float Angle, float Vf);// writes ending pos, dir to args. For chaining
  void init(vec2d& Pos, vec2d& T, float Width, float Angle, float Vf);// writes ending pos, dir to args. For chaining
  virtual ~pipeSegArc() {}

  virtual bool is_inMe(mvHit& mh, float& b, vec2d& T);// writes distance off centerline to b (+ toward wallLt)
  virtual void draw(sf::RenderWindow& rRW)const {
    wallOut.draw(rRW); wallIn.draw(rRW);
  }
};



#endif // PIPESEG_H_INCLUDED
