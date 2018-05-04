#include "lineSegRotate.h"
#include "mvHit.h"

lineSegRotate::lineSegRotate(std::istream& fin) : lineSeg(fin)
{
  fin >> rotVel;
}

void lineSegRotate::init(std::istream& fin)
{
  lineSeg::init(fin);// base overload
  fin >> rotVel;
}

void lineSegRotate::to_file(std::ofstream& fout)
{
  fout << "R\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu << '\n';
  fout << rotVel;
}

void lineSegRotate::update(float dt)
{
  // rotate L
  L = L.Rotate(rotVel*dt);
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
  N = L.get_LH_norm();
  return;
}

bool lineSegRotate::hit(mvHit& mh)
{
  vec2d Pimp, Nh;
  float dSep;

  if (mh.is_inMe(*static_cast<const lineSeg*>(this), Pimp, Nh, dSep))
  {
    float magL = L.mag();// as per hit() above
    vec2d T = L / magL;
    vec2d Nu = T.get_LH_norm();
    vec2d s = Pimp - pos;
    float d = s.dot(T);// position along lineSeg

    mh.v += Nu * (d*rotVel);
    mh.bounce(Cf, Nh, friction_on);// velocity response
    mh.v -= Nu * (d*rotVel);

    mh.setPosition(mh.pos + Nh * dSep);// position change response
    return true;
  }

  return false;
}

/*
state_ab* lineSegRotate::newState()
{
std::cout << "\nusing vector<float*>";
std::vector<float*> pMyVars;
pMyVars.push_back( &rotVel );
pMyVars.push_back( &L.x );
pMyVars.push_back( &L.y );
return new state_fn( pMyVars, std::bind( &lineSegRotate::setState, this, std::placeholders::_1 ) );
}   */

state_ab* lineSegRotate::newState()
{ std::cout << "\nusing getState()"; return new state_fn(std::bind(&lineSegRotate::getState, this, std::placeholders::_1), std::bind(&lineSegRotate::setState, this, std::placeholders::_1), 3); }

void lineSegRotate::setState(const float* pf)
{
  rotVel = pf[0];
  L.x = pf[1];
  L.y = pf[2];
  vtx[1].position.x = pos.x + L.x;
  vtx[1].position.y = pos.y + L.y;
}

void lineSegRotate::getState(float* pf)const
{
  pf[0] = rotVel;
  pf[1] = L.x;
  pf[2] = L.y;
}
