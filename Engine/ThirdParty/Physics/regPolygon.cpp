#include "regPolygon.h"
#include "ball.h"

#include "lineSeg.h"
#include "arcSeg.h"

bool regPolygon::hit(mvHit& mh) { return mh.hit(*static_cast<regPolygon*>(this)); }
bool regPolygon::intersect(mvHit& mh) { return mh.intersect(*static_cast<regPolygon*>(this)); }

bool regPolygon::intersect(ball& rB)
{
  if ((pos - rB.pos).mag() < r) return true;// may be entirely within.

  vec2d sep, N;
  float a;
  return is_inMe(rB, sep, N, a);
}

bool regPolygon::intersect(regPolygon& py)
{
  vec2d sep, N;
  float a;
  return is_inMe(py, sep, N, a);
}

bool regPolygon::hit(regPolygon& rpg)
{
  bool Hit = false;
  vec2d sep, N;
  float a;

  Hit = is_inMe(rpg, sep, N, a);
  if (Hit) handleImpact(rpg, sep, N, a);

  return Hit;
}

bool regPolygon::hit(ball& rB)
{
  bool Hit = false;
  vec2d sep, N;
  float a;

  Hit = is_inMe(rB, sep, N, a);
  if (Hit) handleImpact(rB, sep, N, a);

  return Hit;
}

regPolygon::regPolygon() {}// default

regPolygon::regPolygon(std::istream& fin) { init(fin); }// from file data

void regPolygon::init(std::istream& fin)// from file data
{
  float iAngle = 0.0f;
  fin >> nSides >> r >> iAngle;
  fin >> pos.x >> pos.y >> v.x >> v.y;
  fin >> m >> Cr;// new
                 //   sf::Uint8 rd,gn,bu;
  unsigned int rd, gn, bu;
  fin >> rd >> gn >> bu;

  ptVec.reserve(nSides);
  vtxVec.reserve(nSides + 1);
  vec2d pt0(r, 0.0f);// starter side
  pt0 = pt0.Rotate(iAngle);
  float dAngle = 6.283185f / nSides;
  for (size_t i = 0; i<nSides; ++i)
  {
    ptVec.push_back(pt0);
    vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + pt0.x, pos.y + pt0.y), sf::Color(rd, gn, bu)));
    pt0 = pt0.Rotate(dAngle);
  }
  vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + ptVec[0].x, pos.y + ptVec[0].y), sf::Color(gn, rd, bu)));
}

/*
void regPolygon::respond( float dV, bool isFric )// assumes velocity components are T(x) and N(y) to obstacle
{
if( !isFric ) return;// no change in x component can occur
if( v.y == 0.0f ) return;// target speed acheived
// speed needs adjustment
if( dV < 0.0f ) dV *= -1.0f;// assure dV is positive
if( v.y > 0.0f ){ v.y -= dV; if( v.y < 0.0f ) v.y = 0.0f; }
else { v.y += dV; if( v.y > 0.0f ) v.y = 0.0f; }

return;
}   */

void regPolygon::update(float dt)
{
  if (!is_free) return;

  //   if( pGravity ) v += *pGravity;
  pos += v * dt;

  float dr = 0.0f;
  vec2d N(-1.0f, 0.0f);
  //    vec2d T(0.0f,1.0f);
  bool Hit = false;

  if (pos.x < r)
  {
    N.x = 1.0f; N.y = 0.0f;
    dr = project(-1.0f*N);
    if (pos.x < dr)
    {
      pos.x = dr;
      Hit = true;
    }

  }
  else if (pos.x > regPolygon::wdwW - r)
  {
    N.x = -1.0f; N.y = 0.0f;
    dr = project(-1.0f*N);
    if (pos.x > regPolygon::wdwW - dr)
    {
      pos.x = regPolygon::wdwW - dr;
      Hit = true;
    }
  }

  if (Hit) bounce(regPolygon::wdwCf, N, true);
  Hit = false;

  if (!windowTopOpen && pos.y < r)
  {
    N.x = 0.0f; N.y = 1.0f;
    dr = project(-1.0f*N);
    if (pos.y < dr)
    {
      pos.y = dr;
      Hit = true;
    }
  }
  else if (pos.y > regPolygon::wdwH - r)
  {
    N.x = 0.0f; N.y = -1.0f;
    dr = project(-1.0f*N);
    if (pos.y > regPolygon::wdwH - dr)
    {
      pos.y = regPolygon::wdwH - dr;
      Hit = true;
    }
  }

  if (Hit) bounce(regPolygon::wdwCf, N, true);

  for (size_t i = 0; i < ptVec.size(); ++i)
  {
    vtxVec[i].position.x = pos.x + ptVec[i].x;
    vtxVec[i].position.y = pos.y + ptVec[i].y;
  }
  vtxVec[ptVec.size()].position.x = pos.x + ptVec[0].x;
  vtxVec[ptVec.size()].position.y = pos.y + ptVec[0].y;

  return;
}

