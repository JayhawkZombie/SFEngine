#ifndef SFEDITOR_SCREEN_H
#define SFEDITOR_SCREEN_H

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

  class Screen : public GenericContainer
  {
  public:
    PTR_TYPEDEF(Screen);
    ~Screen() override;
    
    static Screen::Ptr Create(std::shared_ptr<RenderTarget> Target, Vec2i Size, Widget *parent);
    void Render(std::shared_ptr<RenderTarget> Target) override final;
    void Update() override;
    bool HandleEvent(const UserEvent &event) override final;
    sf::IntRect Bounds() const override final;
    Vec2i GetChildOffset() const override;

    virtual bool Add(Widget::Ptr widget, std::string ID = "") override;
    virtual bool Remove(Widget::Ptr widget) override;
    virtual bool Remove(std::string ID) override;
    virtual bool RemoveAll() override;
    virtual bool HideAll() override;
    virtual bool ShowAll() override;
    virtual std::shared_ptr<sf::RenderWindow> GetWindow() const override;
    virtual void Destroy();
    void SetFont(std::shared_ptr<sf::Font> Font) override;
    virtual void SetWindow(std::shared_ptr<sf::RenderWindow> Win);
  protected:
    Screen(std::shared_ptr<RenderTarget> Target);
    Screen();

    virtual bool HandleMousePress(const UserEvent &event) override;
    virtual bool HandleMouseRelease(const UserEvent &event) override;
    virtual bool HandleMouseMovement(const UserEvent &event) override;
    virtual bool HandleKeyPressed(const UserEvent &event) override;
    virtual bool HandleKeyReleased(const UserEvent &event) override;
    virtual bool HandleTextEntered(const UserEvent &event) override;

    void AddedTo(Screen *Scr) override final;
    void Initialize() override final;
    void Cleanup() override final;

    sf::Text m_TestText;
    sf::Text m_EventText;
    std::shared_ptr<sf::Font> m_Font;
    std::shared_ptr<sf::RenderWindow> m_Window;
  };

}

#endif // SFEDITOR_SCREEN_H