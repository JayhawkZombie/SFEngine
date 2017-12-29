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

#include "Time\TimedSequence.h"

SequenceNode::SequenceNode(const SequenceNode & Copy)
  : m_Duration(Copy.m_Duration), m_StartCallBack(Copy.m_StartCallBack),
  m_IsDone(Copy.m_IsDone), m_EndCallBack(Copy.m_EndCallBack)
{
}

SequenceNode::SequenceNode(std::initializer_list<SequenceNode> Seq)
{
    
}

SequenceNode::SequenceNode(double delta, std::function<void(void)> start, std::function<void(void)> update, std::function<void(void)> end)
  : m_Duration(delta), m_StartCallBack(start), m_UpdateCallBack(update), m_EndCallBack(end)
{
}

void SequenceNode::TickUpdate(const double & delta)
{
  m_CurrentDuration += delta;

  if (m_CurrentDuration >= m_Duration) {
    m_IsDone = true;;
  }
}

bool SequenceNode::IsDone() const
{
  return m_IsDone;
}

void SequenceNode::Start()
{
  if (m_StartCallBack)
    m_StartCallBack();
}

void SequenceNode::End()
{
  if (m_EndCallBack)
    m_EndCallBack();
}

void TimedSequence::Clear()
{
  while (!m_Nodes.empty())
    m_Nodes.pop();

  m_IsTiming = false;

  if (m_EndCallBack)
    m_EndCallBack();
}

void TimedSequence::AddSequence(double Duration, std::function<void(void)> StartCB, std::function<void(void)> Update, std::function<void(void)> EndCB)
{
  m_Nodes.push({ Duration, StartCB, Update, EndCB });
}

void TimedSequence::AddSequences(std::function<void(void)> Start,
                                  std::function<void(void)> Update,
                                  std::function<void(void)> End,
                                  std::initializer_list<SequenceNode> Nodes)
{
  m_StartCallBack = Start;
  m_EndCallBack = End;

  for (auto & node : Nodes)
    m_Nodes.push(node);
}

void TimedSequence::Start()
{
  m_IsTiming = true;

  if (!m_Nodes.empty())
    m_Nodes.front().Start();

  if (m_StartCallBack)
    m_StartCallBack;
}

void TimedSequence::Stop()
{
  m_IsTiming = false;
}

void TimedSequence::TickUpdate(const double & delta)
{
  if (!m_IsTiming)
    return;

  if (!m_Nodes.empty()) {
    if (!m_Nodes.front().IsDone())
      m_Nodes.front().TickUpdate(delta);
    else {
      m_Nodes.front().End();
      m_Nodes.pop();

      if (!m_Nodes.empty())
        m_Nodes.front().Start();
      else
        if (m_EndCallBack)
          m_EndCallBack();
    }
  }
}

void TimedSequence::SetUpdateCallback(std::function<void(const double&)> CB)
{
  m_UpdateCallBack = CB;
}
