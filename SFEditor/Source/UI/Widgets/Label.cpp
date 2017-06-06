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
#include <UI/Widgets/Label.h>

////////////////////////////////////////////////////////////
// Dependency Headers
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Standard Library Headers
////////////////////////////////////////////////////////////

namespace SFUI
{



  Label::Label()
  {
    m_RenderText.setString("default");
  }

  Label::~Label()
  {
    
  }

  Label::Ptr Label::Create(const std::string & Text, Widget::RPtr parent)
  {
    Label::Ptr label = std::make_shared<Label>();
    label->m_Parent = parent;
    if (parent)
      label->SetSize(parent->GetSize());
    label->SetText(Text);
    return label;
  }

  void Label::Render(std::shared_ptr<RenderTarget> Target)
  {
    Target->draw(m_RenderText);
  }

  void Label::SetFont(std::shared_ptr<sf::Font> Font)
  {
    m_Font = Font;
    m_RenderText.setFont(*Font);
  }

  void Label::SetText(const std::string &Text)
  {
    m_Text = Text;
    m_RenderText.setString(Text);
    Resize();
  }

  void Label::SetTextSize(std::uint32_t size)
  {
    m_RenderText.setCharacterSize(size);
    Resize();
  }

  void Label::SetTextColor(sf::Color color)
  {
    m_TextColor = color;
    m_RenderText.setFillColor(color);
  }

  void Label::AlignInBounds(sf::IntRect bounds, Alignment alignment)
  {
    Widget::AlignInBounds(bounds, alignment);
    m_RenderText.setPosition(static_cast<sf::Vector2f>(m_Position));
  }

  std::string Label::GetText() const
  {
    return m_Text;
  }

  void Label::Resize()
  {
    auto vec2 = m_RenderText.getGlobalBounds();
    SetSize(Vec2i(
      static_cast<int>( floor(vec2.width) ),
      static_cast<int>( floor(vec2.height) )
    ));
  }

  void Label::OnKilled()
  {

  }

  void Label::OnCreated()
  {

  }

  void Label::OnHover(Vec2i where)
  {
    
  }

  void Label::OnEnter(Vec2i where)
  {

  }

  void Label::OnExit(Vec2i where)
  {

  }

  void Label::AddedTo(Screen *Scr)
  {

  }

  void Label::Initialize()
  {

  }

  void Label::Cleanup()
  {

  }

  bool Label::HandleMousePress(const UserEvent &event)
  {
    return false;
  }

  bool Label::HandleMouseRelease(const UserEvent &event)
  {
    return false;
  }

  bool Label::HandleMouseMovement(const UserEvent &event)
  {
    return false;
  }

  bool Label::HandleKeyPressed(const UserEvent &event)
  {
    return false;
  }

  bool Label::HandleKeyReleased(const UserEvent &event)
  {
    return false;
  }

  bool Label::HandleTextEntered(const UserEvent &event)
  {
    return false;
  }

}
