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

/*
 *  Serializable functions that can be chained together to 
 *  add functionality
 **/

#include "Minimal.h"
#include "CoreForward.h"
#include "Globals/GlobalHooks.h"

#include <typeinfo>
#include <variant>

enum EScriptParameterType
{
  Int,
  Uint,
  Float, 
  Double,
  Vec2f,
  Vec2i,
  Vec2u,
  String,
  GameObjectPtr
};

enum EScriptReturnType
{
  Int,
  Uint,
  Float,
  Double,
  Vec2f,
  Vec2i,
  Vec2u,
  String,
  GameObjectPtr
};

struct FTNScriptFunctionParameterInfo
{
  FTNScriptFunctionParameterInfo() = default;

  FTNScriptFunctionParameterInfo(const std::vector<EScriptParameterType> &Params)
    : ParameterTypes(Params)
  {}

  std::vector<EScriptParameterType> ParameterTypes;

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(ParameterTypes);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(ParameterTypes);
  }

};

struct FTNScriptInfo
{
  FTNScriptInfo(const FTNScriptFunctionParameterInfo &Params, EScriptReturnType RetType)
    : ParameterInfo(Params), ReturnType(RetType)
  {}

  FTNScriptFunctionParameterInfo ParameterInfo;
  EScriptReturnType ReturnType;

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(ParameterInfo);
    ar(ReturnType);
  }

  template<class Archive>
  void load(Archive & ar)
  {
    ar(ParameterInfo);
    ar(ReturnType);
  }

};

struct FTNScriptParameter
{
  std::variant<int32_t, uint32_t, float, double, sf::Vector2f, sf::Vector2i, sf::Vector2u,
    GameObject *> Value;

};

const FTNScriptInfo FTNGetCurrentPlayerActor = FTNScriptInfo(
  FTNScriptFunctionParameterInfo(),
  EScriptReturnType::GameObjectPtr
);

const FTNScriptInfo FTNGetActorPosition = FTNScriptInfo(
  FTNScriptFunctionParameterInfo({ EScriptParameterType::GameObjectPtr }),
  EScriptReturnType::Vec2f
);

extern GameObject* GetCurrentPlayerActor();
extern sf::Vector2f GetActorPosition(GameObject *ObjectPtr);
