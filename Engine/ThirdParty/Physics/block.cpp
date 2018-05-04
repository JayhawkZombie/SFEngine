#include "block.h"
#include "ball.h"

block::block(std::istream& fin) { init(fin); }// from file data

void block::init(std::istream& fin)// from file data
{
  nSides = 4;
  fin >> W >> H;
  r = sqrtf(W*W + H * H);

  float iAngle = 0.0f;
  fin >> iAngle;
  fin >> pos.x >> pos.y >> v.x >> v.y;
  fin >> m >> Cr;// new
                 //    sf::Uint8 rd,gn,bu;
  unsigned int rd, gn, bu;
  fin >> rd >> gn >> bu;

  ptVec.reserve(nSides);
  vtxVec.reserve(nSides + 1);
  /*   float ang1 = atanf(W/H);
  float ang2 = atanf(H/W);
  vec2d pt0( -cosf(ang1), -sinf(ang1) );// starter side - up lt
  ptVec.push_back( pt0 );
  pt0.x *= -1.0f;// pt0.y = -sinf(ang1);// up rt
  ptVec.push_back( pt0 );
  pt0.x = cosf(ang2); pt0.y = sinf(ang2);// dn rt
  ptVec.push_back( pt0 );
  pt0.x *= -1.0f;
  ptVec.push_back( pt0 ); */

  //   std::cerr << "block ctor: nSides=" << nSides << " W = " << W << " H = " << H << '\n';

  float hW = W / 2.0f, hH = H / 2.0f;
  ptVec.push_back(vec2d(-hW, -hH));// up lt
  ptVec.push_back(vec2d(hW, -hH));// up rt
  ptVec.push_back(vec2d(hW, hH));// dn rt
  ptVec.push_back(vec2d(-hW, hH));// dn lt

  for (size_t i = 0; i<nSides; ++i) ptVec[i] = ptVec[i].Rotate(iAngle);

  for (size_t i = 0; i<nSides; ++i)
    vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + ptVec[i].x, pos.y + ptVec[i].y), sf::Color(rd, gn, bu)));

  vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + ptVec[0].x, pos.y + ptVec[0].y), sf::Color(rd, gn, bu)));
}

float block::getRotation()const
{
  vec2d top = ptVec[1] - ptVec[0];
  return atan2f(top.y, top.x);
}

void block::setRotation(float angle)
{
  //   circPos = angle;
  float hW = W / 2.0f, hH = H / 2.0f;
  ptVec[0].x = -hW; ptVec[0].y = -hH;// up lt
  ptVec[1].x = hW; ptVec[1].y = -hH;// up rt
  ptVec[2].x = hW; ptVec[2].y = hH;// dn rt
  ptVec[3].x = -hW; ptVec[3].y = hH;// dn lt

  for (size_t i = 0; i<nSides; ++i) ptVec[i] = ptVec[i].Rotate(angle);

  for (size_t i = 0; i<nSides; ++i)
  {
    vtxVec[i].position.x = pos.x + ptVec[i].x;
    vtxVec[i].position.y = pos.y + ptVec[i].y;
  }

  vtxVec[nSides].position.x = pos.x + ptVec[0].x;
  vtxVec[nSides].position.y = pos.y + ptVec[0].y;

  return;
}

