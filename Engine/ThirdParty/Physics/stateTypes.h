#ifndef STATETYPES_H_INCLUDED
#define STATETYPES_H_INCLUDED

#include<vector>
#include<functional>
#include "vec2d.h"

struct state_ab// storage for the dynamic state members of an object
{
  virtual void setState(size_t i)const = 0;// set state of the bound object to ith saved one
                                           //   virtual state_ab* clone_current()const = 0;// obtain new instance in the current state
  virtual void update(size_t i) = 0;// make the ith state the current one
  virtual void pushState() = 0;// expanding cache. back = current state
  virtual void Reserve(size_t cap) = 0;// reserve capacity for each vector storage
  virtual ~state_ab() {}
};

struct state_vv : state_ab// 2 x vec2d
{
  std::function<void(vec2d, vec2d)> pSetFunc;// bind to objects setState()
  const vec2d *pa, *pb;// pointers to the data members this state reps. Read only
  std::vector<vec2d> a, b;// the state data

  state_vv(vec2d *pA, vec2d *pB, std::function<void(vec2d, vec2d)> p_SetFunc) : pSetFunc(p_SetFunc), pa(pA), pb(pB) {  }// no initial state assigned

  virtual void setState(size_t i)const { if (i < a.size() && i < b.size()) pSetFunc(a[i], b[i]); }
  virtual void update(size_t i) { if (i < a.size() && i < b.size()) { a[i] = *pa; b[i] = *pb; } }
  virtual void pushState() { a.push_back(*pa); b.push_back(*pb); }// expanding cache. back = current state
  virtual void Reserve(size_t cap) { a.reserve(cap); b.reserve(cap); }// reserve capacity for each vector storage
  virtual ~state_vv() {}
};

struct state_f : state_ab// 1 x float
{
  std::function<void(float)> pSetFunc;// bind to objects setState()
  float *pa;// pointers to the data members this state reps.
  std::vector<float> a;// the state data

  state_f(float *pA, std::function<void(float)> p_SetFunc) : pSetFunc(p_SetFunc), pa(pA) {}

  virtual void setState(size_t i)const { if (i >= a.size()) return; if (pSetFunc) pSetFunc(a[i]); else *pa = a[i]; }
  virtual void update(size_t i) { if (i < a.size()) a[i] = *pa; }
  virtual void pushState() { a.push_back(*pa); }// expanding cache. back = current state
  virtual void Reserve(size_t cap) { a.reserve(cap); }
  virtual ~state_f() {}
};

struct state_ff : state_ab// 2 x float
{
  std::function<void(float, float)> pSetFunc;// bind to objects setState()
  const float *pa, *pb;// pointers to the data members this state reps.
  std::vector<float> a, b;// the state data

  state_ff(float *pA, float *pB, std::function<void(float, float)> p_SetFunc) : pSetFunc(p_SetFunc), pa(pA), pb(pB) {}

  virtual void setState(size_t i)const { if (i < a.size() && i < b.size()) pSetFunc(a[i], b[i]); }
  virtual void update(size_t i) { if (i < a.size() && i < b.size()) { a[i] = *pa; b[i] = *pb; } }
  virtual void pushState() { a.push_back(*pa); b.push_back(*pb); }// expanding cache. back = current state
  virtual void Reserve(size_t cap) { a.reserve(cap); b.reserve(cap); }// reserve capacity for each vector storage
  virtual ~state_ff() {}
};

struct state_fn : state_ab// n x float
{
  std::function<void(const float*)> pSetFunc;// bind to objects setState()
  std::function<void(float*)> pGetFunc = nullptr;// bind to objects getState()
  std::vector<float*> pfVec;// pointers to the data members this state reps.
  std::vector<float> fVec;// the state data
  size_t n = 1;// # cached

  state_fn(const std::vector<float*>& p_fVec, std::function<void(const float*)> p_SetFunc) : pSetFunc(p_SetFunc), n(p_fVec.size()) { pfVec = p_fVec; }
  state_fn(std::function<void(float*)> p_GetFunc, std::function<void(const float*)> p_SetFunc, size_t N) : pSetFunc(p_SetFunc), pGetFunc(p_GetFunc), n(N) {}

  virtual void setState(size_t i)const { if ((i + 1)*n <= fVec.size()) pSetFunc(&(fVec[i*n])); }

  virtual void update(size_t i)
  {
    if ((i + 1)*n <= fVec.size())
    {
      if (pGetFunc) pGetFunc(&(fVec[i*n]));
      else if (pfVec.size() == n)
        for (size_t j = 0; j<n; ++j) fVec[i*n + j] = *pfVec[j];
    }
  }

  virtual void pushState()
  {
    if (pGetFunc)
    {
      for (size_t j = 0; j<n; ++j) fVec.push_back(0.0f);
      pGetFunc(&(fVec[fVec.size() - n]));
    }
    else for (size_t j = 0; j<n; ++j) fVec.push_back(*pfVec[j]);
  }// expanding cache. back = current state

