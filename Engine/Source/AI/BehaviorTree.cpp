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

#include "AI\BehaviorTree.h"

BehaviorNode::BehaviorNode(std::function<bool(void)> Check, std::function<void(void)> Exec)
  : 
  m_ConditionCheck(Check),  
  m_Exec(Exec)
{
}

BehaviorNode::BehaviorNode(std::function<bool(void)> Check, std::function<void(void)> Exec, std::shared_ptr<BehaviorNode> LeftChild, std::shared_ptr<BehaviorNode> RightChild)
  : 
  m_LeftChild(LeftChild), 
  m_RightChild(RightChild), 
  m_ConditionCheck(Check),
  m_Exec(Exec)
{
}

BehaviorNode::BehaviorNode(std::function<void(void)> Exec)
  : 
  m_Exec(Exec)
{
}

std::shared_ptr<BehaviorNode> BehaviorNode::Create()
{
  return std::make_shared<BehaviorNode>();
}

BehaviorNode::~BehaviorNode()
{
  if (m_LeftChild)
    m_LeftChild.reset();
  if (m_RightChild)
    m_RightChild.reset();
}

void BehaviorNode::Execute()
{
  if (m_Exec)
    m_Exec();
}

void BehaviorNode::TickUpdate(const double & TickDelta)
{
  if (m_Update)
    m_Update(TickDelta);
}

void BehaviorNode::SetLeftChild(std::shared_ptr<BehaviorNode> Left)
{
  m_LeftChild = Left;
}

void BehaviorNode::SetRightChild(std::shared_ptr<BehaviorNode> Right)
{
  m_RightChild = Right;
}

void BehaviorNode::SetExec(std::function<void(void)> Func)
{
  m_Exec = Func;
}

void BehaviorNode::SetUpdate(std::function<void(const double&d)> UpdateFtn)
{
  m_Update = UpdateFtn;
}

BehaviorTree::~BehaviorTree()
{
  if (m_Root)
    m_Root.reset();
}

void BehaviorTree::Execute()
{
  m_IsExecuting = true;
  m_CurrentNode = m_Root;
}

void BehaviorTree::TickUpdate(const double & TickDelta)
{
  if (m_Root)
    ExecuteTree();
}

void BehaviorTree::Reset()
{
  m_IsExecuting = false;
  m_CurrentNode = m_Root;
}

void BehaviorTree::SetRoot(std::shared_ptr<BehaviorNode> Root)
{
  m_Root = Root;
}

void BehaviorTree::Cleanup()
{
  if (m_Root)
    m_Root.reset();
}

void BehaviorTree::ExecuteTree()
{
  ExecuteNode(m_Root);
}

void BehaviorTree::ExecuteNode(std::shared_ptr<BehaviorNode> Node)
{
  Node->Execute();

  if (Node->m_ConditionCheck && Node->m_ConditionCheck() && Node->m_RightChild) {
    ExecuteNode(Node->m_RightChild);
  }
  else if (Node->m_LeftChild) {
    ExecuteNode(Node->m_LeftChild);
  }
}
