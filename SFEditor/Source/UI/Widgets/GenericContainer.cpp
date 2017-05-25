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
#include <UI/Widgets/GenericContainer.h>
#include <UI/Globals.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  bool GenericContainer::Add(Widget::Ptr widget, std::string ID)
  {
    if (!widget)
      return false;

    if (ID == "") {
      ID = std::to_string(GenerateID());
    }

    widget->m_Parent = this;
    m_Widgets[ID] = widget;
    return true;
  }

  bool GenericContainer::Remove(Widget::Ptr widget)
  {
    for (auto & wid : m_Widgets) {
      if (wid.second == widget) {
        m_Widgets.erase(m_Widgets.find(wid.first));
        return true;
      }
    }

    return false;
  }

  bool GenericContainer::Remove(std::string ID)
  {
    auto it = m_Widgets.find(ID);
    if (it != m_Widgets.end()) {
      m_Widgets.erase(it);
      return true;
    }

    return false;
  }

  bool GenericContainer::RemoveAll()
  {
    m_Widgets.clear();
    return true;
  }

  bool GenericContainer::HideAll()
  {
    for (auto & widget : m_Widgets) {
      widget.second->Hide();
    }

    return true;
  }

  bool GenericContainer::ShowAll()
  {
    for (auto & widget : m_Widgets) {
      widget.second->Show();
    }

    return true;
  }

}
