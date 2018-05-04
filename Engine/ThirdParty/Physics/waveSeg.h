#ifndef WAVESEG_H_INCLUDED
#define WAVESEG_H_INCLUDED

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include <vector>
#include "lineSeg.h"

class waveSeg : public lineSeg
{
public:
  static float PIx2;

  float wvSpeed = 1.0f;// = rotFreq/K_wv
                       // traveling wave - right
  float Amp_wvRt, K_wvRt;// K_wvRt = 2*PI/wavelength
  float rotFreqRt;// Note wave speed = v = rotFreq/K_wvRt = rotFreq*wavelength/2pi
  float phsRt = 0.0f;
  // traveling wave - left
  float Amp_wvLt, K_wvLt;// K_wvRt = 2*PI/wavelength
  float rotFreqLt;// but make > 0 too. See '+' vs '-' sign use in y(x) funcs
  float phsLt = 0.0f;

  float magL;// cached length of lineSeg (since lineSeg can't be bothered)
             //    bool viewLt = true, viewRt = true, viewSeg = true;
  bool viewLt = false, viewRt = false, viewSeg = false;
  bool viewBelow = false;
  sf::Color underColor;

  // zones above and below too
  float grav_N;
  float Elev, airDensity;
  float Depth, fluidDensity;

  // draw the waves
  int Npts_wv = 100;
  std::vector<sf::Vertex> wvVec;
  std::vector<sf::Vertex> wvVecLt;
  std::vector<sf::Vertex> wvVecRt;
  // below surface
  std::vector<sf::Vertex> wvVtxVec;
  sf::Vertex underQuad[4];

  // funcs
  waveSeg() {}// defs here
  virtual ~waveSeg() {}
  // defs in cpp
  waveSeg(std::istream& is);
  virtual void init(std::istream& is);
  virtual void to_file(std::ofstream& fout);
  virtual void draw(sf::RenderTarget&)const;
  virtual void update(float dt);
  void setState_1();// called by update()
  void setState(float phase_left, float phase_right);// for caller use
  void initUnderView();

  virtual state_ab* newState();

  virtual bool hit(mvHit&);

  // back to defs here
  //   virtual vec2d getSurfaceNormal( const mvHit& mh )const { return L.get_LH_norm(); }// BASE VERSION. Modify

  float getWavelengthLt()const { return PIx2 / K_wvLt; }
  float getWavelengthRt()const { return PIx2 / K_wvRt; }
  void setWavelengthLt(float wvLen) { K_wvLt = PIx2 / wvLen; rotFreqLt = wvSpeed * K_wvLt; if (viewBelow) initUnderView(); }
  void setWavelengthRt(float wvLen) { K_wvRt = PIx2 / wvLen; rotFreqRt = wvSpeed * K_wvRt; if (viewBelow) initUnderView(); }

  void setAmplitudeLt(float Amp) { Amp_wvLt = Amp; if (viewBelow) initUnderView(); }
  void setAmplitudeRt(float Amp) { Amp_wvRt = Amp; if (viewBelow) initUnderView(); }

  float y_wvRt(float x) { return Amp_wvRt * sinf(K_wvRt*x - phsRt); }// rotFreq > 0  <--> wave traveling to right
  float y_wvLt(float x) { return Amp_wvLt * sinf(K_wvLt*x + phsLt); }// rotFreq > 0  <--> wave traveling to right
  float y_res(float x) { return y_wvRt(x) + y_wvLt(x); }

  float y_vel(float x) { return Amp_wvLt * rotFreqLt*cosf(K_wvLt*x + phsLt) - Amp_wvRt * rotFreqRt*cosf(K_wvRt*x - phsRt); }// partial deriv wrt t
  float wv_slope(float x) { return Amp_wvLt * K_wvLt*cosf(K_wvLt*x + phsLt) + Amp_wvRt * K_wvRt*cosf(K_wvRt*x - phsRt); }// partial deriv wrt x

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<lineSeg>(this));

    ar(wvSpeed, Amp_wvLt, Amp_wvRt, K_wvLt, K_wvRt,
      rotFreqLt, rotFreqRt, phsLt, phsRt,
      magL, viewLt, viewRt, viewSeg, viewBelow,
      underQuad, grav_N, Elev, airDensity,
      Depth, fluidDensity, Npts_wv, wvVtxVec,
      wvVecLt, wvVecRt, wvVtxVec, underQuad);
  }

};

CEREAL_REGISTER_TYPE(waveSeg);

#endif // WAVESEG_H_INCLUDED
