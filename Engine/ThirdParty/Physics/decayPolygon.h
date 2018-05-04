#ifndef DECAYPOLYGON_H_INCLUDED
#define DECAYPOLYGON_H_INCLUDED

#include<vector>

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include "regPolygon.h"

class decayPolygon : public regPolygon
{
public:
  virtual mvHit* clone() const { return new decayPolygon(*this); }
  virtual const char* myName() const { return "decayPolygon"; }

  static std::vector<mvHit*> *p_mvHitVec;
  static float E_split3, E_split4, E_split5;// energy to produce a 3,4 or 5 sided regPolygon in a split
  static float E_fuse;

  decayPolygon(std::istream& fin) : regPolygon(fin) {}
  decayPolygon() {}
  virtual ~decayPolygon() {}
  //    virtual void init( std::ifstream& fin );
  virtual bool hit(ball& rB);// split
  virtual bool hit(mvHit&);
  virtual bool hit(regPolygon& rpg);// absorb
                                    //   virtual void impact( regPolygon& rpg );// absorb

  regPolygon* split_reg(size_t n);// returns pointer to new n sided regPolygon and modifies *this to N-n
  void absorb_reg(regPolygon& rpg);
  // all other inherited functions should do

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<regPolygon>(this));
  }

};

// utility
//   vec2d velCm( const mvHit& A, const mvHit& B );
//  float Ek_Cm( const mvHit& A, const mvHit& B );

CEREAL_REGISTER_TYPE(decayPolygon);

#endif // DECAYPOLYGON_H_INCLUDED
