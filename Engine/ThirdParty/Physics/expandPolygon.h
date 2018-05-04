#ifndef EXPANDPOLYGON_H_INCLUDED
#define EXPANDPOLYGON_H_INCLUDED

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include "regPolygon.h"

class expandPolygon : public regPolygon
{
public:
  float growSpeed;
  float rFull;
  int growState;// usual -1, 0, +1 scheme


  virtual mvHit* clone() const { return new expandPolygon(*this); }
  virtual const char* myName() const { return "expandPolygon"; }

  expandPolygon(std::istream& fin);
  virtual void init(std::istream& fin);
  expandPolygon() {}
  virtual ~expandPolygon() {}

  virtual bool hit(ball& rB);
  virtual bool hit(regPolygon& rpg);
  virtual bool hit(mvHit&);
  virtual bool bounce(float Cf, vec2d N, bool isFric);// rigid bounce. N is line of action
  virtual void update(float dt);

  void setState_xp(vec2d Pos, vec2d Vel, float R, int growSt) { r = R; growState = growSt; v = Vel; setRadius(R); setPosition(Pos); }
  virtual state_ab* newState();

  // utility
  void Transform();// expand or shrink. Will reverse transform in progress.
  void set_rFull(float R);
  virtual bool onFire() { r = growSpeed; growState = 1; return true; }

  //    virtual float vShift();
  // all other inherited functions should do

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<regPolygon>(this));

    ar(growSpeed, growState, rFull);
  }
};

CEREAL_REGISTER_TYPE(expandPolygon);

#endif // EXPANDPOLYGON_H_INCLUDED