void regPolygon::draw(sf::RenderTarget& rRW)const { rRW.draw(&(vtxVec[0]), vtxVec.size(), sf::LinesStrip); }

//bool regPolygon::Float( vec2d Nsurf, vec2d Npen, float penAmt )
bool regPolygon::Float(vec2d Nsurf, vec2d Npen, float penAmt, float grav_N, float airDensity, float fluidDensity)
{
  float belowSurface = (Npen*penAmt).mag();
  if (Nsurf.dot(Npen) < 0.0f) belowSurface = 2.0f*r - belowSurface;

  if (belowSurface > 0.0f && belowSurface < 2.0f*r)// partially immersed
  {
    v = v.to_base(Nsurf);
    float Fbuoy = 2.0f*r*grav_N*(belowSurface*fluidDensity + (2.0f*r - belowSurface)*airDensity);
    v.x += Fbuoy / m;
    if (v.x < 0.0f) v.x -= drag * fluidDensity*v.x*r*2.0f / m;
    v.y -= drag * fluidDensity*v.y*belowSurface / m;
    v = v.from_base(Nsurf);
    return true;

    /*    v = v.to_base(Nsurf);
    float Fbuoy = 2.0f*r*belowSurface*pressure;
    v.x += Fbuoy/m;
    v.x -= drag*v.x*r*2.0f/m;
    v.y -= drag*v.y*belowSurface/m;
    v = v.from_base(Nsurf);
    return true;    */
  }

  return false;
}

bool regPolygon::Float(vec2d Nsurf, float grav_N, float Density)
{
  v = v.to_base(Nsurf);
  float Fbuoy = 3.1416f*r*r*grav_N*Density;
  v.x += Fbuoy / m;
  v -= drag * Density*v*r*2.0f / m;
  v = v.from_base(Nsurf);
  return true;
}

bool regPolygon::hit(const vec2d& pt)
{
  vec2d sep;
  vec2d N;
  float a;

  if (is_inMe(pt, sep, N, a))
  {
    v = v.to_base(N);
    if (v.x < 0.0f)
    {
      v.x *= -Cr;
    }
    v = v.from_base(N);
    pos += N * a;
    return true;
  }

  return false;
}

bool regPolygon::is_thruMe(vec2d pt1, vec2d pt2, vec2d& Pimp, float& fos)const// for bulletproofing, laser sighting, etc.
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
  float a = sqrtf(r*r - b * b);
  Pimp = pos + b * N - a * Lu;
  fos = (pt1 - Pimp).dot(Lu) / magL;

  return true;
}

bool regPolygon::is_inMe(const regPolygon& rpg, vec2d& sep, vec2d& N, float& dSep)const
{
  float sepSq = (pos - rpg.pos).dot(pos - rpg.pos);
  if (sepSq > (r + rpg.r)*(r + rpg.r)) return false;// not touching

  bool Hit = false;

  for (auto& P : rpg.ptVec)
    if (is_inMe(P + rpg.pos, rpg.pos - pos, sep, N, dSep))
    {
      Hit = true;
      break;
    }

  if (!Hit)
    for (auto& P : ptVec)
      if (rpg.is_inMe(P + pos, pos - rpg.pos, sep, N, dSep))
      {
        N *= -1.0f;
        Hit = true;
        break;
      }

  return Hit;
}

