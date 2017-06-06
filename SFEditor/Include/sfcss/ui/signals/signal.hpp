#ifndef SFCSS_SIGNAL_H
#define SFCSS_SIGNAL_H

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
#include <functional>
#include <vector>

namespace css
{

  template<class Css_Ret_t, class ... Css_Args_t>
  struct signal
  {
    void emit(Css_Args_t ... fargs) {
      for (auto & func : subscribers)
        func.second(fargs...);
    }

    void connect(std::function<Css_Ret_t(Css_Args_t...)> fu, std::string id) {
      subscribers.push_back(std::make_pair(id, fu));
    }

    void disconnect(const std::string &id) {
      auto it = subscribers.begin();
      for (it; it != subscribers.end(); ++it) {
        if (( *it ).first == id) break;
      }

      if (it != subscribers.end())
        subscribers.erase(it);
    }

    void disconnect_all() {
      subscribers.clear();
    }

    std::vector<std::pair<std::string, std::function<Css_Ret_t(Css_Args_t...)>>> subscribers;
  };

}

#endif // SFCSS_SIGNAL_H
