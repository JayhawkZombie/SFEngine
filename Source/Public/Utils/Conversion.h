#ifndef SFEngine_Conversion_H
#define SFEngine_Conversion_H

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "BasicIncludes.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                         Conversion                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  /**
  * Convert given string to bool
  * @param: string, case insensitive
  */
  bool StringToBool(const std::string &s);
  bool StringToBool(const std::string &s, bool Default);

  template<typename T>
  sf::Vector2<T> StringToVec2(const std::string &s)
  {
    T a, b;

    std::string astr, bstr;

    std::size_t comma = s.find_first_of(',');
    std::size_t comment = s.find_first_not_of("-0123456789", comma);

    astr = s.substr(1, comma - 1);
    bstr = s.substr(comma + 1, comment);

    std::stringstream converta(astr), convertb(bstr);

    a = (converta >> a ? a : T());
    a = (convertb >> b ? b : T());

    return sf::Vector2<T>(a, b);
  }

  template<typename T>
  sf::Vector2<T> StringToVec2(const std::string &s, sf::Vector2<T> Default)
  {
    T a, b;

    std::string astr, bstr;

    std::size_t comma = s.find_first_of(',');
    std::size_t comment = s.find_first_not_of("-0123456789", comma);

    astr = s.substr(1, comma - 1);
    bstr = s.substr(comma + 1, comment);

    std::stringstream converta(astr), convertb(bstr);

    a = (converta >> a ? a : Default.x);
    a = (convertb >> b ? b : Default.y);

    return sf::Vector2<T>(a, b);
  }

  template<typename T>
  sf::Rect<T> StringToRect(const std::string &s)
  {
    T a, b, c, d;

    std::string astr, bstr, cstr, dstr;
    std::size_t comma1, comma2, comma3, comment;

    comma1 = s.find_first_of(',');
    comma2 = s.find_first_of(',', comma1 + 1);
    comma3 = s.find_first_of(',', comma2 + 1);
    comment = s.find_first_not_of("-0123456789.", comma3 + 1);

    astr = s.substr(1, comma1 - 1);
    bstr = s.substr(comma1 + 1, comma2 - comma1 - 1);
    cstr = s.substr(comma2 + 1, comma3 - comma2 - 1);
    dstr = s.substr(comma3 + 1, comment - comma3 - 1);

    std::stringstream converta(astr), convertb(bstr), convertc(cstr), convertd(dstr);
    a = (converta >> a ? a : T());
    b = (convertb >> b ? b : T());
    c = (convertc >> c ? c : T());
    d = (convertd >> d ? d : T());

    return sf::Rect<T>(a, b, c, d);

  }

  template<typename T>
  sf::Rect<T> StringToRect(const std::string &s, sf::Rect<T> Default)
  {
    T a, b, c, d;

    std::string astr, bstr, cstr, dstr;
    std::size_t comma1, comma2, comma3, comment;

    comma1 = s.find_first_of(',');
    comma2 = s.find_first_of(',', comma1 + 1);
    comma3 = s.find_first_of(',', comma2 + 1);
    comment = s.find_first_not_of("-0123456789.", comma3 + 1);

    astr = s.substr(1, comma1 - 1);
    bstr = s.substr(comma1 + 1, comma2 - comma1 - 1);
    cstr = s.substr(comma2 + 1, comma3 - comma2 - 1);
    dstr = s.substr(comma3 + 1, comment - comma3 - 1);

    std::stringstream converta(astr), convertb(bstr), convertc(cstr), convertd(dstr);
    a = (converta >> a ? a : Default.left);
    b = (convertb >> b ? b : Default.top);
    c = (convertc >> c ? c : Default.width);
    d = (convertd >> d ? d : Default.height);

    return sf::Rect<T>(a, b, c, d);

  }

  template<typename T>
  T StringToType(const std::string &s)
  {
    T a;
    std::string scpy;
    std::size_t comment = s.find_first_of(';');

    scpy = s.substr(0, comment);

    std::stringstream ss(scpy);

    return (ss >> a ? a : T());
  }

  template<typename T>
  T StringToType(const std::string &s, T Default)
  {
    T a;
    std::string scpy;
    std::size_t comment = s.find_first_of(';');

    scpy = s.substr(0, comment);

    std::stringstream ss(scpy);

    return (ss >> a ? a : Default);
  }

}

#endif // SFEngine_Conversion_H 