bool regPolygon::is_inMe(const ball& rB, vec2d& sep, vec2d& N, float& dSep)const
{
  // crude check for collision. Check distance between centers.
  sep = pos - rB.pos;
  float sepMag = sep.mag();
  float sepSq = (pos - rB.pos).dot(pos - rB.pos);
  if (sepSq > (r + rB.r)*(r + rB.r)) return false;// not touching

                                                  // is a point stuck in the ball?
  const vec2d *pPtMin1 = &(ptVec[0]), *pPtMin2 = &(ptVec[1]);// save the 2 closest in case a face hit test follows
  float sSqMin1 = (rB.r + 2.0f*r)*(rB.r + 2.0f*r);// highest possible value
  float sSqMin2 = sSqMin1;
  bool Hit = false;

  for (const vec2d& P : ptVec)
  {
    vec2d s = pos + P - rB.pos;
    sepMag = s.mag();
    float sSq = s.dot(s);
    if (sSq < rB.r*rB.r)// hit!
    {
      sep = s;
      dSep = rB.r - sepMag;
      N = sep / sepMag;
      //    std::cerr << "point hit\n";
      Hit = true;
    }

    if (sSq < sSqMin1)
    {
      pPtMin2 = pPtMin1;
      sSqMin2 = sSqMin1;
      pPtMin1 = &P;
      sSqMin1 = sSq;
      //     std::cerr << "new pPtMin1->x = " << pPtMin1->x << '\n';
      //     std::cerr << "new pPtMin2->x = " << pPtMin2->x << '\n';
    }
    else if (sSq < sSqMin2)
    {
      pPtMin2 = &P;
      sSqMin2 = sSq;
      //     std::cerr << "just new pPtMin2->x = " << pPtMin2->x << '\n';
    }
  }

  // perhaps a face to face hit?
  if (pPtMin1 && pPtMin2)
  {
    vec2d T = *pPtMin2 - *pPtMin1;
    T /= T.mag();
    vec2d b = *pPtMin1 + pos - rB.pos;
    float bDotT = b.dot(T);
    if (bDotT > 0.0f) return Hit;
    sep = b - T * bDotT;
    sepMag = sep.mag();
    sepSq = sep.dot(sep);

    if (sepSq < rB.r*rB.r)
    {
      //  std::cerr << "face hit\n";
      dSep = rB.r - sepMag;
      N = sep / sepMag;
      return true;
    }
  }

  return false;
}

bool regPolygon::is_inMe(vec2d pt, vec2d& sep, vec2d& N, float& dSep)const// writes qtys needed for collision response
{
  sep = pt - pos;
  float sepMag = sep.mag();
  if (sepMag > r) return false;

  // find which vtx the pt is between
  const vec2d *pPt0 = nullptr, *pPt1 = nullptr;
  const vec2d* ppt_1 = nullptr;
  //   vec2d N;
  size_t i = 0;

  for (i = 0; i< ptVec.size(); ++i)
  {
    ppt_1 = &(ptVec[0]);
    if (i < ptVec.size() - 1) ppt_1 = &(ptVec[i + 1]);

    float cross0 = sep.cross(ptVec[i]);
    float cross1 = sep.cross(*ppt_1);
    //       if( cross0 == 0.0f ) { N = ptVec[i]; N /= N.mag(); break; }

    if (cross0 < 0.0f && cross1 > 0.0f)// correct? i just right
    {
      pPt0 = &(ptVec[i]);
      pPt1 = ppt_1;
      //    std::cerr << "i = " << i << '\n';
      break;
    }
  }

  if (pPt0 && pPt1)// wedge found
  {
    // verify hit
    vec2d u = sep - *pPt0;
    float cross0 = u.cross(*pPt0*-1.0f);
    float cross1 = u.cross(*pPt1 - *pPt0);

    if ((cross0 > 0.0f && cross1 < 0.0f))// nailed it !?!
    {
      // hit
      //    std::cout << "i = " << i << '\n';
      N = *pPt0 + *pPt1;
      N /= N.mag();
      N *= -1.0f;// new
      sep = pt;// new
      dSep = u.dot(N);
      return true;
    }
  }

  return false;
}