  virtual void Reserve(size_t cap) { fVec.reserve(n*cap); }// reserve capacity for each vector storage
  virtual ~state_fn() {}
};

/*
struct state_fn : state_ab// n x float
{
std::function<void(const float*)> pSetFunc;// bind to objects setState()
std::vector<float*> pfVec;// pointers to the data members this state reps.
std::vector<float> fVec;// the state data
size_t n = 1;// # cached

state_fn( const std::vector<float*>& p_fVec, std::function<void(const float*)> p_SetFunc ): pSetFunc( p_SetFunc ), n(p_fVec.size()) { pfVec = p_fVec; }

virtual void setState(size_t i)const { if( (i+1)*n <= fVec.size() ) pSetFunc( &(fVec[i*n]) ); }
virtual void update(size_t i) { if( (i+1)*n <= fVec.size() ) { for( size_t j=0; j<n; ++j ) fVec[i*n+j] = *pfVec[j]; } }
virtual void pushState()  { for( size_t j=0; j<n; ++j ) fVec.push_back( *pfVec[j] ); }// expanding cache. back = current state
virtual void Reserve(size_t cap) { fVec.reserve(n*cap); }// reserve capacity for each vector storage
virtual ~state_fn(){}
};
*/

struct state_vvfi : state_ab// 2 x vec2d + float + int
{
  std::function<void(vec2d, vec2d, float, int)> pSetFunc;// bind to objects setState()
  const vec2d *pva, *pvb;// pointers to the data members this state reps. Read only
  std::vector<vec2d> va, vb;// the state data
  const float *pfa;
  std::vector<float> fa;
  const int *pia = nullptr;
  std::vector<int> ia;
  std::function<int(void)> pGetInt = nullptr;

  state_vvfi(vec2d *pvA, vec2d *pvB, float *pfA, int *piA, std::function<void(vec2d, vec2d, float, int)> p_SetFunc)
    : pSetFunc(p_SetFunc), pva(pvA), pvb(pvB), pfa(pfA), pia(piA) {}

  state_vvfi(vec2d *pvA, vec2d *pvB, float *pfA, std::function<int(void)> p_GetInt, std::function<void(vec2d, vec2d, float, int)> p_SetFunc)
    : pSetFunc(p_SetFunc), pva(pvA), pvb(pvB), pfa(pfA), pGetInt(p_GetInt) {}

  virtual void setState(size_t i)const { if (i < va.size()) pSetFunc(va[i], vb[i], fa[i], ia[i]); }
  virtual void update(size_t i) { if (i < va.size()) { va[i] = *pva; vb[i] = *pvb; fa[i] = *pfa; if (pia) ia[i] = *pia; else if (pGetInt) ia[i] = pGetInt(); } }
  virtual void pushState() { va.push_back(*pva); vb.push_back(*pvb); fa.push_back(*pfa); if (pia) ia.push_back(*pia); else if (pGetInt) ia.push_back(pGetInt()); }
  virtual void Reserve(size_t cap) { va.reserve(cap); vb.reserve(cap); fa.reserve(cap); ia.reserve(cap); }

  virtual ~state_vvfi() {}
};

struct state_ffvp : state_ab// 2 x float + void*
{
  std::function<void(float, float, void*)> pSetFunc;// bind to objects setState()
  float *pa, *pb;// pointers to the data members this state reps.
  std::vector<float> a, b;// the state data
  void **ppAddy;// where adress is stored
  std::vector<void*> pAddy;// address stored

                           //   state_ffvp( float *pA, float *pB, void** pp_Addy ): pa(pA), pb(pB), ppAddy( pp_Addy ) {}
  state_ffvp(float *pA, float *pB, void** pp_Addy, std::function<void(float, float, void*)> p_SetFunc = nullptr) : pSetFunc(p_SetFunc), pa(pA), pb(pB), ppAddy(pp_Addy) {}

  //  virtual void setState(size_t i)const { if( i >= a.size() ) return; *pa = a[i]; *pb = b[i]; *ppAddy = pAddy[i]; }
  virtual void setState(size_t i)const { if (i >= a.size()) return; if (pSetFunc) pSetFunc(a[i], b[i], pAddy[i]); else { *pa = a[i]; *pb = b[i]; *ppAddy = pAddy[i]; } }
  virtual void update(size_t i) { if (i >= a.size()) return; a[i] = *pa; b[i] = *pb; pAddy[i] = *ppAddy; }

  virtual void pushState() { a.push_back(*pa); b.push_back(*pb);  pAddy.push_back(*ppAddy); }// expanding cache. back = current state
  virtual void Reserve(size_t cap) { a.reserve(cap); b.reserve(cap); pAddy.reserve(cap); }

  virtual ~state_ffvp() {}
};


#endif // STATETYPES_H_INCLUDED
