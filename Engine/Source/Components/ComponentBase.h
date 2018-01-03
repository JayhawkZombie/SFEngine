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

#include "Globals/GlobalHooks.h"

struct ComponentHandle
{
  std::size_t ComponentIndex;
  std::function<void()> ComponentDestroyedFunction
    = [] () {};
};

  class ComponentBase
  {
  public:
    ComponentBase();
    virtual ~ComponentBase();

    std::string ComponentName = "ComponentBase";
    std::uint32_t ComponentID;
  };

#define ENTITY_COMPONENT_BEGIN(NAME)                             \
class NAME##Component                                            \
: public Engine::ComponentBase                                   \
{                                                                



#define ENTITY_COMPONENT_END(NAME) \
} NAME;                           


#define ENTITY_PART(TYPE, NAME)                                   \
  public: TYPE var_##NAME;                                        \
          TYPE Get##NAME##() const { return var_##NAME; }         \
          void Set##NAME##(const TYPE &v) { var_##NAME = v; }     

#define ENTITY_PART_VECTOR(TYPE, NAME)                                          \
  public: std::vector<TYPE> var_##NAME##Vector;                                 \
          auto Get##NAME##s() { return var_##NAME##Vector; }                    \
          void Add##NAME##(const TYPE &t) { var_##NAME##Vector.push_back(t); }  

#define ENTITY_VECTOR_GETTER(TYPE, NAME)         \
  public: std::vector<TYPE> Get##NAME##s() { return NAME##.Get##NAME##s(); }    
