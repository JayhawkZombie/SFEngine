#pragma once

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

#include "Globals\GlobalHooks.h"

#include "chaiscript\chaiscript.hpp"
#include "chaiscript\utility\utility.hpp"
#include <TGUI\TGUI.hpp>

class ScriptConsole
{
public:
  ScriptConsole(const sf::Vector2f &Size, const sf::Vector2f &Position, tgui::Theme::Ptr themeptr);
  ~ScriptConsole();

  void SetTheme(tgui::Theme::Ptr themeptr);
  void Open();
  void Close();

  void SetInputCallback(std::function<void(std::string)> func);
  void IssueResponse(std::string response);

  void AddToModule(chaiscript::ModulePtr module, const std::string &name);
  static void BindMethods(chaiscript::ModulePtr module);
  void Clear();
protected:
  std::function<void(std::string)> InputCB;
  std::function<void(std::string)> ResponseCB;

  void IssueInput(std::string input);

  sf::Color ConsoleInputColor = sf::Color(109, 109, 109);
  sf::Color ConsoleOutputColor = sf::Color(72, 122, 140);
    
  tgui::Theme::Ptr Theme;
  tgui::Panel::Ptr Panel;
  tgui::ChatBox::Ptr Console;
  tgui::EditBox::Ptr Input;
  tgui::Button::Ptr CommandButton;
};
