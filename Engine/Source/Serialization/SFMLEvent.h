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

namespace cereal
{

  /*
   *  Normally would not do this, but SFML events need to be carefully serialized
   *  and deserialized
   **/

  template<class Archive>
  void load(Archive & ar, sf::Event & Event)
  {
    ar(Event.type);

    switch (Event.type)
    {
      case sf::Event::Closed:
      case sf::Event::GainedFocus:
      case sf::Event::JoystickButtonPressed:
      case sf::Event::JoystickButtonReleased:
      {
        ar(Event.joystickButton);
        break;
      }
      case sf::Event::JoystickConnected:
      case sf::Event::JoystickDisconnected:
      {
        ar(Event.joystickConnect);
        break;
      }
      case sf::Event::JoystickMoved:
      {
        ar(Event.joystickMove);
        break;
      }
      case sf::Event::KeyPressed:
      {
        ar(Event.key);
        break;
      }
      case sf::Event::KeyReleased:
      {
        ar(Event.key);
        break;
      }
      case sf::Event::LostFocus:
        break;
      case sf::Event::MouseButtonPressed:
      {
        ar(Event.mouseButton);
        break;
      }
      case sf::Event::MouseButtonReleased:
      {
        ar(Event.mouseButton);
        break;
      }
      case sf::Event::MouseEntered:
      case sf::Event::MouseLeft:
        break;
      case sf::Event::MouseMoved:
      {
        ar(Event.mouseMove);
        break;
      }
      case sf::Event::MouseWheelMoved
      {
        ar(Event.mouseWheel);
        break;
      }
      case sf::Event::MouseWheelScrolled:
      {
        ar(Event.mouseWheelScroll);
        break;
      }
      case sf::Event::Resized:
      {
        ar(Event.size);
        break;
      }
      case sf::Event::SensorChanged:
      {
        ar(Event.sensor);
        break;
      }
      case sf::Event::TouchBegan:
      case sf::Event::TouchEnded:
      {
        ar(Event.touch);
        break;
      }
      case sf::Event::TextEntered:
      {
        ar(Event.text);
        break;
      }
      default:
      {
        /* Emit error? */
        std::cerr << "Deserializaing unknown event type or forgotten event type\n";
        break;
      }

    } // end switch
  } // Load SFML event

  /*
    *  Deserialize
    **/

  template<class Archive>
  void save(Archive & ar, const sf::Event & Event)
  {
    ar(Event.type);

    switch (Event.type)
    {
      case sf::Event::Closed:
      case sf::Event::GainedFocus:
      case sf::Event::JoystickButtonPressed:
      case sf::Event::JoystickButtonReleased:
      {
        ar(Event.joystickButton);
        break;
      }
      case sf::Event::JoystickConnected:
      case sf::Event::JoystickDisconnected:
      {
        ar(Event.joystickConnect);
        break;
      }
      case sf::Event::JoystickMoved:
      {
        ar(Event.joystickMove);
        break;
      }
      case sf::Event::KeyPressed:
      {
        ar(Event.key);
        break;
      }
      case sf::Event::KeyReleased:
      {
        ar(Event.key);
        break;
      }
      case sf::Event::LostFocus:
        break;
      case sf::Event::MouseButtonPressed:
      {
        ar(Event.mouseButton);
        break;
      }
      case sf::Event::MouseButtonReleased:
      {
        ar(Event.mouseButton);
        break;
      }
      case sf::Event::MouseEntered:
      case sf::Event::MouseLeft:
        break;
      case sf::Event::MouseMoved:
      {
        ar(Event.mouseMove);
        break;
      }
      case sf::Event::MouseWheelMoved
      {
        ar(Event.mouseWheel);
        break;
      }
      case sf::Event::MouseWheelScrolled:
      {
        ar(Event.mouseWheelScroll);
        break;
      }
      case sf::Event::Resized:
      {
        ar(Event.size);
        break;
      }
      case sf::Event::SensorChanged:
      {
        ar(Event.sensor);
        break;
      }
      case sf::Event::TouchBegan:
      case sf::Event::TouchEnded:
      {
        ar(Event.touch);
        break;
      }
      case sf::Event::TextEntered:
      {
        ar(Event.text);
        break;
      }
      default:
      {
        /* Emit error? */
        std::cerr << "Deserializaing unknown event type or forgotten event type\n";
        break;
      }
    } // end switch
  } // save SFML Event

}
