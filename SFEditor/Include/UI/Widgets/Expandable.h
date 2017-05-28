#ifndef SFEDITOR_EXPANDABLE_H
#define SFEDITOR_EXPANDABLE_H

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

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  class Expandable : public GenericContainer
  {
  public:
    Expandable();
    Expandable(Widget::RPtr parent);
    virtual ~Expandable() override;

    virtual bool HandleEvent(const UserEvent &event) override;
    virtual void Update() override;
    virtual void Render(std::shared_ptr<RenderTarget> Target) override;
    virtual void SetExpandableSize(Vec2i size);
    virtual void SetUnexpandedSize(Vec2i size);
    
    virtual bool IsExpanded() const;
    virtual void Expand();
    virtual void Contract();

  protected:
    virtual void OnExpanded();
    virtual void OnContracted();

    Vec2i m_ExpandableSize;
    Vec2i m_UnexpandedSize;
    bool  m_IsExpanded;
  };

}

#endif // SFEDITOR_EXPANDABLE_H
