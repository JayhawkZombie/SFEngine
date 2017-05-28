#ifndef SFEDITOR_FLATBUTTON_H
#define SFEDITOR_FLATBUTTON_H

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
#include <UI/Widgets/Clickable.h>
#include <UI/Widgets/Label.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  class FlatButton : public Clickable
  {
  public:
    PTR_TYPEDEF(FlatButton);
    virtual ~FlatButton() override;
    FlatButton();
    FlatButton(Widget *parent, std::shared_ptr<Label> label = nullptr);
    friend class FlatButtonRenderer;

    static FlatButton::Ptr Create(Widget *parent, std::shared_ptr<Label> label = nullptr);

    virtual void Render(std::shared_ptr<RenderTarget> Target) override;
    virtual void Update() override;
    virtual void SetFont(std::shared_ptr<sf::Font> Font) override;
    virtual void SetText(const std::string &Text);
    virtual void SetTextSize(std::uint32_t size);
    virtual void SetTextColorNormal(sf::Color color);
    virtual void SetTextColorHovered(sf::Color color);
    virtual void SetTextColorPressed(sf::Color color);
    std::string  GetText() const;
    virtual void SetLabelAlignment(Alignment alignment);
    virtual void SetLabelAlignment(VerticalAlignment vAlignment, HorizontalAlignment hAlignment);

    virtual void Connect(std::string slot, std::function<void(Vec2i, MouseButton)> ftn) override;
  protected:

    virtual void OnKilled() override;
    virtual void OnCreated() override;
    virtual void OnHover() override;
    virtual void OnEnter(Vec2i where) override;
    virtual void OnExit(Vec2i where) override;
    virtual void AddedTo(Screen *Scr) override;
    virtual void Initialize() override;
    virtual void Cleanup() override;

    virtual bool HandleMousePress(const UserEvent &event) override;
    virtual bool HandleMouseRelease(const UserEvent &event) override;
    virtual bool HandleMouseMovement(const UserEvent &event) override;
    virtual bool HandleKeyPressed(const UserEvent &event) override;
    virtual bool HandleKeyReleased(const UserEvent &event) override;
    virtual bool HandleTextEntered(const UserEvent &event) override;

    std::uint32_t m_LabelAlignment;
    Label::Ptr m_Label;
    unsigned int m_LabelTextSize;
    bool m_Hovered = false;
    sf::Color m_TextColorNormal;
    sf::Color m_TextColorHighlighted;
    sf::Color m_TextColorPressed;
  };

}

#endif // SFEDITOR_FLATBUTTON_H