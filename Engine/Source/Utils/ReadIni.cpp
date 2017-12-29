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

#include <sstream>

namespace Engine
{
  namespace Util
  {
    bool MoveToCategory(const std::string &category, std::ifstream &in)
    {
      std::string line;
      in.clear();
      in.seekg(0, std::ios::beg);
      std::string _categ;
      std::size_t pos = std::string::npos;

      while (std::getline(in, line)) {
        pos = line.find_first_of('[');

        if (pos != std::string::npos) {
          std::size_t end = line.find_first_of(']');

          if (end != std::string::npos) {
            _categ = line.substr(pos + 1, end - pos - 1);

            if (_categ == category)
              return true;
          }
        }
      }
      return false;
    }

    std::string MoveToKey(const std::string &key, std::ifstream &in)
    {
      std::string line, _key;
      std::streampos loc = in.tellg();
      std::size_t eqpos = std::string::npos;
      std::size_t comment = std::string::npos;

      while (std::getline(in, line)) {
        if (line.find('[') != std::string::npos) { //If line has '[', it is the beg of a category, we went too far
          in.clear(); in.seekg(loc);
          return "";
        }
        else {
          eqpos = line.find_first_of('=');
          comment = line.find_first_of(';'); //Ignore anything on the line after the comment symbol (';')
          if (eqpos != std::string::npos) {
            _key = line.substr(0, eqpos);
            if (_key == key)
              return line.substr(line.find_first_not_of(" \t", eqpos + 1), comment); //Find where the VALUE starts and go from there to the position of the comment (if there is any comment)
          }
        }
      } //while getline(in, line)

      return "";
    }

    std::pair<std::string, std::string> GetPairText(const std::string &line, std::size_t &curroffset) 
    {
      std::size_t pos = line.find_first_of('<', curroffset);
      std::size_t comma = line.find_first_of(',', pos + 1);
      std::size_t end = line.find_first_of('>', comma + 1);
      if (pos == std::string::npos || comma == std::string::npos || end == std::string::npos) {
        curroffset = 0;
        return std::pair<std::string, std::string>("", "");
      }
      else {
        std::string first = line.substr(pos + 1, comma - pos - 1);
        std::string second = line.substr(line.find_first_not_of(" \t", comma + 1), end - comma - 2);
        curroffset = end;
        return std::pair<std::string, std::string>(first, second);
      }
    }

    std::string GetBracedText(const std::string &key, std::ifstream &in)
    {
      std::string line, _key;
      std::streampos loc = in.tellg();
      std::size_t lbrace = std::string::npos;
      std::size_t eqpos = std::string::npos;
      std::size_t comment = std::string::npos;

      std::stringstream bracedvalue;

      while (std::getline(in, line)) {
        if (line.find_first_of('[') != std::string::npos) {
          in.clear(); in.seekg(loc);
          return "{}";
        }
        else {
          eqpos = line.find_first_of('=');
          _key = line.substr(0, eqpos);
          if (_key == key) {
            lbrace = line.find_first_of('{', eqpos);
            if (eqpos != std::string::npos && lbrace != std::string::npos) {
              char c;
              std::string substr;
              substr = line.substr(lbrace);
              bracedvalue << substr;
              while (in.get(c)) {
                bracedvalue << c;
                if (c == '}')
                  break;
              }

              return bracedvalue.str();
            }
          } //if _key == key

        } //else (from .find('[')
      }

      return "{}";
    }

    std::vector<std::pair<std::string, std::string>> ParsePairedText(const std::string &str, const std::size_t &paircount)
    {
      std::vector<std::pair<std::string, std::string>> V;
      std::size_t beg{ 0 }, end{ std::string::npos }, currentpos{ 0 };
      for (std::size_t i = 0; i < paircount; ++i) {
        beg = str.find_first_of("<", currentpos);
        end = str.find_first_of(">", beg + 1);

        V.push_back(Util::GetPairText(str, beg));
        currentpos = str.find_first_of(",", end + 1);
      }
      
      return V;
    }

    bool GetBooleanConfig(const std::string &category, const std::string &key, const bool &defaultValue, const std::string &inifile, std::ifstream &in)
    {
      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      std::string valstring = MoveToKey(key, in);
      return (Util::StringToBool(valstring));
    }

    unsigned int GetUnsignedIntConfig(const std::string &category, const std::string &key, const unsigned int &defaultValue, const std::string &inifile, std::ifstream &in)
    {
      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      std::string valstring = MoveToKey(key, in);

      if (valstring == "")
        return defaultValue;

      //std::cout << "value for ui string: " << valstring << std::endl;
      return Util::StringToType<unsigned int>(valstring);
    }

    sf::Vector2f GetVec2fConfig(const std::string &category, const std::string &key, const sf::Vector2f &defaultValue, const std::string &inifile, std::ifstream &in)
    {
      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      std::string valstring = MoveToKey(key, in);

      if (valstring == "")
        return defaultValue;

      return Util::StringToVec2<float>(valstring);
    }

    sf::FloatRect GetFloatRectConfig(const std::string &category, const std::string &key, const sf::FloatRect &defaultValue, const std::string &inifile, std::ifstream &in)
    {

      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      std::string val = MoveToKey(key, in);

      if (val == "")
        return defaultValue;

      return Util::StringToRect<float>(val);

    }

    float GetFloatConfig(const std::string &category, const std::string &key, const float &defaultValue, const std::string &inifile, std::ifstream &in)
    {
      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      std::string valstring = MoveToKey(key, in);
      if (valstring == "")
        return defaultValue;

      return Util::StringToType<float>(valstring);
    }

    double GetDoubleConfig(const std::string &category, const std::string &key, const bool &defaultValue, const std::string &inifile, std::ifstream &in)
    {
      return defaultValue;
    }

    std::string GetStringConfig(const std::string &category, const std::string &key, const std::string &defaultValue, const std::string &infile, std::ifstream &in)
    {
      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      std::string val = MoveToKey(key, in);
      if (val == "") {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      return val;
    }

    std::string GetBracedConfig(const std::string &category, const std::string &key, const std::string &defaultValue, const std::string &infile, std::ifstream &in)
    {
      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }

      std::string val = GetBracedText(key, in);
      return val;
    }

    std::pair<std::string, std::string> GetStringPair(const std::string &category, const std::string &key, const std::pair<std::string, std::string> &defaultValue, const std::string &infile, std::ifstream &in)
    {
      if (!MoveToCategory(category, in)) {
        in.seekg(std::ios::beg);
        return defaultValue;
      }
      std::size_t pos = 0;
      std::string line = MoveToKey(key, in);
      auto pair = GetPairText(line, pos);
      return pair;
    }

    void WriteBooleanConfig(const std::string &category, const std::string &key, const bool &value, const std::string &inifile, std::ifstream &in)
    {

    }

    void WriteUnsignedIntConfig(const std::string &category, const std::string &key, const unsigned int &value, const std::string &inifile, std::ifstream &in)
    {

    }

    void WriteVec2fConfig(const std::string &category, const std::string &key, const sf::Vector2f &value, const std::string &inifile, std::ifstream &in)
    {

    }

    void WriteFloatConfig(const std::string &category, const std::string &key, const float &value, const std::string &inifile, std::ifstream &in)
    {

    }

    void WriteDoubleConfig(const std::string &category, const std::string &key, const bool &value, const std::string &inifile, std::ifstream &in)
    {

    }

    void WriteStringValue(const std::string &category, const std::string &key, const std::string &value, const std::string &infile, std::ifstream &in)
    {

    }
  }
}
