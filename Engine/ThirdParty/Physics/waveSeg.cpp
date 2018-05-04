#include "waveSeg.h"
#include "mvHit.h"

float waveSeg::PIx2 = 6.283185f;

waveSeg::waveSeg(std::istream& is) { init(is); }

void waveSeg::init(std::istream& is)
{
  lineSeg::init(is);
  magL = L.mag();// cached! Yeah!

  is >> Npts_wv;// 1st, not last
  if (Npts_wv < 2) Npts_wv = 2;

  float L_wv = 100.0f;
  is >> Amp_wvRt >> L_wv;
  if (L_wv < magL / 100.0f) L_wv = magL / 100.0f;
  K_wvRt = PIx2 / L_wv;
  is >> rotFreqRt; if (rotFreqRt < 0.0f) rotFreqRt *= 0.0f;

  wvSpeed = rotFreqRt * L_wv / PIx2;

  is >> Amp_wvLt >> L_wv;
  if (L_wv < magL / 100.0f) L_wv = magL / 100.0f;
  K_wvLt = PIx2 / L_wv;
  is >> rotFreqLt; if (rotFreqLt < 0.0f) rotFreqLt *= 0.0f;

  rotFreqLt = wvSpeed * K_wvLt;

  is >> Elev >> airDensity;
  is >> Depth >> fluidDensity;
  std::cerr << "airD: " << airDensity << "  fluD: " << fluidDensity;

  // fill the vector<vertex>
  wvVec.reserve(Npts_wv);
  wvVecLt.reserve(Npts_wv);
  wvVecRt.reserve(Npts_wv);
  float dx = magL / ( float ) (Npts_wv - 1);
  sf::Vertex vtx_loc;
  // right wave
  vtx_loc.color = sf::Color::Red;// right wave red
  for (int i = 0; i<Npts_wv; ++i)
  {
    float x_rel = dx * ( float ) i;
    vtx_loc.position.x = pos.x + x_rel;
    vtx_loc.position.y = pos.y + y_wvRt(x_rel);
    wvVecRt.push_back(vtx_loc);
  }
  // left wave
  vtx_loc.color = sf::Color::Green;// left wave green
  for (int i = 0; i<Npts_wv; ++i)
  {
    float x_rel = dx * ( float ) i;
    vtx_loc.position.x = pos.x + x_rel;
    vtx_loc.position.y = pos.y + y_wvLt(x_rel);
    wvVecLt.push_back(vtx_loc);
  }
  // resultant wave
  vtx_loc.color = sf::Color::Blue;// result is blue
  for (int i = 0; i<Npts_wv; ++i)
  {
    float x_rel = dx * ( float ) i;
    vtx_loc.position.x = pos.x + x_rel;
    vtx_loc.position.y = wvVecRt[i].position.y + wvVecLt[i].position.y - pos.y;
    wvVec.push_back(vtx_loc);
  }

  // under water image
  //   viewBelow = true;
  if (viewBelow)
  {
    underColor = sf::Color(0, 50, 205, 30);
    initUnderView();
  }
}

void waveSeg::initUnderView()
{
  wvVtxVec.resize(4 * Npts_wv);
  for (int i = 0; i<Npts_wv - 1; ++i)
  {
    wvVtxVec[4 * i].position = wvVtxVec[4 * i + 3].position = wvVec[i].position;// lt side
    wvVtxVec[4 * i + 3].position.y = pos.y + Amp_wvLt + Amp_wvRt;

    wvVtxVec[4 * i + 1].position = wvVtxVec[4 * i + 2].position = wvVec[i + 1].position;// rt side
    wvVtxVec[4 * i + 2].position.y = pos.y + Amp_wvLt + Amp_wvRt;

    wvVtxVec[4 * i].color = wvVtxVec[4 * i + 1].color = wvVtxVec[4 * i + 2].color = wvVtxVec[4 * i + 3].color = underColor;
  }

  underQuad[0].position.x = pos.x;
  underQuad[0].position.y = pos.y + Amp_wvLt + Amp_wvRt;// up lt
  underQuad[1].position = underQuad[2].position = underQuad[3].position = underQuad[0].position;
  underQuad[1].position.x += magL;// up rt
  underQuad[2].position.x += magL; underQuad[2].position.y = pos.y + Depth;// dn rt
  underQuad[3].position.y = pos.y + Depth;// dn lt
  underQuad[0].color = underQuad[1].color = underQuad[2].color = underQuad[3].color = underColor;

  //   std::cerr << "\n initUnderView";
}

void waveSeg::to_file(std::ofstream& fout)
{
  ( void ) fout;
  return;
}

void waveSeg::draw(sf::RenderTarget& rRW)const
{
  if (viewSeg) lineSeg::draw(rRW);
  rRW.draw(&wvVec[0], wvVec.size(), sf::LinesStrip);
  if (viewLt)  rRW.draw(&wvVecLt[0], wvVecLt.size(), sf::LinesStrip);
  if (viewRt)  rRW.draw(&wvVecRt[0], wvVecRt.size(), sf::LinesStrip);

  if (viewBelow)
  {
    rRW.draw(&wvVtxVec[0], wvVtxVec.size(), sf::Quads);
    rRW.draw(underQuad, 4, sf::Quads);
  }
}

