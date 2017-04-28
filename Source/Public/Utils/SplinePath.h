#ifndef SFEngine_SplinePath_H
#define SFEngine_SplinePath_H

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

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <SelbaWard\Spline.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        SplinePath                                    */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/04/27                                  */
/************************************************************************/

namespace SFEngine
{

  class SplinePath
  {
  public:
    SplinePath(UINT32 PathStyle = SplinePath::Default);
    ~SplinePath() = default;

    static enum Style : UINT32
    {
      Default = 1,
      Connected = 2,
      Unconnected = 3,
      Linear = 4,
      Cubic = 5,
      Smooth = 6,
      Jagged = 7
    };

    void MakeCirclularPath(const SVector2F &Center, SFLOAT Radius, UINT32 NumPts = 100);
    void SetThickness(SFLOAT Thickness);
    UINT32 GetNumInterpolantPoints() const;
    void AddVertexAtEnd(const SVector2F &Position);
    void AddVertices(const STDVector<SVector2F> &Vertices);
    void MoveVertex(UINT32 Index, const SVector2F &NewPosition);
    void MakeSmooth();
    void SetInterpolationSteps(UINT32 NumSteps);
    void RemoveVertex(UINT32 Index);
    void SetPrimitiveType(sf::PrimitiveType PType);
    void SetColor(sf::Color Color);
    SVector2F operator[](const UINT32 &Index);
    void Update();
    void Render(SharedRTexture Target);

    SVector2F GetNextPathPoint();

  protected:
    int m_CurrentPathPoint = 0;
    ::sw::Spline m_Spline;
    sf::PrimitiveType m_SplinePrimitiveType;
    UINT32 m_Style;

  };
}

#endif // SFEngine_SplinePath_H 
