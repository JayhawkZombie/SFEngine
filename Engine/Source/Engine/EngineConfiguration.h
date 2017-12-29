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

#include <bitset>

#include "BasicIncludes.h"

struct Config
{
  /**
  * Settings pulled from ini file
  * Variable naming
  * <Category>_<type><Name>
  * ex: Diagnostc_bDisplayFrameStats
  * Category - Diagnostic, type = b (bool), Name = DisplayFrameStats
  */

  //Diagnostic ini settings
  bool           Diagnostic_bDisplayFrameStats; //Whether to display the FPS/Timing counter in the corner
  bool           Diagnostic_bBenchmarkShaders;  //Whether to benchmark increase in rendering times due to using shaders, can identify slow pipelines
  unsigned int   Diagnostic_uiLogLevel;         //How high of log levels to log
  std::string    Diagnostic_strDiagnosticFont;  //Font to use for rendered text

                                                //Render ini settings
  bool               Render_bVsyncEnabled;
  bool               Render_bUseRenderTexture;
  bool               Render_bTextureSmoothingEnabled;
  unsigned int       Render_uiAALevel;
  bool               Render_bShadersEnabled;

  //Timing ini settings
  float              Timing_fMinTick;
  float              Timing_fMaxTick;

  //Window ini settings
  sf::Vector2f       Window_v2fWindowSize;
  bool               Window_bFullscreen;
  bool               Window_bShowSplashScreen;
  bool               Window_bPlaySplashScreenAudio;
  UINT32             Window_uiDepthBits;
  UINT32             Window_uiStencilBits;

  //Effects ini settings
  bool              Effects_bPostProcessEnabled;
  UINT32            Effects_uiMaxNumParticles;
  std::vector<std::string> Effects_strShaderPath; //Vector of paths to shaders
  std::vector<std::string> Effects_strShader;     //Vector of the names of the shaders
};
