#include "ball.h"

#include "lineSeg.h"
#include "arcSeg.h"

#include <cereal/archives/portable_binary.hpp>

bool ball::hit(regPolygon& py) {
  return py.hit(*static_cast<ball*>(this));
}
bool ball::hit(mvHit& mh) {
  return mh.hit(*static_cast<ball*>(this));
}

/*
bool ball::hit( mvHit& mh )
{
vec2d& Pimp;
float& fos;
if( is_thruMe( vec2d pt1, vec2d pt2, vec2d& Pimp, float& fos ) )
{
return true;
}

return mh.hit( *static_cast<ball*>(this) );
}   */

ball::ball() {}// default

ball::ball(std::istream& fin) {
  init(fin);
}// from file data

void ball::init(std::istream& fin)// from file data
{
  fin >> pos.x >> pos.y >> v.x >> v.y >> r;
  fin >> m >> Cr;// new
  unsigned int red, g, b;
  fin >> red >> g >> b;
  img.setRadius(r);
  img.setPosition(pos.x, pos.y);
  img.setFillColor(sf::Color(red, g, b));
  img.setOrigin(r, r);
  //    std::cout << "ball.v = " << v.mag() << '\n';
}

/*
void ball::respond( float dV, bool isFric )// assumes velocity components are T(x) and N(y) to obstacle
{

if( !isFric ) return;// no change in x component can occur
if( v.y == 0.0f ) return;// target speed acheived
// speed needs adjustment
if( dV < 0.0f ) dV *= -1.0f;// assure dV is positive
if( v.y > 0.0f ){ v.y -= dV; if( v.y < 0.0f ) v.y = 0.0f; }
else { v.y += dV; if( v.y > 0.0f ) v.y = 0.0f; }

return;
}   */

void ball::update()// virtual
{
  if (!is_free) return;// new

  vec2d N(1.0f, 0.0f);
  bool Hit = false;

  pos += v;

  if (pos.x < r)
  {
    pos.x = r;
    Hit = true;
    N.x = 1.0f; N.y = 0.0f;
  }
  else if (pos.x > ball::wdwW - r)
  {
    pos.x = ball::wdwW - r;
    Hit = true;
    N.x = -1.0f; N.y = 0.0f;
  }

  if (Hit) bounce(ball::wdwCf, N, true);

  Hit = false;

  if (!windowTopOpen && pos.y < r)
  {
    pos.y = r;
    Hit = true;
    N.x = 0.0f; N.y = 1.0f;
  }
  else if (pos.y > ball::wdwH - r)
  {
    pos.y = ball::wdwH - r;
    Hit = true;
    N.x = 0.0f; N.y = -1.0f;
  }

  if (Hit) bounce(ball::wdwCf, N, true);
  img.setPosition(pos.x, pos.y);
}

void ball::draw(sf::RenderTarget& rRW)const {
  rRW.draw(img);
}

bool ball::hit(ball& rB)
{
  // check for collision. Check distance between centers.
  float sepSq = (pos - rB.pos).dot(pos - rB.pos);
  if (sepSq > (r + rB.r)*(r + rB.r)) return false;// not touching

  vec2d sep = rB.pos - pos;// from this center to rB center
  float sepMag = sep.mag();// take the sqrt 1 time
                           //   vec2d N = -sep/sepMag;// unit length. First of local base set. 2nd is LH normal
  vec2d N = vec2d(1.0f, 0.0f);// unit length. First of local base set. 2nd is LH normal
  if (sepMag > 1.0f) N = -sep / sepMag;
  handleImpact(rB, sep, N, r + rB.r - sepMag);
  return true;
}

/* // This is working ok
bool ball::Float( vec2d Nsurf, vec2d Npen, float penAmt, float grav_N, float airDensity, float fluidDensity )
{
float belowSurface = (Npen*penAmt).mag();
if( Nsurf.dot(Npen) < 0.0f ) belowSurface = 2.0f*r - belowSurface;

if( belowSurface > 0.0f && belowSurface < 2.0f*r )// partially immersed
{
float b = r - belowSurface;
float A = 2.0f*r*acosf(b/r) - b*sqrtf(r*r - b*b);
float Fbuoy = grav_N*( A*fluidDensity + (3.1416*r*r - A)*airDensity );
v = v.to_base(Nsurf);
v.x += Fbuoy/m;
if( v.x < 0.0f ) v.x -= drag*fluidDensity*v.x*r*2.0f/m;
v.y -= drag*fluidDensity*v.y*belowSurface/m;
v = v.from_base(Nsurf);
return true;
}

return false;
}   */

