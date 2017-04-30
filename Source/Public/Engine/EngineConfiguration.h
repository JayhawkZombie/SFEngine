#ifndef SFEngine_EngineConfiguration_H
#define SFEngine_EngineConfiguration_H

////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// Copyright(c) 2017 Austin Bailey
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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        EngineConfiguration                           */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{

  struct EngineConfig
  {
    /**
    * Settings pulled from ini file
    * Variable naming
    * <Category>_<type><Name>
    * ex: Diagnostc_bDisplayFrameStats
    * Category - Diagnostic, type = b (bool), Name = DisplayFrameStats
    */

    //Diagnostic ini settings
    bool           DisplayFrameStats = false; //Whether to display the FPS/Timing counter in the corner
    bool           BenchmarkShaders = false;  //Whether to benchmark increase in rendering times due to using shaders, can identify slow pipelines
    unsigned int   LogLevel = 1;         //How high of log levels to log
    std::string    DiagnosticFont = "";  //Font to use for rendered text

                                                  //Render ini settings
    bool               VsyncEnabled = false;
    bool               UseRenderTexture = true;
    bool               TextureSmoothingEnabled = true;
    unsigned int       AALevel = 8;
    bool               ShadersEnabled = true;

    //Timing ini settings
    float              MinTick = 0.f;
    float              MaxTick = 33.33f;

    //Window ini settings
    sf::Vector2u       WindowSize = SVector2U(1700, 900);
    SString            WindowTitle = "SFEngine";
    bool               ShowCloseButton = true;
    bool               Resizable = true;
    bool               HasTitlebar = true;
    bool               Fullscreen = false;
    bool               ShowSplashScreen = true;
    sf::Vector2u       SplashScreenSize = SVector2U(0, 0);
    SString            SplashScreenTexturePath = "";
    bool               PlaySplashScreenAudio = true;
    UINT32             DepthBits;
    UINT32             StencilBits;

    //Effects ini settings
    bool              PostProcessEnabled = true;
    UINT32            MaxNumParticles;
    std::vector<std::string> ShaderPath; //Vector of paths to shaders
    std::vector<std::string> Shader;     //Vector of the names of the shaders
    sf::Uint32 Style = sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar;

    sf::ContextSettings __context_settings = sf::ContextSettings(0, 0, 8, 3, 2, sf::ContextSettings::Default, false);
  };

}

#endif // SFEngine_EngineConfiguration_H
