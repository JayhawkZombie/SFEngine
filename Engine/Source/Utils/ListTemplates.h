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

#include <memory>

namespace Engine
{
  namespace Util
  {

    template<typename T>
    struct Node {
      Node() = default;
      virtual ~Node() = default;
      virtual void Destroy() {
        Value.reset();
        if (Next)
          Next->Destroy();
        Next.reset();
      }
      bool IsHead = false;
      bool IsTail = false;
      bool IsGoingForward = true;
      std::shared_ptr<Node<T>> Next = nullptr;
      std::weak_ptr<Node<T>> Previous;
      std::shared_ptr<T> Value;
      std::uint32_t Index = 0;
    };

    template<typename T, bool Loop, bool PingPong>
    class DoublyLinkedList
    {
    public:
      DoublyLinkedList() {
        ISLooping = Loop;
        ISPingPong = PingPong;
      }
      ~DoublyLinkedList() {
        if (Head)
          Head->Destroy();
      }

      void InsertBack(std::shared_ptr<T> value) {
        if (!Tail) {
          Tail = std::make_shared<Node<T>>();
          Tail->Value = value;
          Tail->Index = 0;
          Head = Tail;
          Head->IsHead = true;
          Tail->IsTail = true;
        }
        else {
          std::shared_ptr<Node<T>> Temp = std::make_shared<Node<T>>();
          Temp->Value = value;
          Temp->Previous = Tail;
          Tail->Next = Temp;
          Tail->IsTail = false;
          Tail = Temp;
          Tail->IsTail = true;
          Tail->Index = NodeCount;
        }

        NodeCount++;
      }

      void InsertFront(std::shared_ptr<T> value) {
        if (!Head) {
          Head = std::make_shared<Node<T>>();
          Head->Value = value;
          Head->Index = 0;
          Tail = Head;
          Head->IsHead = true;
          Tail->IsTail = true;
        }
        else {
          std::shared_ptr<Node<T>> Temp = std::make_shared<Node<T>>();
          Temp->Value = value;
          Temp->Next = Head;
          Head->IsHead = false;
          Head->Previous = Temp;
          Head = Temp;
          Head->IsHead = true;
          Head->Index = NodeCount;
        }

        NodeCount++;
      }

      std::shared_ptr<Node<T>> Advance(std::shared_ptr<Node<T>> node) const {
        std::shared_ptr<Node<T>> ret = nullptr;
        if (node->IsGoingForward)
          ret = AdvanceForward(node);
        else
          ret = AdvanceBackward(node);

        return ret;
      }

      std::shared_ptr<Node<T>> AdvanceBackward(std::shared_ptr<Node<T>> node) const {
        std::shared_ptr<Node<T>> ret = nullptr;

        if (node->IsHead) {
          if (ISLooping) {
            node->IsGoingForward = true;
            Tail->IsGoingForward = false;
            return Tail;
          }
          else {
            ret = node->Next;
            node->IsGoingForward = true;
            ret->IsGoingForward = true;
          }
        }
        else {
          node->IsGoingForward = true;
          ret = node->Previous.lock();
          ret->IsGoingForward = false;
        }

        return ret;
      }

      std::shared_ptr<Node<T>> AdvanceForward(std::shared_ptr<Node<T>> node) const {
        std::shared_ptr<Node<T>> ret = nullptr;

        if (node->IsTail) {
          if (ISLooping) {
            node->IsGoingForward = false;
            Head->IsGoingForward = true;
            return Head;
          }
          else {
            ret = node->Previous.lock();
            node->IsGoingForward = true;
            ret->IsGoingForward = false;
          }
        }
        else {
          node->IsGoingForward = true;
          ret = node->Next;
          ret->IsGoingForward = true;
        }

        return ret;
      }

      std::uint32_t GetSize() const {
        return NodeCount;
      }

      std::shared_ptr<Node<T>> GetHead() const {
        return Head;
      }
      std::shared_ptr<Node<T>> GetTail() const {
        return Tail;
      }

      void MakeLooped(bool b) {
        ISLooping = b;
      }

      void MakePingPong(bool b) {
        ISPingPong = b;
      }

    protected:
      std::uint32_t NodeCount = 0;
      std::shared_ptr<Node<T>> Head = nullptr;
      std::shared_ptr<Node<T>> Tail = nullptr;

      bool ISLooping = true;
      bool ISPingPong = false;
    };

  }
}
