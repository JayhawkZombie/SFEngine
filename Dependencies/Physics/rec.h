#ifndef REC_H_INCLUDED
#define REC_H_INCLUDED

#include<vector>
#include<string>
#include<sstream>
#include<iostream>

#include "stateTypes.h"

namespace rec
{
  // Value of z "history" is stored in cacheVec
  void saveState();// val will be saved in cacheVec
  void restoreState(size_t ofst);// writes value stored in cacheVec at back + ofst position
  bool update();// will use function pointer to store pFunc(z) in cacheVec, or z itself otherwise.
  void init(size_t cacheSz, size_t saveFreq, void(*p_InitFunc)(std::vector<state_ab*>&), bool* p_onOff = nullptr);
  void re_init();// after cloning
  void cleanup();
  void initControl(std::vector<std::string>*& pLabelVec, std::vector< std::function<void(void)> >*& p_pFuncVec, size_t stepSz = 50);

  void jog_rev();// false if already at initial state
  void jog_fwd();// false if already at final state
  void rewind_50();

  bool fwd(size_t n);
  bool rewind(size_t n);
  bool goTo(size_t n);
  bool is_recording();

  void goTo_initial();
  void goTo_final();

  void onOff();
  void record();
  void play();
  void stop();

}

#endif // REC_H_INCLUDED

/*
void init_rec( std::vector<state_ab*>& );

rec::init( 1000, 1, init_rec );// initA_bunch

void init_rec( std::vector<state_ab*>& p_stateVec )
{
if( !ppMvHitVec ) return;

std::vector<mvHit*>& pMHvec = *ppMvHitVec;
if( p_wvSeg ) p_stateVec.reserve( pMHvec.size() + 1 );// + 1 for waveSeg instance
else p_stateVec.reserve( pMHvec.size() );// just the mvHits

for( auto& mh : pMHvec )
{
std::function<void(vec2d,vec2d)> p_SetFunc = nullptr;//std::bind(mvHit::setState, mh, std::placeholders::_2);
p_stateVec.push_back( new state_vv( &(mh->pos), &(mh->v), p_SetFunc ) );
}


if( p_wvSeg );
//    p_stateVec.push_back( new state_ff( &(p_wvSeg->phsLt), &(p_wvSeg->phsRt), std::bind(waveSeg::setState, p_wvSeg, std::placeholders::_2) ) );

}
*/