bool regPolygon::is_inMe(vec2d pt, vec2d ctr, vec2d& sep, vec2d& N, float& dSep)const// writes qtys needed for collision response toward ctr
{
  sep = pt - pos;
  float sepMag = sep.mag();
  if (sepMag > r) return false;

  // find which vtx the ctr is between
  const vec2d *pPt0 = nullptr, *pPt1 = nullptr;
  const vec2d* ppt_1 = nullptr;
  size_t i = 0;

  for (i = 0; i< ptVec.size(); ++i)
  {
    ppt_1 = &(ptVec[0]);
    if (i < ptVec.size() - 1) ppt_1 = &(ptVec[i + 1]);

    if ((sep - ptVec[i]).cross(*ppt_1 - ptVec[i]) > 0.0f) return false;// pt is outside of polygon

    float cross0 = ctr.cross(ptVec[i]);
    float cross1 = ctr.cross(*ppt_1);

    if (cross0 < 0.0f && cross1 > 0.0f)// correct? i just right
    {
      pPt0 = &(ptVec[i]);
      pPt1 = ppt_1;
      //    std::cerr << "i = " << i << '\n';
      //    break;
    }
  }

  if (pPt0 && pPt1)// wedge found
  {
    // verify hit
    vec2d u = sep - *pPt0;
    //    std::cout << "i = " << i << '\n';
    N = *pPt0 + *pPt1;
    N /= N.mag();
    N *= -1.0f;// new
    sep = pt;// new
    dSep = u.dot(N);
    return true;
  }

  return false;
}

float regPolygon::project(vec2d vUnit)const// max projection along vUnit
{
  float x = 0.0f;
  for (vec2d P : ptVec)
    if (P.dot(vUnit) > x) x = P.dot(vUnit);

  return x;
}

void regPolygon::setPosition(vec2d Pos)
{
  pos = Pos;
  for (size_t i = 0; i < ptVec.size(); ++i)
  {
    vtxVec[i].position.x = pos.x + ptVec[i].x;
    vtxVec[i].position.y = pos.y + ptVec[i].y;
    //      equate( vtxVec[i].position, pos + ptVec[i] );
  }

  vtxVec[ptVec.size()].position.x = pos.x + ptVec[0].x;
  vtxVec[ptVec.size()].position.y = pos.y + ptVec[0].y;
  //   equate( vtxVec[ ptVec.size() ].position, pos + ptVec[0] );
}

float regPolygon::getRotation()const
{
  return atan2f(ptVec[0].y, ptVec[0].x);
}

void regPolygon::setRotation(float angle)
{
  vec2d pt0(r, 0.0f);// starter side
  pt0 = pt0.Rotate(angle);
  float dAngle = 6.283185f / nSides;
  for (size_t i = 0; i<nSides; ++i)
  {
    ptVec[i] = pt0;
    //        equate( vtxVec[i], pos + pt0 );
    vtxVec[i].position.x = pos.x + pt0.x;
    vtxVec[i].position.y = pos.y + pt0.y;
    pt0 = pt0.Rotate(dAngle);
  }
  vtxVec.back().position = vtxVec.front().position;
}

void regPolygon::setRadius(float R)
{
  r = R;
  setRotation(getRotation());
}

