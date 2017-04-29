#ifndef LINESEGFLIP_H_INCLUDED
#define LINESEGFLIP_H_INCLUDED

#include "lineSegRotate.h"

class lineSegFlip : public lineSegRotate
{
public:
  vec2d Lup, Ldn;
  float rotVelFlip;//
  int state;// -1=going down, 0=stopped, +1=going up
  bool isUp;

  lineSegFlip() : lineSegRotate() {}
  lineSegFlip(std::istream& fin);

  virtual ~lineSegFlip() {}
  virtual void init(std::istream& fin);

  virtual void update();
  virtual void to_file(std::ofstream& fout);

  bool is_up()const;
  void init_up();// trigger actions
  void init_dn();
  void set_up();// set state
  void set_dn();
};

#endif // LINESEGFLIP_H_INCLUDED
