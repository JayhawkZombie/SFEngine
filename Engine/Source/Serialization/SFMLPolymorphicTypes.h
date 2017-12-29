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

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "SFMLTypes.h"

namespace cereal
{

  /*
  *  Loaders
  **/

  template<class Archive>
  void load(Archive & ar, sf::Transformable & trs)
  {
    sf::Vector2f pos;
    float rot;
    sf::Vector2f scale;
    sf::Vector2f origin;

    ar(pos);
    ar(rot);
    ar(scale);
    ar(origin);

    trs.setPosition(pos);
    trs.setRotation(rot);
    trs.setScale(scale);
    trs.setOrigin(origin);
  }

  template<class Archive>
  void load(Archive & ar, sf::Shape & Shape)
  {
    ar(cereal::base_class<sf::Transformable>(std::addressof(Shape)));
    ar(cereal::base_class<sf::Drawable>(std::addressof(Shape)));

    sf::Color   col;
    float       outline;
    sf::Color   outlineColor;
    size_t      nPts;
    sf::IntRect tRect;

    ar(col);
    ar(outline);
    ar(outlineColor);
    ar(nPts);
    ar(tRect);

    Shape.setFillColor(col);
    Shape.setOutlineColor(outlineColor);
    Shape.setOutlineThickness(outline);
    Shape.setTextureRect(tRect);
  }

  template<class Archive>
  void load(Archive & ar, sf::CircleShape & Circ)
  {
    ar(cereal::base_class<sf::Shape>(std::addressof(Circ)));

    float rad;

    ar(rad);

    Circ.setRadius(rad);
  }

  template<class Archive>
  void load(Archive & ar, sf::RectangleShape & Rect)
  {
    ar(cereal::base_class<sf::Shape>(std::addressof(Rect)));

    sf::Vector2f size;

    ar(size);

    Rect.setSize(size);
  }

  template<class Archive>
  void load(Archive & ar, sf::ConvexShape & CVShape)
  {
    ar(cereal::base_class<sf::Shape>(std::addressof(CVShape)));
  }

  template<class Archive>
  void load(Archive & ar, sf::Sprite & Sprite)
  {
    ar(cereal::base_class<sf::Drawable>(std::addressof(Sprite)));
    ar(cereal::base_class<sf::Transformable>(std::addressof(Sprite)));

    sf::Color col;
    sf::IntRect tRect;

    ar(col);
    ar(tRect);

    Sprite.setColor(col);
    Sprite.setTextureRect(tRect);
  }

  template<class Archive>
  void load(Archive & ar, sf::Text & Text)
  {
    ar(cereal::base_class<sf::Transformable>(std::addressof(Text)));
    ar(cereal::base_class<sf::Drawable>(std::addressof(Text)));

    sf::String str;
    unsigned int chSize;
    sf::Uint32 style;
    sf::Color col;
    sf::Color ocol;
    float oThk;

    ar(str);
    ar(chSize);
    ar(style);
    ar(col);
    ar(ocol);
    ar(oThk);

    Text.setString(str);
    Text.setCharacterSize(chSize);
    Text.setStyle(style);
    Text.setFillColor(col);
    Text.setOutlineColor(ocol);
    Text.setOutlineThickness(oThk);
  }

  template<class Archive>
  void load(Archive & ar, sf::String & String)
  {
    std::vector<sf::Uint32> utfVector;

    ar(utfVector);
    utfVector.push_back(0);

    String = sf::String(utfVector.data());
  }

  template<class Archive>
  void load(Archive & ar, sf::RenderTexture &RTexture)
  {
    ar(cereal::base_class<sf::RenderTarget>(std::addressof(RTexture)));

    bool smooth;
    bool rept;
    bool genMipMap;
    sf::Vector2u size;
    sf::View view;
    sf::View defView;

    ar(smooth);
    ar(rept);
    ar(size);
    ar(view);
    ar(defView);

    RTexture.create(size.x, size.y);
    RTexture.setSmooth(smooth);
    RTexture.setRepeated(rept);
    RTexture.setView(view);
  }

  template<class Archive>
  void load(Archive & ar, sf::VertexArray &Varr)
  {
    ar(cereal::base_class<sf::Drawable>(std::addressof(Varr)));

    sf::PrimitiveType primType;
    std::vector<sf::Vertex> verts;

    ar(primType);
    ar(verts);

    /* Again, can't believe I have to do this */
    Varr.resize(verts.size());

    std::size_t i = 0;
    for (const auto vert : verts)
    {
      Varr[i++] = vert;
    }
  }

  template<class Archive>
  void load(Archive & ar, sf::IpAddress & IP)
  {
    std::string addrString;

    ar(addrString);

    IP = sf::IpAddress(addrString);
  }

  template<class Archive>
  void load(Archive & ar, sf::Music & music)
  {
    float pitch;
    sf::Time playingOffset;
    float vol;
    float atten;
    sf::Vector3f pos;

    ar(pitch);
    ar(playingOffset);
    ar(vol);
    ar(atten);
    ar(pos);

    music.setPitch(pitch);
    music.setPlayingOffset(playingOffset);
    music.setVolume(vol);
    music.setAttenuation(atten);
    music.setPosition(pos);
  }

  /*
  *  Savers
  **/

