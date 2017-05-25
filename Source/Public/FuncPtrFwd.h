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

#ifndef SFEngine_FuncPtrFwd_H
#define SFEngine_FuncPtrFwd_H

/************************************************************************/
/*                         Internal  Headers                            
/************************************************************************/
#include "Globals.h"
#include "BasicIncludes.h"

/************************************************************************/
/*                       Dependency  Headers                            
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       
/************************************************************************/
#include <functional>

/************************************************************************/
/*                         MainWindow                                   
/************************************************************************/
/*                                                                      
/*                                                                      
/************************************************************************/

/************************************************************************/
/* Last Edit: (Name) - 2017/05/10                                  
/************************************************************************/

/* forward decs */
namespace tgui {  class Gui; class Theme; class Widget; }

namespace SFEngine
{
  template<typename _func_t>
  using FPtr = std::function<_func_t>;

  /* No arg, No return */
  using FPtr_Void = FPtr<void(void)>;

  /* GUI arg, Theme arg */
  using FPtr_Gui_Theme = FPtr<void(SPtrShared<tgui::Gui>, SPtrShared<tgui::Theme>)>;

  /* GUI widget arg, no return */
  using FPtr_Widget = FPtr<void(SPtrShared<tgui::Widget>)>;

  /* String arg, no return */
  using FPtr_String = FPtr<void(std::string)>;

  /* No return, single arg type */
  template<typename Arg1>
  using FPtr_1 = FPtr<void(Arg1)>;

  /* lambda decl (for taking in as argument) */
  template<typename RetV, typename ...ArgV>
  using FPtr_RetV_ArgN = FPtr<RetV(ArgV...)>;

  /* auto lambda for calling own instance's method */
#define FPtr_InstanceLambda(InstMethod, ...)         \
        FPtr_Void(                                   \
        [this](__VA_ARGS__)                          \
        {                                            \
           this->InstMethod(__VA_ARGS__);            \
        }                                            \
        );
#define FPtr_VoidInstanceLambda(InstMethod)          \
        FPtr_Void( [this](){ this->InstMethod; } );

#define FPtr_StaticClassInstanceMethod(InstMethod) \
        FPtr_Void( []() { InstMethod(); } );

} // namespace SFEngine

#endif // ifndef SFEngine_FuncPtrFwd_H
