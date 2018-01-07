#include "lineSeg.h"
#include "mvHit.h"

#include <cereal/archives/portable_binary.hpp>

lineSeg::lineSeg(std::istream& fin) : segHit() {
  init(fin);
}

lineSeg::~lineSeg() {}

void lineSeg::init(std::istream& fin)
{
  //    unsigned int r,g,b;
  //    fin >> pos.x >> pos.y;
  segHit::init(fin);
  fin >> L.x >> L.y;
  L -= pos;// new
           //    fin >> r >> g >> b;
           //    vtx[0].color.r = r; vtx[0].color.g = g; vtx[0].color.b = b;
  vtx[0].color.r = 0; vtx[0].color.g = 255; vtx[0].color.b = 0;
  //    std::cout << pos.x << ' ' << pos.y << ' ' << L.x << ' ' << L.y << ' ' << r << ' ' << g << ' ' << b << '\n';
  vtx[1].color = vtx[0].color;
  vtx[0].position.x = pos.x; vtx[0].position.y = pos.y;
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
  N = L.get_LH_norm();
  len = L.mag();
}

void lineSeg::to_file(std::ofstream& fout)
{
  fout << "L\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu;
}

lineSeg::lineSeg(float x1, float y1, float x2, float y2, sf::Color clr) {
  init(x1, y1, x2, y2, clr);
}

void lineSeg::init(float x1, float y1, float x2, float y2, sf::Color clr)
{
  pos.x = x1; pos.y = y1;
  L.x = x2 - x1;  L.y = y2 - y1;
  vtx[0].color = vtx[1].color = clr;
  vtx[0].position.x = x1; vtx[0].position.y = y1;
  vtx[1].position.x = x2; vtx[1].position.y = y2;
  N = L.get_LH_norm();
  len = L.mag();
}

void lineSeg::init(vec2d pt1, vec2d pt2, sf::Color clr)
{
  pos = pt1;
  L = pt2 - pt1;
  vtx[0].color = vtx[1].color = clr;
  vtx[0].position.x = pt1.x; vtx[0].position.y = pt1.y;
  vtx[1].position.x = pt2.x; vtx[1].position.y = pt2.y;
  N = L.get_LH_norm();
  len = L.mag();
}

void lineSeg::setPosition(vec2d Pos)
{
  pos = Pos;
  vtx[0].position.x = pos.x; vtx[0].position.y = pos.y;
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
}

/*
bool lineSeg::is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen )const
{
return mh.is_inMe( *static_cast<const lineSeg*>(this), Pimp, Nh, pen );
}   */

bool lineSeg::hit(mvHit& mh)
{
  //   if( is_hard && deflect(mh) ) return true;

  vec2d Pimp, Nh;
  float dSep;

  if (is_bulletProof && is_hard && is_thruMe(mh.pos, mh.pos + mh.v, Pimp, dSep))// this ruins normal behavior. This acts at too low a speed.
  {
    // v is opposite sidedness
    if (hitSide == 1 && mh.v.dot(N) > 0.0f) return false;// new
    if (hitSide == -1 && mh.v.dot(N) < 0.0f) return false;// new
                                                          // it penetrated
                                                          //     mh.v = mh.v.to_base(N);
                                                          //     mh.v.x *= -mh.Cr;
                                                          //     mh.v = mh.v.from_base(N);
    deflect(mh);
    mh.setPosition(pos + Pimp + dSep*mh.v);
    return true;
  }

  if (mh.is_inMe(*static_cast<const lineSeg*>(this), Pimp, Nh, dSep))
  {
    if (hitSide == 1 && Nh.dot(N) < 0.0f) return false;// new
    if (hitSide == -1 && Nh.dot(N) > 0.0f) return false;// new

    if (is_hard)
    {
      mh.bounce(Cf, Nh, friction_on);// velocity response
      mh.setPosition(mh.pos + Nh*dSep);// position change response
    }
    else
    {
      float grav_N = 0.4f, airDensity = 0.001, fluidDensity = 0.04;
      mh.Float(N, Nh, dSep, grav_N, airDensity, fluidDensity);
    }

    return true;
  }


  return false;
}

bool lineSeg::is_thruMe(vec2d pt1, vec2d pt2, vec2d& Pimp, float& fos)const
{
  vec2d Sf = pt1 - pos;
  vec2d Si = pt2 - pos;
  float Sin = Si.dot(N);
  if (Sin == 0.0f) return false;// because on line. There are other tests for this case.
  float Sfn = Sf.dot(N);
  if (Sfn / Sin > 0.0f) return false;// didn't cross
  float vn = (Sf - Si).dot(N);
  if (vn == 0.0f) return false;// travelling paralel
  fos = Sfn / vn;
  Pimp = Sf - fos*(Sf - Si);
  //    float magL = L.mag();
  //    vec2d T = L/magL;
  vec2d T = L / len;
  float d = Pimp.dot(T);
  //   std::cerr << "\n d: "  << d << " lnpos.N: " << linePos.dot(N);
  //    if( d < 0.0f || d > magL ) return false;// missed ends
  if (d < 0.0f || d > len) return false;// missed ends

  return true;
}

void lineSeg::deflect(mvHit& mh)
{
  mh.v = mh.v.to_base(N);
  mh.v.x *= -mh.Cr;
  mh.v = mh.v.from_base(N);
  //    mh.setPosition( pos + linePos + fos*mh.v );
  return;
}

/*
bool lineSeg::hit( mvHit& mh )
{
vec2d Pimp, Nh;
float dSep;

if( is_onMe( mh, Pimp, Nh, dSep ) )
{
mh.bounce( Cf, Nh, friction_on );// velocity response
mh.setPosition( mh.pos + Nh*dSep );// position change response
return true;
}

return false;
}   */

CEREAL_REGISTER_TYPE(lineSeg);