  template<class Archive>
  void save(Archive & ar, const sf::Transformable & trs)
  {
    auto pos = trs.getPosition();
    auto rot = trs.getRotation();
    auto scl = trs.getScale();
    auto org = trs.getOrigin();

    ar(pos);
    ar(rot);
    ar(scl);
    ar(org);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Shape & Shape)
  {
    ar(cereal::base_class<sf::Transformable>(std::addressof(Shape)));
    ar(cereal::base_class<sf::Drawable>(std::addressof(Shape)));

    sf::Color   col = Shape.getFillColor();
    sf::Color   outlineColor = Shape.getOutlineColor();
    size_t      nPts = Shape.getPointCount();
    float       outline = Shape.getOutlineThickness();
    sf::IntRect tRect = Shape.getTextureRect();

    ar(col);
    ar(outline);
    ar(outlineColor);
    ar(nPts);
    ar(tRect);
  }

  template<class Archive>
  void save(Archive & ar, const sf::CircleShape & Circ)
  {
    ar(cereal::base_class<sf::Shape>(std::addressof(Circ)));

    auto rad = Circ.getRadius();

    ar(rad);
  }

  template<class Archive>
  void save(Archive & ar, const sf::RectangleShape & Rect)
  {
    ar(cereal::base_class<sf::Shape>(std::addressof(Rect)));

    auto size = Rect.getSize();

    ar(size);
  }

  template<class Archive>
  void save(Archive & ar, const sf::ConvexShape & CVShape)
  {
    ar(cereal::base_class<sf::Shape>(std::addressof(CVShape)));
  }

  template<class Archive>
  void save(Archive & ar, const sf::Sprite & Sprite)
  {
    ar(cereal::base_class<sf::Drawable>(std::addressof(Sprite)));
    ar(cereal::base_class<sf::Transformable>(std::addressof(Sprite)));

    sf::Color col = Sprite.getColor();
    sf::IntRect tRect = Sprite.getTextureRect();

    ar(col);
    ar(tRect);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Text & Text)
  {
    ar(cereal::base_class<sf::Transformable>(std::addressof(Text)));
    ar(cereal::base_class<sf::Drawable>(std::addressof(Text)));

    sf::String      str = Text.getString();
    const sf::Font* font = Text.getFont();
    unsigned int    chSize = Text.getCharacterSize();
    sf::Uint32 style = Text.getStyle();
    sf::Color col = Text.getFillColor();
    sf::Color ocol = Text.getOutlineColor();
    float     oThk = Text.getOutlineThickness();

    ar(str);
    ar(chSize);
    ar(style);
    ar(col);
    ar(ocol);
    ar(oThk);
  }

  template<class Archive>
  void save(Archive & ar, const sf::String & String)
  {
    std::basic_string<sf::Uint32> UTFString = String.toUtf32();

    std::size_t len = UTFString.size();

    std::vector<sf::Uint32> utfVector(len);

    std::size_t i = 0;
    for (const auto & ch : UTFString)
    {
      utfVector[i++] = ch;
    }

    ar(utfVector);
  }

  template<class Archive>
  void save(Archive & ar, const sf::RenderTexture &RTexture)
  {

    bool smooth = RTexture.isSmooth();
    bool rept = RTexture.isRepeated();
    sf::Vector2u size = RTexture.getSize();
    const sf::View &view = RTexture.getView();
    const sf::View &defView = RTexture.getDefaultView();

    ar(smooth);
    ar(rept);
    ar(size);
    ar(view);
    ar(defView);
  }

  template<class Archive>
  void save(Archive & ar, const sf::VertexArray &Varr)
  {
    ar(cereal::base_class<sf::Drawable>(std::addressof(Varr)));

    std::size_t vertCount = Varr.getVertexCount();
    sf::PrimitiveType primType = Varr.getPrimitiveType();

    ar(primType);

    /* I really can't fuckin' believe I have to do this
    * Why can SFML not give us access to the underlying data?
    * */
    std::vector<sf::Vertex> arr(vertCount, sf::Vertex());
    std::size_t i = 0;

    for (auto & vert : arr)
    {
      vert = Varr[i++];
    }

    ar(arr);
  }

  template<class Archive>
  void save(Archive & ar, const sf::IpAddress & IP)
  {
    std::string addrString = IP.toString();

    ar(addrString);
  }

  template<class Archive>
  void save(Archive & ar, const sf::Music & music)
  {
    float pitch = music.getPitch();
    sf::Time playingOffset = music.getPlayingOffset();
    float vol = music.getVolume();
    float atten = music.getAttenuation();
    sf::Vector3f pos = music.getPosition();

    ar(pitch);
    ar(playingOffset);
    ar(vol);
    ar(atten);
    ar(pos);
  }

}

/* Cereal disambiguation for types */

namespace cereal
{
  template<class Archive> struct specialize<Archive, sf::Shape,          cereal::specialization::non_member_load_save> { };
  template<class Archive> struct specialize<Archive, sf::CircleShape,    cereal::specialization::non_member_load_save> { };
  template<class Archive> struct specialize<Archive, sf::RectangleShape, cereal::specialization::non_member_load_save> { };
}

CEREAL_REGISTER_TYPE(sf::Shape);
CEREAL_REGISTER_TYPE(sf::Drawable);
CEREAL_REGISTER_TYPE(sf::Transformable);
CEREAL_REGISTER_TYPE(sf::Text);
CEREAL_REGISTER_TYPE(sf::Sprite);
CEREAL_REGISTER_TYPE(sf::ConvexShape);
CEREAL_REGISTER_TYPE(sf::RectangleShape);
CEREAL_REGISTER_TYPE(sf::CircleShape);
CEREAL_REGISTER_TYPE(sf::VertexArray);
