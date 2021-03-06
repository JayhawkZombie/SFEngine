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

#include <boost/tokenizer.hpp>
#include <optional>

using TTokenizer = boost::tokenizer<boost::char_separator<char>>;

class IniParser
{
public:
  IniParser() = default;
  ~IniParser() = default;

  void Parse(const std::string &Filename);
  void Parse(std::stringstream &stream);
  void ParseOption(const std::string &OptionString);

  bool HasSection(const std::string &Name);
  bool HasKey(const std::string &Section, const std::string &KeyString);

  std::optional<std::string> TryGetValue(const std::string &Section, const std::string &KeyString);

  const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& GetValueMap() const;

  void AddSection(const std::string &Name);
  void AddKeyValuePair(const std::string &Section, const std::string &Key, const std::string &Value);

private:

  bool TryParseHeader();
  bool TryParseValues();

  void ErrorSectionHeaderInvalid();
  void ErrorKeyInvalid(const std::string &KeyStr);
  void ErrorValueInvalid(const std::string &KeyStr);

  std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_ValueMap;

};

