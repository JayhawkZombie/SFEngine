#ifndef SFCSS_TYPES_H
#define SFCSS_TYPES_H

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
#include <sfcss/preproc.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include <cfloat>
#include <sstream>
#include <cstdint>
#include <functional>
#include <chrono>

using sstring = std::string;
using sstream = std::stringstream;
template<class css_t, class css_u> using pair = std::pair<css_t, css_u>;

#if defined(ENV_64)
using cfloat_hp = double;
using cfloat_lp = float;
#else //defined(ENV_64)
using cfloat_hp = float;
using cfloat_lp = float;
#endif

/* Integral types */
using cint_64 = std::int64_t;
using cint_32 = std::int32_t;
using cint_16 = std::int16_t;
using cint_8  = std::int8_t;

using cuint_64 = std::uint64_t;
using cuint_32 = std::uint32_t;
using cuint_16 = std::uint16_t;
using cuint_8  = std::uint8_t;

#if defined(ENV_64)
constexpr cint_64  cint_64_bits  = 64;
constexpr cuint_64 cuint_64_bits = 64;
#else //defined(ENV_64)
constexpr cint_64  cint_64_bits  = 32;
constexpr cuint_64 cuint_64_bits = 32;
#endif //defined (ENV_64)

constexpr cint_32  cint_32_bits  = 32;
constexpr cint_16  cint_16_bits  = 16;
constexpr cint_8   cint_8_bits   = 8;
constexpr cuint_32 cuint_32_bits = 32;
constexpr cuint_16 cuint_16_bits = 16;
constexpr cuint_8  cuint_8_bits  = 8;

constexpr cint_64 cint_64_max = INT64_MAX;
constexpr cint_64 cint_64_min = INT64_MIN;
constexpr cint_32 cint_32_max = INT32_MAX;
constexpr cint_32 cint_32_min = INT32_MIN;
constexpr cint_16 cint_16_max = INT16_MAX;
constexpr cint_16 cint_16_min = INT16_MIN;
constexpr cint_8  cint_8_max  = INT8_MAX;
constexpr cint_8  cint_8_min  = INT8_MIN;

constexpr cuint_64 cuint_64_max = UINT64_MAX;
constexpr cuint_32 cuint_32_max = UINT32_MAX;
constexpr cuint_16 cuint_16_max = UINT16_MAX;
constexpr cuint_8  cuint_8_max  = UINT8_MAX;

extern constexpr cint_64 cint_64_bit_set(const cint_64 &v);
extern constexpr cint_32 cint_32_bit_set(const cint_32 &v);
extern constexpr cuint_64 cuint_64_bit_set(const cuint_64 &v);
extern constexpr cuint_32 cuint_32_bit_set(const cuint_32 &v);

template<typename __css_t> using css_shared_ptr = std::shared_ptr<__css_t>;
template<typename __css_t> using css_unique_ptr = std::unique_ptr<__css_t>;
template<typename __css_t, typename __css_u> using css_pair = std::pair<__css_t, __css_u>;
template<typename __css_t, typename __css_u> using css_map = std::map<__css_t, __css_u>;

using system_clock = std::chrono::system_clock;
template<typename css_t> using time_pt = std::chrono::time_point<css_t>;
using ms   = std::chrono::milliseconds;
using ns   = std::chrono::nanoseconds;
using sec  = std::chrono::seconds;
using mins = std::chrono::minutes;
using hrs  = std::chrono::hours;

namespace ch = std::chrono;

#define CSS_PTR_TYPEDEF(CSS_CLASS)       \
using sptr = css_shared_ptr<CSS_CLASS>;  \
using uptr = css_unique_ptr<CSS_CLASS>;  \
using rptr = CSS_CLASS*;

#define CREATE_SHARED_DEFAULT(CSS_CLASS)      \
static CSS_CLASS##::sptr create() { return std::make_shared<CSS_CLASS>(); }

#define CREATE_SHARED_WPARENT(CSS_CLASS)      \
static CSS_CLASS##::sptr create(CSS_CLASS##::rptr par) \
{                                                      \
  CSS_CLASS##::sptr wid = create();                    \
  wid->parent = par;                                   \
  return wid;                                          \
}

#define DEFAULT_FUNCTION_1ARG [](auto arg) { return; }
#define DEFAULT_FUNCTION_0ARG []() { return; }

#define PRIVATE_VAR(TYPE, VAR)   \
private: TYPE VAR##;             \
public:                          \

constexpr float to_float(const int &i) { return static_cast<float>( i ); }
constexpr float to_float(const unsigned int &i) { return static_cast<float>( i ); }

constexpr ms operator"" _ms(unsigned long long l) { return std::chrono::milliseconds(l); }

namespace css
{

  enum : cint_32 { normal = 0, null = cint_32_max, inherit = -1 };

}

#endif // SFCSS_TYPES_H
