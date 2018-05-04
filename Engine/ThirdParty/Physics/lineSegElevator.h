#ifndef LINESEGELEVATOR_H_INCLUDED
#define LINESEGELEVATOR_H_INCLUDED

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include "lineSeg.h"

class lineSegElevator : public lineSeg
{
private:
  vec2d vel;
  vec2d uVel;// unit vector in direction of vel
public:
  float magVel;
  //    public:
  // inherited data members
  //    vec2d pos, L, N;
  //    sf::Vertex vtx[2];

  //    float drag;

  // added dms
  vec2d iPos;// position at s = 0.0f
  float s, sMin, sMax;// travel
  int state;// -1=going down, 0=stopped, +1=going up
  bool isUp, isDn;

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<lineSeg>(this));

    ar(vel, uVel, magVel, iPos, s, sMin, sMax, state, isUp, isDn);
  }

  // funcs
  lineSegElevator() : lineSeg() {}// don't use a default constructed lineSeg
  lineSegElevator(std::istream& fin);

  virtual ~lineSegElevator() {}
  virtual void init(std::istream& fin);
  virtual void to_file(std::ofstream& fout);

  virtual void setPosition(vec2d);// to update iPos
  virtual vec2d getPosition()const { return iPos; }
  virtual void setVel(vec2d V);
  //    virtual bool hit( ball& rB );// base version OK. No hit based triggers yet
  virtual void update(float dt);
  virtual bool hit(mvHit& mh);

  bool is_up()const { return isUp; }
  bool is_dn()const { return isDn; }
  void init_up();// trigger actions
  void init_dn();
  void set_up();// set state
  void set_dn();
  void stop() { state = 0; vel *= 0.0f; }

  virtual state_ab* newState();
  void setState(const float* pf);
  void getState(float* pf)const;
};

CEREAL_REGISTER_TYPE(lineSegElevator);

#endif // LINESEGELEVATOR_H_INCLUDED
