#include "lineSegFlip.h"

lineSegFlip::lineSegFlip(std::istream& fin) : lineSegRotate(fin)
{
  float angle = 0.0f;
  fin >> angle;
  Lup = L.Rotate(-angle);
  Ldn = L;
  rotVelFlip = rotVel;
  rotVel = 0.0f;
  state = 0;
  isUp = false;
}

void lineSegFlip::init(std::istream& fin)
{
  lineSegRotate::init(fin);
  float angle = 0.0f;
  fin >> angle;
  Lup = L.Rotate(-angle);
  Ldn = L;
  rotVelFlip = rotVel;
  rotVel = 0.0f;
  state = 0;
  isUp = false;
}

void lineSegFlip::to_file(std::ofstream& fout)
{
  return;// define properly or lineSegRotate will be written
}

void lineSegFlip::update()
{
  if (state == 0) return;

  lineSegRotate::update();
  if (state == 1)// up
  {
    //   if( L.cross( Lup ) > 0.0f )
    if (L.cross(Lup)*rotVel < 0.0f)
    {
      L = Lup;
      rotVel = 0.0f;
      vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
      N = L.get_LH_norm();
      state = 0;
      isUp = true;
    }
  }
  else// flip down
  {
    //  if( L.cross( Ldn ) < 0.0f )
    if (L.cross(Ldn)*rotVel < 0.0f)
    {
      L = Ldn;
      rotVel = 0.0f;
      vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
      N = L.get_LH_norm();
      state = 0;
    }
  }

  return;
}

bool lineSegFlip::is_up()const
{
  return isUp;
}

void lineSegFlip::init_up()// trigger actions
{
  state = 1;
  rotVel = -rotVelFlip;
}

void lineSegFlip::init_dn()
{
  state = -1;
  rotVel = rotVelFlip;
  isUp = false;
}

void lineSegFlip::set_up()// trigger actions
{
  state = 0;
  rotVel = 0.0f;
  L = Lup;
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
  N = L.get_LH_norm();
  isUp = true;
}

void lineSegFlip::set_dn()
{
  state = 0;
  rotVel = 0.0f;
  L = Ldn;
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
  N = L.get_LH_norm();
  isUp = false;
}
