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

#include "Engine\ScriptConsole.h"

namespace Engine
{

  ScriptConsole::ScriptConsole(const sf::Vector2f & Size, const sf::Vector2f & Position, tgui::Theme::Ptr themepotr)
  {
    Theme = themepotr; //lol

    Panel = Theme->load("Panel");
    Panel->setSize(Size);
    Panel->setPosition(Position);
    Panel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0));

    sf::Vector2f consoleSize = { Size.x, Size.y - 50 };

    Console = Theme->load("ChatBox");
    Console->setTextColor(ConsoleInputColor);
    Console->setLineLimit(100);
    Console->setSize(consoleSize);
    Console->setTextSize(10);

    tgui::Scrollbar::Ptr scroller = Theme->load("ScrollBar");
    scroller->setSize({ 15, consoleSize.y });
    scroller->setPosition({ consoleSize.x - 15, 0 });
    Console->setScrollbar(scroller);

    Console->addLine("# chai", sf::Color(242, 83, 9));

    Input = Theme->load("EditBox");
    Input->setDefaultText("Console Command");
    Input->setTextSize(12);
    Input->setSize({ Size.x - 10 - 110, 20 });
    Input->setPosition({ 10, Size.y - 30 });

    Input->connect("ReturnKeyPressed", [this](std::string str) { this->IssueInput(str); });

    CommandButton = Theme->load("Button");
    CommandButton->setText("OK");
    CommandButton->setSize({ 100, 20 });
    CommandButton->setPosition({ Size.x - 110, Size.y - 30 });
    CommandButton->connect("Clicked", [this]() { std::string str = Input->getText();  this->IssueInput(str); });

    Panel->getRenderer()->setBackgroundColor(sf::Color(40, 40, 40, 40));
    Panel->getRenderer()->setBorderColor(sf::Color(100, 100, 100, 100));

    Panel->add(Console);
    Panel->add(Input);
    Panel->add(CommandButton);
    Panel->hide();
    GUI->add(Panel);
  }

  ScriptConsole::~ScriptConsole()
  {
  }

  void ScriptConsole::SetTheme(tgui::Theme::Ptr themeptr)
  {
    Theme = themeptr;
  }

  void ScriptConsole::Open()
  {
    SetKeyRepeatEnabled(true);
    Panel->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
    Panel->moveToFront();
  }

  void ScriptConsole::Close()
  {
    SetKeyRepeatEnabled(false);
    Panel->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
  }

  void ScriptConsole::SetInputCallback(std::function<void(std::string)> func)
  {
    InputCB = func;
  }

  void ScriptConsole::IssueResponse(std::string response)
  {
    Console->addLine(response, ConsoleOutputColor);
  }

  void ScriptConsole::AddToModule(chaiscript::ModulePtr module, const std::string &name)
  {
    //ScriptEngine->add(chaiscript::fun<void (ScriptConsole::*)()>(&ScriptConsole::Clear, this), "CClear");
    //ScriptEngine->add(chaiscript::fun<void (ScriptConsole::*)()>(&ScriptConsole::Close, this), "CClose");
    ScriptEngine->add(chaiscript::var(*this), name);
    ScriptEngine->add(chaiscript::fun([this](std::string str) {this->IssueResponse(str); }), "printLine");
    //module->add(chaiscript::fun<void (ScriptConsole::*)()>(&ScriptConsole::Close, this), "CClose");
    //module->add(chaiscript::fun<void (ScriptConsole::*)()>(&ScriptConsole::Clear, this), "CClear");
    //ScriptEngine->add(chaiscript::var(*this), "sConsole");
  }

  void ScriptConsole::BindMethods(chaiscript::ModulePtr module)
  {
    chaiscript::utility::add_class<Engine::ScriptConsole>(*module, "ScriptConsole",
    {},
    { {
        chaiscript::fun(static_cast<void(ScriptConsole::*)()>(&Engine::ScriptConsole::Clear)), "Clear" },
        { chaiscript::fun(static_cast<void(ScriptConsole::*)()>(&ScriptConsole::Open)), "Open" },
        { chaiscript::fun(static_cast<void(ScriptConsole::*)()>(&ScriptConsole::Close)), "Close"
      }
    });
  }

  void ScriptConsole::Clear()
  {
    Console->removeAllLines();
    Console->addLine("# chai", sf::Color(242, 83, 9));
  }

  void ScriptConsole::IssueInput(std::string input)
  {
    //Try to issue input to the registered callback
    Console->addLine("> " + input, ConsoleInputColor);
    try
    {
      if (InputCB)
        InputCB(input);
    }
    catch (chaiscript::exception::eval_error)
    {
      IssueResponse("Eval error : unrecognized command");
    }

    Input->setText("");
  }

}
