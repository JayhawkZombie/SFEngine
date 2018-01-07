#ifndef SEGHIT_H_INCLUDED
#define SEGHIT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "vec2d.h"
#include "stateTypes.h"

class mvHit;

class segHit
{
public:
  vec2d pos;
  bool testEnd1 = false, testEnd2 = false;

  float Cf = 0.5f;// friction coeff
  bool friction_on = false;
  bool is_hard = true;
  bool is_bulletProof = false;
  int hitSide = 0;// -1 = !Nside, 1 = Nside, 0 = both sides

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(pos);
    ar(testEnd1, testEnd2);
    ar(Cf, friction_on, is_hard, is_bulletProof, hitSide);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(pos);
    ar(testEnd1, testEnd2);
    ar(Cf, friction_on, is_hard, is_bulletProof, hitSide);
  }

  segHit() {}
  segHit(std::istream& fin);
  virtual ~segHit() {}
  virtual void init(std::istream& fin);
  virtual void to_file(std::ofstream& fout);
  virtual void setPosition(vec2d) = 0;
  virtual vec2d getPosition()const {
    return pos;
  }

  virtual void draw(sf::RenderTarget&)const = 0;
  virtual void update();// added so lineRotateSeg has in interface

                        //    virtual bool hit( mvHit& );
  virtual bool hit(mvHit&) = 0;
  virtual bool is_thruMe(vec2d pt1, vec2d pt2, vec2d& Pimp, float& fos)const = 0;// for bulletproofing, laser sighting, etc.

  virtual state_ab* newState() {
    return nullptr;
  }// over ride in waveSeg

   //   virtual bool is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen )const = 0;
   //   virtual vec2d getSurfaceNormal( const mvHit& mh )const = 0;
};

#endif // SEGHIT_H_INCLUDED
