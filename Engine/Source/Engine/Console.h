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

#include "BasicIncludes.h"

#include "IMGUI\imgui_internal.h"

class Console
{
  ImVector<char *> Items;
  char InputBuff[1000] = { 0 };
  bool ScrollToBottom = false;

public:
  sf::Vector2f Size;

  static void ShowDebugConsole(bool *p_open) {
    static Console console;
    console.Render("Debug Console", p_open);
  }

  Console() {
    ClearConsole();
    memset(InputBuff, 0, 1000);
    AddLog("-Debug Console");
  }

  ~Console() {
    ClearConsole();
  }

  static char *Strdup(const char * str) {
    size_t len = strlen(str) + 1;
    void * buff = malloc(len);
    return (char *)memcpy(buff, (const void *)str, len);
  }

  void ClearConsole() {
    for (auto & i : Items)
      free(i);
    Items.clear();
  }

  void AddLog(const char *fmt, ...) IM_PRINTFARGS(2)
  {
    char buf[1000];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    Items.push_back(Strdup(buf));
    ScrollToBottom = true;
  }

  int TextEditCallback(ImGuiTextEditCallbackData* data)
  {
    return 0; //for now
  }

  static int TextEditCallbackStub(ImGuiTextEditCallbackData* data)
  {
    Console* console = (Console*)data->UserData;
    return console->TextEditCallback(data);
  }

  void ExecCommand(const char* command_line)
  {
    if (strcmp(command_line, "alert") == 0)
      MessageAlert("test alert");

    AddLog(command_line);
  }

  void Render(const char *title, bool *p_open)
  {
    ImGui::SetNextWindowSize(Size, ImGuiSetCond_FirstUseEver);
    if (!ImGui::Begin(title, p_open)) {
      ImGui::End();
      return;
    }

    ImGui::TextWrapped("Console. Enter text to display it in the console window");

    if (ImGui::SmallButton("Clear"))
      ClearConsole();
    if (ImGui::SmallButton("Scroll to bottom"))
      ScrollToBottom = true;
    ImGui::Separator();

    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::BeginPopupContextWindow()) {
      if (ImGui::Selectable("Clear"))
        ClearConsole();
      ImGui::EndPopup();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
    for (int i = 0; i < Items.Size; ++i) {
      const char *item = Items[i];
      ImVec4 col = ImVec4(1.f, 1.f, 1.f, 1.f);
      ImGui::PushStyleColor(ImGuiCol_Text, col);
      ImGui::TextUnformatted(item);
      ImGui::PopStyleColor();
    }
    ImGui::PopStyleVar();
    if (ScrollToBottom)
      ImGui::SetScrollHere();
    ScrollToBottom = false;
    ImGui::EndChild();
    ImGui::Separator();

    //command-line input
    if (ImGui::InputText("Input", InputBuff, IM_ARRAYSIZE(InputBuff), ImGuiInputTextFlags_EnterReturnsTrue, &Console::TextEditCallbackStub, (void *)this)) {
      char *input_end = InputBuff + strlen(InputBuff);
      while (input_end > InputBuff && input_end[-1] == ' ')
        input_end--;
      *input_end = 0;
      if (InputBuff[0])
        ExecCommand(InputBuff);
      strcpy(InputBuff, "");
      
      
      if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))) {
        ImGui::SetKeyboardFocusHere(-1);
      }
    }
    
    ImGui::End();
  }
};
