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
#include <UI/Screen.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{

  Screen::Screen()
  {

  }

  void Screen::OnKilled()
  {
  }

  void Screen::OnCreated()
  {
  }

  void Screen::OnHover()
  {
  }

  void Screen::OnEnter(Vec2i where)
  {
  }

  void Screen::OnExit(Vec2i where)
  {
  }

  void Screen::AddedTo(Screen * Scr)
  {
  }

  void Screen::Initialize()
  {
  }

  void Screen::Cleanup()
  {
  }

  Screen::~Screen()
  {
  }

  Screen::Ptr Screen::Create(std::shared_ptr<RenderTarget> Target)
  {
    Screen::Ptr screen(new Screen(Target));
    return screen;
  }

  WidgetRenderer * Screen::Renderer()
  {
    return nullptr;
  }

  sf::View Screen::View() const
  {
    return sf::View();
  }

  bool Screen::HandleEvent(sf::Event event)
  {
    return false;
  }

  void Screen::Hide()
  {
  }

  void Screen::Show()
  {
  }

  void Screen::Enable()
  {
  }

  void Screen::Disable()
  {
  }

  sf::IntRect Screen::Bounds() const
  {
    return sf::IntRect();
  }

  void Screen::SetPosition(const Vec2i & v)
  {
  }

  void Screen::SetSize(const Vec2i & v)
  {
  }

  Screen::Screen(std::shared_ptr<RenderTarget> Target)
  {

  }

  void Screen::Connect(std::string slot, bsig::signal<void(void)> ftn)
  {

  }

  void Screen::Connect(std::string slot, bsig::signal<void(Vec2i)> ftn)
  {

  }

  void Screen::Connect(std::string slot, bsig::signal<void(Vec2i, MouseButton)> ftn)
  {

  }

}
