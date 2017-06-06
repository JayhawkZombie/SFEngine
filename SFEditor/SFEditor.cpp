// SFEditor.cpp : Defines the entry point for the console application.
//

#include <UI/SFUI.h>

#include <iostream>

int main()
{

  std::shared_ptr<sf::RenderWindow> Window = 
    std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 800), "SFEditor", sf::Style::Default);

  SFUI::Screen::Ptr Screen = SFUI::Screen::Create(Window, Vec2i(Window->getSize()), nullptr);
  Screen->SetWindow(Window);
  Window->setVerticalSyncEnabled(true);

  std::shared_ptr<sf::Font> Font = std::make_shared<sf::Font>();
  system("dir");
  if (!Font->loadFromFile("../Raleway-Light.ttf")) {
    std::cerr << "Unable to load font" << std::endl;
    return -1;
  }

  Screen->SetFont(Font);
  bool closed = false;
  sf::Event event;
  


  SFUI::FlatButton::Ptr button = SFUI::FlatButton::Create(nullptr, nullptr);
  button->SetFont(Font);
  button->SetText("TestButton");
  button->SetTextColorNormal(sf::Color(71, 85, 107));
  button->SetTextColorHovered(sf::Color(155, 155, 155));
  button->SetTextColorPressed(sf::Color(96, 96, 96));
  button->SetTextSize(32);
  button->SetPosition(Vec2i(400, 400));
  button->SetSize(Vec2i(200, 45));
  button->SetLabelAlignment(SFUI::Alignment::Centered);


  SFUI::SolidButton::Ptr sbutton = SFUI::SolidButton::Create(nullptr, nullptr);
  sbutton->SetFont(Font);
  sbutton->SetText("SolidButton");
  sbutton->SetTextColorNormal(sf::Color::Black);
  sbutton->SetTextColorHovered(sf::Color::Black);
  sbutton->SetTextColorPressed(sf::Color::White);
  sbutton->SetTextSize(32);
  sbutton->SetPosition(Vec2i(200, 100));
  sbutton->SetSize(Vec2i(200, 45));
  sbutton->SetLabelAlignment(SFUI::Alignment::Centered);
  sbutton->SetBackgroundColorNormal(sf::Color(49, 61, 81));
  sbutton->SetBackgroundColorHighlighted(sf::Color(49, 79, 104));
  sbutton->SetBackgroundColorPressed(sf::Color(35, 44, 58));

  SFUI::ExpandableList::Ptr list = SFUI::ExpandableList::Create(nullptr, 20);
  list->SetExpandableSize(Vec2i(100, 500));
  list->SetUnexpandedSize(Vec2i(100, 100));
  list->SetSize(Vec2i(100, 500));
  list->SetBackgroundColor(sf::Color(48, 48, 48));
  list->SetBackgroundOutlineColor(sf::Color(109, 109, 109));
  list->SetBackgroundOutlineThickness(-2);
  list->SetPosition(Vec2i(200, 200));
  list->Expand();

  sbutton->Connect("clicked",
    [list](SFUI::Vec2i where, SFUI::MouseButton btn)
    {
      if (list->IsExpanded())
        list->Contract();
      else
        list->Expand();
    }
  );

  SFUI::SolidButton::Ptr sbutton2 = SFUI::SolidButton::Create(nullptr, nullptr);
  sbutton2->SetFont(Font);
  sbutton2->SetText("btn");
  sbutton2->SetTextColorNormal(sf::Color::Black);
  sbutton2->SetTextColorHovered(sf::Color::Black);
  sbutton2->SetTextColorPressed(sf::Color::White);
  sbutton2->SetTextSize(22);
  sbutton2->SetPosition(Vec2i(0, 0));
  sbutton2->SetSize(Vec2i(100, 45));
  sbutton2->SetLabelAlignment(SFUI::Alignment::Centered);
  sbutton2->SetBackgroundColorNormal(sf::Color(49, 61, 81));
  sbutton2->SetBackgroundColorHighlighted(sf::Color(49, 79, 104));
  sbutton2->SetBackgroundColorPressed(sf::Color(35, 44, 58));

  list->Add(sbutton2, "InsideButton");

  Screen->Add(sbutton, "SolidButton");
  Screen->Add(button, "TestButtonLongLongText");
  Screen->Add(list, "TestList");
  
  
  for ( ; ; ) {
    if (closed)
      break;

    while (Window->pollEvent(event)) {
      SFUI::UserEvent evnt(event, Window.get());

      Screen->HandleEvent(evnt);
      closed = closed || ( event.type == sf::Event::Closed );
    }

    if (closed)
      break;

    Screen->Update();

    Window->clear(sf::Color::Black);
    Screen->Render(Window);
    Window->display();
  }

  Screen->Destroy();
  Window->close();
  return 0;
}

