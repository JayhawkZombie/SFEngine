#include "AI\BehaviorTree.h"

namespace Engine
{



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

}