// these replace lineInMe(), arcInMe()s
bool regPolygon::is_inMe(const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep)const// detailed collision detection
{
  // end point test first
  if (is_inMe(LS.pos, Pimp, Nh, dSep)) return true;
  if (is_inMe(LS.pos + LS.L, Pimp, Nh, dSep)) return true;

  //   vec2d L = B - A;
  float magL = LS.L.mag();// length of lineSeg
  vec2d T = LS.L / magL;// unit in direction of lineSeg
  vec2d N = T.get_LH_norm();// unit normal
  vec2d s = pos - LS.pos;// relative position
  float d = s.dot(T);// position along lineSeg

  if ((d < -r) || (d > magL + r)) return false;// rpg too far away
                                               //    if( ( d < 0.0f ) || ( d > magL ) ) return false;// rpg too far away

  float h = T.cross(s);// height above lineSeg.  s.dot(N) should work also
  bool Nside = false;

  if (h < 0.0f) { Nside = true; h *= -1.0f; }
  if (!Nside) N *= -1.0f;

  if (h > r) return false;// too far away

                          // Any point over the line?
  for (size_t i = 0; i< ptVec.size(); ++i)
  {
    const vec2d& P = ptVec[i];
    vec2d s1 = pos + P - LS.pos;
    float d1 = s1.dot(T);
    float h1 = h + P.dot(N);

    if (h1 < 0.0f && d1 > 0.0f && d1 < magL)// P is across line and between line ends
    {
      // check for and dismiss the evil edge cases
      const vec2d& P_prev = (i == 0) ? ptVec.back() : ptVec[i - 1];// who loves the ternary operator? I do too!
      const vec2d& P_next = (i + 1 == ptVec.size()) ? ptVec.front() : ptVec[i + 1];// It mmust be used here. Why?

      if (d < 0.0f)// at left end
      {
        if (Nside) { if ((P_prev - P).cross(LS.pos - (pos + P)) > 0.0f) continue; }// undercut from above
        else if ((P_next - P).cross(LS.pos - (pos + P)) < 0.0f) continue;// undercut from below

      }
      else if (d > magL)// at right end
      {
        if (Nside) { if ((P_next - P).cross(LS.pos + LS.L - (pos + P)) < 0.0f) continue; }// undercut from above
        else { if ((P_prev - P).cross(LS.pos + LS.L - (pos + P)) > 0.0f) continue; }// undercut from below
      }// ennd edge case handling

       // collision has occurred - respond
      Pimp = P + pos;// relative to polygon center

      Nh = LS.L.get_LH_norm();// unit normal
      dSep = -1.0f*Nh.dot(Pimp - LS.pos);// amount of penetration
      if (dSep < 0.0f) { Nh *= -1.0f; dSep *= -1.0f; }

      return true;
    }
  }

  return false;
}

