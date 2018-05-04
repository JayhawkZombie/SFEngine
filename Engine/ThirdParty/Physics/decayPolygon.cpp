#include "decayPolygon.h"
#include "ball.h"

std::vector<mvHit*> *decayPolygon::p_mvHitVec = nullptr;
float decayPolygon::E_split3 = 8.0f, decayPolygon::E_split4 = 12.0f, decayPolygon::E_split5 = 18.0f;
float decayPolygon::E_fuse = 24.0f;

bool decayPolygon::hit(mvHit& mh)
{
  regPolygon* pRP = dynamic_cast<regPolygon*>(&mh);
  if (pRP) return hit(*pRP);// may be absorbed

  ball* pB = dynamic_cast<ball*>(&mh);
  if (pB) hit(*pB);// may cause a split

  return mh.hit(*static_cast<regPolygon*>(this));// for any other mvHit type
}

bool decayPolygon::hit(ball& rB)// a ball can split a decayPolygon
{

  bool Hit = regPolygon::hit(rB);

  if (Hit && p_mvHitVec)// bust a piece off?
  {
    //        float Ek = 0.5f*( m*v.dot(v) + rB.m*rB.v.dot(rB.v) );// total kinetic energy
    float Ek = Ek_Cm(*this, rB);
    regPolygon* pRP = nullptr;// new regPolygon produced in a split
    if (Ek > E_split5 && nSides > 9)      pRP = split_reg(5);
    else if (Ek > E_split4 && nSides > 7) pRP = split_reg(4);
    else if (Ek > E_split3 && nSides > 5) pRP = split_reg(3);

    if (pRP) p_mvHitVec->push_back(pRP);// a pointer to a new regPolygon was returned from the split_reg() call.
  }

  return Hit;
}

bool decayPolygon::hit(regPolygon& rpg)
{
  //    float Ek = 0.5f*( m*v.dot(v) + rpg.m*rpg.v.dot(rpg.v) );// total kinetic energy
  float Ek = Ek_Cm(*this, rpg);
  bool Hit = regPolygon::hit(rpg);

  //   if( Hit ) std::cerr << "\n decayPolygon::impact(rpg). E = " << Ek << " rpg.nSides = " << rpg.nSides;

  if (Hit && Ek > E_fuse) absorb_reg(rpg);

  return Hit;
}

regPolygon* decayPolygon::split_reg(size_t n)// returns pointer to new n sided regPolygon and modifies *this to nSides-n
{
  if (n > 5) return nullptr;// should return a decayPolygon instead
  if (nSides < n + 3) return nullptr;// must leave at least 3 sides for *this

  sf::Color vtxClr = vtxVec[0].color;

  // construct the nSides-n poly (reconstruct *this)
  nSides -= n;
  ptVec.clear();
  ptVec.reserve(nSides);
  vtxVec.clear();
  vtxVec.reserve(nSides + 1);
  vec2d pt0(r, 0.0f);// starter side
                     //    pt0 = pt0.Rotate(  );
  float dAngle = 6.283185f / nSides;
  for (size_t i = 0; i<nSides; ++i)
  {
    ptVec.push_back(pt0);
    vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + pt0.x, pos.y + pt0.y), vtxClr));
    pt0 = pt0.Rotate(dAngle);
  }
  vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + ptVec[0].x, pos.y + ptVec[0].y), vtxClr));


  // construct the new n gon
  regPolygon* pRP = new regPolygon;
  pRP->nSides = n;
  pRP->ptVec.reserve(pRP->nSides);
  pRP->vtxVec.reserve(pRP->nSides + 1);
  pRP->r = r;
  //    pRP->pos = pos - (r+pRP->r);// create just right of hit one
  v = v.mag()*v.get_LH_norm();// arbitrary. Make correct. This makes the 2 polys velocity perpendicular to incident ball. Momentum conservation is violated.
  pRP->v = -1.0f*v;
  pRP->pos = pos - v * ((r + pRP->r) / v.mag());// create just right off of hit one. Also arbitrary, but should accomplish non-overlapping placement. Center of mass position shifts grossly.
  pRP->m = m;// mass not conserved. Correct this
  pRP->Cr = Cr;// reasonable
  pt0.x = r; pt0.y = 0.0f;// default orientation ok?
  dAngle = 6.283185f / ( float ) n;// I shouldn't be doing this. What is right way to define pi?
                                   //   vec2d pt0( r, 0.0f );// starter side
                                   //    pt0 = pt0.Rotate( iAngle );
                                   //   float dAngle = 6.283185f/nSides;
  for (size_t i = 0; i<pRP->nSides; ++i)// for the nSides points and the coincident sf::Vertex
  {
    pRP->ptVec.push_back(pt0);
    //   std::cerr << "\n pt0.mag() = " << pt0.mag();
    pRP->vtxVec.push_back(sf::Vertex(sf::Vector2f(pRP->pos.x + pt0.x, pRP->pos.y + pt0.y), vtxClr));
    pt0 = pt0.Rotate(dAngle);
  }
  // the extra sf::Vertex closing the sf::LinesStrip
  pRP->vtxVec.push_back(sf::Vertex(sf::Vector2f(pRP->pos.x + pRP->ptVec[0].x, pRP->pos.y + pRP->ptVec[0].y), sf::Color::White));
  return pRP;
}

void decayPolygon::absorb_reg(regPolygon& rpg)
{
  if (!p_mvHitVec) return;
  //   mvHit* pMH = nullptr;
  std::vector<mvHit*>& rMHvec = *p_mvHitVec;
  std::vector<mvHit*>::iterator it = rMHvec.begin();
  //    for( std::vector<mvHit*>::iterator it = rMHvec.begin(); it != rMHvec.end(); ++it )
  for (it = rMHvec.begin(); it != rMHvec.end(); ++it)
  {
    if (*it == &rpg)// found it!
    {
      rMHvec.erase(it);
      break;
    }
  }

  size_t dN = rpg.nSides;
  delete &rpg;// now we've done it!

  sf::Color vtxClr = vtxVec[0].color;

  // construct the nSides + dN sided poly
  nSides += dN;
  ptVec.clear();
  ptVec.reserve(nSides);
  vtxVec.clear();
  vtxVec.reserve(nSides + 1);
  vec2d pt0(r, 0.0f);// starter side
                     //    pt0 = pt0.Rotate(  );
  float dAngle = 6.283185f / nSides;
  for (size_t i = 0; i<nSides; ++i)
  {
    ptVec.push_back(pt0);
    vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + pt0.x, pos.y + pt0.y), vtxClr));
    pt0 = pt0.Rotate(dAngle);
  }
  vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + ptVec[0].x, pos.y + ptVec[0].y), vtxClr));
}

// non members
/*
vec2d velCm( const mvHit& A, const mvHit& B )
{
return ( A.v*A.m + B.v*B.m )/( A.m + B.m );
}

float Ek_Cm( const mvHit& A, const mvHit& B )
{
vec2d Vcm = velCm( A, B );
vec2d V = A.v - Vcm;
float Ek = A.m*V.dot(V);
V = B.v - Vcm;
Ek += B.m*V.dot(V);
return 0.5f*Ek;
}   */
