#include <UI/Widgets/FlatButton.h>

void SFUI::FlatButton::SetText(const std::string & Text)
{
  m_Text = Text;
}

std::string SFUI::FlatButton::GetText() const
{
  return m_Text;
}
