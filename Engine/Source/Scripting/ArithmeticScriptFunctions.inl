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

#include <functional>

template<class LHS, class RHS>
bool ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Plus>::Add(chaiscript::ChaiScript &Engine)
{
  static_assert(type::has_operator_binary_plus<LHS, RHS>::value);

  std::function<LHS(const LHS &, const RHS &)> f = [](const LHS &lhs, const RHS &rhs) -> LHS { return (lhs + rhs); };
  ChaiscriptFunctionAdder adder;

  return adder.TryAdd(Engine, f, "+");
}

template<class LHS, class RHS>
bool ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Minus>::Add(chaiscript::ChaiScript &Engine)
{
  static_assert(type::has_operator_binary_minus<LHS, RHS>::value, "no minus operator");

  auto f = [](const LHS &lhs, const RHS &rhs) -> LHS { return (lhs - rhs); };

  ChaiscriptFunctionAdder adder;

  return adder.TryAdd(Engine, f, "-");
}

template<class LHS, class RHS>
bool ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Mult>::Add(chaiscript::ChaiScript &Engine)
{
  static_assert(type::has_operator_mult<LHS, RHS>::value, "no multiplication operator");

  auto f = [](const LHS &lhs, const RHS &rhs) -> LHS { return (lhs * rhs); };

  ChaiscriptFunctionAdder adder;

  return adder.TryAdd(Engine, f, "*");
}

template<class LHS, class RHS>
bool ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Div>::Add(chaiscript::ChaiScript &Engine)
{
  static_assert(type::has_operator_mult<LHS, RHS>::value, "no division operator");

  auto f = [](const LHS &lhs, const RHS &rhs) -> LHS { return (lhs / rhs); };

  ChaiscriptFunctionAdder adder;

  return adder.TryAdd(Engine, f, "/");
}

template<class LHS, class RHS>
bool ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::Assign>::Add(chaiscript::ChaiScript &Engine)
{
  static_assert(
    type::has_operator_assign<LHS>::value
    || (std::is_same_v<LHS, RHS> && std::is_copy_constructible_v<LHS>)
    , "no suitable copy assignment operator or copy constructor"
    );

  std::function<LHS& (LHS&, const RHS&)> f;

  /* If copy assignment operator exists */
  if constexpr (type::has_operator_assign<LHS>::value)
  {
    f = [](LHS &lhs, const RHS &rhs) -> LHS& { lhs = rhs; return lhs; };
  }
  else
  {
    /* If it can be copy constructed, use that instead */
    f = [](LHS &lhs, const RHS &rhs) -> LHS& { lhs = LHS(rhs); return lhs; };
  }

  ChaiscriptFunctionAdder adder;

  return adder.TryAdd(Engine, f, "=");
}

template<class LHS, class RHS>
bool ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::CompoundAssignPlus>::Add(chaiscript::ChaiScript &Engine)
{
  static_assert(type::has_compound_assignment_plus<LHS, RHS>::value
    , "no compound assignment plus operator");

  auto f = [](LHS &lhs, const RHS &rhs) -> LHS & { lhs += rhs; return rhs; };

  ChaiscriptFunctionAdder adder;

  return adder.TryAdd(Engine, f, "+=");
}

template<class LHS, class RHS>
bool ChaiscriptArithmeticOperator<LHS, RHS, EScriptArithmeticOperator::CompoundAssignMinus>::Add(chaiscript::ChaiScript &Engine)
{
  static_assert(type::has_compound_assignment_minus<LHS, RHS>::value,
    "no compoint assignment minus operator");

  auto f = [](LHS &lhs, const RHS &rhs) -> LHS & { lhs -= rhs; return rhs; };

  ChaiscriptFunctionAdder adder;

  return adder.TryAdd(Engine, f, "-=");
}
