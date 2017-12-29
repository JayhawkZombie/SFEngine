#include "rec.h"

namespace rec
{
  bool running = false;
  size_t index_last = 0;
  size_t cacheLimit = 20;
  size_t dFrames = 3;// save period
  size_t frameCnt = 0;// kkeping track of relative position to initial state with this.
  bool* pOn = nullptr;

  // storage
  std::vector< std::vector<state_ab*> > pHistoryVec;// all the states
  std::vector<state_ab*> pStateVec;// current state
                                   // init - binding
  void(*pInitFunc)(std::vector<state_ab*>&);

}

void rec::init(size_t cacheSz, size_t saveFreq, void(*p_InitFunc)(std::vector<state_ab*>&), bool* p_onOff)
{
  cacheLimit = cacheSz;
  dFrames = saveFreq;

  pHistoryVec.reserve(cacheSz);
  pInitFunc = p_InitFunc;
  pInitFunc(pStateVec);
  index_last = 0;
  frameCnt = 0;
  running = false;
  pOn = p_onOff;
}

void rec::re_init()
{
  cleanup();
  pInitFunc(pStateVec);
  pHistoryVec.reserve(cacheLimit);
  std::cerr << "\n re_init: Clearing history";
}

void rec::cleanup()
{
  for (auto& pSt : pStateVec) delete pSt;
  pStateVec.clear();

  for (auto& stVec : pHistoryVec)
    for (auto& pSt : stVec) delete pSt;
  pHistoryVec.clear();

  frameCnt = 0;
  index_last = 0;
}

void rec::saveState()// every dFrames in circular manner
{
  if (pHistoryVec.size() > 0 && pHistoryVec[0].size() != pStateVec.size())// cloning. Clear and restart history. pInitFunc() was called
  {
    std::cerr << "\n saveState: Clearing history";
    // release all memory before clear
    for (auto& stVec : pHistoryVec)
      for (auto& pSt : stVec) delete pSt;

    pHistoryVec.clear();
    pHistoryVec.reserve(cacheLimit);
  }

  for (const auto& st : pStateVec) st->update();// maintain

  if (pHistoryVec.size() < cacheLimit)// push_back next set of datum
  {
    index_last = pHistoryVec.size();
    pHistoryVec.push_back(pStateVec);
    for (auto& pSt : pHistoryVec.back()) pSt = pSt->clone_current();// new instances
    std::cerr << "\n cache building: Nstates = " << pHistoryVec.size();
    std::cerr << " index_last = " << index_last;
  }
  else// over write last+1 (back of queue) then increment index_last
  {
    index_last = (1 + index_last) % cacheLimit;// 1st time rolls index_last = 0
                                               //     pHistoryVec[ index_last ] = pStateVec;
    for (auto& pSt : pHistoryVec[index_last]) pSt->update();// update existing instances
    std::cerr << "\n cache cycling: index_last = " << index_last;
  }

}


void rec::restoreState(size_t ofst)// F9 to step back dFrames
{
  if (index_last >= pHistoryVec.size()) {
    std::cerr << "\nsvbh"; return;
  }// something very bad happened
  if (pHistoryVec.size() == 0) return;// no states

                                      // ofst is from initial state, which is just ahead of index_last = next to be overwritten (oldest).
  size_t idx = 0;// index to 'initial state' if cache still building
  size_t cacheSz = pHistoryVec.size();
  if (cacheSz == cacheLimit) idx = index_last + 1;// 'initial' state follows 'current' state in the "queue" being emulated by cycling index_last
  idx += ofst; idx %= cacheSz;// add ofst and wrap

  for (const auto& st : pHistoryVec[idx]) st->setState();

  return;
}

bool rec::update()// will use function pointer to store pFunc(z) in cacheVec, or z itself otherwise.
{
  if (!running) return false;

  if (pHistoryVec.size() == 0)
  {
    saveState();// should cause index_last = 0 assign
    frameCnt = 0;// reset this value too
  }

  size_t cacheSz = pHistoryVec.size();

  ++frameCnt;

  if (frameCnt < dFrames*(cacheSz - 1))// in playback
  {
    if (frameCnt%dFrames == 0) {
      std::cout << "\n playback: frameCnt= " << frameCnt << " index_last = " << index_last; restoreState(frameCnt / dFrames);
    }
  }
  else if (frameCnt == dFrames*(cacheSz - 1))// end of playback reached
  {
    std::cout << "\n end playback. final state restored. frameCnt = " << frameCnt << " index_last = " << index_last;
    for (const auto& st : pHistoryVec[index_last]) st->setState();
    running = false;
    return false;// pause for user choice: continue forward and overwrite cached values, or replay recording
  }
  else// recording!
  {
    if (frameCnt%dFrames == 0)
    {
      std::cout << " saving: frameCnt= " << frameCnt;
      saveState();
      if (cacheSz == cacheLimit) frameCnt -= dFrames;// index_last got bumped above as well in this case
    }

    if (frameCnt > dFrames*cacheLimit)// illegal values have been seen
    {
      std::cerr << "\n frCnt too high! frCnt= " << frameCnt << " dF*cLmt= " << dFrames*cacheLimit;
      std::cerr << "\ncacheSz= " << cacheSz << " cacheLimit= " << cacheLimit; return false;
    }
  }

  return true;// keep going
}

