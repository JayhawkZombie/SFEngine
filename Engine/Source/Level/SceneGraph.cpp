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

void ShowWaveOptions(waveSeg *wave)
{
  ImGui::Text("Settings");
  ImGui::Separator();
  ImGui::DragFloat("Gravity", &wave->grav_N, 0.01f, 0.f, 10.f);
  ImGui::DragFloat("Amp left", &wave->Amp_wvLt, 5.f, 0.f, 50.f);
  ImGui::DragFloat("Amp right", &wave->Amp_wvRt, 5.f, 0.f, 50.f);

  ImGui::DragFloat("K left", &wave->K_wvLt, 0.01f, 0.f, 1.f);
  ImGui::DragFloat("K right", &wave->K_wvRt, 0.01f, 0.f, 1.f);

  ImGui::DragFloat("Freq left", &wave->rotFreqLt, 0.0005f, 0.f, 0.05f);
  ImGui::DragFloat("Freq right", &wave->rotFreqRt, 0.0005f, 0.f, 0.05f);

  ImGui::InputFloat("Elevation", &wave->Elev, 5.f, 15.f);
  ImGui::InputFloat("Depth", &wave->Depth, 5.f, 15.f);
  ImGui::InputFloat("Air Density", &wave->airDensity, 0.00005f, 0.0001f);
  ImGui::InputFloat("Fluid Density", &wave->fluidDensity, 0.005f, 0.001f);

  ImGui::Checkbox("IsHard", &wave->is_hard);
}

#endif
