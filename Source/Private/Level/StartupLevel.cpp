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
#include "Level\StartupLevel.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        StartupLevel                                  */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/02                                  */
/************************************************************************/

namespace SFEngine
{

  

  StartupLevel::StartupLevel(const sf::Vector2u & LevelSize, const sf::FloatRect & DefaultView, bool showlines, const sf::Vector2f & GridSpacing)
  {
  }

  StartupLevel::~StartupLevel()
  {
  }

  void StartupLevel::TickUpdate(const SFLOAT & delta)
  {
  }

  void StartupLevel::Render(SFLOAT Alpha, SharedRTexture Target)
  {
  }

  void StartupLevel::OnShutDown()
  {
  }

  void StartupLevel::SerializeOut(SOFStream & out)
  {
  }

  void StartupLevel::SerializeIn(SIFStream & in)
  {
  }

  void StartupLevel::HandleInputEvent(const UserEvent & evnt)
  {
  }

  void StartupLevel::StepSimulation(SFLOAT Dt)
  {
  }

  void StartupLevel::InterpolateState(SFLOAT Alpha)
  {
  }

  void StartupLevel::EventUpdate(sf::Event Event)
  {
  }

  void StartupLevel::OnBegin()
  {
  }

  void StartupLevel::OnEnd()
  {
  }

  void StartupLevel::HideUI()
  {
  }

  void StartupLevel::ShowUI()
  {
  }

  void StartupLevel::Reset()
  {
  }

  void StartupLevel::CleanUp()
  {
  }

  void StartupLevel::RenderOnTexture(SFLOAT Alpha, SharedRTexture Texture)
  {
  }

  void StartupLevel::Load()
  {
  }

  void StartupLevel::Unload()
  {
  }

} // namespace SFEngine
