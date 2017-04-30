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
#include "Engine\Engine.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <cereal\access.hpp>
#include <cereal\archives\portable_binary.hpp>
#include <cereal\types\string.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/
#include <sstream>

/************************************************************************/
/*                             Engine                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{

  Engine* Engine::m_StaticCurrentEngine = nullptr;
  STDMap<SString, SharedLevel> Engine::m_Levels;
  SharedLevel                  Engine::StartingLevel;
  SharedLevel                  Engine::m_CurrentLevel;
  SPtrShared<tgui::Gui>        Engine::m_EngineGUI;
  UINT32                       Engine::m_Flags = Engine::VSyncOff;

  Engine::Engine()
  {

  }

  Engine::~Engine()
  {
    /* Not yet saving these configs. Just for testing */
    std::ofstream saveinit("Engine.init", std::ios::binary);
    {
      cereal::BinaryOutputArchive outArchive(saveinit);

      outArchive(*this);
    } //Archive must go out of scope before it flushes contents to the stream
    saveinit.close();
  }

  Engine* Engine::GetCurrentEngine()
  {
    SFENGINE_ASSERT(m_StaticCurrentEngine != nullptr);
    return m_StaticCurrentEngine;
  }

  sf::RenderWindow* Engine::GetCurrentRenderWindow()
  {
    SFENGINE_ASSERT(m_StaticCurrentEngine != nullptr);
    return m_StaticCurrentEngine->m_CurrentRenderWindow;
  }

  void Engine::SignalForClose()
  {

  }

  void Engine::SignalForThrottle()
  {

  }

  SPtrShared<tgui::Gui> Engine::GUI()
  {
    return m_EngineGUI;
  }

  /************************************************************************/
  /* Serialization                                                        */
  /************************************************************************/
  template<class Archive>
  void Engine::load(Archive &ar)
  {
    ar(m_Configuration.DisplayFrameStats, m_Configuration.BenchmarkShaders,
       m_Configuration.LogLevel, m_Configuration.DiagnosticFont,
       m_Configuration.VsyncEnabled, m_Configuration.UseRenderTexture,
       m_Configuration.TextureSmoothingEnabled, m_Configuration.AALevel,
       m_Configuration.WindowSize, m_Configuration.WindowTitle
    );
  }

  template<class Archive>
  void Engine::save(Archive &ar) const
  {
    ar(m_Configuration.DisplayFrameStats, m_Configuration.BenchmarkShaders,
       m_Configuration.LogLevel, m_Configuration.DiagnosticFont,
       m_Configuration.VsyncEnabled, m_Configuration.UseRenderTexture,
       m_Configuration.TextureSmoothingEnabled, m_Configuration.AALevel
    );
  }

} // namespace SFEngine
