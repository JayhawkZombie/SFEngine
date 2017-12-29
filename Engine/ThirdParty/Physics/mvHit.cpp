#include "mvHit.h"

float mvHit::wdwW, mvHit::wdwH;
float mvHit::wdwCf = 0.0f;// friction coeff
bool mvHit::windowTopOpen = false;
//vec2d* mvHit::pGravity = nullptr;

//float mvHit::pressure = 0.002f;// temporary experimental use
float mvHit::drag = 0.001f;

void mvHit::init(std::istream& fin)
{
  fin >> pos.x >> pos.y >> v.x >> v.y;
  fin >> m >> Cr;
}

std::vector<vec2d> mvHit::get_verts()
{
  return { pos };
}

bool mvHit::bounce(float Cf, vec2d N, bool isFric)// rigid bounce. N is line of action
{
  if (v.dot(N) < 0.0f)// pre-collision
  {
    v = v.to_base(N);// velocity change response
    float  dV = Cf*v.x*(1.0f + Cr);
    respond(dV, isFric);
    v.x *= -Cr;
    v = v.from_base(N);
    return true;
  }

  return false;
}

void mvHit::update(vec2d g)
{
  if (is_free)
  {
    v += g;
    update();
  }
  else
  {
    v *= 0.0f;
    update();
  }

}

state_ab* mvHit::newState()
{
  std::function<void(vec2d, vec2d)> p_SetFuncVV = std::bind(&mvHit::setState, this, std::placeholders::_1, std::placeholders::_2);
  return new state_vv(&pos, &v, p_SetFuncVV);
}

void mvHit::respond(float dV, bool isFric)// assumes velocity components are T(x) and N(y) to obstacle
{

  if (!isFric) return;// no change in x component can occur
  if (v.y == 0.0f) return;// target speed acheived
                          // speed needs adjustment
  if (dV < 0.0f) dV *= -1.0f;// assure dV is positive
  if (v.y > 0.0f) {
    v.y -= dV; if (v.y < 0.0f) v.y = 0.0f;
  }
  else {
    v.y += dV; if (v.y > 0.0f) v.y = 0.0f;
  }

  return;
}

void mvHit::handleImpact(mvHit& mh, vec2d sep, vec2d N, float dSep)
{
  if (is_free && mh.is_free)// both are free to move
  {
    float Mtot = mh.m + m;
    vec2d Vcm = (mh.v*mh.m + v*m) / (Mtot);
    mh.v -= Vcm;
    v -= Vcm;
    v = v.to_base(N);
    mh.v = mh.v.to_base(-N);

    if (mh.v.x < 0.0f && v.x < 0.0f)
    {
      mh.v.x *= -mh.Cr;
      v.x *= -mh.Cr;// must be same as above
    }

    v = v.from_base(N);
    mh.v = mh.v.from_base(-N);
    mh.v += Vcm;
    v += Vcm;

    // position correction
    mh.pos -= (dSep*m / Mtot)*N;
    pos += (dSep*mh.m / Mtot)*N;

    setPosition(pos);
    mh.setPosition(mh.pos);

    return;
  }
  // one mvHit is not free
  mvHit& mhFree = is_free ? *static_cast<mvHit*>(this) : mh;
  mvHit& mhFixed = is_free ? mh : *static_cast<mvHit*>(this);
  // N must point from fixed to free
  if (&mhFree == &mh) N *= -1.0f;

  mhFree.v = mhFree.v.to_base(N);
  //        if( polyFree.v.x < 0.0f ){ impact(rpg); polyFree.v.x *= -Cr; }
  if (mhFree.v.x < 0.0f) mhFree.v.x *= -Cr;
  mhFree.v = mhFree.v.from_base(N);
  // correct over penetration. Move apart
  mhFree.pos += dSep*N;
  mhFree.setPosition(mhFree.pos);

  return;
}

// non members

vec2d velCm(const mvHit& A, const mvHit& B)
{
  return (A.v*A.m + B.v*B.m) / (A.m + B.m);
}

float Ek(const mvHit& A, const mvHit& B)
{
  return 0.5f*(A.m*A.v.dot(A.v) + B.m*B.v.dot(B.v));
}

float Ek_Cm(const mvHit& A, const mvHit& B)
{
  vec2d Vcm = velCm(A, B);
  vec2d V = A.v - Vcm;
  float Ek = A.m*V.dot(V);
  V = B.v - Vcm;
  Ek += B.m*V.dot(V);
  return 0.5f*Ek;
}

sf::Vector2f Equate(vec2d v2d) {
  return sf::Vector2f(v2d.x, v2d.y);
}
