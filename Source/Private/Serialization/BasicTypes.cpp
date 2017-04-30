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
#include "Serialization\BasicTypes.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <cereal\access.hpp>

#include <EngineTypes.h>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                         BasicTypes                                   */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/30                                  */
/************************************************************************/

namespace cereal
{
  /****************************************************************************************************/
  /* SFML Type Serialization                                                                          */
  /****************************************************************************************************/

  //FloatRect
  //template<class Archive>
  //void load(Archive &ar, SFLOATRECT &Frect)
  //{
  //  ar(Frect.left, Frect.top, Frect.width, Frect.height);
  //}

  //template<class Archive>
  //void save(Archive &ar, const SFLOATRECT &Frect)
  //{
  //  ar(Frect.left, Frect.top, Frect.width, Frect.height);
  //}

  ////IntRect
  //template<class Archive>
  //void load(Archive &ar, SINTRECT &Irect)
  //{
  //  ar(Irect.left, Irect.top, Irect.width, Irect.height);
  //}

  //template<class Archive>
  //void save(Archive &ar, const SINTRECT &Irect)
  //{
  //  ar(Irect.left, Irect.top, Irect.width, Irect.height);
  //}

  ////Vector2f
  //template<class Archive>
  //void load(Archive &ar, SVector2F &V)
  //{
  //  ar(V.x, V.y);
  //}

  //template<class Archive>
  //void save(Archive &ar, const SVector2F &V)
  //{
  //  ar(V.x, V.y);
  //}

  ////sf::Vector2u
  //template<class Archive>
  //void load(Archive &ar, SVector2U &V)
  //{
  //  ar(V.x, V.y);
  //}

  //template<class Archive>
  //void load(Archive &ar, const SVector2U &V)
  //{
  //  ar(V.x, V.y);
  //}

  ////sf::Color
  //template<class Archive>
  //void load(Archive &ar, sf::Color &Color)
  //{
  //  ar(Color.r, Color.g, Color.b, Colo.a);
  //}

  //template<class Archive>
  //void save(Archive &ar, const sf::Color &Color)
  //{
  //  ar(Color.r, Color.g, Color.b, Colo.a);
  //}
  //template<>
  //void load(cereal::BinaryInputArchive &ar, SFLOATRECT &Rect)
  //{
  //  ar(Rect.left, Rect.top, Rect.width, Rect.height);
  //}

  //template<>
  //void save(cereal::BinaryOutputArchive &ar, const SFLOATRECT &Rect)
  //{
  //  ar(Rect.left, Rect.top, Rect.width, Rect.height);
  //}
  
} // namespace SFEngine
