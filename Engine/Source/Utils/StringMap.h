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

#include "Utils\String.h"

template<typename FIRST, typename SECOND>
struct SimplePair {
  SimplePair() = default;
  SimplePair(const FIRST &f, const SECOND &s) : first(f), second(s) {

  }
  FIRST first;
  SECOND second;
};

template<typename T>
struct MinimalNode {
  MinimalNode() : Next(nullptr) {}
  MinimalNode(const T& v) : value(v), Next(nullptr), Previous(nullptr) {}
  MinimalNode(const T& v, MinimalNode<T> *p) : value(v), Previous(p), Next(nullptr) {}

  T value;
  MinimalNode<T> *Next;
  MinimalNode<T> *Previous;
};

template<typename Item>
class LinkedList
{
public:
  LinkedList() : Front(nullptr) {}
  ~LinkedList() {
    MinimalNode<Item> *Temp = Front;

    while (Front != nullptr) {
      Temp = Front;
      Front = Front->Next;
      delete Temp;
    }
  }

  void AddItem(const Item &item) {
    if (Front == nullptr) {
      Front = new MinimalNode<Item>(item);
      Back = Front;
    }
    else {
      Back->Next = new MinimalNode<Item>(item);
      Back->Previous = Back;
      Back = Back->Next;
    }
  }

  MinimalNode<Item> *Front;
  MinimalNode<Item> *Back;
};

template<typename TO>
class STRINGMAP
{
public:
  STRINGMAP() {

  }
  ~STRINGMAP() {

  }

  void Emplace(const STRING &str, TO &value) {
    SimplePair<STRING, TO> pair(str, value);
    Map.AddItem(pair);
  }

  TO& operator[](const STRING &str) {
    MinimalNode<SimplePair<STRING, TO>> *Front = Map.Front;
    while (Front != nullptr) {
      if (Front->value.first == str) {
        return Front->value.second;
      }
      Front = Front->Next;
    }

    Emplace(str, TO());
    return (Map.Back->value.second);
  }

private:
  LinkedList<SimplePair<STRING, TO>> Map;

};
