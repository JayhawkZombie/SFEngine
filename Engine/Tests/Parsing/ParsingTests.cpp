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

#include "ParsingTests.h"

#include "Parsing/IniParser.h"

void RunParsingTests()
{
  IniParser parser;

  parser.Parse("ParseTest.ini");

  auto winSize = parser.TryGetValue("Window", "WindowSize");
  auto winTitle = parser.TryGetValue("Window", "WindowTitle");
  auto grapApi = parser.TryGetValue("Graphics", "API");
  auto graphVersion = parser.TryGetValue("Graphics", "Version");
  auto graphShadQual = parser.TryGetValue("Graphics", "ShadowQuality");
  auto graphLghtQual = parser.TryGetValue("Graphics", "LightingQuality");
  auto ptclMax = parser.TryGetValue("Particles", "MaxParticles");

  if (winSize.has_value())
  {
    std::cout << "Window.WindowSize = " << *winSize << "\n";
  }


  if (winTitle.has_value())
  {
    std::cout << "Window.WindowTitle = " << *winTitle << "\n";
  }


  if (grapApi.has_value())
  {
    std::cout << "Graphics.API = " << *grapApi << "\n";
  }

  if (graphVersion.has_value())
  {
    std::cout << "Graphics.Version = " << *graphVersion << "\n";
  }

  if (graphShadQual.has_value())
  {
    std::cout << "Graphics.ShadowQuality = " << *graphShadQual << "\n";
  }

  if (graphLghtQual.has_value())
  {
    std::cout << "Graphics.LightingQuality = " << *graphLghtQual << "\n";
  }

  if (ptclMax.has_value())
  {
    std::cout << "Particles.MaxParticles = " << *ptclMax << "\n";
  }

}
