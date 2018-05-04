#pragma once

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

#include "Minimal.h"
#include "BasicIncludes.h"
#include "Events\EventHandler.h"

#include <cereal/types/array.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

/**
* Necessary forward declaration
*  to allow this to be seen by the BaseClass and avoid circular includes
*  will work on fixing later and getting GlobalHooks in better shape
*/
class Level;

#define TYPEDEF_PARENT_CLASS(PARENTCLASS) \
typedef PARENTCLASS Super; 

class BaseEngineInterface
{
public:
  BaseEngineInterface();
  BaseEngineInterface(const BaseEngineInterface &b);
  BaseEngineInterface& operator=(const BaseEngineInterface &) = delete;
  virtual ~BaseEngineInterface();


  //************************************
  // Method:    Clone
  // FullName:  Engine::BaseEngineInterface::Clone
  // Access:    virtual public 
  // Returns:   std::shared_ptr<Engine::BaseEngineInterface>
  // Qualifier: const
  // Purpose:   Create a clone of the object 
  //              ItemID and InternalID will *not* be copied
  //              New IDs will be generated
  //************************************
  virtual std::shared_ptr<BaseEngineInterface> Clone() const = 0;

  //************************************
  // Method:    TickUpdate
  // FullName:  Engine::BaseEngineInterface::TickUpdate
  // Access:    virtual public 
  // Returns:   void
  // Qualifier:
  // Parameter: const double & delta
  // Purpose:   Call every game tick update
  //************************************
  virtual void TickUpdate(const double &delta) = 0;


  //************************************
  // Method:    Render
  // FullName:  Engine::BaseEngineInterface::Render
  // Access:    virtual public 
  // Returns:   void
  // Qualifier:
  // Parameter: std::shared_ptr<sf::RenderTarget> Target
  // Purpose:   Direct the object to render itself onto the Target
  //************************************
  virtual void Render(std::shared_ptr<sf::RenderTarget> Target) = 0;


  //************************************
  // Method:    OnShutDown
  // FullName:  Engine::BaseEngineInterface::OnShutDown
  // Access:    virtual public 
  // Returns:   void
  // Qualifier:
  // Parameter: None
  // Purpose:   Called if object is alive during the shutdown process
  //            Use to clean up any allocated resources that cannot
  //            Clean themselves up (including any OpenGL resources)
  //************************************
  virtual void OnShutDown() = 0;


  //************************************
  // Method:    SerializeOut
  // FullName:  Engine::BaseEngineInterface::SerializeOut
  // Access:    virtual public 
  // Returns:   void
  // Qualifier:
  // Parameter: std::ofstream & out
  // Purpose:   Serialize the object to a file. Class must
  //             be able to reconstruct itself from only 
  //             the information provided in the file
  //************************************
  virtual void SerializeOut(std::ofstream &out) = 0;


  //************************************
  // Method:    SerializeIn
  // FullName:  Engine::BaseEngineInterface::SerializeIn
  // Access:    virtual public 
  // Returns:   void
  // Qualifier:
  // Parameter: std::ifstream & in
  // Purpose:   Create a copy of the object in the state as defined in the serialized file
  //************************************
  virtual void SerializeIn(std::ifstream &in) = 0;


  //************************************
  // Method:    EventUpdate
  // FullName:  Engine::BaseEngineInterface::EventUpdate
  // Access:    virtual public 
  // Returns:   void
  // Qualifier:
  // Parameter: sf::Event event
  // Purpose:   Menually request the object react to an sf::Event
  //************************************
  virtual void EventUpdate(sf::Event event);


  //************************************
  // Method:    HandleInputEvent
  // FullName:  Engine::BaseEngineInterface::HandleInputEvent
  // Access:    virtual public 
  // Returns:   void
  // Qualifier:
  // Parameter: const UserEvent & evnt
  // Purpose:   
  //************************************
  virtual void HandleInputEvent(const UserEvent &evnt);

  EventHandler Handler;
  virtual std::string GetID() const;
  virtual void SetID(const std::string &ID);

  virtual std::uint32_t GetInternalID() const 
  {
    return InternalID;
  }
  
  virtual void SetInternalD(const std::uint32_t &ID) 
  {
    InternalID = ID;
  }

  virtual std::string GetClass() const = 0 
  {
    return "BaseEngineInterface";
  }

protected:
  static void NO_ACTION(BaseEngineInterface *item, const sf::Vector2i &i);
  static void NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &);
  static void NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &);
  static void NO_ACTION(BaseEngineInterface *item);

  std::string ItemID = "";
  std::uint32_t InternalID = 0;

public:

  template<class Archive>
  void load(Archive & ar)
  {
    ar(InternalID);
    ar(ItemID);
  }

  template<class Archive>
  void save(Archive & ar) const
  {
    ar(InternalID);
    ar(ItemID);
  }

};
