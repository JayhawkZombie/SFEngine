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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "Globals.h"

#include "ApplicationEntry\MainEntryPoint.h"
#include "Manager\EditorManager.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <boost\program_options\cmdline.hpp>
#include <boost\program_options\options_description.hpp>
#include <boost\program_options.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        MainEntryPoint                                */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: (Name) - 2017/05/08                                       */
/************************************************************************/

namespace p_ops = boost::program_options;

namespace SFEngine
{
  boost::program_options::options_description MainEntry::PgmOptions;
  boost::program_options::variables_map MainEntry::ParsedOptions;

  UINT32 MainEntry::Launch(int argc, char ** argv)
  {
    //AddCmdDescriptions();
    //ParseCmdOptions(argc, argv);

#if defined( SF_EDITOR )
    return EditorManager::Launch(PgmOptions, ParsedOptions);
#else
    SFEngine::EngineConfig Config;
    Config.WindowSize = SVector2U(1700, 900);
    Config.ShowSplashScreen = true;
    Config.SplashScreenTexturePath = "./Demos/MainMenu/Assets/Textures/SFEngineLogoLarge.png";
    return SFEngine::Engine::Go(argc, argv, Config);
#endif
  }

  void MainEntry::AddCmdDescriptions()
  {
    PgmOptions.add_options()
      ("help", "see help message")
      ("low-power", "launch in low power mode")
      ;
  }

  UINT32 MainEntry::ParseCmdOptions(int argc, char ** argv)
  {
    p_ops::store(p_ops::parse_command_line(argc, argv, PgmOptions), ParsedOptions);

    return 0;
  }

} // namespace SFEngine
