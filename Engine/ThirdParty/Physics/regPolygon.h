#ifndef REGPOLYGON_H_INCLUDED
#define REGPOLYGON_H_INCLUDED

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
//#include "vec2d.h"
//#include "ball.h"
#include "mvHit.h"

class regPolygon : public mvHit
{
public:
  //  float r;// length of rays
  size_t nSides;// = ptVec.size()
  std::vector<vec2d> ptVec;// official
  std::vector<sf::Vertex> vtxVec;// visual

  regPolygon(std::istream& fin);
  regPolygon();
  virtual mvHit* clone() const { return new regPolygon(*this); }
  virtual ~regPolygon() {}
  virtual void init(std::istream& fin);
  virtual const char* myName() const { return "regPolygon"; }

  virtual void update(float dt);
  virtual void draw(sf::RenderTarget& rRW)const;
  virtual void setPosition(vec2d Pos);

  //   virtual void respond( float dV, bool isFric );
  //   virtual void impact( regPolygon& rpg );
  virtual bool hit(const vec2d& pt);

  virtual bool hit(regPolygon& rpg);
  virtual bool hit(ball& rB);
  virtual bool hit(mvHit&);

  virtual bool intersect(mvHit& mh);
  virtual bool intersect(ball& rB);
  virtual bool intersect(regPolygon& py);

  //   virtual void vShift() { return; }
  //   virtual void vShift_inv() { return; }

  virtual bool is_inMe(const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep)const;// detailed collision detection
  virtual bool is_inMe(const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep)const;// code goes here. Impact point is written.
  virtual bool is_inMe(vec2d pt, vec2d& sep, vec2d& N, float& dSep)const;// writes qtys needed for collision response

  bool is_inMe(const regPolygon& rpg, vec2d& sep, vec2d& N, float& dSep)const;// writes qtys needed for collision response
  virtual bool is_inMe(const ball& rB, vec2d& sep, vec2d& N, float& dSep)const;// writes qtys needed for collision response
  bool is_inMe(vec2d pt, vec2d ctr, vec2d& sep, vec2d& N, float& dSep)const;// writes qtys needed for collision response toward ctr
                                                                            //    void handleImpact( mvHit& mh, vec2d sep, vec2d N, float dSep );
  virtual bool is_thruMe(vec2d pt1, vec2d pt2, vec2d& Pimp, float& fos)const;// for bulletproofing, laser sighting, etc = ball version for now

  virtual float project(vec2d vUnit)const;// max projection along vUnit

                                          //   void handleImpact( vec2d ptPos, ball& rB );
                                          //   virtual bool inCircle( vec2d ctr, float R, vec2d& Pimp )const;
  virtual float getRotation()const;
  virtual void setRotation(float angle);

  float getRadius()const { return r; }
  void setRadius(float R);

  virtual bool Float(vec2d Nsurf, vec2d Npen, float penAmt, float grav_N, float airDensity, float fluidDensity);
  virtual bool Float(vec2d Nsurf, float grav_N, float Density);

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<mvHit>(this));

    ar(nSides, ptVec, vtxVec);
  }
};

CEREAL_REGISTER_TYPE(regPolygon);

#endif // REGPOLYGON_H_INCLUDED
