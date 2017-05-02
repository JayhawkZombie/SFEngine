#ifndef SFEngine_BasicLevelState_H
#define SFEngine_BasicLevelState_H

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
#include "Camera\Camera2D.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                        BasicLevelState                               */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/01                                  */
/************************************************************************/

namespace SFEngine
{

  class State
  {
  public:
    State() = default;
    virtual ~State() = default;

    virtual void Interpolate(SFLOAT Alpha) = 0;
    virtual State& operator=(const State &Other) = 0;
    virtual State& Save() = 0;
    virtual void Restore(State&) = 0;
  };
  

  class BasicLevelState
  {
  public:
    BasicLevelState() = default;
    BasicLevelState(SFLOATRECT &Rect, SVector2U V, Camera2D Cam);
    BasicLevelState(const BasicLevelState &Other) = default;
    virtual ~BasicLevelState() = default;

    virtual void Interpolate(SFLOAT Alpha);
    virtual BasicLevelState& operator=(const BasicLevelState &Other);
    virtual BasicLevelState& Save();
    virtual void Restore(BasicLevelState &);

    friend BasicLevelState& operator *(const BasicLevelState &State, const float &F);
    friend BasicLevelState& operator *(const float &F, BasicLevelState &State);
    friend BasicLevelState& operator +(const BasicLevelState &State, const BasicLevelState &State2);
  private:
    SFLOATRECT  m_CurrentView;
    SVector2U   m_Size;
    Camera2D    m_ViewCamera;
  };

}

#endif // SFEngine_BasicLevelState_H 
