#ifndef SFEDITOR_CLICKABLE_H
#define SFEDITOR_CLICKABLE_H

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

namespace SFUI
{

  class Clickable : public Widget
  {
  public:
    PTR_TYPEDEF(Clickable);

    bool HandleEvent(const UserEvent &event) override final;

    enum
    {
      Rest    = 0b00100000,
      Hovered = 0b01000000,
      Pressed = 0b10000000
    };

    int ClickState() const;

  protected:
    Clickable();
    virtual ~Clickable() override;

    std::function<void(Vec2i, MouseButton)> OnClickedCallback;

    virtual void OnClicked();

    virtual void OnKilled() override;
    virtual void OnCreated() override;
    virtual void OnHover(Vec2i where) override = 0;
    virtual void OnEnter(Vec2i where) override = 0;
    virtual void OnExit(Vec2i where) override = 0;
    virtual void OnPressed(Vec2i where) override = 0;
    virtual void OnReleased(Vec2i where) override = 0;
    virtual void AddedTo(Screen *Scr) override;
    virtual void Initialize() override;
    virtual void Cleanup() override;

    virtual bool HandleMouseMovement(const UserEvent &event) override;
    virtual bool HandleMousePress(const UserEvent &event) override;
    virtual bool HandleMouseRelease(const UserEvent &event) override;
    virtual bool HandleKeyPressed(const UserEvent &event) override;
    virtual bool HandleKeyReleased(const UserEvent &event) override;
    virtual bool HandleTextEntered(const UserEvent &event) override;

    //Additions for clickable items
    bsig::signal<void(Vec2i, MouseButton)> Clicked;
    int m_ClickState = Rest;
  };

}

#endif // SFEDITOR_CLICKABLE_H