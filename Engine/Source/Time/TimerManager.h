#pragma once

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

#include "Timer.h"

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/heap/detail/mutable_heap.hpp>

class TimerManager
{
public:
  TimerManager() = default;

  /*
   *  Do NOT add a timer whose duration is less than the engine's tick
   *  This will freeze if you do so
   **/
  void AddTimer(double duration, bool repeat, double delay, double scale, const std::function<void()> &callback);

  template<typename ClassType>
  void AddTimer(double duration, bool repeat, double delay, double scale, ClassType *objectPtr, void (ClassType::*MemPtr)())
  {
    Timer timer;
    timer.IsPeriodic = repeat;
    timer.ExpirationTime = m_TotalElapsedTime + ( duration / scale ) * 1000.0;
    timer.Duration = duration;
    timer.TimeScale = scale;
    timer.Callback = std::bind(MemPtr, objectPtr);

    m_DeferredTimerAdds.push_back(timer);
  }

  void Restart();
  void Tick(double RealTime);
  bool IsHandleValid(const TimerHandle &Handle);
  void ClearAllTimers();

private:

  double m_TotalElapsedTime = 0.0;

  std::priority_queue<Timer> m_Timers;

  std::vector<Timer> m_DeferredTimerAdds;
  std::vector<Timer> m_StoppedTimers;
};
