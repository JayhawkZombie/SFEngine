#ifndef BALL_GO_H_INCLUDED
#define BALL_GO_H_INCLUDED

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include "ball.h"

class ball_go : public ball
{
public:
  float maxVel;// magnitude, so > 0

               // functions
  ball_go(std::istream& fin);
  ball_go() {}
  virtual mvHit* clone() const { return new ball_go(*this); }
  virtual ~ball_go() {}
  virtual const char* myName() const { return "ball_go"; }

  virtual void init(std::istream& fin);
  virtual void respond(float dV, bool isFric);

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<ball>(this));

    ar(maxVel);
  }

};

CEREAL_REGISTER_TYPE(ball_go);

#endif // BALL_GO_H_INCLUDED
