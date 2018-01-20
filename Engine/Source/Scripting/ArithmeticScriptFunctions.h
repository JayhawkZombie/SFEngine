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

#include "Minimal.h"
#include "Utils/TypeTraits.hpp"

#define STRINGIFY(__X__) #__X__

#include <algorithm>
#include <functional>

struct ChaiscriptFunctionAdder
{
  template<typename Func>
  bool TryAdd(chaiscript::ChaiScript &Engine, const Func &f, const std::string &FuncName)
  {
    try
    {
      Engine.add(chaiscript::fun(f), FuncName);
      return true;
    }
    catch (const std::exception &exc)
    {
      std::cerr << "Failed to add function: \"" << FuncName << "\" to chaiscript engine. Error: \""
        << exc.what() << "\"\n";
      return false;
    }
  }
};

enum class EScriptArithmeticOperator
{
  Plus,
  Minus,
  Mult,
  Div,
  Assign,
  CompoundAssignPlus,
  CompoundAssignMinus,
  CompoundAssignMult,
  CompoundAssignDiv
};

enum class EScriptComparisonOperator
{
  LessThan,
  GreaterThan,
  Equal,
  NotEqual,
  LessThanOrEqual,
  GreaterThanOrEqual
};

template<class LHS, class RHS, EScriptArithmeticOperator op>
struct ChaiscriptArithmeticOperator
{
  bool Add(chaiscript::ChaiScript &engine);
};

/* Class specializations for operators */

template<class LHS, class RHS>
struct ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Plus>
{
public:
  bool Add(chaiscript::ChaiScript &Engine);
};

template<class LHS, class RHS>
struct ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Minus>
{
public:
  bool Add(chaiscript::ChaiScript &Engine);
};

template<class LHS, class RHS>
struct ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Mult>
{
public:
  bool Add(chaiscript::ChaiScript &Engine);
};

template<class LHS, class RHS>
struct ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Div>
{
public:
  bool Add(chaiscript::ChaiScript &Engine);
};

template<class LHS, class RHS>
struct ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Assign>
{
public:
  bool Add(chaiscript::ChaiScript &Engine);
};

template<class LHS, class RHS>
struct ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::CompoundAssignPlus>
{
  bool Add(chaiscript::ChaiScript &Engine);
};

template<class LHS, class RHS>
struct ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::CompoundAssignMinus>
{
  bool Add(chaiscript::ChaiScript &Engine);
};

template<class T>
struct ChaiscriptClampFunction
{
private:
  std::function<T(const T&, const T&, const T&)> f;

public:

  ChaiscriptClampFunction(const std::function<T(const T&, const T&, const T&)> &ClampFunc) : f(ClampFunc) {}

  bool Add(chaiscript::ChaiScript &engine)
  {
    try
    {
      engine.add(chaiscript::fun(f), "clamp");
      return true;
    }
    catch (const std::exception &exc)
    {
      std::cerr << "Failed to add clamp function to Chaiscript engine for type \""
        << STRINGIFY(T) << "\" because: " << exc.what() << "\n";
      return false;
    }
  }

};

#include "ArithmeticScriptFunctions.inl"
