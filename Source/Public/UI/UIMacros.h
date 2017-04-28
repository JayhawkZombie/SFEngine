#ifndef SFEngine_UIMacros_H
#define SFEngine_UIMacros_H

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
/*                           UIMacros                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

#include <TGUI\TGUI.hpp>

  //Fuck off Microsoft with your namespace pollution
#ifdef _WINDEF_
#undef _WINDEF_
#undef TEXT
#undef __TEXT
#endif

#define ELEMENT_PTR
#define ELEMENT_POSITION
#define ELEMENT_TEXT
#define ELEMENT_SIZE
#define ELEMENT_THEME
#define ELEMENT_PARENT_GUI
#define ELEMENT_NAME
#define ELEMENT_TEXT_SIZE
#define ELEMENT_DURATION
#define ELEMENT_TO_SHOW
#define ELEMENT_TO_HIDE

#define __TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME)    \
ELEMENT->setPosition(POSITION);                                      \
ELEMENT->setSize(_SIZE);                                             \
GUI->add(ELEMENT, NAME)

#define TGUI_ELEMENT_BUTTON_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)   \
ELEMENT = THEME->load("button");                                                                 \
ELEMENT->setText(TEXT);                                                                          \
ELEMENT->setTextSize(TEXTSIZE);                                                                  \
__TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME);                                       \

#define TGUI_ELEMENT_BUTTON_CREATE_HIDDEN(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)   \
TGUI_ELEMENT_BUTTON_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)                  \
ELEMENT->hide();                                                                                        \

#define TGUI_ELEMENT_LABEL_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, TEXT, TEXTSIZE, GUI)    \
ELEMENT = THEME->load("label");                                                                  \
ELEMENT->setText(TEXT);                                                                          \
__TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME);                                       \

#define TGUI_ELEMENT_PANEL_CREATE(ELEMENT, NAME, THEME, _SIZE, POSITION, GUI)                    \
ELEMENT = THEME->load("panel");                                                                  \
__TGUI_ELEMENT_PLACE(ELEMENT, POSITION, _SIZE, GUI, NAME);                                       \

#define TGUI_PANEL_SWITCH_TRANSITION(PANEL_SHOW, PANEL_HIDE, DURATION)          \
PANEL_HIDE->hideWithEffect(tgui::ShowAnimationType::SlideToRight, DURATION);    \
PANEL_HIDE->disable();                                                          \
PANEL_SHOW->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, DURATION);   \
PANEL_SHOW->enable();                                                           \

#define TGUI_PANEL_SWITCH_TRANSITION_SHOW_LEFT_HIDE_RIGHT(PANEL_SHOW, PANEL_HIDE, DURATION)   \
PANEL_HIDE->hideWithEffect(tgui::ShowAnimationType::SlideToRight, DURATION);                  \
PANEL_HIDE->disable();                                                                        \
PANEL_SHOW->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, DURATION);                 \
PANEL_SHOW->enable();                                                                         

#define TGUI_PANEL_SWITCH_TRANSITION_SHOW_RIGHT_HIDE_LEFT(PANEL_SHOW, PANEL_HIDE, DURATION)   \
PANEL_HIDE->hideWithEffect(tgui::ShowAnimationType::SlideToLeft, DURATION);                   \
PANEL_HIDE->disable();                                                                        \
PANEL_SHOW->showWithEffect(tgui::ShowAnimationType::SlideFromRight, DURATION);                \
PANEL_SHOW->enable();                                                                         \

#define TGUI_CONNECT_MAKE_LAMBDA_MACRO(ELEMENT, SIGNAL, MACRO_CALL)             \
ELEMENT->connect(SIGNAL,  [this](){ MACRO_CALL; });                             \


}

#endif // SFEngine_UIMacros_H 
