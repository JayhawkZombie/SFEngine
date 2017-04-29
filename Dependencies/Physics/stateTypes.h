#ifndef STATETYPES_H_INCLUDED
#define STATETYPES_H_INCLUDED

#include<vector>
#include<functional>
#include "vec2d.h"

struct state_ab// storage for the dynamic state members of an object
{
  virtual void setState()const = 0;// set state of the bound object
  virtual state_ab* clone_current()const = 0;// obtain new instance in the current state
  virtual void update() = 0;// make this instance current
  virtual ~state_ab() {}
};

struct state_vv : state_ab// 2 x vec2d
{
  std::function<void(vec2d, vec2d)> pSetFunc;// bind to objects setState()
  const vec2d *pa, *pb;// pointers to the data members this state reps. Read only
  vec2d a, b;// the state data

  state_vv(vec2d *pA, vec2d *pB, std::function<void(vec2d, vec2d)> p_SetFunc) : pSetFunc(p_SetFunc), pa(pA), pb(pB) {
    a = *pa; b = *pb;
  }

  virtual void setState()const {
    pSetFunc(a, b);
  }
  virtual state_ab* clone_current()const {
    state_vv* pVV = new state_vv(*this); pVV->a = *pa; pVV->b = *pb; return pVV;
  }
  virtual void update() {
    a = *pa; b = *pb;
  }
  virtual ~state_vv() {}
};

struct state_f : state_ab// 1 x float
{
  std::function<void(float)> pSetFunc;// bind to objects setState()
  float *pa;// pointers to the data members this state reps.
  float a;// the state data

  state_f(float *pA, std::function<void(float)> p_SetFunc) : pSetFunc(p_SetFunc), pa(pA) {
    a = *pa;
  }

  virtual void setState()const {
    if (pSetFunc) pSetFunc(a); else *pa = a;
  }
  virtual state_ab* clone_current()const {
    state_f* pFF = new state_f(*this); pFF->a = *pa; return pFF;
  }
  virtual void update() {
    a = *pa;
  }
  virtual ~state_f() {}
};

/*
struct state_fb : state_ab// float + bool
{
std::function<void(float, bool)> pSetFunc;// bind to objects setState()
float *pa;// pointers to the data members this state reps.
float a;// the state data
bool* pBool;
bool tfVal;

state_fb( float *pA, bool* pTFval, std::function<void(float, bool)> p_SetFunc ): pSetFunc( p_SetFunc ), pa(pA), pBool(pTFval) { a = *pa; tfVal = *pBool; }

virtual void setState()const { if( pSetFunc ) pSetFunc(atfVal); else { *pa = a; *pBool = tfVal;} }
virtual state_ab* clone_current()const { state_fb* pFB = new state_fb(*this); pFB->a = *pa; pFB->tfVal = *pBool; return pFB; }
virtual void update() { a = *pa; tfVal = *pBool; }
virtual ~state_fb(){}
};  */

struct state_ff : state_ab// 2 x float
{
  std::function<void(float, float)> pSetFunc;// bind to objects setState()
  const float *pa, *pb;// pointers to the data members this state reps.
  float a, b;// the state data

  state_ff(float *pA, float *pB, std::function<void(float, float)> p_SetFunc) : pSetFunc(p_SetFunc), pa(pA), pb(pB) {
    a = *pa; b = *pb;
  }

  virtual void setState()const {
    pSetFunc(a, b);
  }
  virtual state_ab* clone_current()const {
    state_ff* pFF = new state_ff(*this); pFF->a = *pa; pFF->b = *pb; return pFF;
  }
  virtual void update() {
    a = *pa; b = *pb;
  }
  virtual ~state_ff() {}
};

struct state_vvfi : state_ab// 2 x vec2d + float + int
{
  std::function<void(vec2d, vec2d, float, int)> pSetFunc;// bind to objects setState()
  const vec2d *pva, *pvb;// pointers to the data members this state reps. Read only
  vec2d va, vb;// the state data
  const float *pfa;
  float fa;
  const int *pia = nullptr;
  int ia;
  std::function<int(void)> pGetInt = nullptr;

  state_vvfi(vec2d *pvA, vec2d *pvB, float *pfA, int *piA, std::function<void(vec2d, vec2d, float, int)> p_SetFunc)
    : pSetFunc(p_SetFunc), pva(pvA), pvb(pvB), pfa(pfA), pia(piA)
  {
    va = *pva; vb = *pvb; fa = *pfa; ia = *pia;
  }

  state_vvfi(vec2d *pvA, vec2d *pvB, float *pfA, std::function<int(void)> p_GetInt, std::function<void(vec2d, vec2d, float, int)> p_SetFunc)
    : pSetFunc(p_SetFunc), pva(pvA), pvb(pvB), pfa(pfA), pGetInt(p_GetInt)
  {
    va = *pva; vb = *pvb; fa = *pfa; ia = pGetInt();
  }

  virtual void setState()const {
    pSetFunc(va, vb, fa, ia);
  }
  virtual state_ab* clone_current()const
  {
    state_vvfi* pSt = new state_vvfi(*this);
    pSt->va = *pva; pSt->vb = *pvb; pSt->fa = *pfa;
    if (pia) pSt->ia = *pia;
    else if (pGetInt) pSt->ia = pGetInt();
    return pSt;
  }

  virtual void update() {
    va = *pva; vb = *pvb; fa = *pfa; if (pia) ia = *pia; else if (pGetInt) ia = pGetInt();
  }
  virtual ~state_vvfi() {}
};


#endif // STATETYPES_H_INCLUDED
