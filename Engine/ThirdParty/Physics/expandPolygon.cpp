#include "expandPolygon.h"
#include "ball.h"

#include <cereal/archives/portable_binary.hpp>

//bool expandPolygon::hit( mvHit& mh ) { return mh.hit( *static_cast<regPolygon*>(this) ); }


bool expandPolygon::hit(mvHit& mh)
{
  //    return mh.hit( *static_cast<regPolygon*>(this) );

  if (growState == 0) return mh.hit(*static_cast<regPolygon*>(this));// mh call your version of hit(regPolygon&)
  vec2d N = mh.pos - pos;
  N /= N.mag();
  vec2d v_Shift = N*((float)growState*growSpeed);
  v += v_Shift;
  bool Hit = mh.hit(*static_cast<regPolygon*>(this));
  v -= v_Shift;
  //    static int cnt = 0;
  //   std::cerr << "\n xpp hit mvHit" << ++cnt;

  return Hit;
}

bool expandPolygon::hit(ball& rB)
{
  if (growState == 0) return regPolygon::hit(rB);
  vec2d N = rB.pos - pos;
  N /= N.mag();
  vec2d v_Shift = N*((float)growState*growSpeed);
  v += v_Shift;
  bool Hit = regPolygon::hit(rB);
  v -= v_Shift;
  //   std::cerr << "xpp hit ball\n";
  return Hit;
}

bool expandPolygon::hit(regPolygon& rpg)
{
  if (growState == 0) return regPolygon::hit(rpg);
  vec2d N = rpg.pos - pos;
  N /= N.mag();
  vec2d v_Shift = N*((float)growState*growSpeed);
  v += v_Shift;
  bool Hit = regPolygon::hit(rpg);
  v -= v_Shift;
  //   std::cerr << "xpp hit poly\n";
  return Hit;
}

bool expandPolygon::bounce(float Cf, vec2d N, bool isFric)// rigid bounce. N is line of action
{
  vec2d v_Shift = N*((float)growState*growSpeed);
  if (growState != 0) v -= v_Shift;
  bool Hit = mvHit::bounce(Cf, N, isFric);// base code
  if (growState != 0) v += v_Shift;
  return Hit;
}

/*
bool expandPolygon::bounce( float Cf, vec2d N, bool isFric )// rigid bounce. N is line of action
{
bool Hit = false;
vec2d v_Shift = N*( (float)growState*growSpeed );
if( growState != 0 ) v -= v_Shift;
// base code
if( v.dot(N) < 0.0f )// pre-collision
{
v = v.to_base(N);// velocity change response
float  dV = Cf*v.x*( 1.0f + Cr );
respond( dV, isFric );
v.x *= -Cr;
v = v.from_base(N);
Hit = true;
}
// end base code
if( growState != 0 ) v += v_Shift;

return Hit;
}   */


//float expandPolygon::vShift()
//{
//   std::cerr << "\n xpg vShift " << (float)growState*growSpeed;
//  return 0.0f;
//   return (float)growState*growSpeed;
//}

expandPolygon::expandPolygon(std::istream& fin) {
  init(fin);
}

void expandPolygon::init(std::istream& fin)
{
  float iAngle = 0.0f;
  fin >> nSides >> rFull >> iAngle;
  fin >> pos.x >> pos.y >> v.x >> v.y;
  fin >> m >> Cr >> growSpeed;// new
  unsigned int rd, gn, bu;
  fin >> rd >> gn >> bu;

  ptVec.reserve(nSides);
  vtxVec.reserve(nSides + 1);
  r = growSpeed;
  growState = 1;
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

void expandPolygon::update()
{
  if (growState != 0)// size is changing
  {
    float R = r;
    bool shrinkToFull = false;
    if (growState == -1 && R > rFull) shrinkToFull = true;
    R += (float)growState*growSpeed;

    if (shrinkToFull)
    {
      if (R <= rFull) {
        R = rFull; growState = 0;
      }
    }
    else if (growState == 1 && R >= rFull) {
      R = rFull; growState = 0;
    }
    else if (growState == -1 && R <= growSpeed) {
      R = growSpeed; growState = 0;
    }

    setRadius(R);
  }

  regPolygon::update();
}

state_ab* expandPolygon::newState()
{
  std::function<void(vec2d, vec2d, float, int)> p_SetFuncVVFI = std::bind(&expandPolygon::setState_xp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
  return new state_vvfi(&pos, &v, &r, &growState, p_SetFuncVVFI);
}

/*
void expandPolygon::update()
{
if( growState != 0 )// size is changing
{
float R = r;
R += (float)growState*growSpeed;

if( growState == 1 && R >= rFull ){ R = rFull; growState = 0; }
else if( growState == -1 && R <= growSpeed ){ R = growSpeed; growState = 0; }

setRadius(R);
}

regPolygon::update();
}   */

// utility
void expandPolygon::Transform()// expand or shrink
{
  if (r > 2.0f*growSpeed) growState = -1;// shrink
  else growState = 1;// expand
}

void expandPolygon::set_rFull(float R)
{
  if (R == rFull) return;
  if (R < growSpeed) return;
  if (R > 300.0f) return;

  if (R > rFull) growState = 1;// expand
  else growState = -1;
  rFull = R;
}

/*
void expandPolygon::set_rFull( float R )
{
if( R == rFull ) return;

if( R > rFull ) growState = 1;// expand
else growState = -1;
rFull = R;
}
*/

CEREAL_REGISTER_TYPE(expandPolygon);
