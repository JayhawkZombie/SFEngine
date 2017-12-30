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

#include <variant>
#include <optional>

enum class EObjectPropertyType
{
  String,
  Int,
  Uint, 
  Float,
  Double,
  Vector2f,
  Vector2i,
  Vector2u
};

class ObjectProperty
{
public:
  ObjectProperty();
  ObjectProperty(const ObjectProperty &);
  ~ObjectProperty();

  std::string GetTypeString() const;

  bool ConvertTo(const std::string &TypeString);
  
  const std::string& GetName() const;
  void SetName(const std::string &NameString);

  std::string AsString() const;

  std::optional<std::int32_t> AsInt();
  std::optional<std::uint32_t> AsUint();
  std::optional<float> AsFloat();
  std::optional<double> AsDouble();
  std::optional<sf::Vector2f> AsVector2f();
  std::optional<sf::Vector2i> AsVector2i();
  std::optional<sf::Vector2u> AsVector2u();

  void Set(std::int32_t val);
  void Set(std::uint32_t val);
  void Set(float val);
  void Set(double val);
  void Set(const sf::Vector2f &val);
  void Set(const sf::Vector2i &val);
  void Set(const sf::Vector2u &val);

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(m_Type);
    ar(m_NameString);
    ar(m_ValueString);

    switch (m_Type)
    {
      case EObjectPropertyType::String:
      {
        std::string val = std::get<std::string>(m_Value);
        ar(val);
        break;
      }
      case EObjectPropertyType::Int:
      {
        std::int32_t val = std::get<std::int32_t>(m_Value);
        ar(val);
        break;
      }
      case EObjectPropertyType::Uint:
      {
        std::uint32_t val = std::get<std::uint32_t>(m_Value);
        ar(val);
        break;
      }
      case EObjectPropertyType::Float:
      {
        float val = std::get<float>(m_Value);
        ar(val);
        break;
      }
      case EObjectPropertyType::Double:
      {
        double val = std::get<double>(m_Value);
        ar(val);
        break;
      }
      case EObjectPropertyType::Vector2f:
      {
        sf::Vector2f val = std::get<sf::Vector2f>(m_Value);
        ar(val);
        break;
      }
      case EObjectPropertyType::Vector2i:
      {
        sf::Vector2i val = std::get<sf::Vector2i>(m_Value);
        ar(val);
        break;
      }
      case EObjectPropertyType::Vector2u:
      {
        sf::Vector2u val = std::get<sf::Vector2u>(m_Value);
        ar(val);
        break;
      }
    } // switch (m_Type)
  } // void save(...)

  template<class Archive>
  void load(Archive & ar)
  {
    ar(m_Type);
    ar(m_NameString);
    ar(m_ValueString);

    switch (m_Type)
    {
      case EObjectPropertyType::String:
      {
        std::string val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
      case EObjectPropertyType::Int:
      {
        std::int32_t val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
      case EObjectPropertyType::Uint:
      {
        std::uint32_t val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
      case EObjectPropertyType::Float:
      {
        float val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
      case EObjectPropertyType::Double:
      {
        double val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
      case EObjectPropertyType::Vector2f:
      {
        sf::Vector2f val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
      case EObjectPropertyType::Vector2i:
      {
        sf::Vector2i val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
      case EObjectPropertyType::Vector2u:
      {
        sf::Vector2u val;
        ar(val);

        m_Value.emplace(val);
        break;
      }
    } // switch (m_Type)
  }

protected:

  std::string m_NameString = "";
  std::string m_ValueString = "";

  std::variant<std::string, std::int32_t, std::uint32_t, float, double,
    sf::Vector2f, sf::Vector2i, sf::Vector2u> m_Value;
  EObjectPropertyType m_Type;
};
