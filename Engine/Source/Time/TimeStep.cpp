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

#include "TimeStep.h"


void TimeStep::Update()
{
  TimePoint thisTick = m_Clock.GetTime();

  double delta = std::chrono::duration_cast< std::chrono::duration<double, std::chrono::seconds::period > >
    (thisTick - m_LastTickTime).count();

  if (delta > m_StepDuration)
  {
    m_Accumulation += m_StepDuration;
  }
  else
  {
    m_Accumulation += delta;
  }

  m_LastTickTime = thisTick;
}

void TimeStep::Start()
{
  m_Clock.Restart();
  m_LastTickTime = m_Clock.GetTime();
}

void TimeStep::Pause()
{
  m_Clock.Pause();
}

void TimeStep::Resume()
{
  m_Clock.Resume();
}

void TimeStep::Clear()
{
  m_Accumulation = 0.0;
}

void TimeStep::SetStep(double step)
{
  m_StepDuration = step;
}

void TimeStep::SetMaxAccumulation(double maxAccum)
{
  m_MaxAccumulation = maxAccum;
}

double TimeStep::GetStep() const
{
  return m_StepDuration;
}

double TimeStep::GetAlpha() const
{
  if (m_Accumulation >= m_StepDuration)
    return 1.0;

  return (m_Accumulation / m_StepDuration);
}

bool TimeStep::ShouldStep()
{
  if (m_Accumulation >= m_StepDuration)
  {
    m_Accumulation -= m_StepDuration;
    return true;
  }

  return false;
}
