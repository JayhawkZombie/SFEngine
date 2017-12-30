////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "TimerManager.h"


void TimerManager::AddTimer(double duration, bool repeat, double delay, double scale, const std::function<void()> &callback)
{
  Timer timer;
  timer.IsPeriodic = repeat;
  timer.ExpirationTime = m_TotalElapsedTime + (duration / scale);
  timer.Duration = duration;
  timer.TimeScale = scale;

  m_DeferredTimerAdds.push_back(timer);
}

void TimerManager::Tick(double RealTime)
{
  m_TotalElapsedTime += RealTime;

  while (!m_Timers.empty())
  {
    Timer timer = m_Timers.top();

    auto iter = m_Timers.begin();
    auto handle = boost::heap::fibonacci_heap<Timer>::s_handle_from_iterator(iter);

    if (m_TotalElapsedTime >= timer.ExpirationTime)
    {
      /* Timer is done - execute it */
      iter->Callback();
      
      /* If it should loop, set its future expiration and 
       * add it back into the queue
       * */
      if (iter->IsPeriodic)
      {
        Timer newtimer = *iter;
        newtimer.ExpirationTime = m_TotalElapsedTime + (newtimer.Duration / newtimer.TimeScale);

        m_Timers.update(handle, newtimer);
      }
      else
      {
        m_Timers.erase(handle);
      }
    }
    else
    {
      /* K, well nothing to do here, we can just go now */
      break;
    }
  }
  
  /*
   *  If there were any timers added deferred, push them into the queue
   **/
  for (auto & timer : m_DeferredTimerAdds)
  {
    timer.ExpirationTime = m_TotalElapsedTime + (timer.Duration / timer.TimeScale);

    m_Timers.push(timer);
  }

}

bool TimerManager::IsHandleValid(const TimerHandle &Handle)
{
  return (Handle.TimerID > 1);
}

void TimerManager::ClearAllTimers()
{
  m_Timers.clear();
  m_DeferredTimerAdds.clear();
}