bool regPolygon::is_inMe(const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep)const// code goes here. Impact point is written.
{
  vec2d sep = pos - AS.pos;
  float sepSq = sep.dot(sep);

  if (sepSq > (r + AS.R)*(r + AS.R)) return false;// not touching
  if (sepSq < (AS.R - r)*(AS.R - r)) return false;// not touching

  if (is_inMe(AS.pos + AS.s[0], Pimp, Nh, dSep)) return true;
  if (is_inMe(AS.pos + AS.s[1], Pimp, Nh, dSep)) return true;

  vec2d T = sep.get_LH_norm(); T *= -1.0f;
  //    if( (sep - T*r).cross(AS.s[0]) < 0.0f || (sep + T*r).cross(AS.s[1]) > 0.0f ) return false;// too far past ends
  if (sep.cross(AS.s[0]) < 0.0f || sep.cross(AS.s[1]) > 0.0f) return false;// too far past ends

  float sepMag = sep.mag();
  bool outHit = sepMag > AS.R;

  // any points over the line? Also, save index to closest
  size_t i_min = 0;//, i_max = 0;
  vec2d s1 = ptVec[i_min] + sep;
  vec2d s1_min = s1, s1_max = s1;
  float s1SqMin = s1.dot(s1);
  float s1SqMax = s1SqMin;
  bool pointHit = false;

  for (size_t i = 0; i< ptVec.size(); ++i)
  {
    s1 = ptVec[i] + sep;
    float s1Sq = s1.dot(s1);
    if ((outHit && s1Sq < AS.R*AS.R) || (!outHit && s1Sq > AS.R*AS.R))// hit!
    {
      if (s1.cross(AS.s[0]) > 0.0f && s1.cross(AS.s[1]) < 0.0f)// between ends
      {
        pointHit = true;
      }
    }

    if (s1Sq < s1SqMin)
    {
      s1SqMin = s1Sq;
      i_min = i;
      s1_min = s1;
    }

    if (s1Sq > s1SqMax)
    {
      s1SqMax = s1Sq;
      s1_max = s1;
    }
  }

  const vec2d& P = ptVec[i_min];
  const vec2d& P_prev = (i_min == 0) ? ptVec.back() : ptVec[i_min - 1];// who loves the ternary operator? I do too!
  const vec2d& P_next = (i_min + 1 == ptVec.size()) ? ptVec.front() : ptVec[i_min + 1];// It mmust be used here. Why?

  if (pointHit)
  {
    // screen out the evil edge cases
    /*   if( sep.cross(AS.s[0]) < 0.0f )// at left end - was <
    {
    if( outHit ) { if( ( P_next - P ).cross( AS.pos + AS.s[0] - ( pos + P) ) < 0.0f ) return false; }// < correct
    else if( ( P_prev - P ).cross( AS.pos + AS.s[0] - ( pos + P) ) > 0.0f ) return false;// undercut from below
    }
    else if( sep.cross(AS.s[1]) > 0.0f )// at right end
    {
    if( outHit ) { if( ( P_prev - P ).cross( AS.pos + AS.s[1] - ( pos + P) ) > 0.0f ) return false; }// <  correct?
    else if( ( P_next - P ).cross( AS.pos + AS.s[1] - ( pos + P) ) < 0.0f ) return false;// undercut from below
    }// end edge case handling  */

    if (outHit) Pimp = s1_min;
    else Pimp = s1_max;

    Pimp += AS.pos;
    // new
    Nh = Pimp - AS.pos; Nh /= Nh.mag();// unit normal
    dSep = AS.R - (Pimp - AS.pos).mag();// amount of penetration
    if (dSep < 0.0f) { Nh *= -1.0f; dSep *= -1.0f; }

    return true;
  }
  else if (outHit)// check for face hit
  {
    vec2d b = P + sep;
    vec2d T1 = P_next - P;// try this one
    T1 /= T1.mag();
    float bDotT1 = b.dot(T1);
    if (bDotT1 > 0.0f)
    {
      T1 = P_prev - P;
      T1 /= T1.mag();
      bDotT1 = b.dot(T1);
      if (bDotT1 > 0.0f) return false;// neither face is across arc
    }

    Pimp = b - T1 * bDotT1;

    //    if( Pimp.dot(Pimp) < R*R )
    if (Pimp.dot(Pimp) < AS.R*AS.R && (Pimp.cross(AS.s[0]) > 0.0f && Pimp.cross(AS.s[1]) < 0.0f))// in circle and between ends
    {
      Pimp += AS.pos;
      //    std::cerr << "face hit\n";
      // new
      Nh = Pimp - AS.pos; Nh /= Nh.mag();// unit normal
      dSep = AS.R - (Pimp - AS.pos).mag();// amount of penetration
      if (dSep < 0.0f) { Nh *= -1.0f; dSep *= -1.0f; }

      return true;
    }
  }

  return false;
}

