#ifndef SFEDITOR_GENERICCONTAINER_H
#define SFEDITOR_GENERICCONTAINER_H

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
#include <UI/Widgets/Widget.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <vector>

namespace SFUI
{

  class GenericContainer : public Widget
  {
  public:
    GenericContainer();
    virtual ~GenericContainer() override;

    virtual void Update() override;
    virtual Vec2i GetChildOffset() const override;
    virtual bool Add(Widget::Ptr widget, std::string ID = "");
    virtual bool Remove(Widget::Ptr widget);
    virtual bool Remove(std::string ID);
    virtual bool RemoveAll();
    virtual bool HideAll();
    virtual bool ShowAll();
    virtual void SetSize(const Vec2i &v) override;
    virtual void SetPosition(const Vec2i &v) override;
    virtual void Move(const Vec2i &v) override;
    virtual bool HandleEvent(const UserEvent &event) override;

  protected:
    virtual bool HandleMousePress(const UserEvent &event) override;
    virtual bool HandleMouseRelease(const UserEvent &event) override;
    virtual bool HandleMouseMovement(const UserEvent &event) override;
    virtual bool HandleKeyPressed(const UserEvent &event) override;
    virtual bool HandleKeyReleased(const UserEvent &event) override;
    virtual bool HandleTextEntered(const UserEvent &event) override;

    std::map<std::string, Widget::Ptr> m_Widgets;
    std::shared_ptr<sf::RenderTexture> m_Canvas;
    sf::Sprite m_Sprite;
    bool m_SizeSet;
    Vec2i m_GlobalOffset = Vec2i(0, 0);
  };

}

#endif // SFEDITOR_GENERICCONTAINER_H
