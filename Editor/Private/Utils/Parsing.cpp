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

#define _SCL_SECURE_NO_WARNINGS

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "Globals.h"
#if defined (SF_EDITOR)

#include "Utils\Parsing.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <boost\xpressive\xpressive.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                            Parsing                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: (Name) - 2017/05/07                                       */
/************************************************************************/

namespace SFEngine
{

  const std::string& EnvSubstRX(boost::xpressive::smatch const& matched)
  {
    return Env[matched[1].str()];
  }

  void EnvSubst(SString &Search)
  {
    static boost::xpressive::sregex EnvVarRX =
      "$(" >> (boost::xpressive::s1 = +boost::xpressive::_w) >> ")";

    Search = boost::xpressive::regex_replace(Search, EnvVarRX, EnvSubstRX);
  }

} // namespace SFEngine

#endif // if defined (SF_EDITOR)
