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

#include "Utils\ReadIni.h"
#include "Utils\Convert.h"

#include <unordered_map>
#include <string>
#include <set>

namespace Util
{

  enum IniDelims : char
  {
    SPACE       = ' ',
    COMMA       = ',',
    PLUS        = '+',
    MINUS       = '-',
    STAR        = '*',
    EQUAL       = '=',
    AND         = '&',
    OR          = '|',
    XOR         = '^',
    MOD         = '%',
    NOT         = '!',
    AT          = '@',
    LPARENS     = '(',
    RPARENS     = ')',
    QUOTE       = '\"',
    COLON       = ':',
    SEMICOLON   = ';',
    LANGLE      = '<',
    RANGLE      = '>',
    DOT         = '.',
    FSLASH      = '/',
    BSLASH      = '\\',
    TERNARY     = '?',
    NEWLINE     = '\n',
    OCTOTHORPE  = '#',
    LBRACKET    = '[',
    RBRACKET    = ']'
  };

  enum class IniValueType : std::uint32_t
  {
    Int = 0,
    UnsignedInt,
    Float,
    Double,
    Bool,
    NTouple,
    Vector2f,
    Vector2i,
    Vector2u,
    IntRect,
    FloatRect
  };

  class IniValue
  {
  public:
    IniValue() = default;
    ~IniValue() = default;

    bool Read(std::stringstream &in);
    void Write(std::stringstream &out);

    template<typename ValueType>
    ValueType Get(ValueType Default) const;

    template<typename ValueType>
    void Set(ValueType Value);

    std::string GetKey() const;

    static int          AsInt        (const IniValue &VRef, int          Default);
    static float        AsFloat      (const IniValue &VRef, float        Default);
    static double       AsDouble     (const IniValue &VRef, double       Default);
    static unsigned int AsUnsignedInt(const IniValue &VRef, unsigned int Default);

    static bool AsBool(const IniValue &VRef, bool Default);

    sf::Vector2f  AsVector2f (const IniValue &VRef, sf::Vector2f  Default);
    sf::Vector2i  AsVector2i (const IniValue &VRef, sf::Vector2i  Default);
    sf::Vector2u  AsVector2u (const IniValue &VRef, sf::Vector2u  Default);
    sf::IntRect   AsIntRect  (const IniValue &VRef, sf::IntRect   Default);
    sf::FloatRect AsFloatRect(const IniValue &VRef, sf::FloatRect Default);

  protected:
    std::string            m_StringValueRep;
    std::string            m_KeyRep;
    std::set<IniValueType> m_PossibleTypes;
    //IniValueType m_ValueType;
  };

  /*
    * Template specializations for IniValue Getters
    **/
  template<> int           IniValue::Get<int>          (int           Default) const;
  template<> unsigned int  IniValue::Get<unsigned int> (unsigned int  Default) const;
  template<> float         IniValue::Get<float>        (float         Default) const;
  template<> double        IniValue::Get<double>       (double        Default) const;
  template<> bool          IniValue::Get<bool>         (bool          Default) const;
  template<> sf::Vector2f  IniValue::Get<sf::Vector2f> (sf::Vector2f  Default) const;
  template<> sf::Vector2i  IniValue::Get<sf::Vector2i> (sf::Vector2i  Default) const;
  template<> sf::Vector2u  IniValue::Get<sf::Vector2u> (sf::Vector2u  Default) const;
  template<> sf::IntRect   IniValue::Get<sf::IntRect>  (sf::IntRect   Default) const;
  template<> sf::FloatRect IniValue::Get<sf::FloatRect>(sf::FloatRect Default) const;

  /*
    * Template specializations for IniValue setters
    **/
  template<> void IniValue::Set<int>          (int           Value);
  template<> void IniValue::Set<unsigned int> (unsigned int  Value);
  template<> void IniValue::Set<double>       (double        Value);
  template<> void IniValue::Set<float>        (float         Value);
  template<> void IniValue::Set<bool>         (bool          Value);
  template<> void IniValue::Set<sf::Vector2f> (sf::Vector2f  Value);
  template<> void IniValue::Set<sf::Vector2i> (sf::Vector2i  Value);
  template<> void IniValue::Set<sf::Vector2u> (sf::Vector2u  Value);
  template<> void IniValue::Set<sf::IntRect>  (sf::IntRect   Value);
  template<> void IniValue::Set<sf::FloatRect>(sf::FloatRect Value);

  class IniSectionCache 
  {
  public:
      
    IniSectionCache() = default;
    ~IniSectionCache() = default;

    void Read(std::stringstream &in);
    void Write(std::stringstream &out);

    template<typename ValueType>
    ValueType GetValue(const std::string &Key, ValueType Default) const;

  private:
    std::string m_SectionRep;
    int m_EntryCount;
    std::vector<IniValue> m_Values;
  };
    
  /*
    *  Template specialization for GetValue
    **/
  template<> int           IniSectionCache::GetValue<int>          (const std::string &Key, int           Default) const;
  template<> float         IniSectionCache::GetValue<float>        (const std::string &Key, float         Default) const;
  template<> double        IniSectionCache::GetValue<double>       (const std::string &Key, double        Default) const;
  template<> unsigned int  IniSectionCache::GetValue<unsigned int> (const std::string &Key, unsigned int  Default) const;
  template<> sf::Vector2f  IniSectionCache::GetValue<sf::Vector2f> (const std::string &Key, sf::Vector2f  Default) const;
  template<> sf::Vector2u  IniSectionCache::GetValue<sf::Vector2u> (const std::string &Key, sf::Vector2u  Default) const;
  template<> sf::Vector2i  IniSectionCache::GetValue<sf::Vector2i> (const std::string &Key, sf::Vector2i  Default) const;
  template<> sf::IntRect   IniSectionCache::GetValue<sf::IntRect>  (const std::string &Key, sf::IntRect   Default) const;
  template<> sf::FloatRect IniSectionCache::GetValue<sf::FloatRect>(const std::string &Key, sf::FloatRect Default) const;

  class IniCache
  {
  public:

    template<typename ValueType>
    static ValueType RetrieveValue(const std::string &Section, const std::string &KeyVal, ValueType Default);

    static void Init();
    static void Cleanup();

  private:
    IniCache() = default;
    ~IniCache() = default;

    static IniCache* Get();

    static IniCache *m_Cache;
    std::unordered_map<std::string, IniSectionCache> m_SectionMap;
  };

  /*
    * Template specializations for value retrieval
    **/
  template<> int           IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, int           Default);
  template<> float         IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, float         Default);
  template<> double        IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, double        Default);
  template<> unsigned int  IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, unsigned int  Default);
  template<> sf::Vector2f  IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::Vector2f  Default);
  template<> sf::Vector2i  IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::Vector2i  Default);
  template<> sf::Vector2u  IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::Vector2u  Default);
  template<> sf::IntRect   IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::IntRect   Default);
  template<> sf::FloatRect IniCache::RetrieveValue(const std::string &Section, const std::string &KeyVal, sf::FloatRect Default);

}

#include "CacheIni.inl"
