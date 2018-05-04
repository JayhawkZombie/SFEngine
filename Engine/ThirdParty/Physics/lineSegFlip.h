#ifndef LINESEGFLIP_H_INCLUDED
#define LINESEGFLIP_H_INCLUDED

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/memory.hpp>

#include "lineSegRotate.h"

class lineSegFlip : public lineSegRotate
{
public:
  vec2d Lup, Ldn;
  float rotVelFlip;//
  int state;// -1=going down, 0=stopped, +1=going up
  bool isUp;

  lineSegFlip() : lineSegRotate() { }

  lineSegFlip(std::istream& fin);

  virtual ~lineSegFlip() {}
  virtual void init(std::istream& fin);

  virtual void update(float dt);
  virtual void to_file(std::ofstream& fout);

  bool is_up()const;
  void init_up();// trigger actions
  void init_dn();
  void set_up();// set state
  void set_dn();

  /*   virtual state_ab* newState();
  void setState( const float* pf );
  void getState( float* pf )const;    */

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<lineSegRotate>(this));

    ar(Lup, Ldn, rotVelFlip, state, isUp);
  }

};

CEREAL_REGISTER_TYPE(lineSegFlip);

#endif // LINESEGFLIP_H_INCLUDED
