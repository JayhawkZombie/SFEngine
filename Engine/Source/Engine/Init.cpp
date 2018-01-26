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

#include "Engine/stdafx.h"
#include "Engine\Engine.h"
#include "Messaging\CoreMessager.h"
#include "Time/TimerManager.h"
#include "Parsing/IniParser.h"

#include <filesystem>
#include <boost/stacktrace.hpp>
#include <boost/stacktrace/stacktrace.hpp>
#include <boost/program_options.hpp>

namespace filesystem = std::experimental::filesystem;
namespace prog_opts = boost::program_options;

#ifdef SPLATFORM_WINDOWS
#include <Windows.h>
#endif

UINT32 SFEngine::Init(int argc, char **argv)
{

  if (filesystem::exists(filesystem::current_path() / "crash_trace.dump"))
  {
    std::ifstream trace("crash_trace.dump");

    boost::stacktrace::stacktrace st = boost::stacktrace::stacktrace::from_dump(trace);

    std::cout << "Previous run crashed: \n" << st << "\n";

    trace.close();
    filesystem::remove("crash_trace.dump");
  }

  IniParser parser;
  bool IsRestartingApp = false;

  /*
    Parse command line arguments
  */
  prog_opts::store(prog_opts::parse_command_line(argc, argv, CommmandLineArgumentsDescription), CommandLineArguments);

  std::string DefaultOptionsFile("Engine.ini");

  if (CommandLineArguments.count("defaults-file"))
  {
    DefaultOptionsFile = CommandLineArguments["defaults-file"].as<std::string>();
  }

  /* Parse additional configuration options passed via command-line */
  if (CommandLineArguments.count("?"))
  {
    auto AdditionalOptions = CommandLineArguments["?"].as<std::vector<std::string>>();

    for (const auto & option : AdditionalOptions)
    {
      parser.ParseOption(option);
    }
  }

  if (CommandLineArguments.count("restart"))
  {
    /* Restarting process for when the application is restarted by Windows after a crash/hang */

    IsRestartingApp = true;
  }
  
  parser.Parse(DefaultOptionsFile);
  auto winSize = parser.TryGetValue("Window", "WindowSize");
  auto initLevel = parser.TryGetValue("Game", "LevelFile");
  auto brightness = parser.TryGetValue("Render", "Brightness");
  auto contrast = parser.TryGetValue("Render", "Contrast");
  auto gamma = parser.TryGetValue("Render", "Gamma");
  auto clearcolor_r = parser.TryGetValue("Render", "ClearColor.r");
  auto clearcolor_g = parser.TryGetValue("Render", "Clearcolor.g");
  auto clearcolor_b = parser.TryGetValue("Render", "ClearColor.b");
  auto aalevel = parser.TryGetValue("Render", "uiAALevel");
  auto majorversion = parser.TryGetValue("Render", "MajorVersion");
  auto minorversion = parser.TryGetValue("Render", "MinorVersion");
  auto use_vsync = parser.TryGetValue("Render", "bVsyncEnabled");

  EngineConfig.Window_v2uWindowSize = Util::StringToVec2<unsigned int>(winSize.value_or("(1700, 900)"));
  InitialLevel = initLevel.value_or("none");
  EngineRenderSettings.Brightness = Util::StringToType<float>(brightness.value_or("1"));
  EngineRenderSettings.Contrast = Util::StringToType<float>(contrast.value_or("0.5"));
  EngineRenderSettings.Gamma = Util::StringToType<float>(gamma.value_or("0.5"));
  EngineRenderSettings.BGClearColor.r = Util::StringToType<sf::Uint8>(clearcolor_r.value_or("0"));
  EngineRenderSettings.BGClearColor.g = Util::StringToType<sf::Uint8>(clearcolor_g.value_or("0"));
  EngineRenderSettings.BGClearColor.b = Util::StringToType<sf::Uint8>(clearcolor_b.value_or("0"));
  EngineConfig.Context_VersionMajor = Util::StringToType<unsigned int>(majorversion.value_or("4"));
  EngineConfig.Context_VersionMinor = Util::StringToType<unsigned int>(minorversion.value_or("1"));
  EngineConfig.Render_bVsyncEnabled = Util::StringToBool(use_vsync.value_or("true"));
  EngineConfig.Render_uiAALevel = Util::StringToType<unsigned int>(aalevel.value_or("4"));
  EngineConfig.Window_uiDepthBits = 24;
  EngineConfig.Window_uiStencilBits = 0;
  EngineConfig.Window_u32AttributeFlags = sf::ContextSettings::Attribute::Default;
  EngineConfig.Window_ui8Style = sf::Style::Default;

  //Init timer manager
  m_GlobalTimerManager = std::make_unique<TimerManager>();

  //Initialize the messager
  Messager::Init();

  /* Initialize and launch the level streaming thread */
  ASyncLevelStreamThread::Launch();
  LevelsLock = std::make_shared<std::mutex>();

  if (IsRestartingApp)
    Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Attempting to restart engine"), MessageLogLevel::Critical);
  else
    Messager::PostLogMessage(0, SystemMessage(SystemMessageType::ActivityLog, 0, 0, "Beginning engine startup"), MessageLogLevel::Normal);

  if (IsRestartingApp)
  {
    uint32_t RestartSuccess = TryRestartEngine();

    if (RestartSuccess)
    {
#ifdef SPLATFORM_WINDOWS

      LPCTSTR MsgText = L"Engine failed to restart properly.\nPlease refer to RESTART.log for details and report the issue.";
      LPCTSTR MsgCaption = L"Restart Failed";

      UINT MsgType = MB_OK | MB_SYSTEMMODAL | MB_ICONERROR;

      /* Have to use MessageBoxW because we #undef'd MessageBox in Globals because of a name clash */

      int MsgBoxReturn = MessageBoxW
      (
        NULL,
        MsgText,
        MsgCaption, 
        MsgType
      );

      /* This has to return IDOK, it's the only option presented to the user */

      return ( MsgBoxReturn == IDOK ? 0 : 1 );

#endif
    }
  }

  return Startup();
}
