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
  fout << "F\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu << '\n';
  fout << rotVel << ' ' << acosf(Ldn.dot(Lup) / (len*len));
  return;// define properly or lineSegRotate will be written
}

void lineSegFlip::update(float dt)
{
  if (state == 0) return;

  lineSegRotate::update(dt);
  if (state == 1)// up
  {
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
  else if (L.cross(Ldn)*rotVel < 0.0f)// flip down
  {
    L = Ldn;
    rotVel = 0.0f;
    vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
    N = L.get_LH_norm();
    state = 0;
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

/*
state_ab* lineSegFlip::newState()
{ return new state_fn( std::bind( &lineSegFlip::getState, this, std::placeholders::_1 ), std::bind( &lineSegFlip::setState, this, std::placeholders::_1 ), 4 ); }

void lineSegFlip::setState( const float* pf )
{
rotVel = pf[0];
L.x = pf[1];
L.y = pf[2];
vtx[1].position.x = pos.x + L.x;
vtx[1].position.y = pos.y + L.y;

if( pf[3] > 1.8f ){ isUp = true; state = (int)(pf[3] - 3.0f); }
else { isUp = false; state = (int)pf[3]; }
}

void lineSegFlip::getState( float* pf )const
{
pf[0] = rotVel;
pf[1] = L.x;
pf[2] = L.y;
pf[3] = (float)state + 0.5f;// to round
if( isUp ) pf[3] += 3.0f;
}   */
