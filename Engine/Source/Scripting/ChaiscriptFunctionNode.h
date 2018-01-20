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
#include <basen/basen.hpp>
#include <optional>
#include "chaiscript/chaiscript.hpp"
#include <string>
#include <any>

class ChaiscriptFunctionNode
{
public:
  ChaiscriptFunctionNode() = default;
  virtual ~ChaiscriptFunctionNode() = default;

  virtual void Add(chaiscript::ChaiScript &engine) = 0;
  virtual bool Execute() = 0;
  virtual std::any Get(const std::string &ValName) = 0;
  virtual bool GetArgs(ChaiscriptFunctionNode &Node) = 0;

protected:

  bool IsPrepared = false;

};

class ChaiscriptValueNode
{
public:
  ChaiscriptValueNode() = default;
  virtual ~ChaiscriptValueNode() = default;

  virtual std::any Get() = 0;
  virtual bool Set(const std::any &AnyVal) = 0;
};

class ChaiscriptFloatValueNode : public ChaiscriptValueNode
{
public:
  ChaiscriptFloatValueNode() = default;
  explicit ChaiscriptFloatValueNode(float f)
    : FloatVal(f)
  {
  }

  float FloatVal;

  std::any Get() override final
  {
    return FloatVal;
  }

  bool Set(const std::any &AnyVal) override final
  {
    if (AnyVal.type().hash_code() != typeid(float).hash_code())
    {
      return false;
    }

    FloatVal = std::any_cast< float >(AnyVal);
    return true;
  }

};

class ChaiscriptVector2fValueNode : public ChaiscriptValueNode
{
public:
  ChaiscriptVector2fValueNode() = default;
  explicit ChaiscriptVector2fValueNode(const sf::Vector2f &Val)
    : Vector2fVal(Val)
  {
  }

  sf::Vector2f Vector2fVal;

  std::any Get() override final
  {
    return Vector2fVal;
  }

  bool Set(const std::any &AnyVal) override final
  {
    if (AnyVal.type().hash_code() != typeid(sf::Vector2f).hash_code())
    {
      return false;
    }

    Vector2fVal = std::any_cast< sf::Vector2f >(AnyVal);
    return true;
  }

};

class ChaiscriptFunctionNode_ScaleVec2f : public ChaiscriptFunctionNode
{
private:

  bool HasBeenAdded = false;

public:

  ChaiscriptFunctionNode_ScaleVec2f() = default;
  ~ChaiscriptFunctionNode_ScaleVec2f() override = default;

  using func_type = std::function<sf::Vector2f(const sf::Vector2f &, float)>;

  ChaiscriptFloatValueNode ScalarValue;
  ChaiscriptVector2fValueNode VectorValue;
  ChaiscriptVector2fValueNode ReturnValue;

  sf::Vector2f Param_Vector;
  float Param_Scalar;
  sf::Vector2f Return_Vector;

  void Add(chaiscript::ChaiScript &engine) override final
  {
    if (HasBeenAdded) return;
    HasBeenAdded = true;

    Func = engine.eval<func_type>("Scale");
  }

  template<typename T>
  void Set(const std::string &ArgName, const T &Val)
  {
    if constexpr (std::is_same_v<T, ChaiscriptVector2fValueNode>)
    {
      if (ArgName == "Vector")
        VectorValue = Val;
    }
    else if constexpr (std::is_same_v<T, sf::Vector2f>)
    {
      if (ArgName == "Vector")
        Param_Vector = Val;
    }
    else if constexpr (std::is_same_v<T, ChaiscriptFloatValueNode>)
    {
      if (ArgName == "Scalar")
        ScalarValue = Val;
    }
    else if constexpr (std::is_same_v<T, float>)
    {
      if (ArgName == "Scalar")
        Param_Scalar = Val;
    }
  }

  std::any Get(const std::string &VarName) override final
  {
    if (VarName == "Return")
    {
      return ReturnValue.Get();
    }
    else if (VarName == "Vector")
    {
      return VectorValue.Get();
    }
    else if (VarName == "Scalar")
    {
      return ScalarValue.Get();
    }

    return std::nullopt;
  }

  bool GetArgs(ChaiscriptFunctionNode &Node) override final
  {
    std::any MaybeVector = Node.Get("Vector");
    std::any MaybeScalar = Node.Get("Scalar");

    if (MaybeVector.type().hash_code() != typeid(sf::Vector2f).hash_code())
    {
      return false;
    }

    if (MaybeScalar.type().hash_code() != typeid(float).hash_code())
    {
      return false;
    }

    VectorValue.Set(MaybeVector);
    ScalarValue.Set(MaybeScalar);
    IsPrepared = true;

    return true;
  }

  bool Execute() override final
  {
    if (!VectorValue.Get().has_value() || !ScalarValue.Get().has_value())
      return false;

    try
    {
      ReturnValue.Set(Func(std::any_cast< sf::Vector2f >(VectorValue.Get()),
        std::any_cast< float >(ScalarValue.Get())
      ));
      return true;
    }
    catch (...)
    {
      return false;
    }
  }

  func_type Func;
};
