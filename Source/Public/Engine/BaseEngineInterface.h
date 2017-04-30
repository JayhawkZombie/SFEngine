#ifndef SFEngine_BaseEngineInterface_H
#define SFEngine_BaseEngineInterface_H

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
#include "Events\EventHandler.h"
#include "Events\UserEvent.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <cereal\archives\binary.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        BaseEngineInterface                           */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace SFEngine
{

#define TYPEDEF_PARENT_CLASS(PARENTCLASS) \
  typedef PARENTCLASS Super; 

  class BaseEngineInterface
  {
  public:
    BaseEngineInterface();
    BaseEngineInterface(const BaseEngineInterface &b);
    BaseEngineInterface& operator=(const BaseEngineInterface &) = delete;
    virtual ~BaseEngineInterface();

    /************************************************************************/
    /* Pure virtual interface methods                                       */
    /************************************************************************/
    virtual SPtrShared<BaseEngineInterface> Clone() const = 0;
    virtual void TickUpdate(const SFLOAT &delta) = 0;
    virtual void Render(SharedRTexture Target) = 0;
    virtual void OnShutDown() = 0;
    virtual void SerializeOut(SOFStream &out) = 0;
    virtual void SerializeIn(SIFStream &in) = 0;
    virtual void EventUpdate(sf::Event event);
    virtual void HandleInputEvent(const UserEvent &evnt);

    EventHandler Handler;

    /************************************************************************/
    /* Getters                                                              */
    /************************************************************************/
    virtual SString GetID() const;
    virtual UINT32 GetInternalID() const;
    virtual SString GetClass() const = 0;

    /************************************************************************/
    /* Setters                                                              */
    /************************************************************************/
    virtual void SetInternalD(const UINT32 &ID);
    virtual void SetID(const SString &ID);

  protected:
    static void NO_ACTION(BaseEngineInterface *item, const SVector2I &i);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &);
    static void NO_ACTION(BaseEngineInterface *item);

    SString ItemID = "";
    UINT32 InternalID = 0;
  };

}

#endif // SFEngine_BaseEngineInterface_H
