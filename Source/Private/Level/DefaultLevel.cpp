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
#include "Level\DefaultLevel.h"
#include "Engine\Engine.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <Plinth/all.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                            DefaultLevel                              */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{

  DefaultLevel::DefaultLevel()
    : BasicLevel(SVector2U(1700u, 900u), SFLOATRECT(0, 0, 1700.f, 900.f))
  {
  }

  DefaultLevel::~DefaultLevel()
  {
  }

  void DefaultLevel::TickUpdate(const SFLOAT & delta)
  {
    BasicLevel::TickUpdate(delta);

    if (circ_pos.x >= WindowSize.x)
      circ_dir.x = -1;
    if (circ_pos.y >= WindowSize.y)
      circ_dir.y = -1;
    if (circ_pos.x <= 0)
      circ_dir.x = 1;
    if (circ_pos.y <= 0)
      circ_dir.y = 1;

    old_circ_pos = circ_pos;

    circ_pos += circ_vel * circ_dir;


    if (DoInterpolateRender)
      m_Text.setString("Interpolating");
    else
      m_Text.setString("Not Interpolating");

    auto bounds = m_Text.getGlobalBounds();
    float xDiff = WindowSize.x - bounds.width;
    m_Text.setPosition(SVector2F(xDiff / 2.f, 200.f));
  }

  void DefaultLevel::Render(SFLOAT Alpha, SharedRTexture Target)
  {
    BasicLevel::Render(Alpha, Target);

    sf::Vector2f pos = plinth::Tween::linear(old_circ_pos, circ_pos, Alpha);
    m_Circ.setPosition(pos);
  }

  void DefaultLevel::OnShutDown()
  {
  }

  void DefaultLevel::SerializeOut(SOFStream & out)
  {
  }

  void DefaultLevel::SerializeIn(SIFStream & in)
  {
  }

  void DefaultLevel::HandleInputEvent(const UserEvent & evnt)
  {
  }

  void DefaultLevel::StepSimulation(SFLOAT Dt)
  {
    BasicLevel::StepSimulation(Dt);
  }

  SString DefaultLevel::GetClass() const
  {
    return SString("DefaultLevel");
  }

  void DefaultLevel::EventUpdate(sf::Event Event)
  {
    if (Event.type == sf::Event::KeyPressed) {
      if (Event.key.code == sf::Keyboard::R) {
        std::for_each(m_Colliders.begin(), m_Colliders.end(), [](auto coll) { coll->Reset(); });
      }
      else if (Event.key.code == sf::Keyboard::I) {
        DoInterpolateRender = !DoInterpolateRender;
        if (DoInterpolateRender)
          m_Text.setString("Interpolating");
        else
          m_Text.setString("Not Interpolating");

        auto bounds = m_Text.getGlobalBounds();
        float xDiff = WindowSize.x - bounds.width;
        m_Text.setPosition(SVector2F(xDiff / 2.f, 200.f));
      }
      else if (Event.key.code == sf::Keyboard::Up) {
        SFEngine::Engine::IncreaseTimeStep(0.01f);
      }
      else if (Event.key.code == sf::Keyboard::Down) {
        SFEngine::Engine::DecreaseTimeStep(0.01f);
      }
      else if (Event.key.code == sf::Keyboard::Left) {
        SFEngine::Engine::DecreaseTimeSpeed(0.1f);
      }
      else if (Event.key.code == sf::Keyboard::Right) {
        SFEngine::Engine::IncreaseTimeSpeed(0.1f);
      }
    }
  }

  void DefaultLevel::LoadLevel(const std::string & lvlfile)
  {
  }

  void DefaultLevel::OnBegin()
  {
    m_Gravity.x = 0.f;
    m_Gravity.y = 1.f;
    AssignBoundaries((float)WindowSize.x, (float)WindowSize.y);
    m_CurrentView = SFLOATRECT(0.f, 0.f, 1700.f, 900.f);
    SetGravity(m_Gravity);
  }

  void DefaultLevel::OnEnd()
  {
  }

  void DefaultLevel::HideUI()
  {
  }

  void DefaultLevel::ShowUI()
  {
  }

  void DefaultLevel::Reset()
  {
  }

  void DefaultLevel::CleanUp()
  {
  }

  void DefaultLevel::SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f & Position)
  {
  }

  void DefaultLevel::SpawnObject(std::shared_ptr<GameObject> Object, const sf::Vector2f & Position)
  {
  }

  void DefaultLevel::RenderOnTexture(SFLOAT Alpha, SharedRTexture Texture)
  {
    BasicLevel::RenderOnTexture(Alpha, Texture);
    Texture->draw(m_Circ);
    Texture->draw(m_Text);

    m_ColliderTree.RenderOnTexture(Alpha, Texture, SFLOATRECT(0.f, 0.f, 1700.f, 900.f));
  }

  void DefaultLevel::Load()
  {
    std::cout << "Loading DefaultLevel" << std::endl;
    m_MenuThemePtr = std::make_shared<tgui::Theme>("./Demos/MainMenu/Assets/UIThemes/TransparentGray.theme");
    m_QuitButtonPtr = m_MenuThemePtr->load("button");
    m_QuitButtonPtr->setText("quit");
    m_QuitButtonPtr->setPosition({ 10, 10 });
    m_QuitButtonPtr->setSize({ 200, 35 });
    m_QuitButtonPtr->setTextSize(14);

    m_Font.loadFromFile("./Demos/MainMenu/Assets/Fonts/Raleway-Light.ttf");
    m_Text.setFont(m_Font);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setCharacterSize(30);
    m_Text.setString(DoInterpolateRender ? "Interpolating" : "Not Interpolating");
    auto bounds = m_Text.getGlobalBounds();
    float xDiff = WindowSize.x - bounds.width;
    m_Text.setPosition(SVector2F(xDiff / 2.f, 100.f));

    m_Gravity.x = 0.f;
    m_Gravity.y = 3.f;

    m_Circ.setPosition({ 300.f, 300.f });
    m_Circ.setRadius(40.f);
    m_Circ.setFillColor(sf::Color::Green);

    m_QuitButtonPtr->connect("clicked", []() { Engine::SignalForClose(); });

    auto gui = Engine::GUI();
    if (gui) {
      gui->add(m_QuitButtonPtr, "DefaultLevelQuitButtonPtr");
    }

    m_Colliders.emplace_back(Collider2D::CreatePolygonMesh(4, 40.f, 0.f, SVector2F(300.f, 300.f), SVector2F(0.f, 0.f), 3.f, 0.7f, sf::Color::Red));
    m_Colliders.emplace_back(Collider2D::CreatePolygonMesh(5, 30.f, 0.f, SVector2F(700.f, 300.f), SVector2F(0.f, 0.f), 2.f, 0.5f, sf::Color::Green));

    for (int i = 0; i < 25; ++i) {
      m_Colliders.emplace_back(Collider2D::CreatePolygonMesh(5, 15, 0.f, { rand() % 1700 + 10.f, 10.f + (rand() % 300 + 210.f)  }, { 0, 0 }, 7.f, 0.9f, sf::Color::Red));
    }

  }

  void DefaultLevel::Unload()
  {
    auto gui = Engine::GUI();
    if (gui) {
      gui->remove(m_QuitButtonPtr);
    }
  }

} // namespace SFEngine
