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
#include <UI/Widgets/Widget.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  class Screen : public Widget
  {
  public:
    PTR_TYPEDEF(Screen);
    ~Screen() override;
    
    Screen::Ptr Create(std::shared_ptr<RenderTarget> Target);
    WidgetRenderer* Renderer() override final;
    sf::View View() const override final;

    bool HandleEvent(sf::Event event) override final;
    void Hide() override final;
    void Show() override final;
    void Enable() override final;
    void Disable() override final;
    sf::IntRect Bounds() const override final;
    void SetPosition(const Vec2i &v) override final;
    void SetSize(const Vec2i &v) override final;

    void Connect(std::string slot, bsig::signal<void(void)> ftn) override final;
    void Connect(std::string slot, bsig::signal<void(Vec2i)> ftn) override final;
    void Connect(std::string slot, bsig::signal<void(Vec2i, MouseButton)> ftn) override final;

  protected:
    Screen(std::shared_ptr<RenderTarget> Target);
    Screen();

    void OnKilled() override final;
    void OnCreated() override final;
    void OnHover() override final;
    void OnEnter(Vec2i where) override final;
    void OnExit(Vec2i where) override final;
    void AddedTo(Screen *Scr) override final;
    void Initialize() override final;
    void Cleanup() override final;
  };

}

#endif // SFEDITOR_SCREEN_H