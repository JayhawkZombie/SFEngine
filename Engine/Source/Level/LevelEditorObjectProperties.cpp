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

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_internal.h"

namespace Engine
{

  void BasicLevel::ShowObjectProperties(std::shared_ptr<Engine::LevelObject> Object)
  {
    static sf::Vector2f __Position = { 0.f, 0.f };
    static sf::Vector2f __Size = { 0.f, 0.f };
    static sf::Vector2f __PDelta;
    static float __Rotation = 0.f;
    
    static float __DragLowSpeed  = 0.5f;
    static float __DragHighSpeed = 10.f;

    __Position.x = Object->Position.x;
    __Position.y = Object->Position.y;

    __Size.x = Object->Size.x;
    __Size.y = Object->Size.y;

    ImGui::Text("Position("); ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("X:##Position_x", &Object->Position.x, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("Y:##Position_y", &Object->Position.y, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); ImGui::Text(")");
    ImGui::NewLine();
    
    ImGui::Text("Size("); ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("X:##Size_x", &Object->Size.x, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); 
    ImGui::PushItemWidth(80.f); ImGui::InputFloat("Y:##Size_y", &Object->Size.y, __DragLowSpeed, __DragHighSpeed); ImGui::PopItemWidth();
    ImGui::SameLine(); ImGui::Text(")");

    ImGui::NewLine();
    ImGui::InputFloat("Rotation:", &__Rotation, 1.f, 10.f);

    __PDelta = Object->Position - __Position;
    Object->Move(__PDelta);

  }

}
