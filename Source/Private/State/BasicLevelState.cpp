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
#include "State\BasicLevelState.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <Plinth\all.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        BasicLevelState                               */
/************************************************************************/
/*                                                                      */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/01                                  */
/************************************************************************/

namespace SFEngine
{

  

  BasicLevelState::BasicLevelState(SFLOATRECT & Rect, SVector2U V, Camera2D Cam)
    : m_CurrentView(Rect), m_Size(V), m_ViewCamera(Cam)
  {
  }

  void BasicLevelState::Interpolate(SFLOAT Alpha)
  {
    
  }

  BasicLevelState & BasicLevelState::operator=(const BasicLevelState & Other)
  {
    // TODO: insert return statement here
    m_CurrentView = Other.m_CurrentView;
    m_Size = Other.m_Size;
    m_ViewCamera = Other.m_ViewCamera;
    return *this;
  }

  BasicLevelState & BasicLevelState::Save()
  {
    // TODO: insert return statement here
    return *this;
  }

  void BasicLevelState::Restore(BasicLevelState &Copy)
  {
    m_CurrentView = Copy.m_CurrentView;
    m_Size = Copy.m_Size;
    m_ViewCamera = Copy.m_ViewCamera;
  }

  BasicLevelState& operator*(const BasicLevelState & State, const float & F)
  {
    SFLOATRECT Rect = State.m_CurrentView;
    Rect.height *= F; Rect.left *= F; Rect.top *= F; Rect.width *= F;
    SVector2U S = State.m_Size;
    S.x *= F; S.y *= F;
    return BasicLevelState(Rect, S, State.m_ViewCamera);
  }

  BasicLevelState& operator*(const float & F, BasicLevelState & State)
  {
    return (State * F);
  }

  BasicLevelState& operator+(const BasicLevelState &State, const BasicLevelState &State2)
  {
    SFLOATRECT Rect = State.m_CurrentView;
    SFLOATRECT Rect2 = State2.m_CurrentView;
    Rect.left += Rect2.left; Rect.top += Rect2.top; Rect.width += Rect2.width; Rect.height += Rect2.height;
    SVector2U V1 = State.m_Size;
    SVector2U V2 = State2.m_Size;
    V1 += V2;
    return BasicLevelState(Rect, V1, State.m_ViewCamera);
  }

} // namespace SFEngine