/*
bool regPolygon::hit( regPolygon& rpg )
{
bool Hit = false;
vec2d sep, N;
float a;

Hit = is_inMe( rpg, sep, N, a );

**   for( auto& P : rpg.ptVec )
//        if( is_inMe( P + rpg.pos, sep, N, a ) )
if( is_inMe( P + rpg.pos, rpg.pos-pos, sep, N, a ) )
{
Hit = true;
break;
}

if( !Hit )
for( auto& P : ptVec )
//            if( rpg.is_inMe( P + pos, sep, N, a ) )
if( rpg.is_inMe( P + pos, pos-rpg.pos, sep, N, a ) )
{
N *= -1.0f;
Hit = true;
break;
}   **

if( Hit )
{
//    static int cnt = 0;
//    std::cerr << "\n rpg vs rpg. cnt = " << ++cnt;
if( is_free && rpg.is_free )// both are free to move
{
float Mtot = rpg.m + m;
vec2d Vcm = ( rpg.v*rpg.m + v*m )/( Mtot );
rpg.v -= Vcm;
v -= Vcm;
v = v.to_base( N );
rpg.v = rpg.v.to_base( -N );
vShift();
rpg.vShift();
//            if( rpg.v.x > 0.0f && v.x < 0.0f )
if( rpg.v.x < 0.0f && v.x < 0.0f )
{
//         impact(rpg);
//         rpg.impact( *this );
rpg.v.x *= -rpg.Cr;
v.x *= -rpg.Cr;
}
vShift_inv();
rpg.vShift_inv();
v = v.from_base( N );
rpg.v = rpg.v.from_base( -N );
rpg.v += Vcm;
v += Vcm;

// position correction
rpg.pos -= (a*m/Mtot)*N;
pos += (a*rpg.m/Mtot)*N;

setPosition( pos );
rpg.setPosition( rpg.pos );

return true;
}
// one ball is not free
regPolygon& polyFree = is_free ? *this : rpg;
regPolygon& polyFixed = is_free ? rpg : *this;// must be other ball
// N must point from fixed to free
//   N = polyFree.pos - polyFixed.pos; N /= N.mag();// unit length needed
if( &polyFree == &rpg ) N *= -1.0f;

polyFree.v = polyFree.v.to_base( N );
polyFree.vShift();
//        if( polyFree.v.x < 0.0f ){ impact(rpg); polyFree.v.x *= -Cr; }
if( polyFree.v.x < 0.0f ) polyFree.v.x *= -Cr;
polyFree.vShift_inv();
polyFree.v = polyFree.v.from_base( N );
// correct over penetration. Move apart
polyFree.pos += a*N;// preserves position of center of mass
polyFree.setPosition( polyFree.pos );

return true;
}

return false;
}
*/

/*
bool regPolygon::hit( ball& rB )
{
vec2d Pimp;
if( inCircle( rB.pos, rB.r, Pimp ) )
{
handleImpact( Pimp, rB );
return true;
}
return false;
}   */

/*
void regPolygon::handleImpact( vec2d ptPos, ball& rB )
{
const float myCf = 0.3f;// new!

// xform to base set through ball centers
vec2d sep = ptPos - rB.pos;// from this center to rB center
float magSep = sep.mag();
vec2d r_r_base = sep/magSep;// unit length. First of local base set. 2nd is LH normal

if( is_free && rB.is_free )// both are free to move
{
// xform velocities to center of mass
float Mtot = m + rB.m;
vec2d Vcm = ( v*m + rB.v*rB.m )/( Mtot );
v -= Vcm;
rB.v -= Vcm;
v = v.to_base( r_r_base );
rB.v = rB.v.to_base( -r_r_base );
vShift();
rB.vShift();
// collision response is along line through centers
//       if( v.x < 0.0f && rB.v.x > 0.0f )
if( v.x < 0.0f && rB.v.x < 0.0f )
{
respond( myCf*v.x*( 1.0f + Cr ), true );
v.x *= -Cr;

rB.respond( myCf*rB.v.x*( 1.0f + Cr ), true );
rB.v.x *= -Cr;
// correct over penetration. Move apart
float dSep = rB.r - magSep;
if( dSep > 0.0f )
{
pos += r_r_base*(rB.m*dSep/Mtot);// preserves c.m. position
rB.pos -= r_r_base*(m*dSep/Mtot);// good for energy conservation in a gravity field for example
}
}
// transform back
vShift_inv();// new
rB.vShift_inv();// new
v = v.from_base( r_r_base );// rotate
rB.v = rB.v.from_base( -r_r_base );
v += Vcm;// translate
rB.v += Vcm;
return;
}

// Only one mvHit is free
mvHit& mhFree = is_free ? *static_cast<mvHit*>(this) : *static_cast<mvHit*>(&rB);
mvHit& mhFixed = is_free ? *static_cast<mvHit*>(&rB) : *static_cast<mvHit*>(this);
// N must point from fixed to free
if( &mhFree == &rB ) r_r_base *= -1.0f;

mhFree.v = mhFree.v.to_base( r_r_base );
mhFree.vShift();
if( mhFree.v.x < 0.0f ) { mhFree.respond( myCf*mhFree.v.x*( 1.0f + Cr ), true ); mhFree.v.x *= -Cr; }
mhFree.vShift_inv();
mhFree.v = mhFree.v.from_base( r_r_base );
// correct over penetration. Move apart
mhFree.pos += (rB.r - magSep)*r_r_base;

return;
}   */

