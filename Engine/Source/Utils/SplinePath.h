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

#include "ThirdParty\SelbaWard.hpp"
#include "BasicIncludes.h"
#include <SFML\Graphics.hpp>

class SplinePath
{
public:
  SplinePath(UINT32 PathStyle = SplinePath::Default);
  ~SplinePath() = default;

  enum Style : UINT32
  {
    Default      = 1,
    Connected    = 2,
    Unconnected  = 3,
    Linear       = 4,
    Cubic        = 5,
    Smooth       = 6,
    Jagged       = 7
  };

  void MakeCirclularPath(const sf::Vector2f &Center, SFLOAT Radius, UINT32 NumPts = 100);
  void SetThickness(SFLOAT Thickness);
  UINT32 GetNumInterpolantPoints() const;
  void AddVertexAtEnd(const sf::Vector2f &Position);
  void AddVertices(const std::vector<sf::Vector2f> &Vertices);
  void MoveVertex(UINT32 Index, const sf::Vector2f &NewPosition);
  void MakeSmooth();
  void SetInterpolationSteps(UINT32 NumSteps);
  void RemoveVertex(UINT32 Index);
  void SetPrimitiveType(sf::PrimitiveType PType);
  void SetColor(sf::Color Color);
  sf::Vector2f operator[](const UINT32 &Index);
  void Update();
  void Render(std::shared_ptr<sf::RenderTarget> Target);

  sf::Vector2f GetNextPathPoint();

protected:
  std::size_t m_CurrentPathPoint = 0;
  ::sw::Spline m_Spline;
  sf::PrimitiveType m_SplinePrimitiveType;
  UINT32 m_Style;

};
