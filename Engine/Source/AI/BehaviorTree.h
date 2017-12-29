#ifndef SFENGINE_AI_BEHAVIOR_TREE_H
#define SFENGINE_AI_BEHAVIOR_TREE_H

#include "BasicIncludes.h"

namespace Engine
{
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

}

#endif