/*
bool regPolygon::inCircle( vec2d ctr, float R, vec2d& Pimp )const
{
// crude check for collision. Check distance between centers.
float sepSq = ( pos - ctr ).dot( pos - ctr );
if( sepSq > (r + R)*(r + R) ) return false;// not touching

// is a point stuck in the ball?
const vec2d *pPtMin1 = &(ptVec[0]), *pPtMin2 = &(ptVec[1]);// save the 2 closest in case a face hit test follows
float sSqMin1 = ( R + 2.0f*r )*( R + 2.0f*r );// highest possible value
float sSqMin2 = sSqMin1;
bool Hit = false;

for( const vec2d& P : ptVec )
{
vec2d s = pos + P - ctr;
float sSq = s.dot(s);
if( sSq < R*R )// hit!
{
Pimp = ctr + s;
//    std::cerr << "point hit\n";
Hit = true;
}

if( sSq < sSqMin1 )
{
pPtMin2 = pPtMin1;
sSqMin2 = sSqMin1;
pPtMin1 = &P;
sSqMin1 = sSq;
//     std::cerr << "new pPtMin1->x = " << pPtMin1->x << '\n';
//     std::cerr << "new pPtMin2->x = " << pPtMin2->x << '\n';
}
else if( sSq < sSqMin2 )
{
pPtMin2 = &P;
sSqMin2 = sSq;
//     std::cerr << "just new pPtMin2->x = " << pPtMin2->x << '\n';
}
}

// perhaps a face to face hit?
if( pPtMin1 && pPtMin2 )
{
vec2d T = *pPtMin2 - *pPtMin1;
T /= T.mag();
vec2d b = *pPtMin1 + pos - ctr;
float bDotT = b.dot(T);
if( bDotT > 0.0f ) return Hit;
Pimp = b - T*bDotT;
//        sepSq = b.dot(b) - bDotT*bDotT;
sepSq = Pimp.dot(Pimp);

if( sepSq < R*R )
{
Pimp += ctr;
//  std::cerr << "face hit\n";
return true;
}
}

return false;
}   */

/*
void regPolygon::handleImpact( mvHit& mh, vec2d sep, vec2d N, float dSep )
{
if( is_free && mh.is_free )// both are free to move
{
float Mtot = mh.m + m;
vec2d Vcm = ( mh.v*mh.m + v*m )/( Mtot );
mh.v -= Vcm;
v -= Vcm;
v = v.to_base( N );
mh.v = mh.v.to_base( -N );
vShift();
mh.vShift();
if( mh.v.x < 0.0f && v.x < 0.0f )
{
mh.v.x *= -mh.Cr;
v.x *= -mh.Cr;// must be same as above
}
vShift_inv();
mh.vShift_inv();
v = v.from_base( N );
mh.v = mh.v.from_base( -N );
mh.v += Vcm;
v += Vcm;

// position correction
mh.pos -= (dSep*m/Mtot)*N;
pos += (dSep*mh.m/Mtot)*N;

setPosition( pos );
mh.setPosition( mh.pos );

return;
}
// one mvHit is not free
mvHit& mhFree = is_free ? *static_cast<mvHit*>(this) : mh;
mvHit& mhFixed = is_free ? mh : *static_cast<mvHit*>(this);
// N must point from fixed to free
if( &mhFree == &mh ) N *= -1.0f;

mhFree.v = mhFree.v.to_base( N );
mhFree.vShift();
//        if( polyFree.v.x < 0.0f ){ impact(rpg); polyFree.v.x *= -Cr; }
if( mhFree.v.x < 0.0f ) mhFree.v.x *= -Cr;
mhFree.vShift_inv();
mhFree.v = mhFree.v.from_base( N );
// correct over penetration. Move apart
mhFree.pos += dSep*N;
mhFree.setPosition( mhFree.pos );

return;
}   */
