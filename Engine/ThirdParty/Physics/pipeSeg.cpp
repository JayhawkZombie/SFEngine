#pragma warning ( push )
#pragma warning ( disable : 4244 )

#include "pipeSeg.h"

// pipeSeg funcs
bool pipeSeg::hit(mvHit& mh)
{
  float b;
  vec2d T;// fluid flow direction
  if (is_inMe(mh, b, T))
  {
    mh.v = mh.v.to_base(T);
    float Cdrag = 0.1f;
    mh.v -= (mh.v - T*vf)*Cdrag;
    mh.v = mh.v.from_base(T);
    return true;
  }
  return false;
}

// pipeSegLine funcs
pipeSegLine::pipeSegLine(vec2d& Pos, vec2d& T, float Width, float Length, float Vf)// writes ending pos, dir to args. For chaining
{
  init(Pos, T, Width, Length, Vf);
}

void pipeSegLine::init(vec2d& Pos, vec2d& T, float Width, float Length, float Vf)// writes ending pos, dir to args. For chaining
{
  pos = Pos;
  W = Width;
  L = Length;
  vf = Vf;
  vec2d hfW = T.get_LH_norm()*W / 2.0f;

  wallLt.init(pos + hfW, pos + T*L + hfW, sf::Color::Cyan);
  wallRt.init(pos - hfW, pos + T*L - hfW, sf::Color::Cyan);
  pos += T*L;
}

bool pipeSegLine::is_inMe(mvHit& mh, float& b, vec2d& T)// writes distance off centerline to b (+ toward wallLt)
{
  T = wallLt.L / L;
  vec2d N = T.get_LH_norm();
  vec2d sep = mh.pos - pos;
  float d = sep.dot(T);

  if (d < 0.0f || d > L) return false;
  b = sep.dot(N);
  if (b < -W / 2.0f || b > W / 2.0f) return false;

  if (!wallLt.hit(mh))
    wallRt.hit(mh);

  return true;
}


// pipeSegArc funcs
pipeSegArc::pipeSegArc(vec2d& Pos, vec2d& T, float Width, float Angle, float Vf)// writes ending pos, dir to args. For chaining
{
  init(Pos, T, Width, Angle, Vf);
}

void pipeSegArc::init(vec2d& Pos, vec2d& T, float Width, float Angle, float Vf)
{
  return;
}

bool pipeSegArc::is_inMe(mvHit& mh, float& b, vec2d& T)// writes distance off centerline to b (+ toward wallLt)
{
  return false;
}

#pragma warning ( pop )