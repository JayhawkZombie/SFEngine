#ifndef SFEngine_Launcher_H
#define SFEngine_Launcher_H

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

#include "Launcher\LauncherDisplay.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <boost\thread.hpp>
#include <boost\atomic.hpp>
#include <boost\shared_ptr.hpp>
#include <boost\lockfree\spsc_queue.hpp>
#include <boost\function.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\program_options.hpp>

#include <SFML\Graphics.hpp>
#include <SelbaWard.hpp>
#include <Kairos.hpp>
/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <functional>
#include <string>
#include <queue>

/************************************************************************/
/*                           Launcher                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/07                                  */
/************************************************************************/

namespace SFEngine
{

  class Launcher
  {
  public:
    static UINT32 Go(boost::program_options::options_description &Options,
                     boost::program_options::variables_map &VarMap,
                     boost::shared_ptr<boost::property_tree::ptree> Props);

    enum : UINT32
    {
        Waiting  = 0b000000
      , Working  = 0b000001
      , Finished = 0b000010
    };

    void operator()();
  protected:
    Launcher(const Launcher &) = delete;
    Launcher() = delete;
    ~Launcher() = delete;

    static void SetUpEnvironment();
    static void LoadConfig(boost::shared_ptr<LauncherDisplay> LaunchDisplay);
    static void CreateUI(boost::shared_ptr<LauncherDisplay> LaunchDisplay);
    static void LaunchEngine(boost::shared_ptr<LauncherDisplay> LaunchDisplay);

    static boost::shared_ptr<boost::property_tree::ptree> m_Properties;
    static boost::shared_ptr<boost::lockfree::spsc_queue<SString>> m_Messages;
    static boost::atomic<UINT32> m_ThreadStatus;
    static boost::shared_ptr<LauncherDisplay> m_LaunchDisplay;
    

  };

} // namespace SFEngine

#endif // if defined (SF_EDITOR)

#endif // SFEngine_Launcher_H
