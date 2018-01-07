#ifndef EXPANDPOLYGON_H_INCLUDED
#define EXPANDPOLYGON_H_INCLUDED

#include "regPolygon.h"

class expandPolygon : public regPolygon
{
public:
  float growSpeed;
  float rFull;
  int growState;// usual -1, 0, +1 scheme

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(cereal::base_class<regPolygon>(this));

    ar(growSpeed, rFull, growState);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(cereal::base_class<regPolygon>(this));

    ar(growSpeed, rFull, growState);
  }

  virtual mvHit* clone() const {
    return new expandPolygon(*this);
  }
  virtual const char* myName() const {
    return "expandPolygon";
  }

  expandPolygon(std::istream& fin);
  virtual void init(std::istream& fin);
  expandPolygon() {}
  virtual ~expandPolygon() {}

  virtual bool hit(ball& rB);
  virtual bool hit(regPolygon& rpg);
  virtual bool hit(mvHit&);
  virtual bool bounce(float Cf, vec2d N, bool isFric);// rigid bounce. N is line of action
  virtual void update();

  void setState_xp(vec2d Pos, vec2d Vel, float R, int growSt) {
    r = R; growState = growSt; v = Vel; setPosition(Pos);
  }
  virtual state_ab* newState();

  // utility
  void Transform();// expand or shrink. Will reverse transform in progress.
  void set_rFull(float R);

  //    virtual float vShift();
  // all other inherited functions should do
};

#endif // EXPANDPOLYGON_H_INCLUDED
