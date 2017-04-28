#ifndef SFEngine_BasicLevel_H
#define SFEngine_BasicLevel_H

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
#include "BasicIncludes.h"
#include "Engine\BaseEngineInterface.h"
#include "Globals.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <jsoncpp\json.h>
#include <SelbaWard\TileMap.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                         BasicLevel                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  class LevelObject;
  class TileSheet;
  class Animation;
  class Collider2D;
  class GenericActor;
  class ProjectileBase;
  class WeatherSystem;
  class WeatherEvent;

  class BasicLevel : public BaseEngineInterface
  {
  public:
    BasicLevel();

    //Oh gawd no please don't every try this
    BasicLevel(const BasicLevel &) = delete;
    BasicLevel(const BaseEngineInterface &Copy);
    BasicLevel& operator=(const BasicLevel &) = delete;
    BasicLevel(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
    virtual ~BasicLevel();

    /************************************************************************/
    /* Required method overrides                                            */
    /************************************************************************/
    virtual void TickUpdate(const SFLOAT &delta) override;
    virtual void Render(SharedRTexture Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(SOFStream &out) override;
    virtual void SerializeIn(SIFStream &in) override;
    virtual void HandleInputEvent(const UserEvent &evnt) override;

    /************************************************************************/
    /* Basic functionality methods                                          */
    /************************************************************************/
    virtual void LoadLevel(const std::string &lvlfile);
    virtual void OnBegin();
    virtual void OnEnd();
    virtual void HideUI();
    virtual void ShowUI();
    virtual void Reset();
    virtual void CleanUp();
    virtual void SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position);
    virtual void SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f &Position);

    virtual void RenderOnTexture(SharedRTexture Texture) = 0;

  protected:
    /************************************************************************/
    /* Asset loading methods                                                */
    /************************************************************************/
    virtual void LoadFromFile(const std::string &file);
    virtual void LoadAssets(const Json::Value &value);
    virtual void LoadAudio(const Json::Value &value);
    virtual void LoadTextures(const Json::Value &value);
    virtual void LoadTileSheets(const Json::Value &value);
    virtual void LoadSheet(const Json::Value &value);
    virtual void LoadAnimations(const Json::Value &value);

    /************************************************************************/
    /* Conditional variables                                                */
    /************************************************************************/
    bool m_DoUpdatePhysics = true;
    bool m_ShowGridLines   = false;

    /************************************************************************/
    /* Basic variables provided                                             */
    /************************************************************************/
    SString     m_ProjectPath;
    SFLOATRECT  m_CurrentView;
    SVector2U   m_Size;
    sw::TileMap m_TileMap;
    STexture    m_TileMapTexture;

    /************************************************************************/
    /* SFML Content - Textures/Autio/Etc                                    */
    /************************************************************************/
    SStringTextureMap     m_Textures;
    SStringSoundBufferMap m_SoundBuffers;
  };

}

#endif // SFEngine_BasicLevel_H
