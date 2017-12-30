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

#include "RealTimeClock.h"


RealTimeClock::RealTimeClock()
  : m_StartTime(std::chrono::steady_clock::now())
{

}

void RealTimeClock::Pause()
{
  m_IsPaused = true;
  m_PauseTime = std::chrono::steady_clock::now();
}

void RealTimeClock::Resume()
{
  m_IsPaused = false;
  m_StartTime += (std::chrono::steady_clock::now() - m_PauseTime);
}

void RealTimeClock::Restart()
{
  m_IsPaused = false;
  m_StartTime = std::chrono::steady_clock::now();
}

TimePoint RealTimeClock::GetTime()
{
  return std::chrono::steady_clock::now();
}

double RealTimeClock::GetTimeSinceStart()
{
  std::chrono::duration<double, std::chrono::seconds::period> elapsed =
    std::chrono::duration_cast< std::chrono::duration<double, std::chrono::seconds::period > >
    (std::chrono::steady_clock::now() - m_StartTime);

  return elapsed.count();
}

double RealTimeClock::GetTimeSince(const TimePoint &tp)
{
  std::chrono::duration<double, std::chrono::seconds::period> elapsed =
    std::chrono::duration_cast< std::chrono::duration<double, std::chrono::seconds::period > >
    (std::chrono::steady_clock::now() - tp);

  return elapsed.count();
}
