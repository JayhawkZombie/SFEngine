#ifndef SFEngine_Phaser_H
#define SFEngine_Phaser_H

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

/************************************************************************/
/*                         Internal  Headers                            */
/************************************************************************/
#include "BasicIncludes.h"
#include "Engine\BaseEngineInterface.h"

/************************************************************************/
/*                       Dependency  Headers                            */
/************************************************************************/
#include <Kairos\all.hpp>

/************************************************************************/
/*                     Standard  Library  Headers                       */
/************************************************************************/

/************************************************************************/
/*                             Phaser                                   */
/************************************************************************/
/*                                                                      */
/*                       File Description                               */
/************************************************************************/

/************************************************************************/
/* Last Edit: Kurt Slagle - 2017/05/02                                  */
/************************************************************************/

namespace SFEngine
{

  /************************************************************************/
  /* Phaser - applies effects to objects                                  */
  /*   Yes, it is supposed to be that general and non-specific            */
  /************************************************************************/

  class GameObject;

  class Phaser
  {
  public:
    Phaser() = default;
    virtual ~Phaser() = default;
    
    virtual void Update(SFLOAT Dt) = 0;
    virtual void Start(SFLOAT Duration) = 0;
    virtual void Restart(SFLOAT Duration) = 0;
    virtual void SetStartCallback(std::function<void(void)> Ftn);
    virtual void SetFinishedCallback(std::function<void(void)> Ftn);
    virtual void SetObjectPtr(GameObject *Ptr);
    virtual void SetUpdateStep(SFLOAT Delta);

  protected:
    GameObject      *m_ObjectPtr;
    kairos::Timestep m_UpdateStep;
    kairos::Duration m_EffectDuration;
    kairos::Duration m_TotalEffectDuration;
    std::function<void(void)> m_StartCallBack;
    std::function<void(void)> m_EndCallBack;
    bool m_IsDone = false;
    bool m_IsAffecting = false;
  };

}

#endif // SFEngine_Phaser_H 