// accepted version works best so far
bool ball::Float(vec2d Nsurf, vec2d Npen, float penAmt, float grav_N, float airDensity, float fluidDensity)
{
  float belowSurface = (Npen*penAmt).mag();
  if (Nsurf.dot(Npen) < 0.0f) belowSurface = 2.0f*r - belowSurface;

  if (belowSurface > 0.0f && belowSurface < 2.0f*r)// partially immersed
  {
    v = v.to_base(Nsurf);
    //        float Fbuoy = 2.0f*r*belowSurface*pressure;
    float Fbuoy = 2.0f*r*grav_N*(belowSurface*fluidDensity + (2.0f*r - belowSurface)*airDensity);
    v.x += Fbuoy / m;
    //        v.x -= drag*v.x*r*2.0f/m;
    if (v.x < 0.0f) v.x -= drag*fluidDensity*v.x*r*2.0f / m;
    v.y -= drag*fluidDensity*v.y*belowSurface / m;
    v = v.from_base(Nsurf);
    return true;
  }

  return false;
}


bool ball::Float(vec2d Nsurf, float grav_N, float Density)// fully immersed
{
  v = v.to_base(Nsurf);
  float Fbuoy = 3.1416f*r*r*grav_N*Density;
  v.x += Fbuoy / m;
  v -= drag*Density*v*r*2.0f / m;
  v = v.from_base(Nsurf);
  return true;
}

bool ball::hit(const vec2d& pt)
{
  vec2d sep, N;
  float dSep;
  if (is_inMe(pt, sep, N, dSep))
  {
    v = v.to_base(N);
    if (v.x < 0.0f) v.x *= -Cr;// reverse component along sep
    v = v.from_base(N);
    pos += N*dSep;
    return true;
  }

  return false;
}

void ball::setPosition(vec2d Pos)
{
  pos = Pos;
  img.setPosition(pos.x, pos.y);
}

bool ball::is_inMe(vec2d pt, vec2d& sep, vec2d& N, float& dSep)const// sep is relative to ball center
{
  sep = pt - pos;
  float sepMag = sep.mag();
  if (sepMag > r) return false;

  N = -1.0f*sep / sepMag;
  sep = pt;// new
  dSep = r - sepMag;
  return true;
}

// these replace lineInMe(), arcInMe()s
bool ball::is_inMe(const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep)const// detailed collision detection
{
  float magL = LS.L.mag();// length of line
  vec2d T = LS.L / magL;// unit in direction of line
  vec2d N = T.get_LH_norm();// unit normal
  vec2d s = pos - LS.pos;// relative position
  float d = s.dot(T);// position along line

  float h = s.dot(N);// height above line.  s.dot(N) should work also
  if (h > r || h < -r) return false;// too far away

  if ((d > 0.0f) && (d < magL))// center is between ends
  {
    if (h > 0) Pimp = pos - r*N;// on Nside
    else Pimp = pos + r*N;// on back side
    Nh = LS.L.get_LH_norm();// unit normal
    dSep = -1.0f*Nh.dot(Pimp - LS.pos);// amount of penetration
    if (dSep < 0.0f) {
      Nh *= -1.0f; dSep *= -1.0f;
    }
    return true;
  }
  // test for end hits
  if (is_inMe(LS.pos, Pimp, Nh, dSep)) return true;
  return is_inMe(LS.pos + LS.L, Pimp, Nh, dSep);
}

bool ball::is_inMe(const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep)const// code goes here. Impact point is written.
{
  // crude check for collision. Check distance between centers.
  float sepSq = (pos - AS.pos).dot(pos - AS.pos);
  //   float R = ( AS.s[0] ).mag();

  if (sepSq > (r + AS.R)*(r + AS.R)) return false;// too far outside
  if (sepSq < (AS.R - r)*(AS.R - r)) return false;// too far inside

  bool Hit = is_inMe(AS.pos + AS.s[0], Pimp, Nh, dSep);
  if (!Hit) Hit = is_inMe(AS.pos + AS.s[1], Pimp, Nh, dSep);
  // face test even if end is hit. mvHit can roll over end point across face.

  vec2d sep = pos - AS.pos;
  if (sep.cross(AS.s[0]) < 0.0f || sep.cross(AS.s[1]) > 0.0f) return Hit;// ends missed

  sep /= sep.mag();// now a unit vector
  if (sepSq > AS.R*AS.R) Pimp = pos - sep*r;// outside hit
  else Pimp = pos + sep*r;// inside hit

  Nh = Pimp - AS.pos; Nh /= Nh.mag();// unit normal
  dSep = AS.R - (Pimp - AS.pos).mag();// amount of penetration
  if (dSep < 0.0f) {
    Nh *= -1.0f; dSep *= -1.0f;
  }

  return true;
}

bool ball::is_thruMe(vec2d pt1, vec2d pt2, vec2d& Pimp, float& fos)const// for bulletproofing, laser sighting, etc.
{
  vec2d L = pt1 - pt2;
  float magL = L.mag();
  if (magL < 1.0f) return false;
  vec2d Lu = L / magL;
  vec2d S = pt1 - pos;
  vec2d N = vec2d(Lu.y, -Lu.x);
  float b = Lu.cross(S);
  if (b < 0.0f && b < -r) return false;// missed
  if (b > 0.0f && b > r)  return false;// missed
  float a = sqrtf(r*r - b*b);
  Pimp = pos + b*N - a*Lu;
  fos = (pt1 - Pimp).dot(Lu) / magL;

  return true;
}

CEREAL_REGISTER_TYPE(ball);
