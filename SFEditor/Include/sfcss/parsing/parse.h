#ifndef SFCSS_PARSE_H
#define SFCSS_PARSE_H

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

////////////////////////////////////////////////////////////
// Internal Headers
////////////////////////////////////////////////////////////
#include <sfcss/types.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <string>
#include <sstream>

namespace css
{

  class Property;
  class Value;
  class Selector;
  class Stylesheet;
  class Callback;
  class Rule;
  
  using stringpos  = std::string::size_type;
  using stringsize = std::string::size_type;
  
  extern bool parse_stylesheet        (const sstring &filename, css_shared_ptr<Stylesheet> sheet_ptr);
  extern bool parse_rule              (const sstring &source, stringpos start, css_shared_ptr<Rule> rule_ptr);
  extern bool parse_selector_list     (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_basic_selector    (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_class_selector    (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_id_selector       (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_universal_selector(const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_attribute_selector(const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_combinator        (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_pseudo_element    (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_pseudo_class      (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_at_rule           (const sstring &source, stringpos start, css_shared_ptr<Selector> selector_ptr);
  extern bool parse_property          (const sstring &source, stringpos start, sstring &accum);
  extern bool parse_value             (const sstring &source, stringpos start, sstring &accum);

  extern cfloat_hp ParseFloatHP(const sstring &val);
  extern cfloat_lp ParseFloatLP(const sstring &val);
}

#endif // SFCSS_PARSE_H
