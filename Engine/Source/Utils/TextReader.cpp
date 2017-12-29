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

#include "Utils\TextReader.h"

namespace Engine
{

  namespace Text
  {

    int ReadInteger(std::string RawString, bool Unsigned)
    {
      static std::string ReadInteger("-?[1-9][0-9]*");
      static std::regex IntegerRegex(ReadInteger);

      //Does the string contain anything it isn't supposed to?
      auto pos = RawString.find_first_not_of("0123456789-");
      if (pos != std::string::npos)
        return 0;

      std::smatch match;
      int ToReturn = 0;
      if (std::regex_search(RawString, match, IntegerRegex)) {
        std::stringstream SS(match.str());
        SS >> ToReturn;
      }

      return ToReturn;
    }

    float ReadDecimal(std::string RawString)
    {
      //Read a decimal
      static std::string ReadDecimal("-?[1-9][0-9]*(\\.?[0-9]*)?");
      static std::regex DecimalRegex(ReadDecimal);

      //Does the string contain anything it isn't supposed to?
      auto pos = RawString.find_first_not_of("0123456789-.");
      if (pos != std::string::npos)
        return 0;

      std::smatch match;
      float ToReturn = 0.f;
      if (std::regex_search(RawString, match, DecimalRegex)) {
        std::stringstream SS(match.str());
        SS >> ToReturn;
      }

      return ToReturn;
    }

  }

}
