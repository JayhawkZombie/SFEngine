#ifndef LINESEGROTATE_H_INCLUDED
#define LINESEGROTATE_H_INCLUDED

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include "lineSeg.h"

class lineSegRotate : public lineSeg
{
public:
  float rotVel;

  lineSegRotate() : lineSeg() {}// don't use a default constructed lineSeg
  lineSegRotate(std::istream& fin);
  virtual void init(std::istream& fin);
  virtual ~lineSegRotate() {}
  virtual void to_file(std::ofstream& fout);
  //  virtual state_ab* newState() { return new state_f( &rotVel, nullptr ); }// caching vel in a state_f

  virtual state_ab* newState();
  void setState(const float* pf);
  void getState(float* pf)const;

  virtual void update(float dt);
  virtual bool hit(mvHit& mh);

  template<class Archive>
  void serialize(Archive &ar)
  {
    ar(cereal::base_class<lineSeg>(this));

    ar(rotVel);
  }

};

CEREAL_REGISTER_TYPE(lineSegRotate);

#endif // LINESEGROTATE_H_INCLUDED
