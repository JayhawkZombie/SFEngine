#ifndef SFEDITOR_SOLIDBUTTON_H
#define SFEDITOR_SOLIDBUTTON_H

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
#include <UI/Widgets/FlatButton.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  class SolidButton : public FlatButton
  {
  public:
    PTR_TYPEDEF(SolidButton);

    SolidButton(Widget *parent = nullptr, std::shared_ptr<Label> label = nullptr);
    virtual ~SolidButton() override;
    virtual void Update() override;
    virtual void Render(std::shared_ptr<RenderTarget> Target) override;
    static SolidButton::Ptr Create(Widget *parent = nullptr, std::shared_ptr<Label> label = nullptr);
    virtual void SetSize(const Vec2i &v) override;
    virtual void SetPosition(const Vec2i &v) override;
    virtual void SetBackgroundColorNormal(const sf::Color &color);
    virtual void SetBackgroundColorHighlighted(const sf::Color &color);
    virtual void SetBackgroundColorPressed(const sf::Color &color);

  protected:
    virtual void OnHover() override;
    virtual void OnEnter(Vec2i where) override;
    virtual void OnExit(Vec2i where) override;

    virtual bool HandleMousePress(const UserEvent &event) override;
    virtual bool HandleMouseRelease(const UserEvent &event) override;
    virtual bool HandleMouseMovement(const UserEvent &event) override;
    virtual bool HandleKeyPressed(const UserEvent &event) override;
    virtual bool HandleKeyReleased(const UserEvent &event) override;
    virtual bool HandleTextEntered(const UserEvent &event) override;

    sf::RectangleShape m_BGShape;
    sf::Color m_BGColorNormal;
    sf::Color m_BGColorHighlighted;
    sf::Color m_BGColorPressed;
  };

}

#endif // SFEDITOR_SOLIDBUTTON_H
