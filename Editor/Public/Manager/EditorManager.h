#ifndef SFEngine_EditorManager_H
#define SFEngine_EditorManager_H

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

#include "Engine\Engine.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <boost\shared_ptr.hpp>
#include <boost\atomic\atomic.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\program_options.hpp>

#include <SelbaWard/BitmapFont.hpp>
#include <SelbaWard\BitmapText.hpp>
#include <TGUI\TGUI.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        EditorManager                                 */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/07                                  */
/************************************************************************/

namespace SFEngine
{

  class EditorManager
  {
  public:
    ~EditorManager();
    static UINT32 Launch(boost::program_options::options_description &Options, boost::program_options::variables_map &VarMap);
    static UINT32 MainLoop(SPtrShared<sf::RenderWindow> Window);
    static std::shared_ptr<tgui::Gui> GetUIHandle();

  private:
    boost::atomic<bool> m_GuiFinished;
    void UILoadingLoop();
    void CreateBMPFont(sw::BitmapFont &BFont, sw::BitmapText &BText);
    EditorManager();
    void SetupUI();
    SFLOAT UpdatePass();
    SFLOAT RenderPass(SPtrShared<sf::RenderWindow> Window);

    SFLOAT m_InterpDelta;
    SharedRTexture m_GameTexture;
    SRectShape m_GameRect;
    SPtrShared<sf::RenderWindow> m_MainWindow;
    static boost::shared_ptr<EditorManager> Get();
    static boost::shared_ptr<EditorManager> m_StaticManager;

    /************************************************************************/
    /* Member variables/functions for static manager                        */
    /************************************************************************/
    boost::shared_ptr<Engine> m_StaticEngine;
    boost::shared_ptr<boost::property_tree::ptree> m_Properties;
    std::shared_ptr<tgui::Gui> m_EditorGui;
  };

} // namespace SFEngine

#endif // if defined (SF_EDITOR)

#endif // SFEngine_EditorManager_H
