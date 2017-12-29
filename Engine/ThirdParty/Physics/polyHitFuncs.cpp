//#include "polyHitFuncs.h"
//
//bool hit(regPolygon& rpg, const lineSeg& Lseg)
//{
//  float magL = Lseg.L.mag();// length of lineSeg
//  vec2d T = Lseg.L / magL;// unit in direction of lineSeg
//  vec2d N = T.get_LH_norm();// unit normal
//  vec2d s = rpg.pos - Lseg.pos;// relative position
//  float d = s.dot(T);// position along lineSeg
//
//  float h = T.cross(s);// height above lineSeg
//  bool Nside = false;
//
//  if (h < 0.0f) {
//    Nside = true; h *= -1.0f;
//  }
//
//  if ((d < -rpg.r) || (d > magL + rpg.r)) return false;
//
//  //   bool Hit = false;
//  if (rpg.hit(Lseg.pos)) {
//    //std::cerr << "Hit 1\n"; return true;
//  }
//  else if (rpg.hit(Lseg.pos + Lseg.L)) {
//    //std::cerr << "Hit 2\n"; return true;
//  }
//  else if (h < rpg.r)// collide
//  {
//    //    if( rpg.hit( Lseg.pos ) ) return true;// best spot?
//    //    if( rpg.hit( Lseg.pos + Lseg.L ) ) return true;
//
//    if (!Nside) N *= -1.0f;
//
//    if (rpg.v.dot(N) < 0.0f)// pre-collision
//    {
//      vec2d s1;
//      float h1 = 0.0f;
//      for (vec2d P : rpg.ptVec)// find which P crossed the line
//      {
//        s1 = rpg.pos + P - Lseg.pos;
//
//        float d1 = s1.dot(T);
//        if (Nside) h1 *= -1.0f;
//        h1 = h + P.dot(N);
//        //      if( h1 < 0.0f && d1 > 0.0f && d1 < magL )// hit
//        if (h1 < 0.0f && h1 > 2.0f*rpg.v.dot(N) && d1 > 0.0f && d1 < magL)// hit
//        {
//          rpg.v = rpg.v.to_base(T);
//          float  dV = Lseg.Cf*rpg.v.y*(1.0f + rpg.Cr);
//          rpg.respond(dV, Lseg.friction_on);
//          rpg.v.y *= -rpg.Cr;
//          rpg.v = rpg.v.from_base(T);
//          //    std::cout << "h1 = " << h1 << '\n';
//          rpg.setPosition(Lseg.pos + T*d - N*(P.dot(N) + h1));
//          return true;
//        }
//      }
//    }
//  }
//
//  return false;
//}
//
//bool hit(regPolygon& rpg, const arcSeg& asg)
//{
//  vec2d sep = rpg.pos - asg.pos;// vector from arcSeg center to ball center. This will be line of action
//
//                                // ball is between arc ends. How far away?
//  float magSep = sep.mag();
//
//  if (magSep > asg.R + rpg.r) return false;// ball too far
//  if (magSep < asg.R - rpg.r) return false;// ball too near
//
//                                           // all is just right. Handle collision
//                                           //    sep /= magSep;// unit length. Good for base vector
//
//  bool corrected = true;
//  vec2d T = sep.get_LH_norm();
//  if ((sep + T*rpg.r).cross(asg.s[0]) < 0.0f || (sep - T*rpg.r).cross(asg.s[1]) > 0.0f) return false;// too far past ends
//
//  if (magSep > asg.R)// outside hit
//  {
//    //    if( (sep + T*rpg.r).cross(asg.s[0]) < 0.0f || (sep - T*rpg.r).cross(asg.s[1]) > 0.0f ) return false;// too far past ends
//
//    vec2d Pimp;// impact point
//    if (rpg.inCircle(asg.pos, asg.R, Pimp))
//    {
//      Pimp -= asg.pos;
//      if (!(Pimp.cross(asg.s[0]) < 0.0f || Pimp.cross(asg.s[1]) > 0.0f))// ball center misses arc ends
//      {
//        if (rpg.v.dot(sep) < 0.0f)// uncorrected
//        {
//          T = Pimp; T = T.get_LH_norm();
//          magSep = Pimp.mag();
//          vec2d N = Pimp / magSep;
//          float dSep = asg.R - magSep;
//          rpg.setPosition(rpg.pos + N*dSep);
//          //     rpg.setPosition( asg.pos + sep*( asg.R + rpg.r ) );
//          corrected = false;
//        }
//      }
//    }
//  }
//  else if (rpg.v.dot(sep) > 0.0f)// uncorrected inside hit
//  {
//    vec2d s1;
//    float h1 = 0.0f;
//    for (vec2d& P : rpg.ptVec)// find which P crossed the line
//    {
//      s1 = rpg.pos + P - asg.pos;
//      if (s1.cross(asg.s[0]) < 0.0f || s1.cross(asg.s[1]) > 0.0f) continue;
//      float s1mag = s1.mag();
//      vec2d s1u = s1 / s1.mag();
//      if (s1.dot(s1) > asg.R*asg.R)// this is the one
//      {
//        T = s1.get_LH_norm();
//        h1 = s1mag - asg.R;
//        rpg.setPosition(asg.pos + s1 - s1u*h1 - P);
//        corrected = false;
//      }
//    }
//  }
//
//  if (!corrected)
//  {
//    rpg.v = rpg.v.to_base(T);
//    float  dV = asg.Cf*rpg.v.y*(1.0f + rpg.Cr);
//    rpg.respond(dV, asg.friction_on);
//    rpg.v.y *= -rpg.Cr;
//    rpg.v = rpg.v.from_base(T);
//    corrected = true;
//  }
//
//  if (rpg.hit(asg.pos + asg.s[0])) return true;
//  if (rpg.hit(asg.pos + asg.s[1])) return true;
//
//  //    return true;
//  return corrected;
//}
//
//bool hit(regPolygon& rpg, ball& rB)
//{
//  vec2d Pimp;
//  if (rpg.inCircle(rB.pos, rB.r, Pimp))
//  {
//    handleImpact(Pimp, rpg, rB);
//    return true;
//  }
//  return false;
//}
//
//void handleImpact(vec2d ptPos, regPolygon& rpg, ball& rB)
//{
//  // xform velocities to center of mass
//  float Mtot = rpg.m + rB.m;
//  vec2d Vcm = (rpg.v*rpg.m + rB.v*rB.m) / (Mtot);
//  rpg.v -= Vcm;
//  rB.v -= Vcm;
//  // xform to base set through ball centers
//  vec2d sep = ptPos - rB.pos;// from this center to rB center
//  float magSep = sep.mag();
//  vec2d r_r_base = sep / magSep;// unit length. First of local base set. 2nd is LH normal
//  rpg.v = rpg.v.to_base(r_r_base);
//  rB.v = rB.v.to_base(r_r_base);
//
//  // collision response is along line through centers
//  if (rpg.v.x < 0.0f && rB.v.x > 0.0f)
//  {
//    rpg.v.x *= -rpg.Cr;
//    rB.v.x *= -rpg.Cr;
//    // correct over penetration. Move apart
//    float dSep = rB.r - magSep;
//    if (dSep > 0.0f)
//    {
//      rpg.pos += r_r_base*(rB.m*dSep / Mtot);// preserves c.m. position
//      rB.pos -= r_r_base*(rpg.m*dSep / Mtot);// good for energy conservation in a gravity field for example
//    }
//  }
//
//  // transform back
//  rpg.v = rpg.v.from_base(r_r_base);// rotate
//  rB.v = rB.v.from_base(r_r_base);
//  rpg.v += Vcm;// translate
//  rB.v += Vcm;
//
//  return;
//}
