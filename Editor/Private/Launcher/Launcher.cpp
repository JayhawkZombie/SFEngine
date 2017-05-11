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
#if defined (SF_EDITOR)
#include "Launcher\Launcher.h"
#include "Manager\EditorManager.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <boost\atomic\atomic.hpp>
#include <boost\circular_buffer.hpp>
#include <boost\memory_order.hpp>
#include <boost\assign.hpp>
#include <boost\filesystem.hpp>
#include <boost\chrono.hpp>
#include <boost\thread.hpp>
#include <boost\thread\detail\move.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <chrono>

/************************************************************************/
/*                           Launcher                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: (Name) - 2017/05/07                                       */
/************************************************************************/

namespace {  
  struct dont_care {
    dont_care() = default;
    dont_care(boost::function<void(void)> f) : empty_f(f) {}
    void operator()() {
      return empty_f();
    }
    boost::function<void(void)> empty_f = []() { return; };
  } empty_thread;

  boost::thread make_thread_work(boost::function<void(void)> ftn)
  {
    dont_care d_(ftn);
    return boost::thread(d_);
  }

  boost::thread make_empty_thread()
  {
    return make_thread_work([]() {});
  }
}

namespace SFEngine
{

#include "..\..\Public\Launcher\Launcher.h"

  boost::atomic<UINT32> Launcher::m_ThreadStatus;
  boost::shared_ptr<LauncherDisplay> Launcher::m_LaunchDisplay;
  boost::shared_ptr<boost::property_tree::ptree> Launcher::m_Properties;
  boost::shared_ptr<boost::lockfree::spsc_queue<SString>> Launcher::m_Messages;

  UINT32 Launcher::Go(boost::program_options::options_description &Options,
                      boost::program_options::variables_map &VarMap,
                      boost::shared_ptr<boost::property_tree::ptree> Props)
  {
    m_ThreadStatus.store(Launcher::Waiting);
    SetUpEnvironment();

    Launcher::m_Properties = Props;
    bool DoneLaunching = false;
    m_LaunchDisplay = boost::make_shared<LauncherDisplay>();

    m_LaunchDisplay->Launch(UINT32(600), UINT32(500));
    m_LaunchDisplay->Update();
    m_LaunchDisplay->Draw();

    std::thread config_setup(
      []()
      {
        LoadConfig(m_LaunchDisplay);
        CreateUI(m_LaunchDisplay);
        LaunchEngine(m_LaunchDisplay);
      }
    );

    for ( ; ; ) {
      if (m_ThreadStatus.load() == Launcher::Finished) {
        break;
      }

      m_LaunchDisplay->Update();
      m_LaunchDisplay->Draw();
    }
    config_setup.join();

    m_LaunchDisplay->ShutDown();
    auto win = m_LaunchDisplay->GetWindow();
    m_LaunchDisplay.reset();
    return EditorManager::MainLoop(win);
  }
  
  void Launcher::operator()()
  {
  }

  void Launcher::SetUpEnvironment()
  {
    boost::filesystem::path curr_path = boost::filesystem::current_path();
    Env["PATH"] = curr_path.string();
    std::cout << "PATH: " << Env["PATH"] << std::endl;
  }

  void Launcher::LoadConfig(boost::shared_ptr<LauncherDisplay> LaunchDisplay)
  {
    LaunchDisplay->PostLaunchUpdate(SString("Loading Configuration Settings"));
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  void Launcher::CreateUI(boost::shared_ptr<LauncherDisplay> LaunchDisplay)
  {
    LaunchDisplay->PostLaunchUpdate(SString("Constructing Editor UI"));
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  void Launcher::LaunchEngine(boost::shared_ptr<LauncherDisplay> LaunchDisplay)
  {
    LaunchDisplay->PostLaunchUpdate(SString("Launching Engine"));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m_ThreadStatus.store(Launcher::Finished);
  }

} // namespace SFEngine

#endif // if defined (SF_EDITOR)
