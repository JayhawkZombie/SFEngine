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

#include "Utils\UntimedSequence.h"

namespace Engine
{



  UntimedSequenceNode::UntimedSequenceNode(std::function<void(void)> m_StartCB, std::function<bool(void)> m_CheckCB, std::function<void(void)> m_EndCB)
    : m_CheckCallBack(m_CheckCB), m_StartedCallBack(m_StartCB), m_EndedCallBack(m_EndCB), m_IsDone(false)
  {
  }

  UntimedSequenceNode::UntimedSequenceNode(const UntimedSequenceNode & node)
    : m_CheckCallBack(node.m_CheckCallBack), m_EndedCallBack(node.m_EndedCallBack),
      m_StartedCallBack(node.m_StartedCallBack), m_IsDone(false)
  {
  }

  UntimedSequenceNode::~UntimedSequenceNode()
  {
  }

  void UntimedSequenceNode::Start()
  {
    m_IsDone = false;
    if (m_StartedCallBack)
      m_StartedCallBack();
  }

  void UntimedSequenceNode::Stop()
  {
    m_IsDone = true;
    if (m_EndedCallBack)
      m_EndedCallBack();
  }

  void UntimedSequenceNode::Update()
  {
    m_IsDone = (m_CheckCallBack && m_CheckCallBack());
  }

  bool UntimedSequenceNode::IsDone() const
  {
    return m_IsDone;
  }

  UntimedSequence::UntimedSequence()
  {
  }

  UntimedSequence::~UntimedSequence()
  {
  }

  void UntimedSequence::Start()
  {
    m_IsSequencing = true;
  }

  void UntimedSequence::Stop()
  {
    m_IsSequencing = false;
  }

  void UntimedSequence::Update()
  {
    //If we have waiting nodes, update the front one
    //Then if the first one is now done, then we take care of it this frame instead of next frame
    //Last check to see if all of our sequence nodes are gone. If so, tirgger the
    //EndedCallBack to be invoked, otherwise begin the next sequence node
    if (!m_Nodes.empty()) {
      m_Nodes.front().Update();

      if (m_Nodes.front().IsDone()) {
        m_Nodes.front().Stop();
        m_Nodes.pop();

        if (m_Nodes.empty())
          m_EndCallBack();
        else {
          m_Nodes.front().Start();
        }
      }
    }

  }

  void UntimedSequence::AddSequence(std::function<void(void)> SeqStart, std::function<void(void)> SeqDone, UntimedSequenceNode Node)
  {
    m_EndCallBack = SeqDone;
    m_StartCallBack = SeqStart;

    m_Nodes.push(Node);
    if (m_StartCallBack)
        m_StartCallBack();
  }

  void UntimedSequence::AddSequences(std::function<void(void)> SeqStart, std::function<void(void)> SeqDone, std::initializer_list<UntimedSequenceNode> Nodes)
  {
    m_EndCallBack = SeqDone;
    m_StartCallBack = SeqStart;

    for (auto & node : Nodes)
      m_Nodes.push(node);

    if (m_StartCallBack)
      m_StartCallBack();
  }

}
