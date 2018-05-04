#include "lineSegSwing.h"
#include "mvHit.h"

bool lineSegSwing::gravity_on = true;
vec2d lineSegSwing::grav = vec2d(0.0f, 0.4f);

lineSegSwing::lineSegSwing(std::istream& fin) : lineSegRotate(fin)
{
  fin >> m;// >> grav.x >> grav.y;
}

void lineSegSwing::init(std::istream& fin)
{
  lineSegRotate::init(fin);// base overload
  fin >> m;// >> grav.x >> grav.y;
}

void lineSegSwing::to_file(std::ofstream& fout)
{
  fout << "S\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu << '\n';
  fout << rotVel << ' ' << m << ' ' << grav.x << ' ' << grav.y;
}

void lineSegSwing::update(float dt)
{
  float I = m * L.dot(L) / 3.0f;
  if (gravity_on) rotVel -= dt * grav.cross(L)*m / (2.0f*I);
  // rotate L
  L = L.Rotate(rotVel*dt);
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
  N = L.get_LH_norm();
  return;
}

bool lineSegSwing::hit(mvHit& mh)
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

                       // adapt
                       //   mh.v = mh.v.to_base(T);
    float I = m * L.dot(L) / 3.0f;
    float dw = 0.0f;//-1.0f*( 1.0f + mh.Cr )*( mh.v.y + d*rotVel )/( I/(mh.m*d) + d );
    float  dV = 0.0f;//-1.0f*(1.0f+mh.Cr)*mh.v.y;//I*dw/(mh.m*d);

                     //        if( d > 0.01f*magL && d < magL )
    if (d <= 0.0f)// fixed end hit
    {
      mh.bounce(Cf, Nh, friction_on);
    }
    //   else if( d >= magL )// moving end hit
    //   {
    //       mh.v += Nu*(magL*rotVel);
    //       mh.bounce( Cf, Nh, friction_on );
    //        mh.v -= Nu*(magL*rotVel);
    //    }
    else// in the face
    {
      mh.v = mh.v.to_base(T);
      dw = -1.0f*(1.0f + mh.Cr)*(mh.v.y + d * rotVel) / (I / (mh.m*d) + d);
      dV = I * dw / (mh.m*d);

      if (Nh.dot(Nu) > 0.0f)// "Nside"
      {
        if (mh.v.y + d * rotVel < 0.0f)// pre-collision
        {
          //    rB.respond( Cf*dV, friction_on );
          mh.v.y += dV;
          rotVel += dw;
          //    std::cout << "Nside hit on RLS\n";
        }
      }
      else if (mh.v.y + d * rotVel > 0.0f)// pre-collision
      {
        //   rB.respond( Cf*dV, friction_on );
        mh.v.y += dV;
        rotVel += dw;
      }

      if (d >= magL) mh.v.x *= -mh.Cr;// moving end hit - new
      mh.v = mh.v.from_base(T);
    }

    // end adapt

    mh.setPosition(mh.pos + Nh * dSep);// position change response
    return true;
  }

  return false;
}

/*
bool lineSegSwing::hit( ball& rB )
{
float magL = L.mag();// as per hit() above
vec2d T = L/magL;
vec2d N = T.get_LH_norm();
vec2d s = rB.pos - pos;
float d = s.dot(T);// position along lineSeg

if( d < 0.0f )// ball center misses lineSeg
{
if( !testEnd1 ) return false;
// try ends 1st
if( d > -rB.r )
if( rB.hit( pos ) ) return true;// fixed end

return false;
}

if( d > magL )// ball center misses lineSeg
{
if( !testEnd2 ) return false;
bool Hit = false;
// try ends 1st
if( d < magL + rB.r )
{
rB.v += N*(d*rotVel);
//Hit = hit( rB, pos + L );
Hit = rB.hit( pos + L );
rB.v -= N*(d*rotVel); // moving end
}

return Hit;
}

// ball is between ends
float h = T.cross(s);// height above lineSeg
bool Nside = false;

if( h < 0.0f ) { Nside = true; h *= -1.0f; }

if( h < rB.r )// collide
{
//    rB.v += N*(d*rotVel);// relative to co-moving reference frame
rB.v = rB.v.to_base(T);
float I = m*L.dot(L)/3.0f;
float dw = -1.0f*( 1.0f + rB.Cr )*( rB.v.y + d*rotVel )/( I/(rB.m*d) + d );
float  dV = I*dw/(rB.m*d);

if( Nside )
{
if( rB.v.y + d*rotVel < 0.0f )// pre-collision
{
rB.respond( Cf*dV, friction_on );
rB.v.y += dV;
rotVel += dw;
rB.pos = pos + T*d + N*rB.r;// ball position = lineSeg end + displace along line + 1 radius off of line
//    std::cout << "Nside hit on RLS\n";
}
}
else if( rB.v.y + d*rotVel > 0.0f )// pre-collision
{
rB.respond( Cf*dV, friction_on );
rB.v.y += dV;
rotVel += dw;
rB.pos = pos + T*d - N*rB.r;
}

rB.v = rB.v.from_base( T );
//    rB.v -= N*(d*rotVel);// shift back

return true;
}

return false;
}
*/
