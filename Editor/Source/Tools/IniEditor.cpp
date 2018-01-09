#ifdef WITH_EDITOR

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

#include "Editor/Source/Tools.h"
#include "Engine/Source/Parsing/IniParser.h"

struct IniValueMapBuf
{
  std::string SectionString;

  std::vector<std::pair<std::string, std::array<char, 150>>> InputBufs;
};

void ShowIniEditor()
{
  static char filename[256] = "Engine.ini";
  static IniParser parser;
  
  static std::unordered_map<std::string, IniValueMapBuf> parser_value_bufs;

  if (ImGui::Begin("IniEditor"))
  {
    ImGui::Indent();

    ImGui::InputText("File:", filename, 256);

    ImGui::SameLine();

    if (ImGui::Button("Load"))
    {
      std::string file(filename);
      parser.Parse(file);

      parser_value_bufs.clear();

      /* Load settings into value buffers */
      const auto &val_map = parser.GetValueMap();

      for (const auto & section : val_map)
      {
        parser_value_bufs[section.first] = {};

        /* Copy values over into their buffers */
        const auto & values = section.second;
        IniValueMapBuf &parser_buf = parser_value_bufs[section.first];

        parser_buf.SectionString = section.first;
        parser_buf.InputBufs.resize(values.size());

        std::size_t i = 0;
        for (const auto & val_pair : section.second)
        {
          parser_buf.InputBufs[i].first = val_pair.first;

          /* Ugh */
          strcpy_s(parser_buf.InputBufs[i].second.data(), 150, val_pair.second.c_str());
          ++i;
        }

      } // for (const auto & section : val_map)

    } // Button("Load")

    ImGui::Separator();

    /* Show collapsible header for each section */
    for (const auto & section : parser_value_bufs)
    {
      ImGui::Indent();

      if (ImGui::TreeNode(section.first.c_str()))
      {
        ImGui::Indent();

        const IniValueMapBuf &IniMapBuf = section.second;
        ImGui::Columns(2);

        ImGui::Text("Key"); ImGui::NextColumn();
        ImGui::Text("Value"); ImGui::NextColumn();

        ImGui::Separator();

        for (auto & key_vals : IniMapBuf.InputBufs)        
        {

          ImGui::Text("%s", key_vals.first.c_str());
          ImGui::NextColumn();
          ImGui::Text("%s", ( char * ) key_vals.second.data());
          ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::TreePop();
        ImGui::Unindent();
      } // if (CollapsingHeader)

      ImGui::Unindent();
    } // for (section : parser_value_bufs)

    ImGui::Separator();

    if (ImGui::Button("Save"))
    {
      //Save to file

      std::ofstream ofile(filename);
      if (!ofile)
        return;

      for (const auto & section : parser_value_bufs)
      {

        ofile << "[" << section.first << "]\n";

        const IniValueMapBuf &ValMap = section.second;

        for (const auto & val_pair : ValMap.InputBufs)
        {
          ofile << val_pair.first << "=" << std::string(val_pair.second.data()) << "\n";
        }
      }

      ofile.close();

    } //Button("Save")

    ImGui::Unindent();
    ImGui::End();
  } //ShowIniEditor

}

#endif
