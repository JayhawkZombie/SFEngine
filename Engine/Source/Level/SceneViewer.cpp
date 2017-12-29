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

#include "Level\BasicLevel.h"
#include "Level\LevelObject.h"

#ifdef WITH_EDITOR

namespace Engine
{

  void BasicLevel::ShowScene(std::shared_ptr<sf::RenderTexture> Texture)
  {

    //if (ImGui::Begin("Scene Viewer", NULL, ImGuiWindowFlags_MenuBar)) {

    //  if (ImGui::BeginMenuBar()) {
    //    if (ImGui::BeginMenu("Spawn")) {
    //      if (ImGui::MenuItem("Show Spawner")) {
    //      }

    //      ImGui::EndMenu();
    //    }

    //    if (ImGui::BeginMenu("Properties")) {

    //      ImGui::Checkbox("Physics", &DoUpdatePhysics);

    //      ImGui::EndMenu();
    //    }

    //    ImGui::EndMenuBar();
    //  }

    //  ImGui::Separator();

    //  if (ImGui::Button("Clear Objects")) {
    //    for (auto & obj : TestObjects)
    //      obj.reset();
    //    TestObjects.clear();
    //  }

    //  ImGui::Image(Texture->getTexture(), ImVec2(800, 800), sf::FloatRect({ 0, Size.y - 700.f, 800.f, 800.f }));

    //  ImGui::End(); //end Scene Viewer
    
  }

}
#endif //WITH_EDITOR