bool block::is_inMe(const ball& rB, vec2d& sep, vec2d& N, float& dSep)const
{
  // crude check for collision. Check distance between centers.
  sep = pos - rB.pos;
  float sepMag = sep.mag();
  float sepSq = (pos - rB.pos).dot(pos - rB.pos);
  if (sepSq > (r + rB.r)*(r + rB.r)) return false;// not touching

                                                  // is a point stuck in the ball?
  bool Hit = false;
  size_t i_min = 0;
  vec2d s = pos + ptVec[0] - rB.pos;
  float sSqMin = s.dot(s);
  if (sSqMin < rB.r*rB.r) Hit = true;// hit! 1st try too!

                                     // try the other points too
  for (size_t i = 1; i<nSides; ++i)
  {
    s = pos + ptVec[i] - rB.pos;
    float sSq = s.dot(s);
    if (sSq < rB.r*rB.r) Hit = true;// hit!

    if (sSq < sSqMin)
    {
      i_min = i;
      sSqMin = sSq;
    }
  }

  if (Hit)
  {
    sep = pos + ptVec[i_min] - rB.pos;
    sepMag = sep.mag();
    dSep = rB.r - sepMag;
    N = sep / sepMag;
  }

  const vec2d& P = ptVec[i_min];
  const vec2d& P_prev = (i_min == 0) ? ptVec.back() : ptVec[i_min - 1];// who loves the ternary operator? I do too!
  const vec2d& P_next = (i_min + 1 == ptVec.size()) ? ptVec.front() : ptVec[i_min + 1];
  // check for face hit
  vec2d T = P_next - P;
  vec2d b = pos + P - rB.pos;
  T /= T.mag();
  float bDotT = b.dot(T);
  if (bDotT > 0.0f)
  {
    T = P_prev - P;
    T /= T.mag();
    bDotT = b.dot(T);
    if (bDotT > 0.0f) return Hit;// neither face is across arc
  }

  sep = b - T * bDotT;
  sepMag = sep.mag();
  sepSq = sep.dot(sep);

  if (sepSq < rB.r*rB.r)// in circle
  {
    dSep = rB.r - sepMag;
    N = sep / sepMag;
    return true;
  }

  return false;
}

bool block::intersect(ball& rB)
{
  vec2d sep = pos - rB.pos;
  float sepMag = sep.mag();
  vec2d uh = ptVec[1] - ptVec[2]; uh /= uh.mag();
  float projH = fabs(sep.dot(uh));
  vec2d uw = ptVec[1] - ptVec[0]; uw /= uw.mag();
  float projW = fabs(sep.dot(uw));
  if (projH < H / 2.0f && projW < W / 2.0f) return true;// may be entirely within.

                                                        //   vec2d sep, N;
  vec2d N;
  float a;
  return is_inMe(rB, sep, N, a);
}

/*
bool block::inCircle( vec2d ctr, float R, vec2d& Pimp )const
{
// crude check for collision. Check distance between centers.
float sepSq = ( pos - ctr ).dot( pos - ctr );
if( sepSq > (r + R)*(r + R) ) return false;// not touching

// is a point stuck in the ball?
bool Hit = false;
size_t i_min = 0;
vec2d s = pos + ptVec[0] - ctr;
float sSqMin = s.dot(s);
if( sSqMin < R*R )// hit! 1st try too!
{
Pimp = ctr + s;
Hit = true;
}

// try the other points too
for( size_t i=1; i<nSides; ++i )
{
s = pos + ptVec[i] - ctr;
float sSq = s.dot(s);
if( sSq < R*R )// hit!
{
Pimp = ctr + s;
Hit = true;
}

if( sSq < sSqMin )
{
i_min = i;
sSqMin = sSq;
}
}

if( Hit )
{
Pimp = pos + ptVec[i_min];
//     return true;// ?? seems to be ok
}

const vec2d& P = ptVec[i_min];
const vec2d& P_prev = ( i_min == 0 ) ? ptVec.back() : ptVec[i_min-1];// who loves the ternary operator? I do too!
const vec2d& P_next = ( i_min + 1 == ptVec.size() ) ? ptVec.front() : ptVec[i_min+1];
// check for face hit
vec2d T = P_next - P;
vec2d b = pos + P - ctr;
T /= T.mag();
float bDotT = b.dot(T);
if( bDotT > 0.0f )
{
T = P_prev - P;
T /= T.mag();
bDotT = b.dot(T);
if( bDotT > 0.0f ) return Hit;// neither face is across arc
}

Pimp = b - T*bDotT;

if( Pimp.dot(Pimp) < R*R  )// in circle
{
Pimp += ctr;
return true;
}

return false;
}   */
