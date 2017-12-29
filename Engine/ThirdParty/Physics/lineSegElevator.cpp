#include "lineSegElevator.h"
#include "mvHit.h"

lineSegElevator::lineSegElevator(std::istream& fin) : lineSeg(fin)
{
  fin >> vel.x >> vel.y;
  fin >> sMin >> sMax;
  iPos = pos;
  magVel = vel.mag();
  uVel = vel / magVel;
  set_dn();
}

void lineSegElevator::init(std::istream& fin)
{
  lineSeg::init(fin);// base overload
  fin >> vel.x >> vel.y;
  fin >> sMin >> sMax;
  iPos = pos;
  magVel = vel.mag();
  uVel = vel / magVel;
  set_dn();
}

void lineSegElevator::to_file(std::ofstream& fout)
{
  fout << "E\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu << '\n';
  //   fout << vel.x << ' '  << vel.y << '\n';
  fout << magVel*uVel.x << ' ' << magVel*uVel.y << '\n';
  fout << sMin << ' ' << sMax;
}

void lineSegElevator::update()
{
  if (state == 0) return;

  if (state == 1)// going up
  {
    s += magVel;
    if (s > sMax)
    {
      s = sMax;
      state = 0;
      isUp = true;
      vel *= 0.0f;
    }
  }
  else// going down
  {
    s -= magVel;
    if (s < sMin)
    {
      s = sMin;
      state = 0;
      isDn = true;
      vel *= 0.0f;
    }
  }

  lineSeg::setPosition(iPos + uVel*s);

  return;
}

bool lineSegElevator::hit(mvHit& mh)
{
  vec2d Pimp, Nh;
  float dSep;

  if (mh.is_inMe(*static_cast<const lineSeg*>(this), Pimp, Nh, dSep))
  {
    mh.v -= vel;// relative to co-moving reference frame
    mh.bounce(Cf, Nh, friction_on);// velocity response
    mh.v += vel;// relative to co-moving reference frame
    mh.setPosition(mh.pos + Nh*dSep);// position change response
    return true;
  }

  return false;
}

void lineSegElevator::setPosition(vec2d Pos)
{
  iPos = Pos;
  lineSeg::setPosition(iPos + uVel*s);
}

void lineSegElevator::setVel(vec2d V)
{
  vel = V;
  magVel = vel.mag();
  uVel = vel / magVel;
}

void lineSegElevator::init_up()// trigger actions
{
  if (isUp) return;

  state = 1;
  isDn = false;
  vel = uVel*magVel;
}

void lineSegElevator::init_dn()
{
  if (isDn) return;

  state = -1;
  isUp = false;
  vel = uVel*(-magVel);
}

void lineSegElevator::set_up()// set state
{
  s = sMax;
  isUp = true;
  isDn = false;
  state = 0;
  lineSeg::setPosition(iPos + uVel*s);
  vel *= 0.0f;
}

void lineSegElevator::set_dn()
{
  s = sMin;
  isUp = false;
  isDn = true;
  state = 0;
  lineSeg::setPosition(iPos + uVel*s);
  vel *= 0.0f;
}
