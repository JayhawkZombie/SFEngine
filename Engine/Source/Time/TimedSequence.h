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

#include "BasicIncludes.h"

#include <queue>

namespace Engine
{

  class TimedSequence;

  class SequenceNode
  {
  public:
    SequenceNode() = default;
    SequenceNode(const SequenceNode &Copy);
    SequenceNode(std::initializer_list<SequenceNode> Seq);
    SequenceNode(double delta, 
                 std::function<void(void)> start,
                 std::function<void(void)> update,
                 std::function<void(void)> end);

    ~SequenceNode() = default;

    void TickUpdate(const double &delta);
    bool IsDone() const;

    void Start();
    void End();

  protected:

    double m_Duration;
    double m_CurrentDuration = 0.0;
    bool   m_IsDone = false;
    
    std::function<void(void)> m_StartCallBack  = []() {};
    std::function<void(void)> m_EndCallBack    = []() {};
    std::function<void(void)> m_UpdateCallBack = []() {};
  };


  class TimedSequence
  {
  public:
    TimedSequence() = default;
    ~TimedSequence() = default;

    void Clear();

    void AddSequence(
      double Duration,
      std::function<void(void)> StartCB,
      std::function<void(void)> Update,
      std::function<void(void)> EndCB
    );

    void AddSequences(
      std::function<void(void)> Start,
      std::function<void(void)> Update,
      std::function<void(void)> End,
      std::initializer_list<SequenceNode> Nodes
    );

    void Start();
    void Stop();
    void TickUpdate(const double &delta);
    void SetUpdateCallback(std::function<void(const double &)> CB);
  protected:

    bool m_IsTiming = false;
    std::queue<SequenceNode> m_Nodes;
    std::function<void(void)> m_StartCallBack = []() {};
    std::function<void(void)> m_EndCallBack   = []() {};
    std::function<void(const double &)> m_UpdateCallBack = [](const double &) {};
  };

}
