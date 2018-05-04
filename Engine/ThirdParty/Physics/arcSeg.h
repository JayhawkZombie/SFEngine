#ifndef ARCSEG_H_INCLUDED
#define ARCSEG_H_INCLUDED

#include <cereal/types/array.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/archives/portable_binary.hpp>

#include "segHit.h"

class arcSeg : public segHit
{
public:
  vec2d s[2];// use inherited pos as Ctr
  float R;
  sf::Vertex Q[20];// draw arc as a lineStrip

  arcSeg() {}// don't use a default constructed lineSeg
  void init(float x1, float y1, float x2, float y2, float radius, sf::Color clr = sf::Color::Red);
  arcSeg(vec2d s0, vec2d s1, float radius, sf::Color clr = sf::Color::Red) { init(s0.x, s0.y, s1.x, s1.y, radius, clr); }
  arcSeg(float x1, float y1, float x2, float y2, float radius, sf::Color clr = sf::Color::Red) { init(x1, y1, x2, y2, radius, clr); }
  arcSeg(std::istream& fin);
  virtual void init(std::istream& fin);
  virtual void to_file(std::ofstream& fout);
  virtual ~arcSeg();
  virtual void setPosition(vec2d Pos);

  virtual void draw(sf::RenderTarget& rRW)const { rRW.draw(Q, 20, sf::LinesStrip); }
  virtual bool hit(mvHit&);
  virtual bool is_thruMe(vec2d pt1, vec2d pt2, vec2d& Pimp, float& fos)const;
  //   bool is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& N, float& pen )const;
  //   virtual vec2d getSurfaceNormal( const mvHit& mh )const;

  template<class Archive>
  void serialize(Archive & ar)
  {
    ar(cereal::base_class<segHit>(this));
    ar(s[0], s[1], R);
    ar(Q);
  }
};

CEREAL_REGISTER_TYPE(arcSeg);

#endif // ARCSEG_H_INCLUDED
