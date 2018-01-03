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

#include "Engine/stdafx.h"
#include "Property.h"


ObjectProperty::ObjectProperty()
{
  m_Type = EObjectPropertyType::Int;
  m_Value = std::int32_t(0);
}

ObjectProperty::ObjectProperty(const ObjectProperty &Prop)
{
  m_NameString = Prop.m_NameString;
  m_Type = Prop.m_Type;
  m_ValueString = Prop.m_ValueString;
  m_Value = Prop.m_Value;
}

ObjectProperty::~ObjectProperty()
{

}

std::string ObjectProperty::GetTypeString() const
{
  switch (m_Type)
  {
    case EObjectPropertyType::String: return "String";
    case EObjectPropertyType::Int: return "Int";
    case EObjectPropertyType::Uint: return "Uint";
    case EObjectPropertyType::Float: return "Float";
    case EObjectPropertyType::Double: return "Double";
    case EObjectPropertyType::Vector2f: return "Vector2f";
    case EObjectPropertyType::Vector2i: return "Vector2i";
    case EObjectPropertyType::Vector2u: return "Vector2u";
  }
}

bool ObjectProperty::ConvertTo(const std::string &TypeString)
{
  return false;
}

const std::string& ObjectProperty::GetName() const
{
  return m_NameString;
}

void ObjectProperty::SetName(const std::string &NameString)
{
  m_NameString = NameString;
}

std::string ObjectProperty::AsString() const
{
  return m_ValueString;
}

std::optional<std::int32_t> ObjectProperty::AsInt()
{
  try
  {
    std::int32_t val = std::get<std::int32_t>(m_Value);
    return val;
  }
  catch (const std::exception&)
  {
    return std::nullopt;
  }
}

std::optional<std::uint32_t> ObjectProperty::AsUint()
{
  try
  {
    std::uint32_t val = std::get<std::uint32_t>(m_Value);
    return val;
  }
  catch (const std::exception&)
  {
    return std::nullopt;
  }
}

std::optional<float> ObjectProperty::AsFloat()
{
  try
  {
    float val = std::get<float>(m_Value);
    return val;
  }
  catch (const std::exception&)
  {
    return std::nullopt;
  }
}

std::optional<double> ObjectProperty::AsDouble()
{
  try
  {
    double val = std::get<double>(m_Value);
    return val;
  }
  catch (const std::exception&)
  {
    return std::nullopt;
  }
}

std::optional<sf::Vector2f> ObjectProperty::AsVector2f()
{
  try
  {
    sf::Vector2f val = std::get<sf::Vector2f>(m_Value);
    return val;
  }
  catch (const std::exception&)
  {
    return std::nullopt;
  }
}

std::optional<sf::Vector2i> ObjectProperty::AsVector2i()
{
  try
  {
    sf::Vector2i val = std::get<sf::Vector2i>(m_Value);
    return val;
  }
  catch (const std::exception&)
  {
    return std::nullopt;
  }
}

std::optional<sf::Vector2u> ObjectProperty::AsVector2u()
{
  try
  {
    sf::Vector2u val = std::get<sf::Vector2u>(m_Value);
    return val;
  }
  catch (const std::exception&)
  {
    return std::nullopt;
  }
}

void ObjectProperty::Set(std::int32_t val)
{
  m_Type = EObjectPropertyType::Int;
  m_Value = val;
}

void ObjectProperty::Set(std::uint32_t val)
{
  m_Type = EObjectPropertyType::Uint;
  m_Value = val;
}

void ObjectProperty::Set(float val)
{
  m_Type = EObjectPropertyType::Float;
  m_Value = val;
}

void ObjectProperty::Set(double val)
{
  m_Type = EObjectPropertyType::Double;
  m_Value = val;
}

void ObjectProperty::Set(const sf::Vector2f &val)
{
  m_Type = EObjectPropertyType::Vector2f;
  m_Value = val;
}

void ObjectProperty::Set(const sf::Vector2i &val)
{
  m_Type = EObjectPropertyType::Vector2i;
  m_Value = val;
}

void ObjectProperty::Set(const sf::Vector2u &val)
{
  m_Type = EObjectPropertyType::Vector2u;
  m_Value = val;
}
