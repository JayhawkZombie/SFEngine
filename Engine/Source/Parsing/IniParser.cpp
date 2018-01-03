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

#include "IniParser.h"
#include <Engine/Source/Utils/Filereader.h>

void IniParser::Parse(const std::string &Filename)
{
  std::stringstream stream;
  ReadFileIntoStream(Filename, stream);

  Parse(stream);
}

void IniParser::Parse(std::stringstream &stream)
{
  boost::char_separator<char> seps("\n", "[]=");
  const std::string str = stream.str();

  TTokenizer tokens(str, seps);

  auto tok = tokens.begin();

  std::string SectionString;
  std::string KeyString;
  std::string ValueString;

  while (tok != tokens.end())
  {

    /* If the token is '[', extract the section string */
    if (*tok == "[")
    {

      /* The next token should be the key, and the next after that should be ']' */

      if (++tok == tokens.end())
      {
        std::cerr << "IniParser::Error: Expected string after \"]\" but reached end of input\n";
        ErrorSectionHeaderInvalid();
        break;
      }

      SectionString = *tok;

      if (++tok == tokens.end())
      {
        std::cerr << "IniParser::Error: Expected \"]\" but reached end of input\n";
        ErrorSectionHeaderInvalid();
        break;
      }

      /* Verify this token is "]" */
      if (*tok != "]")
      {
        std::cerr << "IniParser::Error: Expected \"]\" but found \"" << *tok << "\"\n";
        ErrorSectionHeaderInvalid();
        break;
      }

      tok++;

      m_ValueMap.try_emplace(SectionString);

    } // if (*tok == "[")

    else if (*tok != "\n")
    {
      /* If not a section header, we should try to parse a key-value pair */

      KeyString = *tok;

      if (++tok == tokens.end())
      {
        std::cerr << "IniParser::Error: Expected \"=\" but reached end of input\n";
        ErrorKeyInvalid(KeyString);
        break;
      }

      if (*tok != "=")
      {
        std::cerr << "IniParser::Error: Expected \"=\" but found \"" << *tok << "\"\n";
        ErrorValueInvalid(KeyString);
        break;
      }

      if (++tok == tokens.end())
      {
        std::cerr << "IniParser::Error: Expected to find value string but reached end of input\n";
        ErrorValueInvalid(KeyString);
        break;
      }

      ValueString = *tok;

      ++tok;

      m_ValueMap[SectionString].try_emplace(KeyString, ValueString);

    } // else (not a section header)
    else
    {
      tok++;
    }

  } // while (tok != tokens.end())
}

bool IniParser::HasSection(const std::string &Name)
{
  return ( m_ValueMap.find(Name) != m_ValueMap.end() );
}

bool IniParser::HasKey(const std::string &Section, const std::string &KeyString)
{
  auto optl = TryGetValue(Section, KeyString);

  return optl.has_value();
}

std::optional<std::string> IniParser::TryGetValue(const std::string &Section, const std::string &KeyString)
{
  auto sectn = m_ValueMap.find(Section);

  if (sectn != m_ValueMap.end())
  {
    auto key = ( *sectn ).second.find(KeyString);

    if (key != ( *sectn ).second.end())
    {
      return std::make_optional(( *key ).second);
    }
  }

  return std::nullopt;
}

bool IniParser::TryParseHeader()
{
  return false;
}

bool IniParser::TryParseValues()
{
  return false;
}

void IniParser::ErrorSectionHeaderInvalid()
{
  std::cerr << "IniParser::SectionHeaderInvalid\n";
}

void IniParser::ErrorKeyInvalid(const std::string &KeyStr)
{
  std::cerr << "IniParser::KeyInvalid (Key is \"" << KeyStr << "\"\n";
}

void IniParser::ErrorValueInvalid(const std::string &KeyStr)
{
  std::cerr << "IniParser::ValueInvalid (Key was \"" << KeyStr << "\"\n";
}
