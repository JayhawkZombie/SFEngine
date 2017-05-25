#ifndef SFEngine_UIEditor_H
#define SFEngine_UIEditor_H

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

/************************************************************************/
/*                         Internal  Headers                            
/************************************************************************/
#include "Globals.h"
#if defined (SF_EDITOR)

#include "FuncPtrFwd.h"
/************************************************************************/
/*                       Dependency  Headers                            
/************************************************************************/
#include <TGUI\TGUI.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       
/************************************************************************/

/************************************************************************/
/*                        EditorManager                                 
/************************************************************************/
/*                                                                      
/*                                                                      
/************************************************************************/

/************************************************************************/
/* Last Edit: (Kurt Slagle) - 2017/05/10                                 
/************************************************************************/

namespace SFEngine
{

  using FPtrGUITheme = FPtr<void(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme)>;
  class UIEditor
  {
  public:
    UIEditor();
    ~UIEditor();
  
    static void CreateTool(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);

  private:
    static void CreateItemPanel(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
    static void OnItemSelected(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
    static void OnItemDropped(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
    static void OnItemDeselected(SPtrShared<tgui::Gui> GUI, SPtrShared<tgui::Theme> Theme);
    static void ShowSelectedItemEditControls();
    static void OnToolClosed();
    static void OnToolOpened();

    static FPtr_Void ToolClosedReponse;
    static FPtr_Void ToolOpenedResponse;

    /* Controls for editing items */
    static SVector2F m_ItemPosition;
    static SVector2F m_ItemSize;
    static void ShowSelectedItemProperties();

  };

} // namespace SFEngine

#endif // if defined (SF_EDITOR)

#endif // SFEngine_UIEditor_H