void rec::initControl(std::vector<std::string>*& pLabelVec, std::vector< std::function<void(void)> >*& p_pFuncVec, size_t stepSz)
{
  static std::vector<std::string> LabelVec;
  static std::vector< std::function<void(void)> > pFuncVec;
  LabelVec.clear();
  LabelVec.reserve(8);
  pFuncVec.clear();
  pFuncVec.reserve(8);

  LabelVec.push_back("recorder");  pFuncVec.push_back(std::bind(rec::onOff));
  LabelVec.push_back("stop");      pFuncVec.push_back(std::bind(rec::stop));
  LabelVec.push_back("record");    pFuncVec.push_back(std::bind(rec::record));
  LabelVec.push_back("play");      pFuncVec.push_back(std::bind(rec::play));
  std::string rewStr("rew ");
  std::stringstream ss; ss << stepSz;
  rewStr += ss.str();
  LabelVec.push_back(rewStr);    pFuncVec.push_back(std::bind([stepSz](void) { rec::rewind(stepSz); }));
  LabelVec.push_back("goto 0");    pFuncVec.push_back(std::bind(rec::goTo_initial));
  LabelVec.push_back("jog rev");   pFuncVec.push_back(std::bind(rec::jog_rev));
  LabelVec.push_back("jog fwd");   pFuncVec.push_back(std::bind(rec::jog_fwd));

  pLabelVec = &LabelVec;
  p_pFuncVec = &pFuncVec;
}

void rec::jog_rev()
{
  if (frameCnt == 0) {
    std::cout << "still at initial state\n"; std::cerr << "\n too far"; return;
  }

  if (frameCnt%dFrames != 0)// backup to state just behind
    frameCnt = dFrames*(frameCnt / dFrames);
  //    else// frCnt is a multiple of dFrames already
  frameCnt -= dFrames;// backup to previous state

                      //   frameCnt = dFrames*(frameCnt/dFrames);// even up any fraction
  std::cout << "jog_rev: frameCnt= " << frameCnt;
  restoreState(frameCnt / dFrames);
  return;
}

void rec::jog_fwd()
{
  frameCnt = dFrames*(frameCnt / dFrames);// even up any fraction
  if (frameCnt == dFrames*(pHistoryVec.size() - 1)) {
    std::cout << "already at final state\n"; std::cerr << "\n at end already"; return;
  }
  frameCnt += dFrames;// forward to next state
  std::cout << "jog_fwd: frameCnt= " << frameCnt;
  restoreState(frameCnt / dFrames);
  return;
}// false if already at final state

bool rec::fwd(size_t n)
{
  if (frameCnt + n*dFrames > dFrames*pHistoryVec.size()) return false;
  frameCnt += n*dFrames;
  restoreState(frameCnt / dFrames);
  return true;
}

bool rec::rewind(size_t n)
{
  if (frameCnt < n*dFrames) return false;
  frameCnt -= n*dFrames;
  frameCnt = dFrames*(frameCnt / dFrames);// even up any fraction
  std::cout << "rewind: frameCnt= " << frameCnt;
  restoreState(frameCnt / dFrames);
  return true;
}

void rec::rewind_50()
{
  if (frameCnt < 50 * dFrames) {
    std::cerr << "\n too far";  return;
  }
  frameCnt -= 50 * dFrames;
  frameCnt = dFrames*(frameCnt / dFrames);// even up any fraction
  std::cout << "rewind: frameCnt= " << frameCnt;
  restoreState(frameCnt / dFrames);
  return;
}


bool rec::goTo(size_t n)
{
  if (n >= pHistoryVec.size()) return false;
  frameCnt = n*dFrames;
  restoreState(n);
  return true;
}

void rec::goTo_initial()
{
  frameCnt = 0;
  restoreState(0);
}

void rec::goTo_final()
{
  frameCnt = dFrames*pHistoryVec.size();
  for (const auto& st : pStateVec) st->setState();
}

void rec::onOff()
{
  if (pOn)
  {
    if (*pOn)// closing?
    {
      stop();
    }
    *pOn = !*pOn;
  }
}

void rec::record()
{
  if (pHistoryVec.size() == 0) {
    frameCnt = 0; saveState();
  }
  else frameCnt = dFrames*(pHistoryVec.size() - 1);// begin at current final_state

  std::cout << " rec begin curr value: frameCnt= " << frameCnt << " index_last: " << index_last;
  running = true;
}

/*
bool rec::play()// false if in final state
{
if( pHistoryVec.size() == 0 ) { std::cout << "play: empty vector\n"; return false; }
//   if( frameCnt == dFrames*mh_posVec.size() ) { std::cout << "play: at final state\n"; return false; }
if( frameCnt == dFrames*(pHistoryVec.size() - 1 ) ) { std::cout << "play: at final state\n"; return false; }
running = true;
return true;
}   */

void rec::play()// false if in final state
{
  if (pHistoryVec.size() == 0) {
    std::cout << "play: empty vector\n"; return;
  }
  //   if( frameCnt == dFrames*mh_posVec.size() ) { std::cout << "play: at final state\n"; return false; }
  if (frameCnt == dFrames*(pHistoryVec.size() - 1)) {
    std::cout << "play: at final state\n"; return;
  }
  running = true;
  return;
}

void rec::stop()
{
  //   residualCnt = frameCnt%dFrames;
  std::cout << "\n stop:";
  running = false;
}

bool rec::is_recording()
{
  return running && frameCnt >= dFrames*(pHistoryVec.size() - 1);
}
