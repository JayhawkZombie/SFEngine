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
  *  Loaders
  * */
  template<class Archive>
  void load(Archive & ar, sf::Color & c)
  {
    ar(c.r, c.g, c.b, c.a);
  }

  template<class Archive>
  void load(Archive & ar, sf::Vector2f & vec)
  {
    ar(vec.x, vec.y);
  }

  template<class Archive>
  void load(Archive & ar, sf::Vector3f & vec)
  {
    ar(vec.x, vec.y, vec.z);
  }

  template<class Archive>
  void load(Archive & ar, sf::Vector2u & vec)
  {
    ar(vec.x, vec.y);
  }

  template<class Archive>
  void load(Archive & ar, sf::Vector2i & vec)
  {
    ar(vec.x, vec.y);
  }

  template<class Archive>
  void load(Archive & ar, sf::FloatRect & rect)
  {
    ar(rect.left, rect.top, rect.width, rect.height);
  }

  template<class Archive>
  void load(Archive & ar, sf::IntRect & rect)
  {
    ar(rect.left, rect.top, rect.width, rect.height);
  }

  template<class Archive>
  void load(Archive & ar, sf::Vertex & vtx)
  {
    ar(vtx.color, vtx.position, vtx.texCoords);
  }

  template<class Archive>
  void load(Archive & ar, sf::Drawable & Draw)
  {
    //Empty, sf::Drawable holds no unique data to serialize
  }

  /*
  *  Savers
  **/
  template<class Archive>
  void save(Archive & ar, const sf::Color & c)
  {
    ar(c.r, c.g, c.b, c.a);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Vector2f & vec)
  {
    ar(vec.x, vec.y);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Vector3f & vec)
  {
    ar(vec.x, vec.y, vec.z);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Vector2u & vec)
  {
    ar(vec.x, vec.y);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Vector2i & vec)
  {
    ar(vec.x, vec.y);
  }

  template<class Archive>
  void save(Archive & ar, const sf::FloatRect & rect)
  {
    ar(rect.left, rect.top, rect.width, rect.height);
  }

  template<class Archive>
  void save(Archive & ar, const sf::IntRect & rect)
  {
    ar(rect.left, rect.top, rect.width, rect.height);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Vertex & vtx)
  {
    ar(vtx.color, vtx.position, vtx.texCoords);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Drawable & Draw)
  {
    //Empty, sf::Drawable holds no unique data to serialize
  }

  /* Different event types */

  template<class Archive>
  void serialize(Archive & ar, sf::Event::SizeEvent &SEvent)
  {
    ar(SEvent.height);
    ar(SEvent.width);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::KeyEvent &KEvent)
  {
    ar(KEvent.alt);
    ar(KEvent.code);
    ar(KEvent.control);
    ar(KEvent.shift);
    ar(KEvent.system);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::TextEvent &TEvent)
  {
    ar(TEvent.unicode);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::MouseMoveEvent &MMEvent)
  {
    ar(MMEvent.x);
    ar(MMEvent.y);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::MouseButtonEvent &MBEvent)
  {
    ar(MBEvent.button);
    ar(MBEvent.x);
    ar(MBEvent.y);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::MouseWheelEvent &MWEvent)
  {
    ar(MWEvent.delta);
    ar(MWEvent.x);
    ar(MWEvent.y);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::MouseWheelScrollEvent &MWSEvent)
  {
    ar(MWSEvent.delta);
    ar(MWSEvent.wheel);
    ar(MWSEvent.x);
    ar(MWSEvent.y);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::JoystickConnectEvent &JSCEvent)
  {
    ar(JSCEvent.joystickId);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::JoystickMoveEvent &JSMEvent)
  {
    ar(JSMEvent.axis);
    ar(JSMEvent.joystickId);
    ar(JSMEvent.position);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::JoystickButtonEvent &JSBEvent)
  {
    ar(JSBEvent.button);
    ar(JSBEvent.joystickId);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::TouchEvent &TEvent)
  {
    ar(TEvent.finger);
    ar(TEvent.x);
    ar(TEvent.y);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Event::SensorEvent &SEvent)
  {
    ar(SEvent.type);
    ar(SEvent.x);
    ar(SEvent.y);
    ar(SEvent.z);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::BlendMode & Blendmode)
  {
    ar(Blendmode.colorDstFactor);
    ar(Blendmode.colorSrcFactor);
    ar(Blendmode.colorEquation);
    ar(Blendmode.alphaDstFactor);
    ar(Blendmode.alphaSrcFactor);
    ar(Blendmode.alphaEquation);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::ContextSettings & CSettings)
  {
    ar(CSettings.depthBits);
    ar(CSettings.stencilBits);
    ar(CSettings.antialiasingLevel);
    ar(CSettings.majorVersion);
    ar(CSettings.minorVersion);
    ar(CSettings.attributeFlags);
    ar(CSettings.sRgbCapable);
  }

  template<class Archive>
  void serialize(Archive & ar, sf::Glyph & glyph)
  {
    ar(glyph.advance);
    ar(glyph.bounds);
    ar(glyph.textureRect);
  }

}
