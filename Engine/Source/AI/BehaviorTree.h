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

class BehaviorTree;

class BehaviorNode
{
public:
  BehaviorNode() = default;

  BehaviorNode(std::function<bool(void)> Check, 
                std::function<void(void)> Exec);
  BehaviorNode(std::function<bool(void)> Check,
                std::function<void(void)> Exec,
                std::shared_ptr<BehaviorNode> LeftChild,
                std::shared_ptr<BehaviorNode> RightChild);
  BehaviorNode(std::function<void(void)> Exec);
  static std::shared_ptr<BehaviorNode> Create();
  BehaviorNode(const BehaviorNode &) = delete;
  BehaviorNode(const BehaviorNode &&) = delete;
  BehaviorNode& operator=(const BehaviorNode&) = delete;
  ~BehaviorNode();

  void Execute();
  void TickUpdate(const double &TickDelta);

  void SetLeftChild(std::shared_ptr<BehaviorNode> Left);
  void SetRightChild(std::shared_ptr<BehaviorNode> Right);
  void SetExec(std::function<void(void)> Func);
  void SetUpdate(std::function<void(const double &d)> UpdateFtn);

  std::function<bool(void)> m_ConditionCheck = []() -> bool { return false; };
  std::function<void(const double &)> m_Update = [](auto t) -> void { };

  std::function<void(void)> m_Exec = []() {};

  std::shared_ptr<BehaviorNode> m_LeftChild;
  std::shared_ptr<BehaviorNode> m_RightChild;
};

class BehaviorTree
{
public:
  BehaviorTree() = default;
  BehaviorTree(const BehaviorTree&) = delete;
  BehaviorTree(const BehaviorTree &&) = delete;
  BehaviorTree& operator=(const BehaviorTree &) = delete;
  ~BehaviorTree();

  void Execute();
  void TickUpdate(const double &TickDelta);
  void Reset(); //make current node the root node

  void SetRoot(std::shared_ptr<BehaviorNode> Root);
  void Cleanup();
protected:
  void ExecuteTree();
  void ExecuteNode(std::shared_ptr<BehaviorNode> Node);
  bool m_PrintTree = true;
  bool m_IsExecuting = false;

  std::shared_ptr<BehaviorNode> m_Root;
  std::weak_ptr<BehaviorNode>   m_CurrentNode;
};

