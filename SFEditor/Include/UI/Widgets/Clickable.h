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
    virtual WidgetRenderer* Renderer() override = 0;
    virtual sf::View View() const override;

    virtual bool HandleEvent(sf::Event event) override = 0;
    virtual sf::IntRect Bounds() const override;

    virtual void Connect(std::string slot, bsig::signal<void(void)> ftn) override;
    virtual void Connect(std::string slot, bsig::signal<void(Vec2i)> ftn) override;
    virtual void Connect(std::string slot, bsig::signal<void(Vec2i, MouseButton)> ftn) override;

    enum
    {
      Rest = 0b0001,
      Hovered = 0b0010,
      Pressed = 0b0100
    };

    int ClickState() const;

  protected:
    Clickable();
    virtual ~Clickable() override;

    virtual void OnKilled() override = 0;
    virtual void OnCreated() override = 0;
    virtual void OnHover() override = 0;
    virtual void OnEnter(Vec2i where) override = 0;
    virtual void OnExit(Vec2i where) override = 0;
    virtual void AddedTo(Screen *Scr) override = 0;
    virtual void Initialize() override = 0;
    virtual void Cleanup() override = 0;

    //Additions for clickable items
    bsig::signal<void(Vec2i, MouseButton)> Clicked;
    int m_ClickState = Rest;
  };

}

#endif // SFEDITOR_CLICKABLE_H