#include "lineBumper.h"
#include "mvHit.h"

lineBumper::lineBumper(std::istream& fin)
{
  init(fin);
}

void lineBumper::init(std::istream& fin)
{
  lineSeg::init(fin);// base overload
  float magV;
  fin >> magV >> bumpSteps;
  vel = N*magV;
  std::cerr << "lineBumper: vel.x = " << vel.x << "  vel.y = " << vel.y << '\n';
}

void lineBumper::to_file(std::ofstream& fout)
{
  fout << "B\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu;
  fout << vel.mag() << ' ' << bumpSteps;
}

void lineBumper::update()
{
  if (state == 0) return;

  if (state == 1)// going up
  {
    if (++bumpIdx >= bumpSteps) state = -1;
  }
  else// going down
  {
    if (--bumpIdx <= 0) state = 0;// motion done
  }

  vtx[0].position.x = pos.x + (float)bumpIdx*vel.x;
  vtx[0].position.y = pos.y + (float)bumpIdx*vel.y;
  vtx[1].position.x = pos.x + L.x + (float)bumpIdx*vel.x;
  vtx[1].position.y = pos.y + L.y + (float)bumpIdx*vel.y;

  return;
}

bool lineBumper::hit(mvHit& mh)
{
  vec2d Pimp, Nh;
  float dSep;

  //   if( is_onMe( mh, Pimp, Nh, dSep ) )
  if (mh.is_inMe(*static_cast<const lineSeg*>(this), Pimp, Nh, dSep))
  {
    float magL = L.mag();// as per hit() above
    vec2d T = L / magL;
    vec2d Nu = T.get_LH_norm();
    vec2d s = Pimp - pos;
    float d = s.dot(T);// position along lineSeg

    if (d < 0.0f || d > magL)// end hit
    {
      mh.bounce(Cf, Nh, friction_on);
    }
    else// in the face
    {
      vec2d Vtn_N = (mh.v - vel).to_base(T);// active side is Nside
      vec2d Vtn_0 = mh.v.to_base(T);

      if (Nh.dot(Nu) > 0.0f)// "Nside" = active side
      {
        if (Vtn_N.y < 0.0f)// pre-collision
        {
          Vtn_N.y *= -mh.Cr;
          mh.v = Vtn_N.from_base(T);
          mh.v += vel;// shift back
          state = 1;// trigger animation
          bumpIdx = 0;
        }
      }
      else if (Vtn_0.y > 0.0f)// pre-collision
      {
        Vtn_0.y *= -mh.Cr;
        mh.v = Vtn_0.from_base(T);
      }
    }

    mh.setPosition(mh.pos + Nh*dSep);// position change response
    return true;
  }

  return false;
}

/*
bool lineBumper::hit( ball& rB )
{
float magL = L.mag();// as per hit() above
vec2d T = L/magL;
vec2d N = T.get_LH_norm();
vec2d s = rB.pos - pos;
float d = s.dot(T);// position along lineSeg
bool Hit = false;

if( d < 0.0f )// ball center misses lineSeg
{
// try ends 1st
if( d > -rB.r )
{
//     rB.v -= vel;
Hit = rB.hit( pos );
//     rB.v += vel; // moving end
}

return Hit;
}

if( d > magL )// ball center misses lineSeg
{
// try ends 1st
if( d < magL + rB.r )
{
//    rB.v -= vel;
Hit = rB.hit( pos + L );
//    rB.v += vel; // moving end
}

return Hit;
}

// ball is between ends
float h = T.cross(s);// height above lineSeg
bool Nside = false;

if( h < 0.0f ) { Nside = true; h *= -1.0f; }

if( h < rB.r )// collide
{
vec2d Vtn_N = (rB.v - vel).to_base(T);// active side is Nside
vec2d Vtn_0 = rB.v.to_base(T);
//    rB.v -= vel;// relative to co-moving reference frame
//    vec2d Vtn = rB.v.to_base(T);
if( Nside )
{
if( Vtn_N.y < 0.0f )// pre-collision
{
Vtn_N.y *= -rB.Cr;
rB.v = Vtn_N.from_base( T );
rB.v += vel;// shift back
rB.pos = pos + T*d + N*rB.r;

state = 1;// trigger animation
bumpIdx = 0;
}
}
else if( Vtn_0.y > 0.0f )// pre-collision
{
Vtn_0.y *= -rB.Cr;
rB.v = Vtn_0.from_base( T );
//   rB.v += vel;// shift back
rB.pos = pos + T*d - N*rB.r;
}

return true;
}

return false;
}   */

/*

bool lineBumper::hit( ball& rB )
{
float magL = L.mag();// as per hit() above
vec2d T = L/magL;
vec2d N = T.get_LH_norm();
vec2d s = rB.pos - pos;
float d = s.dot(T);// position along lineSeg
bool Hit = false;

if( d < 0.0f )// ball center misses lineSeg
{
// try ends 1st
if( d > -rB.r )
{
rB.v -= vel;
Hit = rB.hit( pos );
rB.v += vel; // moving end
}

return Hit;
}

if( d > magL )// ball center misses lineSeg
{
// try ends 1st
if( d < magL + rB.r )
{
rB.v -= vel;
Hit = rB.hit( pos + L );
rB.v += vel; // moving end
}

return Hit;
}

// ball is between ends
float h = T.cross(s);// height above lineSeg
bool Nside = false;

if( h < 0.0f ) { Nside = true; h *= -1.0f; }

if( h < rB.r )// collide
{
rB.v -= vel;// relative to co-moving reference frame
vec2d Vtn = rB.v.to_base(T);
if( Nside )
{
if( Vtn.y < 0.0f )// pre-collision
{
Vtn.y *= -rB.Cr;
rB.v = Vtn.from_base( T );
rB.v += vel;// shift back
rB.pos = pos + T*d + N*rB.r;

state = 1;// trigger animation
bumpIdx = 0;
}
}
else if( Vtn.y > 0.0f )// pre-collision
{
Vtn.y *= -rB.Cr;
rB.v = Vtn.from_base( T );
rB.v += vel;// shift back
rB.pos = pos + T*d - N*rB.r;
}

return true;
}

return false;
}
*/