void waveSeg::update(float dt)
{
  phsLt += rotFreqLt * dt; if (phsLt > PIx2) phsLt -= PIx2;
  phsRt += rotFreqRt * dt; if (phsRt > PIx2) phsRt -= PIx2;
  setState_1();
  /*   float dx = magL/(float)(Npts_wv-1);
  float x_rel = 0.0f;

  // don't assign all if only resultant being drawn require if( viewLt || viewRt )
  for( int i=0; i<Npts_wv; ++i )
  {
  x_rel = dx*(float)i;
  wvVecRt[i].position.y = pos.y + y_wvRt(x_rel);
  wvVecLt[i].position.y = pos.y + y_wvLt(x_rel);
  wvVec[i].position.y = wvVecRt[i].position.y + wvVecLt[i].position.y - pos.y;
  }   */

  return;
}

void waveSeg::setState(float phase_left, float phase_right)
{
  phsLt = phase_left;
  phsRt = phase_right;
  setState_1();
}

void waveSeg::setState_1()
{
  float dx = magL / ( float ) (Npts_wv - 1);
  float x_rel = 0.0f;
  for (size_t i = 0; i<wvVec.size(); ++i)
  {
    x_rel = dx * ( float ) i;
    if (viewRt && wvVecRt.size() == wvVec.size()) wvVecRt[i].position.y = pos.y + y_wvRt(x_rel);
    if (viewLt && wvVecLt.size() == wvVec.size()) wvVecLt[i].position.y = pos.y + y_wvLt(x_rel);
    wvVec[i].position.y = wvVecRt[i].position.y + wvVecLt[i].position.y - pos.y;
    wvVec[i].position.y = pos.y + y_wvLt(x_rel) + y_wvRt(x_rel);

    if (viewBelow && i + 1 < wvVec.size())
    {
      wvVtxVec[4 * i].position.y = wvVec[i].position.y;
      wvVtxVec[4 * i + 1].position.y = wvVec[i + 1].position.y;
    }
  }

  return;
}

state_ab* waveSeg::newState()
{
  std::function<void(float, float)> p_SetFuncFF = std::bind(&waveSeg::setState, this, std::placeholders::_1, std::placeholders::_2);
  return new state_ff(&phsLt, &phsRt, p_SetFuncFF);
}

bool waveSeg::hit(mvHit& mh)
{
  // above the top?
  vec2d sepAtTop = mh.pos - (pos + N * Elev);// sep is rel position
  float h = sepAtTop.dot(N);// > 0 if above
  if (h > 0.0f) return false;
  float d = N.cross(sepAtTop);
  if (d < 0.0f || d > L.mag()) return false;// not above seg

                                            // below the bottom?
  vec2d sepAtBot = mh.pos - (pos - N * Depth);// sep is rel position
  h = sepAtBot.dot(N);// > 0 if above
  if (h < 0.0f) return false;

  // will be treating hit
  vec2d sep = mh.pos - pos;// sep is rel position
  float yPm = wv_slope(sep.x);// new pos
  float ampRes = y_res(sep.x) - mh.project(-N)*(sqrtf(1.0f + yPm * yPm) - 1.0f);// wave amplitude + set above
  sep.y -= ampRes;
  h = sep.dot(N);// height above wave to mh.pos
                 //position shift
  mh.pos.y -= ampRes;
  // velocity shift relative to rising wave
  float vShift_y = y_vel(sep.x);
  mh.v.y -= vShift_y;
  // Get normal to surface
  vec2d Nsurf(1.0f, yPm);
  Nsurf = Nsurf.get_LH_norm();

  bool Hit = false;
  vec2d Pimp, Nh;
  float dSep;
  //    if( is_onMe( mh, Pimp, Nh, dSep ) )
  if (mh.is_inMe(*static_cast<const lineSeg*>(this), Pimp, Nh, dSep))
  {
    if (is_hard)
    {
      mh.bounce(Cf, Nsurf, friction_on);// velocity response
      mh.pos.y += ampRes;
      mh.v.y += vShift_y;
      mh.setPosition(mh.pos + Nh * dSep);// position change response
      return true;
    }
    else
      mh.Float(Nsurf, Nh, dSep, grav_N, airDensity, fluidDensity);

    Hit = true;
  }

  mh.v.y += vShift_y;// old pos
  mh.pos.y += ampRes;// new pos

  if (!is_hard && !Hit)
  {
    if (sep.dot(N) > 0.0f)// in air
      mh.Float(N, grav_N, airDensity);
    else
      mh.Float(N, grav_N, fluidDensity);
  }

  return Hit;
}


/*
bool waveSeg::hit( mvHit& mh )
{
vec2d sep = mh.pos - pos;// sep is rel position
float ampRes = y_res( sep.x );// wave amplitude here
float h = sep.dot(N);// > 0 if above

if( h > Amp_wv + Amp_wvLt + mh.project( vec2d(0.0f,1.0f) ) ) return false;// mh above wave
if( h < -1.0f*( Amp_wv + Amp_wvLt + mh.project( vec2d(0.0f,-1.0f) ) ) ) return false;// mh above wave

//position shift
mh.pos.y -= ampRes;
// velocity shift relative to rising wave
float vShift_y = y_vel(sep.x);
mh.v.y -= vShift_y;
// finally, rotate velocity to face. Will need to vShift_x also.

bool Hit = false;
vec2d Pimp, Nh;
float dSep;
if( is_onMe( mh, Pimp, Nh, dSep ) )
{
if( is_hard )
{
mh.bounce( Cf, Nh, friction_on );// velocity response
mh.pos.y += ampRes;
mh.v.y += vShift_y;
mh.setPosition( mh.pos + Nh*dSep );// position change response
return true;
}
else
mh.Float( getSurfaceNormal(mh), Nh, dSep );

Hit = true;
}

mh.pos.y += ampRes;
mh.v.y += vShift_y;

return Hit;
}
*/
