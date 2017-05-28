#ifndef SFEDITOR_WINDOW_H
#define SFEDITOR_WINDOW_H

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
#include <UI/Widgets/Screen.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////
#include <boost/any.hpp>
#include <SFML\Graphics.hpp>

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////
#include <thread>
#include <mutex>

namespace SFUI
{

  class Window : public Widget
  {
  public:
    Window();
    Window(sf::RenderWindow *Win);
    ~Window() override;

    void Update() override;
    void Render(std::shared_ptr<RenderTarget>) override;
    void Render();
    void Add(Widget::Ptr widget, std::string ID = "");
    void Remove(std::string ID);
    void Remove(Widget::Ptr widget);
    void Close();
    void Open();
    void Hide() override;
    void Show() override;
    void SetWindow(sf::RenderWindow *Win);
    bool IsOpen() const;
    bool HandleEvent(const UserEvent &event);
    void SetFont(std::shared_ptr<sf::Font> Font);
    
  protected:

    void OnKilled() override final;
    void OnCreated() override final;
    void OnHover() override final;
    void OnEnter(Vec2i where) override final;
    void OnExit(Vec2i where) override final;
    void AddedTo(Screen *Scr) override final;
    void Initialize() override final;
    void Cleanup() override final;

    virtual bool HandleMousePress(const UserEvent &event) override final;
    virtual bool HandleMouseRelease(const UserEvent &event) override final;
    virtual bool HandleMouseMovement(const UserEvent &event) override final;
    virtual bool HandleKeyPressed(const UserEvent &event) override final;
    virtual bool HandleKeyReleased(const UserEvent &event) override final;
    virtual bool HandleTextEntered(const UserEvent &event) override final;
    
    std::shared_ptr<sf::Font> m_Font;
    Screen::Ptr m_Screen;
    sf::Sprite m_Sprite;
    std::shared_ptr<sf::RenderTexture> m_Texture;
    bool m_Open;
    bool m_Visible;
    sf::RenderWindow *m_Window;
    Widget::Ptr m_ConnectedWidget;
  };

}

#endif // SFEDITOR_WINDOW_H